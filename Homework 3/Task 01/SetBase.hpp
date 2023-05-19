#pragma once
#include "Vector.hpp"

template <class T>
class SetBase {

protected:

	Vector<T> data;
	size_t elementsAmount;

public:

	SetBase();
	virtual ~SetBase();

	const T& getAtIndex(size_t index) const;
	bool contains(const T& value) const;
	size_t size() const;
	virtual void insert(const T& value);
	void erase(const T& value);
	virtual void printAllElements() const = 0;

	void mergeWith(const SetBase<T>& other);
	void intersectWith(const SetBase<T>& other);

};

template <class T>
SetBase<T>::SetBase() : elementsAmount(0) {}

template <class T>
SetBase<T>::~SetBase() {}

template <class T>
size_t SetBase<T>::size() const {
	return elementsAmount;
}

template <class T>
const T& SetBase<T>::getAtIndex(size_t index) const {
	if (index >= elementsAmount) {
		throw std::length_error("Error! Index out of bounds!");
	}
	return this->data[index];
}

template <class T>
bool SetBase<T>::contains(const T& value) const {
	for (size_t i = 0; i < elementsAmount; i++) {
		if (data[i] == value) {
			return true;
		}
	}
	return false;
}

template <class T>
void SetBase<T>::insert(const T& value) {

	if (contains(value)) {
		return;
	}
	data.pushBack(value);
	elementsAmount++;
}

template <class T>
void SetBase<T>::erase(const T& value) {
	for (size_t i = 0; i < elementsAmount; i++) {
		if (data[i] == value) {
			data.popAt(i);
			elementsAmount--;
		}
	}
}

template <class T>
void SetBase<T>::mergeWith(const SetBase<T>& other) {
	//const size_t otherSetSize = other.size();
	for (size_t i = 0; i < other.elementsAmount; i++) {
		insert(other.data[i]);
	}
}

template <class T>
void SetBase<T>::intersectWith(const SetBase<T>& other) {

	for (size_t i = 0; i < this->elementsAmount; i++) {
		if (!other.contains(this->data[i])) {
			erase(this->data[i]);
		}
	}
}
