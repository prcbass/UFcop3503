#include <iostream>

using namespace std;

/////////////////////////////////////////////////////
//--------------------NODE CLASS--------------------
/////////////////////////////////////////////////////

class Node{
	private:
		string data;
		Node *next;
	public:
		Node();
		string getData();
		Node *getNext();
		void setData(string inputData);
		void setNext(Node *nextInput);
};

Node::Node(){}

string Node::getData(){
	return this->data;
}

Node* Node::getNext(){
	return this->next;
}

void Node::setData(string inputData){
	this->data = inputData;
}

void Node::setNext(Node *nextInput){
	this->next = nextInput;
}

/////////////////////////////////////////////////////
//--------------------STACK CLASS--------------------
/////////////////////////////////////////////////////

class Stack{
	private:
		Node *top;
	public:
		Stack();
		void push(string element);
		string pop();
};

Stack::Stack(){
	this->top = NULL;
}

void Stack::push(string element){
	Node *np = new Node;
	np -> setData(element);
	np -> setNext(NULL);

	if(top == NULL){
		top = np;
	}
	else{
		np -> setNext(top);
		top = np;
	}
}

string Stack::pop(){
	string word = " ";
	if(top == NULL){
		cout << "Stack is empty" << endl;
	}
	else{
		Node *popper = new Node;
		popper = top;
		top = top -> getNext();
		word = popper->getData();

		return word;
		delete(popper);
	}
}

/////////////////////////////////////////////////////
//--------------------LEXICAL ANALYSIS METHODS-------
/////////////////////////////////////////////////////