#include <Python.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> 

using namespace std;

bool exitBool = false; //Check for exit criteria


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




void menu()
{
	string menuInput; //input var for outside of loops
	string itemInput; //name of item 
	int value; //input var for checking input stream
	int numInput; //input var for inside of loops


	//DISPLAY menu options
	cout << "1 : Display frequency of each item file" << endl;
	cout << "2 : Return specific item frequency" << endl;
	cout << "3 : View histogram of all item frequencies from file" << endl;
	cout << "4 : Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

	getline(cin, menuInput); //GET input



	istringstream iss(menuInput);
	while (iss >> value) {

		//IF user selects 1: show all items and count through python
		if (value == 1) {
			CallProcedure("ItemFrequencyAll");
			cout << endl; //add space
			//cout << "Do: 1" << endl; //DEBUG print loop value
		};

		//IF user selects 2: Search item through Python
		if (value == 2) { 
			cout << "Enter item name to search: " << endl;
			string itemInput; //FIXME add error catch for non-string
			cin >> itemInput;
			int itemFrequency = callIntFunc("ItemFrequencySpecific", itemInput);
			if (itemFrequency != -1) {
				cout << itemInput << " were sold " << itemFrequency << " time(s)." << endl; //add space
			}
			else {
				cout << endl;
			}
			//cout << "Do: 2" << endl; //DEBUG print loop value
		};


		//IF user selects 3: Go to python for compilation/writing of list into file, return to read out and format
		if (value == 3) {
			CallProcedure("ItemFrequencyHisto"); //Generate histogram values
			std::ifstream file; //New input file stream
			string line;
			file.open("frequency.dat", ios::binary);
			if (!file.is_open()) { //Catch if file not open
				cout << "File open error." << endl; //Error message
				return;
			}
			else {
				//cout << "File open." << endl; //DEBUG print statement
				while ( getline(file, line)) { //Read in lines from file
					int subStrOnePos = line.find(' '); //find delineation character
					string subStrOne = line.substr(0, subStrOnePos); //Separate line into substr 
					
					cout << subStrOne << " "; //PRINT out first part of string up to space

					subStrOnePos += 1; //ADVANCE index to after space
					string subStrTwo = line.substr(subStrOnePos); //Get substring after space
					int number = stoi(subStrTwo); //CONVERT second substing to int
					
					cout << setw(number) << setfill('*') << ""; //PRINT out * for value of int number
				
					cout << endl; //PRINT space
				}
				
				
			}

		};

		//IF user selects 4: Exit program
		if (value == 4) { 
			exitBool = true;
			cout << endl; //add space
			//cout << "Do: 4" << endl; //DEBUG print loop value
		};

		if ((value > 4) || (value < 1)) { //IF user inputs number outside of range in menu
			cout << "Error, please enter a valid number from the menu." << endl;
		};
		
		//WAIT for anykey to continue
		system("pause");
		cin.clear(); //EXTRACT and discard input
		cin.ignore(); //CLEAR input
		system("CLS"); //CLEAR screen
		return;
	}

}

void main()
{
	while (not(exitBool)) { //Loop until condition statement is reached, continuous menu
		menu();
	}

}