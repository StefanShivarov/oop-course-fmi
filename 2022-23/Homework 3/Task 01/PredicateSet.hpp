#pragma once
#include "SetBase.hpp"

//this class looks a bit silly, because of the task requirements. 
//The predicate functions need to have access to outer numbers
//( the vector of numbers) from the text files
// that's why I've made methods for with vector and for without vector .......

template <class T>
class PredicateSet : public SetBase<T> {

private:

	bool (*predicateWithVector)( const T& element, const Vector<T>& numbers) = nullptr;
	bool (*predicateWithoutVector)(const T& element) = nullptr;

public:

	PredicateSet(bool (*function)(const T& el, const Vector<T>& numbers));
	PredicateSet(bool (*function)(const T& el));

	void insert(const T& value, const Vector<T>& numbers);
	void insert(const T& value) override;
	bool accepts(const T& value, const Vector<T>& numbers) const;
	bool accepts(const T& value) const;
	void printAllElements() const override;
};

template <class T>
PredicateSet<T>::PredicateSet(bool (*function)(const T&, const Vector<T>& numbers)) 
	: SetBase<T>(), predicateWithVector(function) {}

template <class T>
PredicateSet<T>::PredicateSet(bool (*function)(const T&)) 
	: SetBase<T>(), predicateWithoutVector(function) {}


template <class T>
bool PredicateSet<T>::accepts(const T& value, const Vector<T>& numbers) const {
	return predicateWithVector(value, numbers);
}

template <class T>
bool PredicateSet<T>::accepts(const T& value) const {
	return predicateWithoutVector(value);
}

template <class T>
void PredicateSet<T>::insert(const T& value, const Vector<T>& numbers) {

	if (!accepts(value, numbers)) {

		throw std::exception("Error! The item you are trying to add doesn't match the criteria for this set.");
	}

	SetBase<T>::insert(value);
}

template <class T>
void PredicateSet<T>::insert(const T& value) {

	if (!accepts(value)) {

		throw std::exception("Error! The item you are trying to add doesn't match the criteria for this set.");
	}

	SetBase<T>::insert(value);
}

template <class T>
void PredicateSet<T>::printAllElements() const {

	std::cout << "PredicateSet: ";
	for (size_t i = 0; i < this->elementsAmount; i++) {
		std::cout << this->data[i] << " ";
	}
	std::cout << std::endl;
}