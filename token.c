#include "header.h"

char *keywords[] = {"int", "float", "char", "double", "if", "else", "while", "for", "return", "void", "break", "continue", "struct", "typedef", NULL};

void handle_string(int* i, int line, int col)
{
    char word[200];
    int k = 0;

    word[k++] = buffer[*i];
    (*i)++;

    while(buffer[*i] != '"' && buffer[*i] != '\0' && buffer[*i] != '\n')
    {
        word[k++] = buffer[*i];
        (*i)++;

        
    }
    word[k] = '\0';

    if(buffer[*i] == '"')
    {
        word[k++] = buffer[*i];
        word[k] = '\0';

        //printf("%-20s: %s\n", "String Literal", word);
        printf(MAGENTA "%-20s" RESET ": %s\n", "String Literal", word);
    }
    else
    {
        printf(RED"\n%s:%d:%d: error: missing terminating '\"' character\n" RESET, file, line, col);
        exit(1);
    }
}

void extract_identifier(char *word, int *i)
{
    int k = 0;

    while(isalnum(buffer[*i]) || buffer[*i] == '_')  //since identfiers can also star with _
    {
        word[k++] = buffer[*i];
        (*i)++;
    }

    word[k] = '\0';
    (*i)--;      //because loop increments extra
}

void key(int line, int col, char* word)
{

    for(int i = 0; keywords[i] != NULL; i++)
    {
        if(strcmp(word, keywords[i]) == 0) //if word matches with any keyword
        {
            //printf("%-20s: %s\n", "Keyword", word);
            printf(BLUE "%-20s" RESET ": %s\n", "Keyword", word);
            return;
        }
    }
    //printf("%-20s: %s\n", "Identifier", word);  
    printf(CYAN "%-20s" RESET ": %s\n", "Identifier", word); //if word doesnt match with keyword it is an identifier
}

void extract_number(char *word, int *i)
{
    int k = 0;

    while(isalnum(buffer[*i]) || buffer[*i] == '.' || buffer[*i] == 'x' || buffer[*i] == 'X' || buffer[*i] == 'b' || buffer[*i] == 'B')
    {
        word[k++] = buffer[*i];
        (*i)++;
    }

    word[k] = '\0';
    (*i)--;  // decrement i to avoid skipping one character in buffer
}

int isnum(int line, int col, char *word)
{
    int i = 0;

    // HEXADECIMAL
    if(word[0] == '0' && (word[1] == 'x' || word[1] == 'X'))
    {
        if(word[2] == '\0')
        {
            printf(RED"\n%s:%d:%d: error: invalid hexadecimal constant\n"RESET, file, line, col);
            exit(1);
        }

        for(i = 2; word[i] != '\0'; i++)
        {
            if(!isxdigit(word[i]))
            {
                printf(RED"\n%s:%d:%d: error: invalid digit '%c' in hexadecimal constant\n"RESET, file, line, col+i, word[i]);
                exit(1);
            }
        }

        //printf("%-20s: %s\n", "Hex Constant", word);
        printf(BRIGHT_YELLOW "%-20s" RESET": %s \n", "Hex Constant", word);
        return 1;
    }

    // BINARY
    if(word[0] == '0' && (word[1] == 'b' || word[1] == 'B'))
    {
        if(word[2] == '\0')
        {
            printf(RED"\n%s:%d:%d: error: invalid binary constant\n"RESET,file, line, col);
            exit(1);
        }

        for(i = 2; word[i] != '\0'; i++)
        {
            if(word[i] != '0' && word[i] != '1')
            {
                printf(RED"\n%s:%d:%d: error: invalid digit '%c' in binary constant\n"RESET,file, line, col+i, word[i]);
                exit(1);
            }
        }

        printf("%-20s: %s\n", "Binary Constant", word);
        return 1;
    }

    // OCTAL
    if(word[0] == '0' && word[1] != '\0')
    {
        for(i = 1; word[i] != '\0'; i++)
        {
            if(word[i] < '0' || word[i] > '7')
            {
                printf(RED"\n%s:%d:%d: error: invalid digit '%c' in octal constant\n"RESET,file, line, col+i, word[i]);
                exit(1);
            }
        }

        //printf("%-20s: %s\n", "Octal Constant", word);
        printf(LIGHT_CYAN "%-20s"RESET": %s \n", "Octal Constant", word);
        return 1;
    }

    // DECIMAL
    for(i = 0; word[i] != '\0'; i++)
    {
        if(!isdigit(word[i]))
        {
            printf(RED"\n%s:%d:%d: error: invalid integer constant '%s'\n"RESET, file, line, col, word);
            exit(1);
        }
    }

    //printf("%-20s: %s\n", "Integer Constant", word);
    printf(YELLOW "%-20s" RESET ": %s\n", "Integer Constant", word);
    return 1;
}

int isfloat_or_double(int line, int col, char *word)
{
    int i = 0;
    int dot_count = 0;

    if(word[0] == '.' && word[1] == '\0')
    {
        //printf("%s:%d:%d: error: invalid float constant '%s'\n",file, line, col, word);
        printf(RED "\n%s:%d:%d: error: invalid float constant '%s'\n" RESET, file, line, col, word);
        exit(1);
    }

    while(word[i] != '\0')
    {
        if(word[i] == '.')
        {
            dot_count++;
            if(dot_count > 1)
            {
                printf(RED"\n%s:%d:%d: error: invalid float constant '%s'\n"RESET,file, line, col, word);
                exit(1);
            }
        }
        else if(isdigit(word[i]))
        {
            // valid digit
            i++;
            continue;
        }
        else if((word[i] == 'f' || word[i] == 'F') && word[i+1] == '\0')
        {
            //printf("%-20s: %s\n", "Float Constant", word);
            printf(GREEN "%-20s" RESET ": %s\n", "Float Constant", word);
            return 1;
        }
        else
        {
            printf(RED"\n%s:%d:%d: error: invalid suffix '%c' on floating constant\n"RESET,file, line, col+i, word[i]);
            exit(1);
        }

        i++;
    }

    if(dot_count == 1)
    {
        // printf("%-20s: %s\n", "Double Constant", word);
        printf(GREEN "%-20s" RESET ": %s\n", "Double Constant", word);
        return 1;
    }

    printf(RED"\n%s:%d:%d: error: invalid float constant '%s'\n"RESET, file, line, col, word);
    exit(1);
}
