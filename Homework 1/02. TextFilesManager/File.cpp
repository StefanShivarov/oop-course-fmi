#include "File.h"
#include<iostream>
#pragma warning(disable : 4996)

File::File(const char* name, const char* content, unsigned int size,
	const DateTime& creationTime, const DateTime& lastModificationTime,
	const char* accessRights):creationTime(creationTime), lastModificationTime(lastModificationTime){

	setName(name);
	setContent(content);
	setSize(size);
	setAccessRights(accessRights);
}

File::File(const char* name, const char* content, unsigned int size, unsigned int creationTimeDay,
	unsigned int creationTimeMonth, unsigned int creationTimeYear, unsigned int creationTimeHours,
	unsigned int creationTimeMinutes, unsigned int creationTimeSeconds, unsigned int modificationTimeDay,
	unsigned int modificationTimeMonth, unsigned int modificationTimeYear, unsigned int modificationTimeHours,
	unsigned int modificationTimeMinutes, unsigned int modificationTimeSeconds, const char* accessRights)
	: creationTime(creationTimeDay, creationTimeMonth, creationTimeYear, creationTimeHours, creationTimeMinutes, creationTimeSeconds),
	lastModificationTime(modificationTimeDay, modificationTimeMonth, modificationTimeYear, modificationTimeHours, 
		modificationTimeMinutes, modificationTimeSeconds)
{
	setName(name);
	setContent(content);
	setSize(size);
	setAccessRights(accessRights);
}

File::File() : File("", "", 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, "") {}

const char* File::getName() const {
	return name;
}

const char* File::getContent() const {
	return content;
}

size_t File::getSize() const {
	return size;
}

const DateTime& File::getCreationTime() const {
	return creationTime;
}

const DateTime& File::getLastModificationTime() const {
	return lastModificationTime;
}

const char* File::getAccessRights() const {
	return accessRights;
}

void File::setName(const char* name) {
	if (strlen(name) > 20) {
		return;
	}
	else {
		strcpy(this->name, name);
	}
}

void File::setContent(const char* content) {
	if (strlen(content) > 512) {
		return;
	}
	else {
		strcpy(this->content, content);
	}
}

void File::setSize(size_t size) {
	this->size = size;
}

void File::setCreationTime(const DateTime& creationTime) {
	this->creationTime = creationTime;
}

void File::setLastModificationTime(const DateTime& lastModificationTime) {
	this->lastModificationTime = lastModificationTime;
}

void File::setAccessRights(const char* accessRights) {
	if (strlen(accessRights) != 9) {
		return;
	}
	else {
		strcpy(this->accessRights, accessRights);
	}
}

void File::addMoreContent(const char* contentToAdd) {

	size_t startingLength = strlen(this->content);
	size_t lengthAfterAppend = startingLength + strlen(contentToAdd);

	if (lengthAfterAppend > CONTENT_MAX_LENGTH) {
		std::cout << "Error! Invalid content length!" << std::endl;
		return;
	}

	for (size_t i = 0; i < lengthAfterAppend; i++) {

		this->content[i + startingLength] = contentToAdd[i];
	}
	this->content[lengthAfterAppend] = '\0';
}

bool File::canBeRead(char role) {

	switch (role) {

		case 'u':
			return this->accessRights[0] == 'r';

		case 'g':
			return this->accessRights[3] == 'r';

		case 'o':
			return this->accessRights[6] == 'r';

		default:
			std::cout << "Error! Invalid role!" << std::endl;
	}
}

bool File::canBeWrittenTo(char role) {

	switch (role) {

	case 'u':
		return this->accessRights[1] == 'w';

	case 'g':
		return this->accessRights[4] == 'w';

	case 'o':
		return this->accessRights[7] == 'w';

	default:
		std::cout << "Error! Invalid role!" << std::endl;
	}
}

bool File::canBeExecuted(char role) {
	switch (role) {

	case 'u':
		return this->accessRights[2] == 'x';

	case 'g':
		return this->accessRights[5] == 'x';

	case 'o':
		return this->accessRights[8] == 'x';

	default:
		std::cout << "Error! Invalid role!" << std::endl;
	}
}

void File::toggleRightSymbol(size_t index, char rightSymbol) {
	this->accessRights[index] == rightSymbol ? this->accessRights[index] = '-' : this->accessRights[index] = rightSymbol;
}

void File::changeRights(char role, char rightSymbol) {
	switch (role) {

		case 'u':
			if (rightSymbol == 'r') {
				toggleRightSymbol(0, rightSymbol);
			}
			else if (rightSymbol == 'w') {
				toggleRightSymbol(1, rightSymbol);
			}
			else if (rightSymbol == 'x') {
				toggleRightSymbol(2, rightSymbol);
			}
			break;
		case 'g':
			if (rightSymbol == 'r') {
				toggleRightSymbol(3, rightSymbol);
			}
			else if (rightSymbol == 'w') {
				toggleRightSymbol(4, rightSymbol);
			}
			else if (rightSymbol == 'x') {
				toggleRightSymbol(5, rightSymbol);
			}
			break;
		case 'o':
			if (rightSymbol == 'r') {
				toggleRightSymbol(6, rightSymbol);
			}
			else if (rightSymbol == 'w') {
				toggleRightSymbol(7, rightSymbol);
			}
			else if (rightSymbol == 'x') {
				toggleRightSymbol(8, rightSymbol);
			}
			break;

		default:
			std::cout << "Error! Invalid role!" << std::endl;
	}
}

void File::print() {

	std::cout << "Name: " << getName() << std::endl
		<< "Size: " << getSize() << std::endl
		<< "Created on: ";
		getCreationTime().print();
		std::cout << "Last modified on: ";
		getLastModificationTime().print();
		std::cout << "Rights: " << getAccessRights() << std::endl;
}

int File::compareTo(const File& otherFile, SortOptions compareCriteria) {
	
	switch (compareCriteria) {

		case SortOptions::name :
			return strcmp(this->name, otherFile.getName());

		case SortOptions::size :
			if (this->size > otherFile.getSize()) {
				return 1;
			}
			else if (this->size > otherFile.getSize()) {
				return -1;
			}
			return 0;

		case SortOptions::creationTime :
			return this->creationTime.compareTo(otherFile.getCreationTime());

		case SortOptions::modificationTime :
			return this->lastModificationTime.compareTo(otherFile.getLastModificationTime());

		default:
			std::cout << "Error! Cannot compare by this criteria!" << std::endl;
	}
}

