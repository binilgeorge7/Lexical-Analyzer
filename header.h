#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include<string.h>
#include<ctype.h>

extern char buffer[5000];
extern char *file;


void lexi();
void key(int line, int col, char* word);

int isnum(int line, int col, char* word);
int isfloat_or_double(int line, int col, char* word);


void extract_identifier(char *word, int *i);
void extract_number(char *word, int *i);
void handle_string(int *i, int line, int col);

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define LIGHT_YELLOW "\033[93m"
#define BRIGHT_RED   "\033[91m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_WHITE "\033[97m"
#define LIGHT_CYAN   "\033[96m"
#define ORANGE "\033[38;5;208m"


#endif
