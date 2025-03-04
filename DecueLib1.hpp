#include <iostream>

using namespace std;

template <typename T>
class Decue {
protected:
	struct Node {
		T value;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node() = default;
		Node(T nval) : value(nval) {};
		~Node() = default;
	};
	Node* first = nullptr;
	Node* last = nullptr;
	int size = 0;
public:
	Decue() = default;
	Decue(const T&);
	Decue(T*, size_t);
	~Decue();
	void push_front(const T&);
	void push_back(const T&);
	T pop_back();
	T pop_front();
	bool is_empty() const;
	int size_();
	T front();
	T back();
};

template <typename T>
Decue<T>::Decue(const T& nval) : first(new Node(nval)), last(first), size(1) {
}

template <typename T>
Decue<T>::Decue(T* nval, size_t sz) {
	for (size_t i = 0; i < sz; i++) {
		push_front(nval[i]);
	}
}

template <typename T>
Decue<T>::~Decue() {
	while (size > 0) {
		pop_front();
	}
}

template <typename T>
void Decue<T>::push_back(const T& nval) {
	Node* NNode = new Node(nval);
	if (is_empty()) {
		first = last = NNode;
	}
	else {
		NNode->next = last;
		last->prev = NNode;
		last = NNode;
	}
	size++;
}

template <typename T>
void Decue<T>::push_front(const T& nval) {
	Node* NNode = new Node(nval);
	if (is_empty()) {
		first = last = NNode;
	}
	else {
		NNode->prev = first;
		first->next = NNode;
		first = NNode;
	}
	size++;
}

template <typename T>
T Decue<T>::pop_back() {
	if (is_empty()) {
		throw runtime_error("Дек пустой, удаление невозможно");
	}
	T value_ = last->value;
	Node* tmp = last;
	last = last->next;
	if (!last) {
		first = nullptr;
	}
	else {
		last->prev = nullptr;
	}
	delete tmp;
	size--;
	return value_;
}

template <typename T>
T Decue<T>::pop_front() {
	if (is_empty()) {
		throw runtime_error("Дек пустой, удаление невозможно");
	}
	T value_ = first->value;
	Node* tmp = first;
	first = first->prev;
	if (!first) {
		last = nullptr;
	}
	else {
		first->next = nullptr;
	}
	delete tmp;
	size--;
	return value_;
}

template <typename T>
bool Decue<T>::is_empty() const {
	return size == 0;
}

template <typename T>
int Decue<T>::size_() {
	return size;
}

template <typename T>
T Decue<T>::front() {
	if (is_empty()) {
		throw runtime_error("Нельзя вывести элемент т.к. дек пуст");
	}
	return first->value;
}

template <typename T>
T Decue<T>::back() {
	if (is_empty()) {
		throw runtime_error("Нельзя вывести элемент т.к. дек пуст");
	}
	return last->value;
}