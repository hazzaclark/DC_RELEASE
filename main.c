/* COPYRIGHT (C) HARRY CLARK 2024 */

/* DREAMCAST ROM TOOLKIT */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALTIY REGARDING */
/* ROM FILES AND THEIR UNDERLYING ARCHITECTURE */

/* SUCH IS THE CASE WITH THIS LITTLE TOOL, THIS FILE WILL BE THE */
/* FOR ALL OF THE INFORMATION PERTAINING TOWARDS THE RELEASE DATE ON THE HEADER */

/* NESTED INCLUDES */

#include "ROM.h"

#undef USE_ROM_PRAGMAS

/* ALLOCATE THE DESIGNATED MEMORY FOR THE ROM BUFFER */
/* ASSUME A STACK SIZE OF 16 BYTES TO DISCERN THE SIZE OF THE BUFFER INITIALLY */

/* STRCPY GOVERNS NULL TERMINATION OF CHAR'S BY DEFAULT */

static char* ROM_BUFFER(const char* RELEASE, char* BUFFER)
{
    strcpy(BUFFER, RELEASE + 3); 
    return BUFFER;
}

/* AFTER THE INTIAL ROM STACK INSTANTIATION */
/* THE PROGRAM WILL BEGIN TO SCAN THROUGH THE HEADER TO EVALUATE */ 
/* THE RELEASE DATE BASED ON THE BUFFER */

/* THIS IS DONE BY PROVIDING RELEVANT STACK SPACE FOR THE ROM STRUCTURE */

static void ROM_PROC_OPTION(const char* RELEASE) 
{
    struct ROM_OPTION* ROM_BASE;

    ROM_BASE = malloc(sizeof(ROM_OPTION));

    ROM_BUFFER(RELEASE, ROM_BASE->RELEASE_BUFFER);
    printf("Domestic Release Date: %s\n", ROM_BASE->RELEASE_BUFFER);
}

/* A REALLY SCUFFED CHECK TO DETERMINE WHETHER THERE IS ANY AND ALL */
/* LEGIBLE WHITESPACE IN BETWEEN CHARS */

/* THIS IS BY ASSUMING AN ARBITRARY SIZE RESPECTIVE TO THE RELEASE DATE CHAR */
/* THEN EVALUATING THE LENGTH */

static bool IS_VALID(const char* VALUE) 
{
    size_t INDEX;
    for (INDEX = 0; INDEX < 16; ++INDEX) 
    {
        if (INDEX % ROM_ITERATE_OFF == ROM_ITERATE_POS)
            continue;

        if (!(VALUE[INDEX] == ' ' || (VALUE[INDEX] >= '0' && VALUE[INDEX] <= '9'))) 
        {
            return false; 
        }
    }

    return true; 
}

int main(int argc, char *argv[]) 
{
    struct ROM_OPTION* ROM_BASE;

    /* ASSUME THAT ALL OF THE CORRECT COMMAND LINE ARGS ARE BEING PROVIDED */

    if (argc < 2) 
    {
        printf("Usage: %s <ROM file path>\n", argv[0]);
        return 1;
    }

    FILE *ROM_FILE = fopen(argv[1], "rb");
    if (ROM_FILE == NULL) 
    {
        printf("Error: Unable to open ROM file.\n");
        return 1;
    }

    /* SEEK INTO THE CONTENTS OF THE PROVIDED FILE */
    /* THIS WILL BE UNDER THE GUISE OF US NOT KNOWING WHAT THE DREAMCAST GDI'S */
    /* OFFSET IS TO BEGIN WITH */

    /* FROM THERE, ALLOCATE THE DESIGNATED MEMORY FROM THE STRUCTURE TO ASSERTAIN THE START AND END OFFSETS */

    fseek(ROM_FILE, 0, SEEK_SET);
    ROM_BASE = malloc(sizeof(struct ROM_OPTION));

    ROM_BASE->ROM_BYTES = fread(ROM_BASE->ROM_FILE_HEADER, 1, MAX_ROM_HEADER_SIZE, ROM_FILE);
    
    if (ROM_BASE->ROM_BYTES != MAX_ROM_HEADER_SIZE) 
    {
        printf("Error: Failed to read ROM header.\n");
        fclose(ROM_FILE);
        free(ROM_BASE);
        return 1;
    }

    if(ROM_PROC_OPTION == NULL)
    {
        printf("Error: Could not allocate designated memory for the ROM Header\n", stderr);
        free(ROM_BASE);
        return 1;
    }

    ROM_BASE->ROM_START = 0; 
    ROM_BASE->ROM_END = MAX_ROM_HEADER_SIZE - 16;

    /* ITERATE THROUGH ALL RESPECTIVE ELEMENTS OF THE HEADER */
    /* INITIALLY, THE RELEASE CHAR WILL ACCOUNT FOR A 17 BIT BUFFER TO ACCOMODATE */
    /* INTEGER OVERFLOW */

    for (size_t OFFSET = ROM_BASE->ROM_START; OFFSET <= ROM_BASE->ROM_END; ++OFFSET) 
    {
        char RELEASE[17];
        memcpy(RELEASE, ROM_BASE->ROM_FILE_HEADER + OFFSET, 16);
        RELEASE[16] = '\0';

        if (IS_VALID(RELEASE)) 
        {
            ROM_PROC_OPTION(RELEASE);
            return 0;
        }
    }

    printf("Error: Unable to find a valid release date in the ROM header.\n");

    free(ROM_BASE->ROM_FILE_HEADER);
    free(ROM_BASE);
    return 1;
}
