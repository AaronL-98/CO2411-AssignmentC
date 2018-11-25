// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#define ASEXPORT
#include "DLL.h"
#include <iostream>
using namespace std;

int Filter(int data[], int count, const WCHAR* parameterString)
{
	cout << "Filter function loaded" << endl;

	return (0);
}