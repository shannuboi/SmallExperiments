#pragma once

#include <memory>
#include <utility>

template <class KeyType, class ValType>
class RBTree {
private:
	typedef std::pair<KeyType, ValType> KVPair;
	class Node {
	public:
		Node(KVPair in_data) : data(std::move(in_data)) {}
		KVPair data;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node* parent = nullptr;
		bool isRed = true;
	};
public:
	class ConstIterator {
	public:
		ConstIterator(Node* ptr) : node_ptr(ptr) {}
		const ValType&	operator*() const {
			return node_ptr->data.first;
		}
		const ValType*	operator->() const {
			return &node_ptr->data.second;
		}
		bool			operator==(const ConstIterator& rhs) const {
			return node_ptr == rhs.node_ptr;
		}
		bool			operator!=(const ConstIterator& rhs) const {
			return !(*this == rhs);
		}
		const ValType&	GetData() const {
			return node_ptr->data.second;
		}
		const KeyType&	GetKey() const {
			return node_ptr->data.first;
		}
		ConstIterator&	GoLeft() {
			node_ptr = node_ptr->left.get();
			return *this;
		}
		ConstIterator	GetLeftChild() const {
			return Iterator(node_ptr->left.get());
		}
		ConstIterator&	GoRight() {
			node_ptr = node_ptr->right.get();
			return *this;
		}
		ConstIterator	GetRightChild() const {
			return Iterator(node_ptr->right.get());
		}
		ConstIterator&	GoUp() {
			node_ptr = node_ptr->parent;
			return *this;
		}
		ConstIterator	GetParent() const {
			return Iterator(node_ptr->parent);
		}
		bool			IsRed() const {
			return node_ptr->isRed;
		}
		bool			IsBlack() const {
			return !node_ptr->isRed;
		}
	private:
		Node* node_ptr;
	};
	class Iterator {
	public:
		Iterator(Node* ptr) : node_ptr(ptr) {}
		operator		ConstIterator() {
			return ConstIterator(node_ptr);
		}
		ValType&		operator*() {
			return node_ptr->data.second;
		}
		ValType*		operator->() {
			return &node_ptr->data.second;
		}
		bool			operator==(const Iterator& rhs) const {
			return node_ptr == rhs.node_ptr;
		}
		bool			operator!=(const Iterator& rhs) const {
			return !(*this == rhs);
		}
		ValType&		GetData() {
			return node_ptr->data.second;
		}
		const KeyType&	GetKey() const {
			return node_ptr->data.first;
		}
		Iterator&		GoLeft() {
			node_ptr = node_ptr->left.get();
			return *this;
		}
		Iterator		GetLeftChild() const {
			return Iterator(node_ptr->left.get());
		}
		Iterator&		GoRight() {
			node_ptr = node_ptr->right.get();
			return *this;
		}
		Iterator		GetRightChild() const {
			return Iterator(node_ptr->right.get());
		}
		Iterator&		GoUp() {
			node_ptr = node_ptr->parent;
			return *this;
		}
		Iterator		GetParent() const {
			return Iterator(node_ptr->parent);
		}
		bool			IsRed() const {
			return node_ptr->isRed;
		}
		bool			IsBlack() const {
			return !node_ptr->isRed;
		}
	private:
		Node* node_ptr;
	};
public:
	RBTree() = default;
	Iterator Insert(KVPair new_data) {
		std::unique_ptr<Node> newnode = std::make_unique<Node>(std::move(new_data));
		newnode->isRed = false;
		root = std::move(newnode);
		return Iterator(root.get());
	}
	ConstIterator begin() const {
		return ConstIterator(root.get());
	}
	Iterator begin() {
		return Iterator(root.get());
	}
	ConstIterator end() const {
		return ConstIterator(nullptr);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
private:
	std::unique_ptr<Node> root;
};