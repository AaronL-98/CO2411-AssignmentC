#ifndef ASEXPORT					// Check for ASEXPORT has been defined
#define DLLIMPORTOREXPORT dllimport	// If not define DLL to import
#else
#define DLLIMPORTOREXPORT dllexport // Else define to export
#endif
#include <Windows.h>
using namespace std;

#ifdef __cplusplus	// If used by C++ code, 
extern "C" {		// we need to export the C interface – with no name mangling
#endif

_declspec(DLLIMPORTOREXPORT) int Filter(int data[], int count, const WCHAR* parameterString);

#ifdef __cplusplus	// If used by C++ code, 
}					// end extern "C"
#endif
