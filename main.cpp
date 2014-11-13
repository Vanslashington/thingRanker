/*
    thingRanker
    David Vaughan
    11/13/2014
*/


#include <iostream>
#include <set>
#include <list>
#include <string>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


// Forward declaration
struct listObject;

// Prototypes
void displayList(const deque<listObject>& objectList);
void displayHelp();
void quickInsert(deque<listObject>& objectList);
bool interactiveComp(const listObject& a, const listObject& b);
void sortedInsert(deque<listObject>& objectList);
void loadFile(deque<listObject>& objectList);
void saveFile(const deque<listObject>& objectList);


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

    /*
        "Less Than" operator
        This operator just calls the interactive compare function. I am
        defining this function mainly so it can be used by STL sort.
    */
    bool operator<(const listObject& other) const
        { return interactiveComp(*this, other); }

    // Members
    string label;
    int index;

  private:
    static int maxIndex;
};

int listObject::maxIndex = 0;


// Main
int main()
{
    // The list that will hold all the objects
    deque<listObject> objectList;

    // Load the saved file
    loadFile(objectList);

    // Main loop
    string command = "";
    do
    {
        // Execute the previously-entered command
        if(command == "h")
            displayHelp();
        else if(command == "qi")
            quickInsert(objectList);
        else if(command == "si")
            sortedInsert(objectList);
        else if(command == "qs")
            sort(objectList.begin(), objectList.end());
        else if(command[0] == 'r')
        {
            stringstream comStream(command);
            char trash;
            int index;
            comStream >> trash >> index;
            objectList.erase(objectList.begin() + index);
        }
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
        getline(cin, command);
    }
    while(command != "q");

    // Save the list to the file
    saveFile(objectList);

    return 0;
}


// Function to display the list
void displayList(const deque<listObject>& objectList)
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
    for(deque<listObject>::const_iterator it = objectList.begin();
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
         << "qi: Quick insert" << endl
         << "si: Sorted insert" << endl
         << "qs: Quick sort" << endl
         << "r #: Remove item" << endl
         << "q: Quit" << endl;
}

// Insert objects into the list without sorting
void quickInsert(deque<listObject>& objectList)
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
        getline(cin, myStr);
    }
    while(myStr != "/q");

    cout << endl;
}

// Interactive comparison operator
bool interactiveComp(const listObject& a, const listObject& b)
{
    // Ask the user where to place the item
    cout << "Is " << a.label
         << " more important than "
         << b.label << "? (y/n)"
         << endl;

    char ans;
    cin >> ans;
    while(ans != 'y' && ans != 'n')
        cout << "Invalid response." << endl;

    return ans == 'y';
}

// Insert and sort objects into sorted list
void sortedInsert(deque<listObject>& objectList)
{
    // Grab items until quit
    string myStr = "";
    do
    {
        // Insert the item
        if(myStr != "")
        {
            listObject myObj(myStr);

            // Binary search for the location
            int beg = 0,
                end = objectList.size() - 1;
            while(beg <= end)
            {
                int mid = (beg + end) / 2;
                listObject thisObj = *(objectList.begin() + mid);
                
                // Compare the objects
                if(interactiveComp(myObj, thisObj))
                    end = mid-1;
                else
                    beg = mid+1;
            }

            // Place the item in the found slot
            objectList.insert(objectList.begin() + beg, myObj);
        }

        // Show the list
        displayList(objectList);

        // Prompt for a new item
        cout << "Enter a new item ('/q' to quit):" << endl;
        getline(cin, myStr);
    }
    while(myStr != "/q");

    cout << endl;
}

// Load the list from a saved file
void loadFile(deque<listObject>& objectList)
{
    // Open the file
    ifstream fin;
    fin.open("listFile");

    // Read items and store in list
    objectList.clear();
    string objLabel;
    while(getline(fin, objLabel))
        objectList.push_back(listObject(objLabel));
}

// Save the list to a file
void saveFile(const deque<listObject>& objectList)
{
    // Open file
    ofstream fout;
    fout.open("listFile");

    // Iterate through the list and write the items to file
    for(deque<listObject>::const_iterator it = objectList.begin();
                                          it != objectList.end(); ++it)
    {
        fout << it->label << endl;
    }
}
