#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>
#pragma warning(disable: 4996)

namespace Constants {
    const int MAX_CELL_VALUE_LENGTH = 50;
    const int MAX_COLS_COUNT = 30;
    const int MAX_ROWS_COUNT = 300;
    const int BUFF_SIZE = 1024;
    const int TAG_NAME_BUFF_LENGTH = 10;
}

namespace Symbols {
    const char HEADER_SYMBOL = '*';
    const char CELL_BOUNDARY_SYMBOL = '|';
    const char SPACE = ' ';
    const char OPENING_TAG_BRACKET = '<';
    const char CLOSING_TAG_BRACKET = '>';
}

namespace Tags {
    const char TABLE[] = "table";
    const char TABLE_ROW[] = "tr";
    const char TABLE_HEADER_CELL[] = "th";
    const char TABLE_DATA_CELL[] = "td";
    const char CLOSE_TABLE[] = "/table";
    const char CLOSE_TABLE_ROW[] = "/tr";
    const char CLOSE_TABLE_HEADER_CELL[] = "/th";
    const char CLOSE_TABLE_DATA_CELL[] = "/td";
}

namespace Commands {
    const char ADD_ROW[] = "addRow";
    const char REMOVE_ROW[] = "remove";
    const char EDIT_ROW[] = "edit";
    const char PRINT_TABLE[] = "print";
    const char SAVE_TO_FILE[] = "save";
    const char QUIT[] = "quit";
}

namespace HelperFunctions {
    bool startsWith(const char* str, char symbol);
    bool endsWith(const char* str, char symbol);
    bool replaceCharacterEntityReferences(char* dest, const char* str);
}

bool HelperFunctions::startsWith(const char* str, char symbol) {
    return str[0] == symbol;
}

bool HelperFunctions::endsWith(const char* str, char symbol) {
    return str[strlen(str) - 1] == symbol;
}

bool HelperFunctions::replaceCharacterEntityReferences(char* dest, const char* str) {
    std::stringstream ss(str);
    std::stringstream result;
    char temp[Constants::BUFF_SIZE];

    while (ss.getline(temp, Constants::BUFF_SIZE, '&')) {
        result << temp;
        if (ss.peek() == '#') {
            ss.get();
            //TODO: check if there is a number after #
            unsigned asciiCode;
            ss >> asciiCode;
            result << (char)asciiCode;
        }
    }

    if (strlen(result.str().c_str()) > Constants::MAX_CELL_VALUE_LENGTH) {
        return false;
    }

    strcpy(dest, result.str().c_str());
    return true;
}

class Cell {
    char value[Constants::MAX_CELL_VALUE_LENGTH + 1]{};
    bool headerCell = false;
    unsigned length = 0;

    char getSurroundingSymbol() const;

public:
    Cell() = default;
    Cell(const char* value);
    Cell(const char* value, bool isHeader);

    const char* getValue() const;
    bool isHeader() const;
    unsigned getLength() const;

    bool setValue(const char* str);
    void setHeader(bool isHeader);
    bool isBlank() const;

    void printFormattedValue(unsigned padding) const;
};

char Cell::getSurroundingSymbol() const {
    return isHeader() ? Symbols::HEADER_SYMBOL : Symbols::SPACE;
}

Cell::Cell(const char* value) : Cell(value, false) {}

Cell::Cell(const char* value, bool isHeader) : headerCell(isHeader) {
    setValue(value);
}

const char* Cell::getValue() const {
    return value;
}

bool Cell::isHeader() const {
    return headerCell;
}

unsigned Cell::getLength() const {
    return length;
}

bool Cell::setValue(const char* str) {
    if (!str || !HelperFunctions::replaceCharacterEntityReferences(value, str)) {
        return false;
    }
    length = strlen(value);
    return true;
}

void Cell::setHeader(bool isHeader) {
    headerCell = isHeader;
}

bool Cell::isBlank() const {
    for (unsigned i = 0; i < Constants::MAX_CELL_VALUE_LENGTH + 1; i++) {
        if (value[i] == '\0') {
            break;
        }

        if (value[i] != ' ') {
            return false;
        }
    }
    return true;
}

void Cell::printFormattedValue(unsigned padding) const {
    char surroundingSymbol = getSurroundingSymbol();
    std::cout << surroundingSymbol << getValue();
    for (unsigned i = 0; i < padding; i++) {
        std::cout << Symbols::SPACE;
    }
    std::cout << surroundingSymbol;
}

class Row {
    Cell cells[Constants::MAX_COLS_COUNT];
    unsigned cellsCount = 0;

public:
    Row() = default;

    const Cell* getCells() const;
    const Cell& getCell(unsigned colNumber) const;
    unsigned getCellsCount() const;

    bool addCell(const Cell& cell, unsigned colNumber);
    void editCell(unsigned colNumber, const char* newValue);
};

const Cell* Row::getCells() const {
    return cells;
}

const Cell& Row::getCell(unsigned colNumber) const {
    if (colNumber > cellsCount || colNumber < 1) {
        return Cell();
    }
    return cells[colNumber - 1];
}

unsigned Row::getCellsCount() const {
    return cellsCount;
}

bool Row::addCell(const Cell& cell, unsigned colNumber) {
    if (cellsCount == Constants::MAX_COLS_COUNT || colNumber > Constants::MAX_COLS_COUNT) {
        return false;
    }
    cells[colNumber - 1] = cell;
    cellsCount = std::max(cellsCount, colNumber);
    return true;
}

void Row::editCell(unsigned colNumber, const char* newValue) {
    cells[colNumber - 1].setValue(newValue);
    cellsCount = std::max(cellsCount, colNumber);
}

class Table {
    Row rows[Constants::MAX_ROWS_COUNT];
    unsigned rowsCount = 0;
    unsigned colsCount = 0;

    bool isValidRowNumber(unsigned rowNumber) const;
    bool isValidColNumber(unsigned colNumber) const;
    void fillMaxColLengths(unsigned* maxColLengths) const;
    void refreshColsCount();

public:
    Table() = default;

    const Row& getRow(unsigned rowNumber) const;
    unsigned getRowsCount() const;
    unsigned getColsCount() const;

    bool addRow(const Row& row, unsigned rowNumber);
    bool removeRow(unsigned rowNumber);
    bool edit(unsigned rowNumber, unsigned colNumber, const char* newValue);

    void print() const;

    void reset();
};

bool Table::isValidRowNumber(unsigned rowNumber) const {
    return rowNumber <= rowsCount && rowNumber >= 1;
}

bool Table::isValidColNumber(unsigned colNumber) const {
    return colNumber <= colsCount && colNumber >= 1;
}

void Table::fillMaxColLengths(unsigned* maxColLengths) const {
    for (unsigned i = 0; i < rowsCount; i++) {
        for (unsigned j = 0; j < colsCount; j++) {
            unsigned cellLength = rows[i].getCell(j + 1).getLength();
            maxColLengths[j] = std::max(maxColLengths[j], cellLength);
        }
    }
}

void Table::refreshColsCount() {
    colsCount = 0;
    for (unsigned i = 0; i < rowsCount; i++) {
        colsCount = std::max(colsCount, rows[i].getCellsCount());
    }
}

const Row& Table::getRow(unsigned rowNumber) const {
    if (rowNumber > rowsCount || rowNumber < 1) {
        return Row();
    }

    return rows[rowNumber - 1];
}

unsigned Table::getRowsCount() const {
    return rowsCount;
}

unsigned Table::getColsCount() const {
    return colsCount;
}

bool Table::addRow(const Row& row, unsigned rowNumber) {
    if (rowNumber > Constants::MAX_ROWS_COUNT || rowsCount == Constants::MAX_ROWS_COUNT) {
        return false;
    }

    if (rowNumber <= rowsCount + 1) {
        for (unsigned i = rowsCount; i >= rowNumber; i--) {
            rows[i] = rows[i - 1];
        }
    }
    else {
        rowNumber = rowsCount + 1;
    }

    rows[rowNumber - 1] = row;
    rowsCount++;
    colsCount = std::max(colsCount, row.getCellsCount());
    return true;
}

bool Table::removeRow(unsigned rowNumber) {
    if (!isValidRowNumber(rowNumber)) {
        return false;
    }

    for (unsigned i = rowNumber; i <= rowsCount - 1; i++) {
        rows[i - 1] = rows[i];
    }

    rowsCount--;
    refreshColsCount();
    return true;
}

bool Table::edit(unsigned rowNumber, unsigned colNumber, const char* newValue) {
    if (!newValue || !isValidRowNumber(rowNumber) || !isValidColNumber(colNumber)) {
        return false;
    }

    rows[rowNumber - 1].editCell(colNumber, newValue);
    return true;
}

void Table::print() const {
    unsigned maxColLengths[Constants::MAX_COLS_COUNT]{ 0 };
    fillMaxColLengths(maxColLengths);

    for (unsigned i = 0; i < rowsCount; i++) {
        const Cell* rowCells = rows[i].getCells();

        std::cout << Symbols::CELL_BOUNDARY_SYMBOL;

        for (unsigned j = 0; j < colsCount; j++) {
            unsigned padding = maxColLengths[j] - rowCells[j].getLength();
            rowCells[j].printFormattedValue(padding);
            std::cout << Symbols::CELL_BOUNDARY_SYMBOL;
        }
        std::cout << std::endl;
    }
}

void Table::reset() {
    rowsCount = 0;
    colsCount = 0;
}

class HtmlTableParser {
    void writeHtmlTag(std::ostream& os, const char* tag, unsigned tabsIndentation) const;

public:
    HtmlTableParser() = default;

    Table parseTableFromHtml(std::istream& is);
    void parseTableToHtml(std::ostream& os, const Table& table) const;
};

void HtmlTableParser::writeHtmlTag(std::ostream& os, const char* tag, unsigned tabsIndentation) const {
    for (unsigned i = 0; i < tabsIndentation; i++) {
        os << '\t';
    }
    os << '<' << tag << '>' << '\n';
}

Table HtmlTableParser::parseTableFromHtml(std::istream& is) {
    Table table;

    bool inCell = false;
    bool isHeaderCell = false;
    bool inRow = false;
    bool inTable = false;

    unsigned colNumber = 1;
    unsigned valueIndex = 0;

    char cellValue[Constants::BUFF_SIZE];

    Row parsedRow;

    char nextSymbol;
    while (is.get(nextSymbol)) {
        if (is.eof()) {
            break;
        }

        if (nextSymbol == Symbols::OPENING_TAG_BRACKET) {
            char tagName[Constants::TAG_NAME_BUFF_LENGTH]{ 0 };
            is.getline(tagName, Constants::TAG_NAME_BUFF_LENGTH, Symbols::CLOSING_TAG_BRACKET);
            if (strcmp(tagName, Tags::TABLE) == 0) {
                inTable = true;
                continue;
            }
            else if (!inCell && !inRow && inTable && strcmp(tagName, Tags::CLOSE_TABLE) == 0) {
                inTable = false;
                break;
            }
            else if (inTable && strcmp(tagName, Tags::TABLE_ROW) == 0) {
                inRow = true;
                colNumber = 1;
                continue;
            }
            else if (inRow && inTable && strcmp(tagName, Tags::CLOSE_TABLE_ROW) == 0) {
                inRow = false;
                table.addRow(parsedRow, table.getRowsCount() + 1);
                continue;
            }
            else if (inRow && !inCell && (strcmp(tagName, Tags::TABLE_HEADER_CELL) == 0 || strcmp(tagName, Tags::TABLE_DATA_CELL) == 0)) {
                inCell = true;
                isHeaderCell = strcmp(tagName, Tags::TABLE_HEADER_CELL) == 0;
                valueIndex = 0;
            }
            else if (inRow && inCell && (strcmp(tagName, Tags::CLOSE_TABLE_HEADER_CELL) == 0 || strcmp(tagName, Tags::CLOSE_TABLE_DATA_CELL) == 0)) {
                inCell = false;
                cellValue[valueIndex] = '\0';
                parsedRow.addCell(Cell(cellValue, isHeaderCell), colNumber);
                colNumber++;
                isHeaderCell = false;
                continue;
            }
        }
        else if (inCell) {
            cellValue[valueIndex++] = nextSymbol;
        }
    }
    return table;
}

void HtmlTableParser::parseTableToHtml(std::ostream& os, const Table& table) const {
    writeHtmlTag(os, Tags::TABLE, 0);
    for (unsigned i = 1; i <= table.getRowsCount(); i++) {
        writeHtmlTag(os, Tags::TABLE_ROW, 1);
        Row row = table.getRow(i);
        for (unsigned j = 1; j <= table.getColsCount(); j++) {
            Cell cell = row.getCell(j);
            if (!cell.isBlank()) {
                writeHtmlTag(os, cell.isHeader() ? Tags::TABLE_HEADER_CELL : Tags::TABLE_DATA_CELL, 2);
                os << "\t\t\t" << cell.getValue() << '\n';
                writeHtmlTag(os, cell.isHeader() ? Tags::CLOSE_TABLE_HEADER_CELL : Tags::CLOSE_TABLE_DATA_CELL, 2);
            }
        }
        writeHtmlTag(os, Tags::CLOSE_TABLE_ROW, 1);
    }
    writeHtmlTag(os, Tags::CLOSE_TABLE, 0);
}

void executeAddRowCommand(std::istream& is, Table& table) {
    //the input will be addRow 2 <value1> <value2> ... <valueN>, so that the values can have spaces inside them!
    unsigned rowNumber;
    is >> rowNumber;
    
    char valueBuff[Constants::BUFF_SIZE];
    char nextSymbol;

    Row row;
    while (is.get(nextSymbol) && nextSymbol != '\n') {
        if (nextSymbol == '<') {
            is.getline(valueBuff, Constants::BUFF_SIZE, '>');
            row.addCell(Cell(valueBuff), row.getCellsCount() + 1);
        }
    }

    table.addRow(row, rowNumber);
}

void executeRemoveRowCommand(std::istream& is, Table& table) {
    unsigned rowNumber;
    is >> rowNumber;

    table.removeRow(rowNumber);
}

void executeEditCommand(std::istream& is, Table& table) {
    unsigned rowNumber, colNumber;
    is >> rowNumber >> colNumber;
    
    char newValue[Constants::BUFF_SIZE];
    is.getline(newValue, Constants::BUFF_SIZE);

    table.edit(rowNumber, colNumber, newValue);
}

void executeSaveToFileCommand(std::istream& is, const Table& table, const HtmlTableParser& htmlTableParser) {
    std::cout << "Enter file name to save table to: ";
    char fileName[Constants::BUFF_SIZE];
    std::cin >> fileName;

    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return;
    }

    htmlTableParser.parseTableToHtml(ofs, table);
    ofs.close();
}

void handleCommand(const char* command, Table& table, const HtmlTableParser& htmlTableParser) {
    if (!command) {
        return;
    }

    if (strcmp(command, Commands::ADD_ROW) == 0) {
        executeAddRowCommand(std::cin, table);
    }
    else if (strcmp(command, Commands::REMOVE_ROW) == 0) {
        executeRemoveRowCommand(std::cin, table);
    }
    else if (strcmp(command, Commands::EDIT_ROW) == 0) {
        executeEditCommand(std::cin, table);
    }
    else if (strcmp(command, Commands::PRINT_TABLE) == 0) {
        table.print();
    }
    else if (strcmp(command, Commands::SAVE_TO_FILE) == 0) {
        executeSaveToFileCommand(std::cin, table, htmlTableParser);
    }
}

int main() {
    std::cout << "Enter a file name to parse table from: ";
    char input[Constants::BUFF_SIZE];
    std::cin >> input;

    std::ifstream ifs(input);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << input << '!';
        return -1;
    }

    HtmlTableParser parser;
    Table parsedTable = parser.parseTableFromHtml(ifs);

    while (true) {
        std::cin >> input;

        if (strcmp(input, Commands::QUIT) == 0) {
            break;
        }
        else {
            handleCommand(input, parsedTable, parser);
        }
    }
    return 0;
}
