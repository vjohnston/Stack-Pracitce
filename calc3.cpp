/* Victoria Johnston ~ Programming assignment 1 ~ calc3*/

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cstdlib>
#include <stack>
#include <unistd.h> // for isatty

using namespace std;

const bool interactive = isatty(0);
int linenum = 0;

/* implementation of a stack that uses a linked list*/
template <class Number>
class lstack
{
	protected:
		typedef struct node {
			Number data;
			struct node *next;
		} node;
		node *head;
		int length;
	public:
		lstack();
		Number top() const;
		void pop();
		void push(const Number&);
		bool empty() const;
		int size() const;
};

// initialize head pointer and length
template <class Number>
lstack<Number>::lstack(){
        head = NULL;
        length = 0;
}

// create a new node and make it point to the old one
template <class Number>
void lstack<Number>::push(const Number &newdata){
        node *newnode = new node;
	newnode->data = newdata;
	if(length==0){
                newnode->next = NULL;
        } else {
                newnode->next = head;
        }
	head = newnode;
        length++;
}

// move head pointer down an element in stack
// this does not account for memory leaks
template <class Number>
void lstack<Number>::pop(){
        head = head->next;
        length--;
}

template <class Number>
Number lstack<Number>::top() const{
        return head->data;
}

template <class Number>
bool lstack<Number>::empty() const{
        return (length==0);
}

template <class Number>
int lstack<Number>::size() const{
	return length;
}


/*Normal member functions*/
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

// push a number onto the stack and print it
template <typename Number>
void push_stack(lstack<double> &cstack,Number x) {
        cstack.push(x);
	cout << cstack.top() << endl;
}

// take one or two elements from the stack perform calculation and push answer back to stack
void do_calculation(lstack<double> &cstack,string s){
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
				push_stack(cstack,(n2-n1));
			} else if (s=="*"){
				push_stack(cstack,(n2*n1));
			} else if (s=="/"){
				push_stack(cstack,(n2/n1));
			} else if (s=="swap"){
				cstack.push(n1);
				push_stack(cstack,n2);
			}	
		}
	} else {
		error("stack underflow");
	}
}

// print used to debug code
void print(lstack<double> stack){
	cout << "stack:";
	while (stack.size()>=1){
		cout << stack.top();
		stack.pop();
	}
	cout << endl;
}

int main (int argc, char *argv[]) {
	lstack<double> cstack;
	stack<lstack<double>> undostack;
	while (!cin.eof()) {
    		if (interactive) cout << "> ";

    		string s;
		double x;
    		getline(cin, s);
    		linenum++;

		if (check_arithmetic(s)){ //check if s is an operation
			do_calculation(cstack,s);
			undostack.push(cstack);
		} else if (string_to_number(s, x) == 0) { //checks if s is a valid number
			push_stack(cstack,x);
			undostack.push(cstack);
 		} else if (s == "") {
      			// do nothing 
      		} else if (s=="undo"){
			int size =  undostack.size();
                        if (size>=1){
				undostack.pop();
				if (size!=1){
					cstack = undostack.top();
					cout << cstack.top() << endl;
				} else cstack.pop();
                        } else {
                                error("cannot undo");
                        }
                }  else {
    			error("couldn't understand input");
    		}
	}
}
