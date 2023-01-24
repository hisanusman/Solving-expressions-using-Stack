#include <iostream>
#include "../Header.h"
using namespace std;

int main() {
	string s, infix, choice;

enter_string:

	cout << "Do you want to enter a postfix or infix expression? ";
	cin >> choice;

	cout << "Enter a string: ";
	cin >> s;

	cout << "\nChecking whether string is balanced or not: " << endl;

	if (isExpBalanced(s)) {

		cout << "String is balanced!\n\n";

		if (choice == "Infix" || choice == "infix" || choice == "in") {

			infix = infixToPostfix(s);
			cout << "Converting infix to postfix: \n" << infix << endl;
			cout << "\nAfter evaluation, the answer is: \n" << evaluatePostFix(infix) << endl;
		}

		else
			cout << "After evaluation, the answer is: \n" << evaluatePostFix(s) << endl;
	}

	else {
		cout << "String is not balanced!\n\n";
		goto enter_string;
	}

	return 0;
}