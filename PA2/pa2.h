//Sebastian Hernandez
//COP 3503
#include <iostream>
using namespace std;

class Node{
	
	public:
		Node();
		string data;
		Node *next;
		int freeBefore;
		int freeAft;
		int progSize;
};


Node::Node(){
	const int size = 4;
}


class LinkedList{
	public:
		Node *head;
		LinkedList();
		bool isEmpty(Node *head);
		void insertFirstElement(Node *&head, string prog, int num);
		void insert(Node *&head, string prog, int num, string algo);
		void showList(Node *current);
		int nodePos(Node *&head, int num, string algo);
		void killProg(Node *&head, string prog);
		int numFragments(Node* curr);
		bool isRunning(Node *&head, string prog);
};

LinkedList::LinkedList(){ 
	head = NULL;
}


bool LinkedList::isEmpty(Node *head){ //used for a completely empty list
	return (head == NULL);
}

//finds positions to input node based on algorithm of choice
int LinkedList::nodePos(Node *&head, int num, string algo){
	int tempPos = -1;
	if(!isEmpty(head)){
		Node *current = head;
		int max = -1;
		int min = 33;
		int curPos = 0;
		int placePos = -1;

		//worst case algorithm chosen
		if(algo.compare("worst")==0){
			//checking free space before point of insertion for program
			if(current -> freeBefore >= num){
				if(max < current -> freeBefore){
					max = current -> freeBefore;
				}
				placePos = curPos;
			}
			curPos++;
			//checking amount of free space after program
			while (current != NULL){
				if(current->freeAft >= num && max < current -> freeAft){
					max = current -> freeAft;
					placePos = curPos;
				}
				current = current ->next;
				curPos++;
			}
			tempPos = placePos;
		}	
		//best case algorithm chosen
		else{
			//verifying free space after is big enough
			if(current -> freeBefore >= num){
				if(min > current -> freeBefore){
					min = current -> freeBefore;
					placePos = curPos;
				}
			}
			curPos++;
			//verifying free space after 
			while(current != NULL){
				if(min > current -> freeAft && current -> freeAft >= num){
					min = current -> freeAft;
					placePos = curPos;
				}
				current = current -> next;
				curPos++;
			}
			tempPos = placePos;
		}
	}
	else{
		if(num < 33)
			tempPos = 0;
	}
	return tempPos;
}

void LinkedList::insertFirstElement(Node *&head, string prog, int num){
	Node *temp = new Node();
	temp -> data = prog;
	temp -> next = NULL;
	temp -> freeAft = 32-num;
	temp -> freeBefore = 0;
	temp -> progSize = num;
	head = temp;
}


void LinkedList::insert(Node *&head, string prog, int num, string algo){
	if(!isRunning(head, prog)){
		int placement = nodePos(head, num, algo);
		//program incorrect size
		if(placement != -1 || num == 0){
			if(isEmpty(head)){
				insertFirstElement(head, prog, num);
			}
			else{
				//changes head 
				if(placement == 0){
					Node *temp = new Node();
					temp->progSize = num;
					temp->data = prog;
					temp->freeBefore = 0;
					temp->next=head;
					temp->freeAft = (head->progSize)-num;
					head -> freeBefore = 0;
					head = temp;
				}
				//changes other values
				else{
					Node *temp = new Node();
					temp->progSize = num;
					temp->data = prog;
					temp->freeBefore=0;
					Node *current = head;
					//finding position
					for(int i=1; i<placement; i++){
						if(current->next != NULL){
							current = current->next;
						}
					}
					temp->next = current -> next;
					//this finds the value the free space will be changing to after node
					temp -> freeAft = (current->freeAft)-num;
					current -> freeAft = 0;
					current -> next= temp;
				}
			}
			cout << "Program " << prog << " added succesffuly." << num << " page(s) allocated" << endl;
		}
		else{
			cout << "ERROR, program size does not apply.";
		}
	}
	else{
		cout << "Program " << prog << " is  already running!" << endl;
	}
}



//determines whether program is already running
bool LinkedList::isRunning(Node *&head, string prog){
	bool cond = false;
	if(!isEmpty(head)){
		Node *current = head;
		//checks first spot
		if(current->data.compare(prog)==0){
			cond = true;
			return cond;
		}
		while(current->next != NULL){
			if(current->data.compare(prog)==0){
				cond = true;
				return cond;
			}
			current = current -> next;
		}
	}
	return cond;
}

//kills program and reclaims space used
void LinkedList::killProg(Node *&head, string prog){
	bool cond = false;
	int progSize = 0;
	if(isEmpty(head)){
		cout << "No program running to kill, add a program." << endl;
	}
	else{
		Node *prevNode = NULL;
		Node *delNode = NULL;
		Node *current = head;
		//occurs when head must be deleted
		if(head -> data.compare(prog) == 0){
			if(current -> next != NULL){
				delNode	= head;
				//will be moving the values
				int tempAfter = head -> freeAft;
				int tempSize = head -> progSize;
				int tempBefore = head -> freeBefore;
				int transfer = tempAfter + tempSize + tempBefore;
				head = delNode->next;
				head -> freeBefore = transfer;
				progSize = delNode -> progSize;
				delete delNode;
				cond = true;
			}
			//occurs when only one node left in list
			else{
				progSize = current -> progSize;
				delete current -> next;
				head = NULL;
				current -> next = NULL;
				cond = true;
			}
		}
		//occurs when removing nodes from middle of list
		prevNode = current;
		delNode = current -> next;
		while(delNode != NULL){
			if(delNode -> data.compare(prog)==0){
				//need to reinitialize the values for later use
				int tempAfter = delNode->freeAft;
				int tempSize = delNode -> progSize;
				int transfer = tempAfter+tempSize;
				if(delNode -> next == NULL){
					delete delNode->next;
					prevNode->next = NULL;
					progSize = delNode->progSize;

					prevNode->freeAft = prevNode->freeAft+transfer;
					delNode = NULL;
					cond = true;
					break;
				}
				else{
					prevNode -> next = delNode -> next;
					prevNode -> freeAft = transfer;
					progSize = delNode -> progSize;
					delete delNode;
					cond = true;
					break;
				}
				break;
			}
			prevNode = delNode;
			delNode = delNode -> next;
		}
		if(cond){
			cout << "Program " << prog << " has been successfully killed. " << progSize << " page(s) reclaimed" << endl;
		}
	}
}

int LinkedList::numFragments(Node* curr){
	int count=1;
	if(!isEmpty(curr)){
		count = 0;
		while(curr -> next != NULL){
			if(curr -> freeBefore != 0){
				count++;
			}
			count++;
			curr = curr->next;
		}
	}
	return count;
}


void LinkedList::showList(Node *current){
	//will only occur when no programs have been added
	if(isEmpty(current)){
		for(int i=0; i<32; i++){
			if(i%8==0){
				cout << "\n";
			}
			cout << "Free\t";
		}
	}
	else{
		int index = 0;
		while(index < 32){
			for(int i=0; i<current->freeBefore; i++){
				if(index%8==0 && index>0){
					cout << "\n";
				}
				cout << "Free\t";
				index++;
			}
			//actual values of elements
			for(int i=0; i<current -> progSize; i++){
				if(index%8==0 && index>0){
					cout << "\n";
				}
				cout << current -> data << "\t";
				index++;
			}
			//elements after given node
			for(int i=0; i < current->freeAft; i++){
				if(index%8==0 && index>0){
					cout << "\n";
				}
				cout << "Free\t";
				index++;
			}
			//moves onto next node
			if(current != NULL){
				current = current -> next;
			}
		}
	}
}
