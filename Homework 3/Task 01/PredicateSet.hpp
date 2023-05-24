#pragma once
#include "SetBase.hpp"


template <class T>
class PredicateSet : public SetBase<T> {

private:

	bool (*predicate)(const Vector<T>&, const T&);

public:

	PredicateSet(bool (*function)(const Vector<T>&numbers, const T& el));

	void insert(const Vector<T>& numbers, const T& value) override;
	bool accepts(const Vector<T>& numbers, const T& value) const;
	void printAllElements() const override;
};

template <class T>
PredicateSet<T>::PredicateSet(bool (*function)(const Vector<T>& numbers, const T&)) : SetBase<T>(), predicate(function) {}

template <class T>
bool PredicateSet<T>::accepts(const Vector<T>& numbers, const T& value) const {
	return predicate(numbers, value);
}

template <class T>
void PredicateSet<T>::insert(const Vector<T>& numbers, const T& value) {

	if (!accepts(numbers, value)) {

		throw std::exception("Error! The item you are trying to add doesn't match the criteria for this set.");
	}

	SetBase<T>::insert(numbers, value);
}

template <class T>
void PredicateSet<T>::printAllElements() const {

	std::cout << "PredicateSet: ";
	for (size_t i = 0; i < this->elementsAmount; i++) {
		std::cout << this->data[i] << " ";
	}
	std::cout << std::endl;
}