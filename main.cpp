/*
    thingRanker
    David Vaughan
    11/11/2014
*/


#include <iostream>
#include <set>
#include <list>
#include <string>

using namespace std;


/*
    Object type to be held in the list.
    The label is what the user will see. Index is only for internal use,
    so the objects can be sorted properly.
*/
struct listObject
{
    // Constructor
    listObject(string label)
        : label(label), index(maxIndex++)
    { }

    // Members
    string label;
    int index;

  private:
    static int maxIndex;
};

int listObject::maxIndex = 0;


// Prototypes
void displayList(const list<listObject>& objectList);
void displayHelp();
void quickInsert(list<listObject>& objectList);


// Main
int main()
{
    // The list that will hold all the objects
    list<listObject> objectList;

    // Main loop
    string command = "";
    do
    {
        // Execute the previously-entered command
        if(command == "h")
            displayHelp();
        else if(command == "i")
            quickInsert(objectList);
        else if(command == "")
            { /* do nothing */ }
        else if(command == "q")
            { /* do nothing */ }
        else
            cout << "Invalid command." << endl << endl;

        // Show the list
        displayList(objectList);

        // Prompt for a new command
        cout << "Type 'h' for help and commands." << endl;
        cin >> command;
    }
    while(command != "q");

    return 0;
}


// Function to display the list
void displayList(const list<listObject>& objectList)
{
    // Padding
    cout << endl;

    // Report if the list is empty
    if(objectList.empty())
    {
        cout << "<List is empty>" << endl << endl;
        return;
    }

    // Print out the list
    int count = 0;
    for(list<listObject>::const_iterator it = objectList.begin();
                                         it != objectList.end();  ++it)
    {
        cout << count++ << ": "
             << it->label << endl;
    }
    cout << endl;
}

// Function to display help and commands
void displayHelp()
{
    // Padding
    for(int i = 0; i < 10; ++i)
        cout << endl;

    // Display menu
    cout << "Help and commands:" << endl
         << "h: Print this" << endl
         << "i: Quick insert" << endl
         << "q: Quit" << endl;
}

// Insert objects into the list without sorting
void quickInsert(list<listObject>& objectList)
{
    // Grab items until quit
    string myStr = "";
    do
    {
        // Make a new object from the string, and insert it
        if(myStr != "")
            objectList.push_back(listObject(myStr));

        // Show the list
        displayList(objectList);

        // Prompt for a new item
        cout << "Enter a new item ('/q' to quit):" << endl;
        cin >> myStr;
    }
    while(myStr != "/q");

    cout << endl;
}
