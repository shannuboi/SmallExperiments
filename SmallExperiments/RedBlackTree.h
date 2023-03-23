#pragma once

#include <memory>
#include <utility>

template <class KeyType, class ValType>
class RBTree {
private:
	typedef std::pair<KeyType, ValType> KVPair;
	struct Node {
		KVPair data;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node* parent = nullptr;
		bool isRed = true;
	};
public:
	class Iterator {
	public:
		Iterator(Node* ptr) : node_ptr(ptr) {}
		const KVPair&	operator*() const {
			return node_ptr->data;
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
	
private:
	std::unique_ptr<Node> root = nullptr;
};