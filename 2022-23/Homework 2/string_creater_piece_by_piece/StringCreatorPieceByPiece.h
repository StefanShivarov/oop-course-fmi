#pragma once
#include "StringPiece.h"
#include "MyString.h"

class StringCreatorPieceByPiece
{
private:
	StringPiece** pieces;
	size_t capacity;
	size_t piecesAmount;

	void resize();

public:

	StringCreatorPieceByPiece();
	StringCreatorPieceByPiece(size_t initialCapacity);

	StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other);
	StringCreatorPieceByPiece& operator=(const StringCreatorPieceByPiece& other);

	StringCreatorPieceByPiece(StringCreatorPieceByPiece&& other);
	StringCreatorPieceByPiece& operator=(StringCreatorPieceByPiece&& other);

	~StringCreatorPieceByPiece();

	void addPiece(const char* str = "");
	void addPieceAtIndex(size_t index, const char* str = "");
	void swap(size_t firstIndex, size_t secondIndex);
	void remove(size_t  index);
	size_t length() const;
	MyString getString() const;

	const StringPiece& operator[](size_t index) const;
	StringPiece& operator[](size_t index);

private:

	void free();
	void copyFrom(const StringCreatorPieceByPiece& other);
	void move(StringCreatorPieceByPiece&& other);
};

