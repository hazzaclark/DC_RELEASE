/* COPYRIGHT (C) HARRY CLARK 2024 */

/* DREAMCAST ROM TOOLKIT */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALTIY REGARDING */
/* ROM FILES AND THEIR UNDERLYING ARCHITECTURE */

/* SUCH IS THE CASE WITH THIS LITTLE TOOL, THIS FILE WILL BE THE */
/* FOR ALL OF THE INFORMATION PERTAINING TOWARDS THE RELEASE DATE ON THE HEADER */

#ifndef ROM
#define ROM

/* SYSTEM INCLUDES */

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(USE_ROM_PRAGMAS)
#define USE_ROM_PRAGMAS
#else
#define USE_ROM_PRAGMAS

#define     MAX_VALUE_LENGTH        128
#define     MAX_ROM_HEADER_SIZE     2048

#define     ROM_ITERATE_POS             2
#define     ROM_ITERATE_OFF             3

typedef struct ROM_OPTION 
{
    char RELEASE_BUFFER[17];
    char* ROM_KEY[MAX_VALUE_LENGTH];
    char* ROM_VALUE[MAX_VALUE_LENGTH];
    char ROM_FILE_HEADER[MAX_ROM_HEADER_SIZE]; 
    const char* RELEASE_DATE;
    size_t ROM_START;
    size_t ROM_END;
    size_t ROM_READ_BUFFER;
    size_t ROM_BYTES;


} ROM_OPTION;

static char* ROM_BUFFER(const char* RELEASE, char* BUFFER);
static void ROM_PROC_OPTION(const char* RELEASE);
static bool IS_VALID_DATE(const char* VALUE);

#endif
#endif
