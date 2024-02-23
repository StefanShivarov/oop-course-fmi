#include "TextFilesManager.h"
#include "SortOptions.h"
#include <iostream>

//Big 4 implementation is made with some help from Github/Angeld55

void TextFilesManager::copyFrom(const TextFilesManager& other) {
	this->maximumFilesAmount = other.maximumFilesAmount;
	this->filesAmount = other.filesAmount;
	this->files = new File[this->maximumFilesAmount];
	for (size_t i = 0; i < filesAmount; i++) {
		this->files[i] = other.files[i];
	}
}

void TextFilesManager::free() {
	delete [] files;
	files = nullptr;
	filesAmount = 0;
	maximumFilesAmount = 0;
}

TextFilesManager::TextFilesManager(size_t size) {
	files = new File[size];
	this->maximumFilesAmount = size;
}

TextFilesManager::TextFilesManager(const TextFilesManager& other) {
	copyFrom(other);
}

TextFilesManager& TextFilesManager::operator=(const TextFilesManager& other) {
	if (this != &other) {

		free();
		copyFrom(other);
	}

	return *this;
}

TextFilesManager::~TextFilesManager() {
	free();
}

const File* TextFilesManager::getFiles() const {
	return files;
}

size_t TextFilesManager::getFileIndexByName(const char* fileName) const {
	for (size_t i = 0; i < maximumFilesAmount; i++) {
		if (strcmp(files[i].getName(), fileName) == 0) {
			return i;
		}
	}

	return -1;
}


void TextFilesManager::addFile(const char* fileName, unsigned int creationTimeHours, unsigned int creationTimeMinutes,
	unsigned int creationTimeSeconds, unsigned int creationTimeDay, unsigned int creationTimeMonth,
	unsigned int creationTimeYear, const char* accessRights) {

	const File& file = File(fileName, "", 0, DateTime(creationTimeDay, creationTimeMonth, creationTimeYear,
		creationTimeHours, creationTimeMinutes, creationTimeSeconds), DateTime(creationTimeDay, creationTimeMonth, creationTimeYear,
			creationTimeHours, creationTimeMinutes, creationTimeSeconds), accessRights);

	if (this->filesAmount == this->maximumFilesAmount) {
		std::cout << "Error! Files limit is already reached!" << std::endl;
		return;
	}
	else {
		this->files[filesAmount] = file;
		setFilesAmount(getFilesAmount() + 1);
	}
}

void TextFilesManager::editFile(const char* fileName, const char* content, unsigned int hours, unsigned int minutes,
	unsigned int seconds, unsigned int day, unsigned int month, unsigned int year, char role) {

	const size_t fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1) {
		std::cout << "Error! No such file was found!" << std::endl;
	}
	else {
		File& fileToEdit = files[fileIndex];
		if (!fileToEdit.canBeWrittenTo(role)) {
			std::cout << "Error! You do not have the rights to edit!" << std::endl;
			return;
		}
		else {
			fileToEdit.setContent(content);
			fileToEdit.setLastModificationTime(DateTime(day, month, year, hours, minutes, seconds));
			fileToEdit.setSize(strlen(fileToEdit.getContent()));
		}
	}
	
}

void TextFilesManager::addInFile(const char* fileName, const char* content, unsigned int hours, unsigned int minutes,
	unsigned int seconds, unsigned int day, unsigned int month, unsigned int year, char role) {

	const size_t fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1) {
		std::cout << "Error! No such file was found!" << std::endl;
		return;
	}
	File& fileToEdit = files[fileIndex];
	if (!fileToEdit.canBeWrittenTo(role)) {
		std::cout << "Error! You do not have the rights to edit!" << std::endl;
		return;
	}
	else {
		fileToEdit.addMoreContent(content);
		fileToEdit.setLastModificationTime(DateTime(day, month, year, hours, minutes, seconds));
		fileToEdit.setSize(strlen(fileToEdit.getContent()));
	}

}

void TextFilesManager::changeRights(const char* fileName, char role, char rightSymbol) {

	const size_t fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1) {
		std::cout << "Error! No such file was found!" << std::endl;
		return;
	}
	files[fileIndex].changeRights(role, rightSymbol);
}


void TextFilesManager::deleteFile(const char* fileName) {

	const size_t fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1) {
		std::cout << "Error! No such file was found!" << std::endl;
		return;
	}

	if (fileIndex != filesAmount - 1) {
		for (size_t i = fileIndex; i < filesAmount - 1; i++) {
			files[i] = files[i + 1];
		}
	}
	filesAmount--;
}

void TextFilesManager::printFile(const char* fileName, char role) const {

	const size_t fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1) {
		std::cout << "No such file was found!" << std::endl;
		return;
	}
	if (files[fileIndex].canBeRead(role)) {
		std::cout << files[fileIndex].getContent() << std::endl;
	}
	else {
		std::cout << "Error! You do not have the rights to read!" << std::endl;
	}

}

void TextFilesManager::printFileInfo(const char* fileName, char role) const {

	const size_t fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1) {
		std::cout << "No such file was found!" << std::endl;
		return;
	}

	if (files[fileIndex].canBeRead(role)) {
		files[fileIndex].print();
	}
	else {
		std::cout << "Error! You do not have the rights to read!" << std::endl;
	}
}

void TextFilesManager::print() const {
	for (size_t i = 0; i < filesAmount; i++) {
		std::cout << files[i].getName() << std::endl;
	}
}

void TextFilesManager::sort(SortOptions sortingCriteria) {

	for (size_t i = 0; i < filesAmount - 1; i++) {
		for (size_t j = i + 1; j < filesAmount; j++) {
			if (files[i].compareTo(files[j], sortingCriteria) > 0) {
				swapFiles(files[i], files[j]);
			}
		}
	}
}

void TextFilesManager::swapFiles(File& f1, File& f2) {
	File temp = f1;
	f1 = f2;
	f2 = temp;
}
