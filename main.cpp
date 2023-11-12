#include <iostream>
#include <vector>
#include "AVLTree.h"

// function to check if the ID is valid
bool isValidID(const string& ID){
    if (ID.length() != 8)
        return false;
    bool valid = true;
    for(char i : ID)
    {
        if (isdigit(i))
            valid = true;
        else
        {
            valid = false;
            break;
        }
    }
    return valid;
}


// check if the n is a valid position within the tree
bool isValidN (const string& n){
    bool valid = true;
    for(char i : n){
        if (isdigit(i)) {
            valid = true;
        }else{
            valid = false;
            break;
        }
    }
    return valid;
}


// function to check if the name is valid
bool isValidName (const string& name) {
    bool valid = true;
    for(char i : name){
        if (isalpha(i) || isspace(i)) {
            valid = true;
        }else{
            valid = false;
            break;
        }

    }

    return valid;
}

void parseCommand(string command, AVLTree &gator)
{
    string name;
    int ID;

    // get index of type of command
    int ind = command.find_first_of(' ');

    // get a string for the function to determine which function to perform in if statements
    string function = command.substr(0, ind);

    // delete the beginning part of the command, as we have already used it
    command = command.substr(ind + 1);

    if (function == "insert") {
        // substring command to get rid of first quotation mark
        command = command.substr(1);

        // find position of last quotation mark
        ind = command.find_first_of('\"');

        // get the name for insertion by slicing name out
        name = command.substr(0, ind);

        // get the ID for the insertion by slicing name out
        string stringID = command.substr(ind + 2);

        // check if ID is valid and if name is valid
        if (isValidID(stringID) && isValidName(name)) {
            ID = stoi(stringID);
            Node* newRoot = gator.insert(gator.getRoot(), name, ID);

            // replace root node with new root node that has the new leafs
            gator.setRoot(newRoot);
        }
        else
            // if something is not valid through check methods
            cout << "unsuccessful" << endl;
    }
    else if (function == "search") {
        // if command string starts with "
        if (command[0] == '"') {

            // get name of
            name = command.substr(1, command.length() - 2);

            //the name is valid
            if(isValidName(name)) {

                // search for name and return true if
                gator.searchName(gator.getRoot(), name);
            } else {
                cout << "unsuccessful" << endl;
            }
        }
            // else then it must be an ID
        else {
            // the ID needs to be valid
            if (isValidID(command)){
                ID = stoi(command);
                gator.searchID(gator.getRoot(), ID);
            } else {
                cout << "unsuccessful" << endl;
            }
        }
    }
    else if (function == "remove") {
        if(isValidID(command)){
            ID = stoi(command);
            // check if ID exists within tree
            if(gator.ifIDExists(gator.getRoot(), ID)){
                cout << "successful" << endl;
                // remove from tree
                gator.setRoot(gator.remove(gator.getRoot(), ID));
            } else {
                cout << "unsuccessful" << endl;
            }

        } else {
            cout << "unsuccessful" << endl;
        }
    }
    else if (function == "printInorder") {
        gator.printInorder(gator.getRoot());
        cout << endl;
    }
    else if (function == "printPreorder") {
        gator.printPreorder(gator.getRoot());
        cout << endl;
    }
    else if (function == "printPostorder") {
        gator.printPostorder(gator.getRoot());
        cout << endl;
    }
    else if (function == "printLevelCount") {
        gator.printLevel(gator.getRoot());
    } else if (function == "removeInorder") {
        //the N position should be valid pos in tree
        if(isValidN(command))
        {
            int n = stoi(command);
            gator.setRoot(gator.removeInorder(gator.getRoot(), n));
        }
        else
            cout << "unsuccessful" << endl;
    }
}

int main() {
    AVLTree gator;
    int numCommands;
    cin >> numCommands;
    string line;
    vector<string> listOfCommands;


    // loop through the number of commands inputted
    for (int i = 0; i < numCommands+1; i++)
    {
        // get the line string
        getline(cin, line);
        // push string into list of commands
        listOfCommands.push_back(line);
    }

    // loop through list of commands, but starting at the second command, first is empty
    for(int i = 1; i < listOfCommands.size(); i++)
    {
        string command = listOfCommands[i];

        // run through function to read inputs
        parseCommand(command, gator);
    }
    return 0;
}
