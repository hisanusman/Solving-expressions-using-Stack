#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Node {
	float data;
	Node* next;
public:
	Node() {
		this->next = nullptr;
	}
	void set_data(float val) {
		data = val;
	}
	float get_data() {
		return data;
	}

	void set_next(Node* n) {
		next = n;
	}
	Node* get_next() {
		return next;
	}
};

class Stack {
	Node* front;			// front == head
	Node* rear;				// rear == tail
public:
	Stack() {
		front = nullptr;
		rear = nullptr;
	}
	Node* get_front() {
		return front;
	}
	void set_front(Node* f) {
		front = f;
	}
	Node* get_rear() {
		return rear;
	}
	void set_rear(Node* r) {
		front = r;
	}
	bool isEmpty() {
		if (front == NULL)
			return true;

		return false;
	}

	void push(float val) {
		Node* temp = new Node();
		temp->set_data(val);
		temp->set_next(front);
		front = temp;
	}

	float peek() {
		return front->get_data();
	}

	bool pop() {
		if (front == NULL)
			return false;

		front = front->get_next();
		return true;
	}
};

//Evaluating the Expression:

bool isExpBalanced(string exp) {
	Stack obj;
	char c;
	int len = exp.length();

	char* arr = new char[len + 1];
#pragma warning(suppress : 4996)
	strcpy(arr, exp.c_str());

	for (int i = 0; i < len; i++) {
		if (*(arr + i) == '{' || *(arr + i) == '[' || *(arr + i) == '(')
			obj.push(*(arr + i));

		else if (*(arr + i) == '}' || *(arr + i) == ']' || *(arr + i) == ')') {
			c = obj.peek();

			if (*(arr + i) == '}' && (toascii('{') == c))
				obj.pop();
			if (*(arr + i) == ']' && (toascii('[') == c))
				obj.pop();
			if (*(arr + i) == ')' && (toascii('(') == c))
				obj.pop();
		}
	}
	if (obj.isEmpty())
		return true;
	else
		return false;
}

int operand_prior(char c) {			// changing priorities according to question
	if (c == '%')
		return 4;

	else if (c == '+' || c == '-')
		return 3;

	else if (c == '*' || c == '/')
		return 2;

	else if (c == '^')
		return 1;

	return 0;
}

string infixToPostfix(string s) {
	int check = 0;
	Stack S;
	string postfix;

	for (int i = 0; i < s.length(); i++) {

		if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' || s[i] == '^' || s[i] == '%')
			postfix += " ";

		if ((s[i] >= '0' && s[i] <= '9')) {
			postfix += s[i];
		}

		else if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			S.push(s[i]);

		else if (s[i] == ')') {
			while (S.peek() != '(') {
				postfix += S.peek();
				S.pop();
			}
			S.pop();
		}
		else if (s[i] == ']') {
			while (S.peek() != '[') {
				postfix += S.peek();
				S.pop();
			}
			S.pop();
		}
		else if (s[i] == '}') {
			while (S.peek() != '{') {
				postfix += S.peek();
				S.pop();
			}
			S.pop();
		}

		else {
			while (!s.empty() && operand_prior(s[i]) <= operand_prior(S.peek())) {
				postfix += char(S.peek());
				S.pop();
			}
			S.push(s[i]);
		}
	}
	return postfix;
}

int evaluatePostFix(string exp) {
	Stack obj;
	float el1, el2, sum = 0;
	int len = exp.length();
	int count = 0;
	int v = 0;

	char* arr = new char[len + 1];
	string postfix;
#pragma warning(suppress : 4996)
	strcpy(arr, exp.c_str());

	for (int i = 0; i < len; i++) {

		if ((int(*(arr + i)) >= 48 && int(*(arr + i)) <= 57) || (*(arr + i) == ' ')) {
			if (int(*(arr + i)) >= 48 && int(*(arr + i)) <= 57) {
				if (count == -1) {
					v = obj.peek();
					v *= 10;
					v += (*(arr + i) - 48);
					obj.pop();
					obj.push(v);
				}
				else {
					obj.push(int(*(arr + i) - 48));
					count = -1;
				}
			}
			if (*(arr + i) == ' ') {
				count = 0;
				v = 0;
			}
		}

		else if (*(arr + i) == '%' || *(arr + i) == '+' || *(arr + i) == '-' ||
			*(arr + i) == '/' || *(arr + i) == '*' || *(arr + i) == '^') {

			count = 0;
			v = 0;

			el1 = obj.peek();
			obj.pop();
			el2 = obj.peek();
			obj.pop();

			if (*(arr + i) == '*')
				sum = float(el2) * float(el1);
			else if (*(arr + i) == '+')
				sum = float(el2) + float(el1);
			else if (*(arr + i) == '-')
				sum = float(el2) - float(el1);
			else if (*(arr + i) == '/')
				sum = float(el2) / float(el1);
			else if (*(arr + i) == '^')
				sum = pow(float(el2), float(el1));
			else if (*(arr + i) == '%')
				sum = int(el2) % int(el1);

			obj.push(sum);
		}
	}
	return obj.peek();
}