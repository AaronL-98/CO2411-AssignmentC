#include <Windows.h>
using namespace std;

const int Success = 0;				// Successful function operation
const int Failure = -1;				// Function operation failure
const int DllNotFound = -2;			// Can't find dll to import
const int DllInvalidFormat = -3;	// Unable to find import function in the dll
const int UnknownError = -4;		// Return when unknown error occurs preventing function operation/ or linking
const int InvalidParameters = -5;	// Invalid parameters for filter input

const int MAX_DATA = 1000;			// The maximum size of the array for loading data 
const int DATE_SIZE = 19;			// The maximum size of a date as a null-terminated string

int LoadMeasurements(const WCHAR* inputFile, int data[], int maxSize);						
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString);	
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize);						 
void displayWconst(const WCHAR* txt);														