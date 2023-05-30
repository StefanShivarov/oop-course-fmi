#pragma once
#include <iostream>

template <typename T>
class Vector {

	static const short DEFAULT_RESIZE_COEFFICIENT = 2;
	static const short INITIAL_VECTOR_CAPACITY = 10;

	T* data = nullptr;
	size_t currentSize = 0;
	size_t capacity;

	void checkIndex(size_t index) const;
	void resize(size_t newCapacity);
	void increaseCapacity();
	void shiftElementsFromIndex(size_t index);

public:

	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();
	
	void pushBack(const T& obj);
	void pushBack(T&& obj);
	void pushAt(const T& obj, size_t index);
	void pushAt(T&& obj, size_t index);
	T popBack();
	T popAt(size_t index);

	size_t size() const;
	bool empty() const;
	void clear();
	void swap(Vector<T>& other);
	
	T& operator[](size_t index);
	const T& operator[](size_t index) const;


private:

	void free();
	void copyFrom(const Vector<T>& other);
	void move(Vector<T>&& other);
};

template <typename T>
void Vector<T>::free() {
	currentSize = capacity = 0;
	delete[] data;
	data = nullptr;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	
	this->capacity = other.capacity;
	this->currentSize = other.currentSize;
	this->data = new T[capacity];
	for (size_t i = 0; i < currentSize; i++) {
		this->data[i] = other.data[i];
	}
}

template <typename T>
void Vector<T>::move(Vector<T>&& other) {

	this->capacity = other.capacity;
	this->currentSize = other.currentSize;
	this->data = other.data;
	other.capacity = 0;
	other.currentSize = 0;
	other.data = nullptr;
}

template <typename T>
void Vector<T>::resize(size_t newCapacity) {

	this->capacity = newCapacity;
	T* temp = new T[capacity];

	if (currentSize > capacity) {
		currentSize = capacity;
	}
	
	for (size_t i = 0; i < currentSize; i++) {
		temp[i] = std::move(data[i]);
	}

	delete[] data;
	data = temp;
}

template <typename T>
void Vector<T>::checkIndex(size_t index) const {
	if (index >= currentSize) {
		throw std::out_of_range("Index is out of range!");
	}
}

template <typename T>
void Vector<T>::increaseCapacity() {

	if (currentSize == capacity) {
		resize(capacity*DEFAULT_RESIZE_COEFFICIENT);
	}
}

template <typename T>
void Vector<T>::shiftElementsFromIndex(size_t index) {

	for (size_t i = currentSize; i > index; i--) {
		data[i] = std::move(data[i - 1]);
	}
}

template <typename T>
Vector<T>::Vector(): capacity(INITIAL_VECTOR_CAPACITY) {}

template <typename T>
Vector<T>::Vector(size_t capacity): capacity(capacity) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
	
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) {

	move(std::move(other));
}

template <typename T>
Vector<T>::~Vector() {

	free();
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {

	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template <typename T>
size_t Vector<T>::size() const {

	return currentSize;
}

template <typename T>
bool Vector<T>::empty() const {

	return currentSize == 0;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const{
	return data[index];
}

template <typename T>
void Vector<T>::pushBack(const T& obj) {
	
	increaseCapacity();
	data[currentSize++] = obj;
}

template <typename T>
void Vector<T>::pushBack(T&& obj) {

	increaseCapacity();
	data[currentSize++] = std::move(obj);
}

template <typename T>
void Vector<T>::pushAt(const T& obj, size_t index) {

	checkIndex(index);
	increaseCapacity();
	shiftElementsFromIndex(index);

	data[index] = obj;
	currentSize++;
}

template <typename T>
void Vector<T>::pushAt(T&& obj, size_t index) {

	checkIndex(index);
	increaseCapacity();
	shiftElementsFromIndex(index);

	data[index] = std::move(obj);
	currentSize++;
}

template <typename T>
T Vector<T>::popBack() {

	if (empty()) {
		throw std::length_error("Vector is already empty!");
	}

	return data[--currentSize];
}

template <typename T>
T Vector<T>::popAt(size_t index) {

	checkIndex(index);
	T temp = data[index];
	currentSize--;

	for (size_t i = index; i < currentSize; i++) {
		data[i] = std::move(data[i + 1]);
	}

	return temp;
}

template <typename T>
void Vector<T>::clear() {
	currentSize = 0;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) {

	T* tempData = data;
	data = other.data;
	other.data = tempData;

	size_t tempSize = currentSize;
	this->currentSize = other.currentSize;
	other.currentSize = tempSize;

	size_t tempCapacity = capacity;
	this->capacity = other.capacity;
	other.capacity = tempCapacity;
}