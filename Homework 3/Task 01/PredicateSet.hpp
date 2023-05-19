#pragma once
#include "SetBase.hpp"
#include <iostream>

template <class T>
class PredicateSet : public SetBase<T> {

private:

	bool (*predicate)(const T&);

public:

	PredicateSet(bool (*function)(const T&));

	void insert(const T& value) override;
	bool accepts(const T& value) const;
	void printAllElements() override;
};

template <class T>
PredicateSet<T>::PredicateSet(bool (*function)(const T&)) : SetBase<T>(), predicate(function) {}

template <class T>
bool PredicateSet<T>::accepts(const T& value) const {
	return predicate(value);
}

template <class T>
void PredicateSet<T>::insert(const T& value) {

	if (!accepts(value)) {

		throw std::exception("Error! The item you are trying to add doesn't match the criteria for this set.");
	}

	SetBase<T>::insert(value);
}

template <class T>
void PredicateSet<T>::printAllElements() {

	std::cout << "PredicateSet: ";
	for (size_t i = 0; i < this->elementsAmount; i++) {
		std::cout << this->data[i] << " ";
	}
	std::cout << std::endl;
}