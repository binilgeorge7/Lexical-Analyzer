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


#endif
