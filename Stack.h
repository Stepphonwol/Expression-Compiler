#pragma once
#ifndef STACK_H_
#define STACK_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Compiler;

template<class E>
class Stack;

template<class E>
class Node {
	friend class Stack<E>;
	friend class Compiler;
	private:
		Node(E x) : val(x), next(NULL) {}
		/*~Node() {
			delete next;
		}*/
		E val;
		Node* next;
};

template<class E>
class Stack {
	friend class Compiler;
	private:
		Stack(Node<E>* x = NULL, int s = 0) : head(x), size(s) {}
		/*~Stack() {
			delete head;
		}*/
		void push(E x) {
			auto temp = new Node<E>(x);
			temp->next = head;
			++size;
			head = temp;
		}
		E pop() {
			auto temp = head;
			auto v = temp->val;
			head = head->next;
			--size;
			delete temp;
			return v;
		}
		E top() {
			return head->val;
		}
		int length() {
			return size;
		}
		void show() {
			Node<E>* temp = head;
			while (temp != NULL) {
				cout << temp->val;
				temp = temp->next;
			}
		}
		Node<E>* head;
		int size;
};

#endif
