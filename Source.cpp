#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
        To call this function, simply pass the function name in Python that you wish to call.
Example:
        callProcedure("printsomething");
Output:
        Python will print on the screen: Hello from python!
Return:
        None
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("PrintMe","Test");
Output:
        Python will print on the screen:
                You sent me: Test
Return:
        100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("doublevalue",5);
Return:
        25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}



void Menu() {

    //initializes variabls for the methods
    int menuLoop = 0;                                                       //Tracks menu loops
    int wordCount = 0;                                                      //Tracks search word frequency
    int itemQty = 0;                                                        //item quantity from frequency.dat
    string searchTerm;                                                      //user input search term
    string itemName;                                                        //item name from frequency.dat
    ifstream fileInput;                                                     

    while (menuLoop != 4) {

        //user menu display
        cout << "1: Calculate the number of times each item appears" << endl;
        cout << "2: Calculate the frequency of a specific item" << endl;
        cout << "3: Create a histogram based on the number of appearances of each item" << endl;
        cout << "4: Quit" << endl;

        cin >> menuLoop;

        //Check if user input is valid. If not, prompt correct input.
        while (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please input a valid selection: ";
            cin >> menuLoop;
        }


        //Switch statement from menu
        switch (menuLoop) {

        //Clears the screen, and calls the Count all python function and displays each item and its frequency
        case 1:
            
            system("CLS");                                         
            
            CallProcedure("CountAll");                      
            
            cout << endl;                           
            
            break;

            //Clears the screen and asks user item to search for
        case 2:

            system("CLS");
            
            cout << "What item would you like to search for?" << endl;
            
            cin >> searchTerm;

            //Calls Python function to return the search item and how many times it was found
            wordCount = callIntFunc("TotalCount", searchTerm);

            //print statment for what was found and the frequency
            cout << endl << searchTerm << ": " << wordCount << endl << endl;

            break;

            //Prints the histogram showing frequency of all items
        case 3:
            system("CLS");                                          
            CallProcedure("HistogramData");           

            fileInput.open("frequency.dat");                  //Opens frequency.dat

            fileInput >> itemName;                            
            fileInput >> itemQty;                        

            //For each line in the file, print a histogram. After every line has been parsed, break.
            while (!fileInput.fail()) {
        
                //Print the item name, then prepare for the histogram
                cout << std::setw(12) << std::left << itemName << std::setw(5);

                //Print itemQty number of asterisks
                for (int i = 0; i < itemQty; i++) {

                    //Print green asterisks in line.
                    cout << std::right << "*";
                }
                //sets next item's name and quantity.
                cout << endl;
                fileInput >> itemName;
                fileInput >> itemQty;
      
            }

            //Close frequency.dat
            fileInput.close();

            cout << endl;

            break;

            //to exit the loop and quit the program
        case 4:
            return;

            //for invalid selection
        default:
            std::cout << "Invalid Selection.";
            std::cout << std::endl;
            break;
        }
    }
}

//Main method that calls the menu method
void main()
{

    Menu();

}