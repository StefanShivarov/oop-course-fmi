#pragma once
#include "Vector.hpp"

template <class T>
class SetBase {

private:

	Vector<T> data;
	size_t elementsAmount;

public:

	SetBase();
	virtual ~SetBase();

	bool contains(const T& value) const;
	size_t size() const;
	void insert(const T& value);
	void erase(const T& value);
	virtual void printAllElements() = 0;
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