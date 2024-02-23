#pragma once
#include <iostream>

template <typename T>
class PairOfOptionals {

	T* first;
	T* second;

public:

	PairOfOptionals();
	PairOfOptionals(const T& first, const T& second);

	const T& getFirst() const;
	const T& getSecond() const;

	void setFirst(const T& obj);
	void setSecond(const T& obj);

	void clearFirst();
	void clearSecond();

	bool firstHasValue() const;
	bool secondHasValue() const;

	bool operator==(const PairOfOptionals<T>& other) const;
	bool operator!=(const PairOfOptionals<T>& other) const;

};

template <typename T>
PairOfOptionals<T>::PairOfOptionals(): first(nullptr), second(nullptr) {}

template <typename T>
PairOfOptionals<T>::PairOfOptionals(const T& first, const T& second) : first(nullptr), second(nullptr) {

	setFirst(first);
	setSecond(second);
}

template <typename T>
void PairOfOptionals<T>::setFirst(const T& obj) {

	delete first;
	first = new T(obj); // requires copy constructor
}

template <typename T>
void PairOfOptionals<T>::setSecond(const T& obj) {

	delete second;
	second = new T(obj); // requires copy constructor
}

template <typename T>
bool PairOfOptionals<T>::firstHasValue() const {

	return first != nullptr;
}

template <typename T>
bool PairOfOptionals<T>::secondHasValue() const {

	return second != nullptr;
}

template <typename T>
const T& PairOfOptionals<T>::getFirst() const {

	if (!firstHasValue()) {
		throw std::logic_error("First optional has no value!");
	}
	return *first;
}

template <typename T>
const T& PairOfOptionals<T>::getSecond() const {

	if (!secondHasValue()) {
		throw std::logic_error("Second optional has no value!");
	}
	return *second;
}

template <typename T>
void PairOfOptionals<T>::clearFirst() {

	delete first;
	first = nullptr;
}

template <typename T>
void PairOfOptionals<T>::clearSecond() {

	delete second;
	second = nullptr;
}

template <typename T>
bool PairOfOptionals<T>::operator==(const PairOfOptionals<T>& other) const {

	return *(this->first) == *(other.first) && *(this->second) == *(other.second);
}

template <typename T>
bool PairOfOptionals<T>::operator!=(const PairOfOptionals<T>& other) const {

	return !this->operator==(other);
}