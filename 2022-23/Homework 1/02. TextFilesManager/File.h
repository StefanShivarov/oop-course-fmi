#pragma once
#include "DateTime.h"
#include "SortOptions.h"

const size_t CONTENT_MAX_LENGTH = 513;

class File
{

private:
	char name[65];
	char content[CONTENT_MAX_LENGTH];
	size_t size;
	DateTime creationTime;
	DateTime lastModificationTime;
	char accessRights[10];

	void toggleRightSymbol(size_t index, char rightSymbol);

public:

	File();
	File(const char* name, const char* content, unsigned int size, const DateTime& creationTime,
		const DateTime& lastModificationTime, const char* accessRights);

	File(const char* name, const char* content, unsigned int size, unsigned int creationTimeDay,
		unsigned int creationTimeMonth, unsigned int creationTimeYear, unsigned int creationTimeHours,
		unsigned int creationTimeMinutes, unsigned int creationTimeSeconds, unsigned int modificationTimeDay,
		unsigned int modificationTimeMonth, unsigned int modificationTimeYear, unsigned int modificationTimeHours,
		unsigned int modificationTimeMinutes, unsigned int modificationTimeSeconds, const char* accessRights);

	const char* getName() const;
	const char* getContent() const;
	size_t getSize() const;
	const DateTime& getCreationTime() const;
	const DateTime& getLastModificationTime() const;
	const char* getAccessRights() const;

	void setName(const char* name);
	void setContent(const char* content);
	void setSize(size_t size);
	void setCreationTime(const DateTime& creationTime);
	void setLastModificationTime(const DateTime& lastModificationTime);
	void setAccessRights(const char* accessRights);

	void addMoreContent(const char* contentToAdd);

	void changeRights(char role, char right);
	bool canBeRead(char role);
	bool canBeWrittenTo(char role);
	bool canBeExecuted(char role);

	void print();

	int compareTo(const File& file, SortOptions compareCriteria);

};

