#pragma once

#include <memory>
#include <assert.h>

template<class datatype>
class BinarySearchTree
{
private:
	class Node
	{
		friend class ConstIterator;
	public:
		Node(const datatype& data, Node* parent)
			:
			data(data),
			parent(parent)
		{}
		void Insert(const datatype& newVal)
		{
			if (newVal < data)
			{
				if (lChild)
					lChild->Insert(newVal);
				else
					lChild = std::make_unique<Node>(newVal, this);
			}
			else
			{
				if (rChild)
					rChild->Insert(newVal);
				else
					rChild = std::make_unique<Node>(newVal, this);
			}
		}
		Node& GetParent()
		{
			assert(parent);
			return *parent;
		}
		Node& GetLeft()
		{
			assert(lChild);
			return *lChild;
		}
		Node& GetRight()
		{
			assert(rChild);
			return *rChild;
		}
	private:
		datatype data;
		Node* parent;
		std::unique_ptr<Node> lChild;
		std::unique_ptr<Node> rChild;
	};

public:
	class ConstIterator
	{
	public:
		ConstIterator()
			:
			nodePtr(nullptr),
			fromBelow(true)
		{}
		ConstIterator(Node* nodeptr)
			:
			nodePtr(nodeptr),
			fromBelow(false)
		{}
		const datatype& operator*() const
		{
			return nodePtr->data;
		}
		ConstIterator& operator++()
		{
			*this = updateNodePtr(nodePtr, fromBelow);
			return *this;
		}
		ConstIterator operator++(int)
		{
			auto temp = *this;
			*this = updateNodePtr(nodePtr, fromBelow);
			return temp;
		}
		bool operator==(const ConstIterator& rhs) const
		{
			return nodePtr == rhs.nodePtr;
		}
		bool operator!=(const ConstIterator& rhs) const
		{
			return !(*this == rhs);
		}
	private:
		ConstIterator(Node* nodeptr, bool fromBelow)
			:
			nodePtr(nodeptr),
			fromBelow(fromBelow)
		{}
		ConstIterator updateNodePtr(Node* cur, bool fromLeft, bool fromRight = false, bool explored = true) const
		{
			if (!cur)
				return ConstIterator();

			if (fromLeft)
				return ConstIterator(cur, true);

			if (fromRight)
			{
				if (!cur->parent)
					return ConstIterator();

				if (cur->data < cur->GetParent().data)
					return updateNodePtr(cur->parent, true, false, false);
				else
					return updateNodePtr(cur->parent, false, true, true);
			}

			if (cur->lChild)
				return updateNodePtr(cur->lChild.get(), false, false, false);

			if (explored)
				return updateNodePtr(cur->rChild.get(), false, false, false);

			return ConstIterator(cur, false);
		}
	private:
		Node* nodePtr;
		bool fromBelow;
	};

public:
	void Insert(const datatype& newVal)
	{
		if (root)
			root->Insert(newVal);
		else
			root = std::make_unique<Node>(newVal, nullptr);
	}
	void DeleteNode(ConstIterator iter)
	{
		// Cant be bothered rn
	}
	ConstIterator begin() const
	{
		return ConstIterator(root.get());
	}
	ConstIterator end() const
	{
		return ConstIterator();
	}
private:
	std::unique_ptr<Node> root;
};