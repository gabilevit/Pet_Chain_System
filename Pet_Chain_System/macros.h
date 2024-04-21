#ifndef __MACROS__
#define __MACROS__

#include <stdio.h>
#include "FileHelper.h"

#define PRINT_RETURN_NUM(ptr, x, str) {if(!ptr) { puts(str); return x; }}
#define FREE_POINTER(ptr) {free(ptr);}
#define WRITE_INT_TEXT_FILE_PRINT_RETURN(x, ptr, msg, y) {if(!writeIntToTextFile(x,ptr,msg)) { return y;}}
#define WRITE_STRING_TEXT_FILE_PRINT_RETURN(str, ptr, msg, y) {if(!writeStringToTextFile(str,ptr,msg)) { return y;}}
#define WRITE_INT_BINARY_FILE_PRINT_RETURN(x, ptr, msg, y) {if(!writeIntToFile(x,ptr,msg)) { return y;}}
#define WRITE_STRING_BINARY_FILE_PRINT_RETURN(str, ptr, msg, y) {if(!writeStringToFile(str,ptr,msg)) { return y;}}

#endif // !__MACROS__