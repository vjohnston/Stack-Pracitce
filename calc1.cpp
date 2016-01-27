/* Victoria Johnston ~ Programming assignment 1 ~ calc1*/

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <unistd.h> // for isatty

using namespace std;

const bool interactive = isatty(0);
int linenum = 0;

void error (const char *s) {
	if (interactive) {
		cout << "error: " << s << endl;
	} else {
		cerr << "error: " << s << " on line " << linenum << endl;
	}
}

template <typename Number>
int string_to_number (const string &s, Number &x) {
	stringstream ss(s);
	ss >> x;
	if (ss.eof() && !ss.fail()) 
		return 0;
	else
		return -1;
}

// returns true if input is an arithmetic operation, false otherwise
bool check_arithmetic(string s){
	if ((s=="+")||(s=="-")||(s=="*")||(s=="/")||(s=="swap")||(s=="drop")){
		return true;
	} else {
		return false;
	}
}

// push the Number x back into the cstack (std::stack)
template <typename Number>
void push_stack(stack<double> &cstack,Number x) {
        cstack.push(x);
	cout << x << endl;
}

// evaluates the string calculation then pushes answer into stack (except drop)
void do_calculation(stack<double> &cstack,string s){
	if (cstack.size()>=2){ //make sure there are at least two elements in stack for calculation
		double n1 = cstack.top();
		cstack.pop();
        	double n2 = cstack.top();
		if (s=="drop") {
			// doesn't pop again like other arithmetic operations
			cout << n2 << endl;
		} else {
        		cstack.pop();
			if (s=="+"){
				push_stack(cstack,(n1+n2));
			} else if (s=="-"){
				push_stack(cstack,n2-n1);
			} else if (s=="*"){
				push_stack(cstack,n2*n1);
			} else if (s=="/"){
				push_stack(cstack,n2/n1);
			} else if (s=="swap"){
				cstack.push(n1);
				push_stack(cstack,n2);
			}
		}
	} else {
		error("stack underflow");
	}
}

int main (int argc, char *argv[]) {
	stack<double> cstack;
	while (!cin.eof()) {
    		if (interactive) cout << "> ";

    		string s;
    		getline(cin, s);
    		linenum++;

		if (check_arithmetic(s)){ //if s is an arithmetic operation, do calculation
			do_calculation(cstack,s);
		} else {
    			double x;
    			if (string_to_number(s, x) == 0) { //check is the input s is a number
				push_stack(cstack,x);
 			} else if (s == "") {
      				// do nothing 
    			} else {
    				error("couldn't understand input");
    			}
		}
	}
}
