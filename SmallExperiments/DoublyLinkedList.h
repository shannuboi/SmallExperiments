#pragma once

#include <memory>

template <class T>
class DoublyLinkedList {
private:
	class Node {
	public:
		Node() = default;
		Node(const T& in_data) : data(in_data) {}
		~Node() = default;
		Node(const Node& src) {
			*this = src;
		}
		Node(Node&&) = default;
		Node& operator=(const Node& src) {
			if (&src == this) return *this;

			data = src.data;
			if (src.next) {
				next = std::make_unique<Node>(*(src.next));
				next->prev = this;
			}
			return *this;
		}
		Node& operator=(Node&&) = default;
	public:
		T data;
		std::unique_ptr<Node> next;
		Node* prev = nullptr;
	};
public:
	class ConstIterator {
	public:
		ConstIterator() : nodePtr(nullptr) {}
		ConstIterator(Node* nodeptr) : nodePtr(nodeptr) {}
		const T& operator*() const {
			return nodePtr->data;
		}
		ConstIterator& operator++() {
			if (nodePtr) nodePtr = nodePtr->next.get();
			return *this;
		}
		ConstIterator operator++(int) {
			auto temp = *this;
			++(*this);
			return temp;
		}
		ConstIterator& operator--() {
			if (nodePtr) nodePtr = nodePtr->prev;
			return *this;
		}
		ConstIterator operator--(int) {
			auto temp = *this;
			--(*this);
			return temp;
		}
		bool operator==(const ConstIterator& rhs) const {
			return nodePtr == rhs.nodePtr;
		}
		bool operator!=(const ConstIterator& rhs) const {
			return !(*this == rhs);
		}
	private:
		Node const* nodePtr;
		friend DoublyLinkedList;
	};

	class Iterator {
	public:
		Iterator() : nodePtr(nullptr) {}
		Iterator(Node* nodeptr) : nodePtr(nodeptr) {}
		T& operator*() {
			return nodePtr->data;
		}
		Iterator& operator++() {
			if (nodePtr) nodePtr = nodePtr->next.get();
			return *this;
		}
		Iterator operator++(int) {
			auto temp = *this;
			++(*this);
			return temp;
		}
		Iterator& operator--() {
			if (nodePtr) nodePtr = nodePtr->prev;
			return *this;
		}
		Iterator operator--(int) {
			auto temp = *this;
			--(*this);
			return temp;
		}
		bool operator==(const Iterator& rhs) const {
			return nodePtr == rhs.nodePtr;
		}
		bool operator!=(const Iterator& rhs) const {
			return !(*this == rhs);
		}
		operator ConstIterator() const {
			return ConstIterator(nodePtr);
		}
	private:
		Node* nodePtr;
		friend DoublyLinkedList;
	};
public:
	DoublyLinkedList() = default;
	~DoublyLinkedList() = default;
	DoublyLinkedList(const DoublyLinkedList& src) {
		*this = src;
	}
	DoublyLinkedList(DoublyLinkedList&&) = default;
	DoublyLinkedList& operator=(const DoublyLinkedList& src) {
		if (&src == this) return *this;

		if (src.head) {
			head = std::make_unique<Node>(*src.head);
			Node* cur;
			for (cur = head.get(); cur->next; cur = cur->next.get());
			tail = cur;
		}
		return *this;
	}
	DoublyLinkedList& operator=(DoublyLinkedList&&) = default;

	bool IsEmpty() const {
		return !head;
	}
	Iterator PushBack(const T& data) {
		std::unique_ptr<Node> newnode = std::make_unique<Node>(data);

		if (tail) {
			newnode->prev = tail;
			tail->next = std::move(newnode);
			tail = tail->next.get();
		}
		else {
			head = std::move(newnode);
			tail = head.get();
		}
		return Iterator(tail);
	}
	Iterator PushFront(const T& data) {
		std::unique_ptr<Node> newnode = std::make_unique<Node>(data);

		if (head) {
			head->prev = newnode.get();
			newnode->next = std::move(head);
			head = std::move(newnode);
		}
		else {
			head = std::move(newnode);
			tail = head.get();
		}
		return Iterator(head.get());
	}
	Iterator AddAfter(const Iterator& iter, const T& data) {
		std::unique_ptr<Node> newnode = std::make_unique<Node>(data);
		Node* prevnode = iter.nodePtr;

		if (!prevnode) {
			return PushFront(data);
		}
		if (prevnode == tail) {
			return PushBack(data);
		}
		newnode->next = std::move(prevnode->next);
		newnode->prev = prevnode;
		newnode->next->prev = newnode.get();
		prevnode->next = std::move(newnode);

		return Iterator(prevnode->next.get());
	}
	Iterator AddBefore(const Iterator& iter, const T& data) {
		std::unique_ptr<Node> newnode = std::make_unique<Node>(data);
		Node* nextnode = iter.nodePtr;

		if (!nextnode) {
			return PushBack(data);
		}
		if (nextnode == head.get()) {
			return PushFront(data);
		}

		newnode->prev = nextnode->prev;
		nextnode->prev = newnode.get();
		newnode->next = std::move(newnode->prev->next);
		newnode->prev->next = std::move(newnode);

		return Iterator(nextnode->prev);
	}

	ConstIterator begin() const {
		return ConstIterator(head.get());
	}
	Iterator begin() {
		return Iterator(head.get());
	}
	ConstIterator end() const {
		return ConstIterator();
	}
	Iterator end() {
		return Iterator();
	}
private:
	std::unique_ptr<Node> head;
	Node* tail = nullptr;
};

