// ----------------------------------------
// = csvee - simple csv-style file parser =
// ----------------------------------------
#pragma once

#include <stdio.h>

typedef struct s_csvparser {
    FILE *csv_file;
    char **fields;
    int max_fields_per_line;
    char delimiter;
} CSVParser;

// allocates memory for a new CSVParser struct used by the other functions
// 'file' = file to be parsed
// 'max_fields_per_line' = max amount of buffers for fields in a line
// 'max_field_size' = size of buffers
// 'delimiter' = character to be used as field separator
CSVParser * csv_new(char *file, int max_fields_per_line, size_t max_field_size, char delimiter);

// calls fclose on file and frees memory allocated by csv_new
// note: memory used by parser object is automatically freed when EOF is found during call to csv_parse
void csv_free(CSVParser *parser);

// updates the 'fields' member of 'parser', overwriting the previous
// fields with the fields in the following line (each call parses the next line)
char csv_parse(CSVParser *parser);

// returns pointer to field of index 'field' in last parsed line of parser 'parser'
// 0 < 'field' < 'max_fields_per_line' - 1
char * csv_get_field(CSVParser *parser, int field);

