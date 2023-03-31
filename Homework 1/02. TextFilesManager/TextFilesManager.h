#pragma once
#include "File.h"
#include "SortOptions.h"
class TextFilesManager
{
private:

	File* files = nullptr;
	size_t filesAmount = 0;
	size_t maximumFilesAmount = 0;

	void swapFiles(File& f1, File& f2);

	void copyFrom(const TextFilesManager& other);
	void free();

public:

	TextFilesManager(size_t size);

	TextFilesManager() = default;
	TextFilesManager(const TextFilesManager& other);
	TextFilesManager& operator=(const TextFilesManager& other);
	~TextFilesManager();

	const File* getFiles() const;

	size_t getFilesAmount() const {
		return filesAmount;
	}

	size_t getMaximumFilesAmount() const {
		return this->maximumFilesAmount;
	}

	void setFilesAmount(size_t filesAmount) {
		this->filesAmount = filesAmount;
	}

	size_t getFileIndexByName(const char* fileName) const;

	void addFile(const char* fileName, unsigned int creationTimeHours, unsigned int creationTimeMinutes,
		unsigned int creationTimeSeconds, unsigned int creationTimeDay, unsigned int creationTimeMonth,
		unsigned int creationTimeYear, const char* accessRights);

	void editFile(const char* fileName, const char* content, unsigned int hours, unsigned int minutes,
		unsigned int seconds, unsigned int day, unsigned int month,
		unsigned int year, char role);

	void addInFile(const char* fileName, const char* content, unsigned int hours, unsigned int minutes, 
		unsigned int seconds, unsigned int day, unsigned int month,unsigned int year, char role);

	void changeRights(const char* fileName, char role, char right);

	void deleteFile(const char* fileName);
	void printFile(const char* fileName, char role) const;
	void printFileInfo(const char* fileName, char role) const;
	void print() const;

	void sort(SortOptions sortingCriteria);
};

