#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
namespace ariel
{
	template <typename T>
	class Node
	{
	public:
		T value;
		Node *left = nullptr;
		Node *right = nullptr;
		Node(T val) : value(val), left(nullptr), right(nullptr) {}
		Node(const Node *other) : value(0), right(nullptr), left(nullptr)
		{
			if (other != nullptr)
			{
				value = other->value;
				if (other->right != nullptr)
				{
					right = new Node(other->right);
				}
				if (other->left != nullptr)
				{
					left = new Node(other->left);
				}
			}
		}
	};

	template <typename T>
	class BinaryTree
	{

	private:
		Node<T> *root = nullptr;

	public:
		BinaryTree<T>()
		{
			root = nullptr;
		}

		BinaryTree(const BinaryTree &other)
		{
			root = new Node<T>(other.root);
		}

		BinaryTree &operator=(const BinaryTree other)
		{
			if (this == &other)
			{
				return *this;
			}
			root = new Node<T>(other.root);
			return *this;
		}

		BinaryTree &operator=(BinaryTree &&other) noexcept
		{
			return *this;
		}

		BinaryTree(BinaryTree &&other) noexcept
		{
		}

		BinaryTree<T> &add_root(T val);
		BinaryTree<T> &add_left(T parent, T left_val);
		BinaryTree<T> &add_right(T parent, T right_val);

		~BinaryTree() {} //destructor

		friend ostream &operator<<(ostream &os, const BinaryTree<T> &b_tree)
		{
			os << "Amit Cohen" << endl;
			return os;
		}

		Node<T> *findValue(Node<T> *node, T value)
		{
			if (node == nullptr)
			{
				return nullptr;
			}
			if (node->value == value)
			{
				return node;
			}
			//Go to left
			Node<T> *left = findValue(node->left, value);
			if (left != nullptr)
			{
				return left;
			}
			//Go to right
			return findValue(node->right, value);
		}

		class PreorderIt
		{
		private:
			size_t currentIndex;
			vector<Node<T> *> sorted_preorder_numbers;

		public:
			PreorderIt(Node<T> *ptr) : currentIndex(0)
			{
				fill(ptr);
				//Sign the end
				sorted_preorder_numbers.push_back(nullptr);
			}
			void fill(Node<T> *n)
			{
				if (n == nullptr)
				{
					return;
				}
				sorted_preorder_numbers.push_back(n);
				fill(n->left);
				fill(n->right);
			}

			T &operator*() const
			{
				return sorted_preorder_numbers.at(currentIndex)->value;
			}

			T *operator->() const
			{
				return &sorted_preorder_numbers.at(currentIndex)->value;
			}

			PreorderIt &operator++()
			{
				currentIndex++;
				return *this;
			}
			PreorderIt operator++(int)
			{
				PreorderIt holder = *this;
				currentIndex++;
				return holder;
			}

			bool operator==(const PreorderIt &second) const
			{
				return sorted_preorder_numbers.at(currentIndex) == second.sorted_preorder_numbers.at(second.currentIndex);
			}

			bool operator!=(const PreorderIt &second) const
			{
				return sorted_preorder_numbers.at(currentIndex) != second.sorted_preorder_numbers.at(second.currentIndex);
			}
		};

		class InorderIt
		{
		private:
			size_t currentIndex;

			vector<Node<T> *> sorted_inorder_numbers;

		public:
			InorderIt(Node<T> *ptr) : currentIndex(0)
			{
				fill(ptr);
				//Sign the end
				sorted_inorder_numbers.push_back(nullptr);
			}
			void fill(Node<T> *n)
			{
				if (n == nullptr)
				{
					return;
				}
				fill(n->left);
				sorted_inorder_numbers.push_back(n);
				fill(n->right);
			}

			T &operator*() const
			{
				return sorted_inorder_numbers.at(currentIndex)->value;
			}

			T *operator->() const
			{
				return &sorted_inorder_numbers.at(currentIndex)->value;
			}

			InorderIt &operator++()
			{
				currentIndex++;
				return *this;
			}

			InorderIt operator++(int)
			{
				InorderIt holder = *this;
				currentIndex++;
				return holder;
			}
			bool operator==(const InorderIt &second) const
			{
				return sorted_inorder_numbers.at(currentIndex) == second.sorted_inorder_numbers.at(second.currentIndex);
			}

			bool operator!=(const InorderIt &second) const
			{
				return sorted_inorder_numbers.at(currentIndex) != second.sorted_inorder_numbers.at(second.currentIndex);
			}
		};

		class PostorderIt
		{
		private:
			size_t currentIndex;

			vector<Node<T> *> sorted_postorder_numbers;

		public:
			PostorderIt(Node<T> *ptr) : currentIndex(0)
			{
				fill(ptr);
				//Sign the end
				sorted_postorder_numbers.push_back(nullptr);
			}

			void fill(Node<T> *n)
			{
				if (n == nullptr)
				{
					return;
				}
				fill(n->left);
				fill(n->right);
				sorted_postorder_numbers.push_back(n);
			}

			T &operator*() const
			{
				return sorted_postorder_numbers.at(currentIndex)->value;
			}

			T *operator->() const
			{
				return &sorted_postorder_numbers.at(currentIndex)->value;
			}

			PostorderIt &operator++()
			{
				currentIndex++;
				return *this;
			}
			PostorderIt operator++(int)
			{
				PostorderIt holder = *this;
				currentIndex++;
				return holder;
			}

			bool operator==(const PostorderIt &second) const
			{
				return sorted_postorder_numbers.at(currentIndex) == second.sorted_postorder_numbers.at(second.currentIndex);
			}

			bool operator!=(const PostorderIt &second) const
			{
				return sorted_postorder_numbers.at(currentIndex) != second.sorted_postorder_numbers.at(second.currentIndex);
			}
		};

		InorderIt begin()
		{
			return begin_inorder();
		};
		InorderIt end()
		{
			return end_inorder();
		};

		PreorderIt begin_preorder()
		{
			return PreorderIt(root);
		}

		PreorderIt end_preorder()
		{
			return PreorderIt(nullptr);
		}

		InorderIt begin_inorder()
		{
			return InorderIt(root);
		}

		InorderIt end_inorder()
		{
			return InorderIt(nullptr);
		}

		PostorderIt begin_postorder()
		{
			return PostorderIt(root);
		}

		PostorderIt end_postorder()
		{
			return PostorderIt(nullptr);
		}
	};

	template <typename T>
	BinaryTree<T> &BinaryTree<T>::add_root(T val)
	{
		if (root != nullptr)
		{
			root->value = val;
		}
		else
		{
			root = new Node<T>(val);
		}
		return *this;
	}

	template <typename T>
	BinaryTree<T> &BinaryTree<T>::add_left(T parent, T left_val)
	{
		Node<T> *node = findValue(root, parent);
		if (node == nullptr)
		{
			throw invalid_argument("Node not found");
		}

		if (node->left == nullptr)
		{
			node->left = new Node<T>(left_val);
		}
		else
		{
			node->left->value = left_val;
		}
		return *this;
	}

	template <typename T>
	BinaryTree<T> &BinaryTree<T>::add_right(T parent, T right_val)
	{
		Node<T> *node = findValue(root, parent);
		if (node == nullptr)
		{
			throw invalid_argument("Node not found");
		}
		if (node->right == nullptr)
		{
			node->right = new Node<T>(right_val);
		}
		else
		{
			node->right->value = right_val;
		}

		return *this;
	}
}
