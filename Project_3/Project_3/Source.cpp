#include <Python.h>
#include <iostream>
#include <Windows.h>
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

void displayMenu() {
	while (true) {
		string parameter; //used to get user input in case 2
		int x; //hold return value of callIntFunc in case 2
		ifstream inputFile; //used to read from freqeuncy.dat in case 3
		string item; //used to read item / quantity pairs from text in case 3
		int quantity;

		
		cout << "1. Do you wish to see all items purchased today, with quantity?\n";
		cout << "2. Do you wish to know how many times a certain item was purchased today?\n";
		cout << "3. Do you wish to see a text based histogram displaying all items purchased today with quantity?\n";
		cout << "4. Do you wish to exit the program?\n";
		cout << "Please respond with 1 2 3 or 4\n";
		char res;
		cin >> res;
		switch (res) {
		case 1:
			CallProcedure("userInput1");
			break;
		case 2:
			cout << "What word do you want to search for?\n";
			
			cin >> parameter;
			x = callIntFunc("userInput2", parameter);
			cout << parameter << " was found " << x << " times!\n";
			break;
		case 3:
			CallProcedure("userInput3"); //execute the python code to populate frequency.dat
			inputFile.open("frequency.dat"); //don't need a "real" path because they are in the same folder

			if (inputFile.is_open()) { //could add error handling for all of the times we open/close files
				while (true) { //infinite loop that breaks once we reach eof for the input
					inputFile >> item; //reading the item, then the quantity
					inputFile >> quantity;

					cout << item << " " << string(quantity, '*') << endl; //output, using a trick to display a char multiple times
					if (inputFile.eof()) { //check if we reached eof
						inputFile.close(); //close our file
						break; //and break if we do
					}
				}
			}
			break;
		case 4:
			cout << "Goodbye!\n";
			return;
			break; 

		default: //the default case is error handling for invalid inputs, ie anything besides 1 2 3 or 3
			cout << "Invalid input, please enter only 1, 2, 3, or 4.\nTry again!\n";
			displayMenu(); //redirect user back to starting prompts
			break;
		}
	}

}


void main()
{
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);
	displayMenu();

}