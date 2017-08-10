// ----------------------------------
// = csvee - simple csv file parser =
// ----------------------------------
#pragma once

#include <stdio.h>

typedef struct s_csvparser {
    FILE *csv_file;
    char **fields;
    int fields_per_line;
    char delimiter;
} CSVParser;

// allocates memory for a new CSVParser struct used by the other functions
CSVParser * csv_new(char *file, int fields_per_line, char delimiter);

// [not for client use] frees memory allocated by csv_new
void csv_free(CSVParser *parser);

// updates the fields member of struct CSVParser, overwriting the previous
// fields with the fields in the following line (each call parses the next line)
char csv_parse(CSVParser *parser);

// returns pointer to field of index <field> in last parsed line of parser <parser>
char * csv_get_field(CSVParser *parser, int field);

