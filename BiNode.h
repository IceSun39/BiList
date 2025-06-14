#pragma once
template <typename T>
struct BiNode {
	T data;
	BiNode<T>* prev, * next;
	BiNode() { data = 0; prev = next = nullptr; }
	BiNode(T x) { data = x; prev = next = nullptr; }
};
