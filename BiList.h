#pragma once
#include "BiNode.h"
#include <vector>

template <typename T>
class BiList {
private:
	BiNode<T>* front; // вказівник на початок списку
public:
	BiList();
	~BiList();

	void clear(); // очищення списку
	BiNode<T>* get_back(); // отримання останнього елемента
	BiNode<T>* get_front(); // отримання першого елемента
	void push_back(T x); // додавання елемента в кінець
	void push_front(T x); // додавання елемента на початок
	void insert(T x, BiNode<T>* node); // вставка перед заданим вузлом
	void insert(BiNode<T>* node, T x); // вставка після заданого вузла
	void remove(BiNode<T>* node); // видалення вузла
	void forward_view(); // перегляд списку зліва направо
	void reverse_view(); // перегляд списку справа наліво
	BiNode<T>* find(T key); // пошук вузла за значенням
	void slice_in(BiNode<T>* node, int index); // вставка іншого списку після індексу
	void slice_out(BiNode<T>* node, int index1, int index2); // копіювання підсписку з поточного у кінець іншого списку
	void swap(BiNode<T>* n1, BiNode<T>* n2); // поміняти місцями два вузли
	void sort(); // сортування методом прямого вибору
};

template<typename T>
inline BiList<T>::BiList()
{
	front = nullptr; // початково список порожній
}

template<typename T>
inline BiList<T>::~BiList()
{
	clear(); // очищення пам'яті при знищенні об'єкта
}

template<typename T>
inline void BiList<T>::clear()
{
	while (front) {
		BiNode<T>* temp = front->next;
		delete front;
		front = temp;
	}
}

template<typename T>
inline BiNode<T>* BiList<T>::get_back()
{
	if (!front) return nullptr;

	BiNode<T>* temp = front;
	while (temp->next) {
		temp = temp->next;
	}

	return temp; // останній елемент списку
}

// отримання першого елемента
template<typename T>
inline BiNode<T>* BiList<T>::get_front()
{
	// якщо першого вузла не існує повернеться nullptr, інакше показчик на перший вузел
	return front;
}

template<typename T>
inline void BiList<T>::push_back(T x)
{
	if (!front) {
		front = new BiNode<T>(x);
		return;
	}
	else {
		BiNode<T>* tail = get_back();
		BiNode<T>* newNode = new BiNode<T>(x);
		tail->next = newNode;
		newNode->prev = tail;
	}
}

template<typename T>
inline void BiList<T>::push_front(T x)
{
	if (!front) {
		front = new BiNode<T>(x);
		return;
	}

	// створення нового вузла перед початком
	front->prev = new BiNode<T>(x);
	front->prev->next = front;
	front = front->prev;
}

// вставка перед заданим вузлом
template<typename T>
inline void BiList<T>::insert(T x, BiNode<T>* node)
{
	if (!node) return;

	if (node == front) {
		this->push_front(x);
		return;
	}

	// вставка нового вузла 
	BiNode<T>* prv = node->prev;
	BiNode<T>* newNode = new BiNode<T>(x);
	prv->next = newNode;
	newNode->prev = prv;
	newNode->next = node;
	node->prev = newNode;
}

// вставка після заданого вузла
template<typename T>
inline void BiList<T>::insert(BiNode<T>* node, T x)
{
	if (!node) return; // захист від крашу

	BiNode<T>* newNode = new BiNode<T>(x);

	newNode->next = node->next;
	newNode->prev = node;

	if (node->next) {
		node->next->prev = newNode;
	}

	node->next = newNode;
}

template<typename T>
inline void BiList<T>::remove(BiNode<T>* node)
{
	if (!node) return;

	// якщо вузол перший
	if (node == front) {
		front = node->next;
		if (front) front->prev = nullptr;
		delete node;
		return;
	}

	// перепідключаємо сусідні вузли
	if (node->prev) node->prev->next = node->next;
	if (node->next) node->next->prev = node->prev;

	delete node;
}

template<typename T>
inline void BiList<T>::forward_view()
{
	BiNode<T>* temp = front;

	while (temp) {
		std::cout << temp->data << " ";
		temp = temp->next;
	}
}

template<typename T>
inline void BiList<T>::reverse_view()
{
	BiNode<T>* back = this->get_back();

	// виводимо список у зворотному порядку
	while (back) {
		std::cout << back->data << " ";
		back = back->prev;
	}
}

template<typename T>
inline BiNode<T>* BiList<T>::find(T key)
{
	BiNode<T>* temp = front;

	while (temp) {
		if (temp->data == key) {
			return temp;
		}
		temp = temp->next;
	}

	return nullptr; // не знайдено
}

// вставити інший список після заданого індексу
template<typename T>
inline void BiList<T>::slice_in(BiNode<T>* node, int index)
{
	BiNode<T>* temp = front;
	std::vector<T> dataFromSecList;

	// пошук позиції вставки за індексом
	for (int i = 0; i < index; i++) {
		if (!temp) return; // індекс за межами
		temp = temp->next;
	}

	// зберігаємо дані з другого списку
	BiNode<T>* pFront2 = node;
	while (pFront2) {
		dataFromSecList.push_back(pFront2->data);
		pFront2 = pFront2->next;
	}

	// вставляємо елементи один за одним
	for (int i = 0; i < dataFromSecList.size(); i++) {
		this->insert(temp, dataFromSecList[i]);
		temp = temp->next;
	}
}

// копіювати підсписок з індексів [index1, index2) і додати в кінець іншого списку
template<typename T>
inline void BiList<T>::slice_out(BiNode<T>* node, int index1, int index2)
{
	std::vector<T> copyData;
	BiNode<T>* temp = front;

	// пошук початкового вузла
	for (int i = 0; i < index1; i++) {
		if (!temp) return;
		temp = temp->next;
	}

	// копіювання даних
	for (int i = 0; i < index2 - index1; i++) {
		if (!temp) return;
		copyData.push_back(temp->data);
		temp = temp->next;
	}

	// переходимо в кінець другого списку
	while (node->next) {
		node = node->next;
	}

	// вставка даних у кінець
	for (int i = 0; i < copyData.size(); i++) {
		BiNode<T>* newNode = new BiNode<T>(copyData[i]);
		node->next = newNode;
		newNode->prev = node;
		node = node->next;
	}
}

template<typename T>
inline void BiList<T>::swap(BiNode<T>* n1, BiNode<T>* n2)
{
	if (n1 && n2) {
		T temp = n1->data;
		n1->data = n2->data;
		n2->data = temp;
	}
	else {
		std::cout << "Values not found";
	}
}

// Сортує список за зростанням методом прямого вибору
template<typename T>
inline void BiList<T>::sort()
{
	BiNode<T>* temp = front;

	while (temp) {
		BiNode<T>* minNode = temp;
		BiNode<T>* current = temp;

		// Знаходження мінімального елемента в решті списку
		while (current) {
			if (current->data < minNode->data)
				minNode = current;
			current = current->next;
		}

		// Обмін значень між поточним вузлом і мінімальним знайденим
		this->swap(temp, minNode);
		temp = temp->next;
	}
}
