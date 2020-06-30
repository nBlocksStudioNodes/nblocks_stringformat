#include "stringformat.h"
#include <string.h>


nBlock_StringFormat::nBlock_StringFormat(const char * formatString) {
    _format = formatString; // Let's keep a pointer to this constant string
	string_buffer_in[0] = 0; 
	string_buffer_out[0] = 0; 
}

void nBlock_StringFormat::triggerInput(uint32_t inputNumber, uint32_t value) { // inputNumber is ignored
    // Insert the value into the format string, and save it into the string buffer
    sprintf(string_buffer_in, _format, value);
	
	// Includes the null-termination
	// this is required to distinguish between a string of length 0 and
	// data not available, and also ensures the null is copied to output buffer
	available[0] = strlen(string_buffer_in) + 1; 
}
void nBlock_StringFormat::endFrame(void) {
	if (available[0] > 0) {
		// Copy contents to output string
		for (uint32_t i=0; i < available[0]; i++){
			string_buffer_out[i] = string_buffer_in[i];
		}
		// Output contains pointer to string
		output[0] = (uint32_t)(&string_buffer_out);
	}
    return;
}

