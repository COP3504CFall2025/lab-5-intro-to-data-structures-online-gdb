#pragma once
#include <iostream>
using namespace std;




template <typename T>
class LinkedList {
	struct Node {
    	T data;
    	Node* prev;
    	Node* next;
	};

public:
	// Behaviors
	void printForward() const {
		
		Node* cursor = head;
		while (cursor) {
			std::cout << cursor->data << ' ';
			cursor = cursor -> next;
		}

		std::cout << std::endl;
	}
	void printReverse() const {
		Node* cursor = tail;
		while (cursor) {
			std::cout << cursor->data << ' ';
			cursor = cursor -> prev;
		}

		std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead() {return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data) {
		Node* newNode = new Node;
		newNode -> data = data;

		if (count >0) {
			newNode -> next = head;
			head -> prev = newNode;
		} else {
			newNode -> next = nullptr;
			tail = newNode;
		}

		newNode -> prev = nullptr;
		head = newNode;

		count ++;
	}

	void addTail(const T& data) {
		Node* newNode = new Node;
		newNode -> data = data;

		if (count > 0) {
			tail -> next = newNode;
			newNode -> prev = tail;
		} else {
			newNode -> prev = nullptr;
			head = newNode;
		}

		newNode -> next = nullptr;
		tail = newNode;

		count ++;
	}

	// Removal
	bool removeHead() {
		if (count==0) return false;
		if (count==1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count = 0;
			return true;
		}

		Node* newHead = head->next;

		delete head;

		head = newHead;
		head->prev = nullptr;

		count --;
		
		return true;
	}

	bool removeTail() {
		if (count==0) return false;
		if (count==1) return removeHead();

		Node* newTail = tail->prev;

		delete tail;

		tail = newTail;
		tail->next = nullptr;

		count --;

		return true;
	}

	void Clear() {
		Node* cursor = head;

		while (cursor) {
			Node* time_to_die_buddy = cursor;
			cursor = cursor->next;
			delete time_to_die_buddy;
		}

		head = nullptr;
		tail = nullptr;
		count = 0;
		/*
		while (count >0) {
			removeHead();
		}
		*/
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;

		Clear();

		count = other.count;
		head = other.head;
		tail = other.tail;

		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;

		return *this;
	}
	
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;
		Clear();
		
		
		if (rhs.count==0) {
			head = nullptr;
			tail = nullptr;
			return *this;
		}

		Node* cursor = rhs.head;
		
		while (cursor) {
			addTail(cursor->data);
			cursor = cursor->next;
		}
		

		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node* cursor = list.head;
		while (cursor) {
			addTail(cursor->data);
			cursor = cursor->next;
		}
		
	}

	LinkedList(LinkedList<T>&& other) noexcept {
		count = other.count;

		head = other.head;
		tail = other.tail;

		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}

	~LinkedList() {
		Clear();
	}

private:

	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};

	
