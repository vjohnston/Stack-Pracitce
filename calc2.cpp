/* Victoria Johnston ~ Programming assignment 1 ~ calc2*/

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

// returns true if input is an arithmetic operation
bool check_arithmetic(string s){
	if ((s=="+")||(s=="-")||(s=="*")||(s=="/")||(s=="swap")||(s=="drop")){
		return true;
	} else {
		return false;
	}
}

// function to push Number back into stack
template <typename Number>
void push_stack(stack<double> &cstack,Number x) {
        cstack.push(x);
	cout << x << endl;
}

//template <typename Number>
void do_calculation(stack<double> &cstack,string s){
	if (cstack.size()>=2){
		double n1 = cstack.top();
		cstack.pop();
        	double n2 = cstack.top();
		if (s=="drop") {
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
	stack<stack<double>> undostack;
	while (!cin.eof()) {
    		if (interactive) cout << "> ";

    		string s;
		double x;
    		getline(cin, s);
    		linenum++;

		if (check_arithmetic(s)){ //check if s is an operation
			undostack.push(cstack); //before operation push current stack into undo list (save old copy)
			do_calculation(cstack,s); 
		} else if (string_to_number(s, x) == 0) {
			undostack.push(cstack); //before pushing number, push current stack into undo list (save old copy)
			push_stack(cstack,x); //if valid number push x into stack
 		} else if (s == "") {
      			// do nothing 
      		} else if (s=="undo"){
                        if (undostack.size()>=1){
                                cstack = undostack.top(); //get the saved stack before the operation
				undostack.pop(); //remove that saved stack since now it is the current stack
				if (cstack.size()>0) cout << cstack.top() << endl; //print out the top element of the new (saved) stack
                        } else {
                                error("cannot undo");
                        }
                }  else {
    			error("couldn't understand input");
    		}
	}
}
