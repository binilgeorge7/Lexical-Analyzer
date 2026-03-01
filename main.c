//Binil George
//2-3-2026
//Project: Lexical Analyzer
/*

Itcan identify
    * Keywords and Identifiers
    * Integer constants (decimal, octal, hexadecimal, binary)
    * Float and Double constants
    * String literals and Character constants
    * Operators and Symbols
    * Bracket mismatches
    * Unterminated comments and invalid numeric formats

*/
#include "header.h"

char buffer[5000];
char* file = NULL;
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s <file name>", argv[0]);
        return 0;
    }

    file = argv[1];

    //to open file
    FILE* fptr = fopen(file, "r");
    if(fptr == NULL)
    {
        printf("Error %s does not exist",file);
        return 0;
    }

    //to copy input file to buffer
    int i = 0;
    char ch;
    while((ch = fgetc(fptr)) != EOF && i < (sizeof(buffer)-1))
    {
        buffer[i] = ch;
        i++; 
    }
    buffer[i] = '\0';

    //close file
    fclose(fptr);

    lexi();

    return 0;
}