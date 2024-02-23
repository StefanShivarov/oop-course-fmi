#pragma once

const unsigned short MAX_SYMBOLS_AMOUNT = 16;

class StringPiece
{
public:
	char data[MAX_SYMBOLS_AMOUNT];
	//char* start; // points to first symbol
	//char* end; // points to last symbol
	unsigned short startIndex;
	unsigned short endIndex;
	unsigned short currentLength;

public:
	//StringPiece();
	StringPiece(const char* data = "");

	const char* getData();
	void setData(const char* data);

	const unsigned short length() const;
	void removeLastKSymbols(unsigned short k);
	void replaceAt(unsigned short index, char replacement);

	StringPiece& operator<<(const char* str);
	StringPiece& operator<<(unsigned int number);
	friend StringPiece& operator>>(const char* str, StringPiece& strPiece);
	friend StringPiece& operator>>(unsigned int number, StringPiece& strPiece);
};

StringPiece& operator>>(const char* str, StringPiece& strPiece);
StringPiece& operator>>(unsigned int number, StringPiece& strPiece);