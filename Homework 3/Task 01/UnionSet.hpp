#pragma once
#include "SetBase.hpp"

template <class T>
class UnionSet : public SetBase<T> {

public:

	UnionSet();
	UnionSet(const Vector<SetBase<T>*>& sets);

	void printAllElements() const override;
};

template <class T>
UnionSet<T>::UnionSet(): SetBase<T>() {}

template <class T>
UnionSet<T>::UnionSet(const Vector<SetBase<T>*>& sets) {

	const size_t setsAmount = sets.getSize();
	for (size_t i = 0; i < setsAmount; i++) {
		this->mergeWith(*(sets[i]));
	}
}

template <class T>
void UnionSet<T>::printAllElements() const {
	std::cout << "UnionSet: ";
	for (size_t i = 0; i < this->elementsAmount; i++) {
		std::cout << this->data[i] << " ";
	}
	std::cout << std::endl;
}