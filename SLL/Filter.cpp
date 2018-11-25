#include "stdafx.h"
#include "Filter.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;

void freeDLL(HINSTANCE& hinstLib);

// Read data from input file into an array
int LoadMeasurements(const WCHAR* inputFile, int data[], int maxSize)
{
	ifstream infile(inputFile); // create file input stream
	
	// test if input file is found
	if (!infile)
	{
		return(Failure);		// Return on failure
	}
	while (!infile.eof())
	{
		infile >> maxSize;		// Store first item as total data length
		for (int i = 0; i < maxSize; ++i)
		{
			infile >> data[i];	// Store measurments to data array
		}
	}

	return(Success);			// Return on success
}

// Link to DLL and filter data array using filter algorithm in the DLL
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString)
{
	typedef int(__cdecl *FPointer)(int d[], int c, const WCHAR* pS);	// Function pointer

	// Get a handle to the DLL module.
	HINSTANCE hinstLib = LoadLibrary(dllName);	// Pointer to DLL and call to open the DLL

	// If the handle is valid, try to get the function address.
	if (hinstLib != NULL)
	{
		//cout << "inside function\n";	// Testing check access
		
		// Set function pointer address to doint at desired DLL function
		FPointer filter = (FPointer)GetProcAddress(hinstLib, "Filter");	

		// If the function address is valid, call the function.
		if (NULL != filter)
		{
			if ((filter)(data, count, parameterString) == 0)
			{
				cout << "Data filter applied" << endl;
			}
			else
			{
				cout << "Data filter unsuccessful" << endl;
			}
			freeDLL(hinstLib);			// Free the DLL module.
			return (Success);			// Return success
		}
		else
		{
			freeDLL(hinstLib);			// Free the DLL module.
			return(DllInvalidFormat);	// Return error
		}
	}
	else
	{
		cout << "cannot connect to DLL library\n"; // Testing 
		return (DllNotFound);			// Return error
	}

	return(UnknownError);				// Return error
}

// Save data in a array to output file
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize)
{
	ofstream outfile(outputFile);	// Create and open outfile stream to output file
	if (!outfile)					// Cannot open file
	{
		exit(1);
		return(Failure);			// Return if failed save
	}

	outfile << maxSize;				// save number of elements

	for (int i = 0; i < maxSize; ++i)
	{
		outfile << " " << data[i];	// Save measurment array
	}

	outfile.close();				// Close the output file stream

	return(Success);				// Return if saved successfully
}

// Display character &/ array 
void displayWconst(const WCHAR* txt)
{
	cout << "***";	// Signify start of character array display

	for (int i = 0; txt[i] != 0; i++)
	{
		cout << (char)(txt[i]);
	}

	cout << "***";	// Signify end of character array display
}

// Free DLL
void freeDLL(HINSTANCE& hinstLib)
{
	BOOL fFreeResult = FreeLibrary(hinstLib);	// free DLL

	// check result
	if (!fFreeResult)
	{
		printf("Unable to unload DLL\n");		// On failure to unload
	}
	else
	{
		printf("DLL unloaded successfully\n");	// On successful unload
	}
		
}