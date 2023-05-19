#pragma once
#include "Vector.hpp"

template <class T>
class PriorityQueue {

private:

	struct ValuePriorityPair {

		T value;
		unsigned int priority;

	};

	unsigned int maxPriorities;
	size_t size;
	Vector<ValuePriorityPair> queue;

public:

	explicit PriorityQueue(unsigned int k);

	void push(const T& value, unsigned int priority);
	void push(T&& value, unsigned int priority);
	void pop();
	const T& peek() const;
	bool empty() const;
};

template <class T>
PriorityQueue<T>::PriorityQueue(unsigned int k): maxPriorities(k), size(0) {
	queue.resize(maxPriorities);
}

template <class T>
void PriorityQueue<T>::push(const T& value, unsigned int priority) {

	if (priority >= maxPriorities) {
		throw std::length_error("Error! Invalid priority level.");
	}

	ValuePriorityPair pair;
	pair.value = value;
	pair.priority = priority;

	queue.pushBack(pair);
	size++;
}

template <class T>
void PriorityQueue<T>::push(T&& value, unsigned int priority) {

	if (priority >= maxPriorities) {
		throw std::length_error("Error! Invalid priority level.");
	}

	ValuePriorityPair pair;
	pair.value = std::move(value);
	pair.priority = priority;

	queue.pushBack(std::move(pair));
	size++;
}

template <class T>
bool PriorityQueue<T>::empty() const {
	return size == 0;
}

template <class T>
void PriorityQueue<T>::pop() {

	if (empty()) {
		throw std::logic_error("Error! Queue is already empty!");
	}

	unsigned int maxPriority = queue[0].priority;
	size_t maxIndex = 0;

	for (size_t i = 1; i < size; i++) {
		if (queue[i].priority > maxPriority) {
			maxPriority = queue[i].priority;
			maxIndex = i;
		}
	}
	queue.popAt(maxIndex);
	size--;
}

template <class T>
const T& PriorityQueue<T>::peek() const {

	if (empty()) {
		throw std::logic_error("Error! Queue is already empty!");
	}

	unsigned int maxPriority = queue[0].priority;
	size_t maxIndex = 0;

	for (size_t i = 1; i < size; i++) {
		if (queue[i].priority > maxPriority) {
			maxPriority = queue[i].priority;
			maxIndex = i;
		}
	}
	return queue[maxIndex].value;
}