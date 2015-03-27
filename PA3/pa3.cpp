#include <string>
#include <sstream>
#include <fstream>
#include "pa3.h" //Node and Stack classes


bool isLeftDelim(string input);
string oppDelim(string input);

int main(){

    string line;
    ifstream myinpfile("input.txt");
    if(myinpfile.is_open()){
        while(getline(myinpfile,line)){
            cout << line << endl;
        }
        myinpfile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }

    /* CHECK FOR MATCHING DELIMETERS 
    Stack delims;
    string input = " ";
    while(getline(cin,input) && input != "0"){
        if(isLeftDelim(input)){
            delims.push(input);
        }
        else{
            if(delims.pop().compare(oppDelim(input)) == 0)
                cout << "The delims are balanced!" << endl;
            else
                cout << "The delims are NOT balanced" << endl;
        }
    }
    */


    /* READS IN SEQUENCE OF CHARS AND PRINTS THEM OUT IN REVERSE
    Stack chars;
    string input = " ";
    string newInput = " ";
    cout << "Enter a string" << endl;
    while(getline(cin,input) && input != "0"){
        cout << input.size() << endl;
        for(int i=0; i<input.size(); i++){
            cout << "PUSHING" << endl;
            chars.push(input.substr(i,1));
        }
        newInput = input;
    }

    for(int i=0; i<newInput.size(); i++){
        cout << "POPPING" << endl;
        chars.pop();
    }
    */

    /*
	Stack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    */
}

bool isLeftDelim(string in){
    if(in.compare("{") == 0)
        return true;
    else if(in.compare("[") == 0)
        return true;
    else if(in.compare("(") == 0)
        return true;
    else
        return false;
}

string oppDelim(string in){
    if(in.compare("}") == 0)
        return "{";
    else if(in.compare("]") == 0)
        return "[";
    else if(in.compare(")") == 0)
        return "(";
    else
        return " ";
}




