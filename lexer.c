#include "header.h"

void lexi()
{
    //for counting differnt brackets
    int round = 0;    // ()
    int square = 0;   // []
    int curly = 0;    // {}

    int line = 1, col = 0;
    char word[100];

    for(int i = 0; buffer[i] != '\0'; i++)
    {
        char ch = buffer[i];
        col++;
        
        if(ch == '\n')
        {
            line++;
            col = 0;
            continue;
        }

        //to skip spaces
        if(isspace(ch))
        {
            continue;
        }

        //to skip preprocessor #...
        if(ch == '#')
        {
            while(buffer[i] != '\n' && buffer[i] != '\0') 
            {
                i++;
            }
            continue;
        }

        //to skip comments
        if(ch == '/' && buffer[i + 1] == '/')
        {
            i = i + 2;
            while(buffer[i] != '\n' && buffer[i] != '\0')
            {
                i++;
            }
            continue;
        }

        //to skip multiline comment
        if(ch == '/' && buffer[i+1] == '*')
        {
            i += 2; //to skip /* 

            while(buffer[i] != '\0')
            {
                if(buffer[i] == '*' && buffer[i+1] == '/')
                {
                    i++;  // move to '/'
                    break;
                }

                if(buffer[i] == '\n')
                {
                    line++;
                    col = 0;
                }

                i++;
            }

            if(buffer[i] == '\0')  //if multilinr =e comment is not closed using */
            {
                printf(RED"\n%s:%d:%d: error: unterminated comment\n"RESET, file, line, col);
                return;
            }

            continue;
        }


        //to handle string
        if(ch == '"')
        {
            handle_string(&i, line, col);
            continue;
        }

        // Character literal
        if(ch == '\'')
        {
            char temp[4];

            temp[0] = buffer[i];
            temp[1] = buffer[i+1];
            temp[2] = buffer[i+2];
            temp[3] = '\0';

            if(buffer[i+2] != '\'')
            {
                printf(RED "\n%s:%d:%d: error: invalid character constant\n" RESET, file, line, col);
                exit(1);
            }

            printf("%-20s: %s\n", "Char Constant", temp);
            i += 2;
            continue;
        }


        //to idetify identifier or keyword
        if(isalpha(ch))
        {
            extract_identifier(word, &i);  //extract and store to word string
            key(line, col, word);
            continue;
        }

        //to identify number
        if(isdigit(ch) || (ch == '.' && isdigit(buffer[i+1])))
        {
            extract_number(word, &i);
            if(strchr(word, '.'))
            {
                isfloat_or_double(line, col, word);
            }
            else
            {
                isnum(line, col, word);
            }
            continue;
        }

        // Symbols
        if(strchr("(){}[];,", ch))
        {
            if(ch == '(') round++;
            if(ch == ')') round--;

            if(ch == '[') square++;
            if(ch == ']') square--;

            if(ch == '{') curly++;
            if(ch == '}') curly--;

            if(round < 0 || square < 0 || curly < 0)
            {
                printf(RED "\n%s:%d:%d: error: unmatched closing bracket '%c'\n" RESET, file, line, col, ch);
                exit(1);
            }

            //printf("%-20s: %c\n", "Symbol",  ch);
            printf(LIGHT_YELLOW "%-20s"RESET": %c\n", "Symbol", ch);
            continue;
        }

        // Operators
        if(strchr("+-*/=%!<>|&", ch))
        {
            if(buffer[i+1] == ch)   // detect &&, ||, ++, --, **, <<, >>
            {
                //printf("%-20s: %c%c\n","Operator", ch, buffer[i+1]);
                printf(ORANGE "%-20s" RESET": %c%c \n", "Operator", ch, buffer[i+1]);
                i++;
            }
            else if(buffer[i+1] == '=')   // detect  +=, -=, *=, /=, <=, >=, &=, |=
            {
                //printf("%-20s: %c%c\n","Operator", ch, buffer[i+1]);
                printf(ORANGE "%-20s"RESET": %c%c\n", "Operator", ch, buffer[i+1]);
                i++;
            }
            else
            {
                //printf("%-20s: %c\n", "Operator", ch);
                printf(ORANGE "%-20s" RESET": %c \n", "Operator", ch);
            }
            continue;
        }

    }

    //to print missing closing bracket error
    if(round != 0)
    printf(RED "\nError: Missing closing ')'\n" RESET);

    if(square != 0)
        printf(RED "\nError: Missing closing ']'\n" RESET);

    if(curly != 0)
        printf(RED "\nError: Missing closing '}'\n" RESET);
        
}

