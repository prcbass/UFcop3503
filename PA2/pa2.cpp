//Sebastián Hernández
// COP 3503
#include <string>
#include <sstream>
#include "pa2.h" //has Node and LinkedList classes

void displayMenu();
bool checkNumInput(int& num);
bool checkStrInput(string& str);
bool getInt(int& data);

int main(){
	LinkedList freeSpace;

	cout << "Please enter algorithm type to use (Enter \"Worst\" or \"Best\"): ";
	string algType = " ";
	getline(cin, algType);

	int count = 0;
	while(!(checkStrInput(algType))){
		if(count > 0)
			getline(cin,algType);
		if(checkStrInput(algType))
			break;
		cout << "Please enter valid input (\"Worst\" or \"Best\"): ";
		count++;
	}


	int memFunc, progSize;
	string progName;
	while(checkNumInput(memFunc)) { 
		switch(memFunc) {
			case 1: {
				cout << "Program name - " << endl;
				cin >> progName;
				cout << "Program size - " << endl;
				cin >> progSize;
				if(progSize%4 != 0){
					progSize = (progSize/4) + 1;
				}
				else{
					progSize = (progSize/4);
				}
				freeSpace.insert(freeSpace.head, progName, progSize, algType);
				break;
			}
			case 2: {
				cout << "Program name - " << endl;
				cin >> progName;
				freeSpace.killProg(freeSpace.head, progName);
				break;
			}
			case 3: {
				cout << "There are " << freeSpace.numFragments(freeSpace.head) <<  " fragmentation(s)\n";
				break;
			}
			case 4: {
				freeSpace.showList(freeSpace.head);
				break;
			}
		}
	}
}

//uses getInt method to take input and then decides on course of action
bool checkNumInput(int& num){
	if(!(getInt(num))){
		cout << "Please enter input of the correct type (int)" << endl;
		return false;
	}
	if(num == 5){
		return false; // this exits the main while loop
	}
	else if(num > 5 || num < 0){
		cout << "Please enter a number between 1 and 5: " << endl;
		return false;
	}
	return true;
}

//verifies input of type string by changing input to lowercase and comparing
bool checkStrInput(string& str){
	for(int i=0; str[i]; i++){
		str[i] = tolower(str[i]); //converts string to lower case
	}
	if(str.compare("worst") == 0 || str.compare("best") == 0)
		return true;
	else 
		return false;
}

//returns true if input is valid (of type int) and returns false otherwise
bool getInt(int& data){
	displayMenu();
	cout << "\nPlease enter one of the above choices: " << endl;
	cout << "choice - ";
	cin >> data;
	if(cin.fail()){
		cin.clear();
		return false;
	}
	return true;
}

void displayMenu(){
		cout << "\n\n1. Add program" << endl;
		cout << "2. Kill program" << endl;
		cout << "3. Fragmentation" << endl;
		cout << "4. Print memory" << endl;
		cout << "5. Exit\n" << endl;
}






