#pragma once
#include "SetBase.hpp"

template <class T>
class IntersectionSet : public SetBase<T> { 

public:

	IntersectionSet();
	IntersectionSet(const Vector<SetBase<T>*>& sets);

	void printAllElements() const override;

private:

	void copyItemsFrom(const SetBase<T>& other);
};

template <class T>
IntersectionSet<T>::IntersectionSet(): SetBase<T>() {}


template <class T>
IntersectionSet<T>::IntersectionSet(const Vector<SetBase<T>*>& sets) {

	const size_t setsAmount = sets.getSize();
	copyItemsFrom(*(sets[0]));
	for (size_t i = 1; i < setsAmount; i++) {
		this->intersectWith(*(sets[i]));
	}
}

template <class T>
void IntersectionSet<T>::copyItemsFrom(const SetBase<T>& other) {

	const size_t otherSetSize = other.size();
	for (size_t i = 0; i < otherSetSize; i++) {
		this->insert(other.getAtIndex(i));
	}
}

template <class T>
void IntersectionSet<T>::printAllElements() const {

	std::cout << "IntersectionSet: ";
	for (size_t i = 0; i < this->elementsAmount; i++) {
		std::cout << this->data[i] << " ";
	}
	std::cout << std::endl;
}