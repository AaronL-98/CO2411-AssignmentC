// CO2411 Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Filter.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	int myData[MAX_DATA];						// Hold measurments
	int* iPtr = myData;							// Pointer
	int dataSize{ 7 };							// Hold number of measurements
	const WCHAR* DLL{ L"DLL.dll" };				// Filter DLL
	const WCHAR* inFile{ L"inputFile.txt" };	// Input file
	const WCHAR* outFile{ L"outputFile.txt" };	// Output file
	const WCHAR* fParameters{ L"3" };			// Filter parameters 
	
	// Call load measurements and check result
	if (LoadMeasurements(inFile, iPtr, dataSize) == Failure)
	{
		cout << "Unable to Load data file" << endl;			// On Failure (-1)
	}
	else
	{
		cout << "successfully loaded data file" << endl;	// On Success (0)
	}

	// Testing: check input into array
	//for (int i{ 0 }; i < dataSize; ++i)
	//{
	//	cout << *(iPtr + i) << " ";
	//}
	//cout << endl;
	//end

	// Call filter 
	switch (UseFilter(DLL, iPtr, dataSize, fParameters))
	{
		case Failure:			// Return (-1)
		{
			cout << "Failed to load Filter" << endl;
			break;
		}
		case DllNotFound:		// Return (-2)
		{
			cout << "Unable to locate DLL to import" << endl;
			break;
		}
		case DllInvalidFormat:	// Return (-3)
		{
			cout << "Unable to import function in the DLL" << endl;
			break;
		}
		case UnknownError:		// Return (-4)
		{
			cout << "Unable to identify error in loading DLL" << endl;
			break;
		}
		case Success:			// Return (0)
		{
			cout << "Successfully loaded filter function" << endl;
			break;
		}
	}

	// Call save measurements
	if (SaveMeasurements(outFile, iPtr, dataSize) == Failure)
	{
		cout << "Cannot save mesurements to file" << endl;
	}
	else
	{
		cout << "Successfully saved to file" << endl;
	}


	system("pause");	// Allow using input and interaction
    return 0;			// End and close console applicaton
}

