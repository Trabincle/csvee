#include "csvee.h"

#include <stdio.h>
#include <stdlib.h>


CSVParser * csv_new(char *file, int max_fields_per_line, size_t max_field_size, char delimiter) {
    int i;
    FILE *try_open_file = fopen(file, "r");

    if (try_open_file == NULL) {
        return NULL;
    }

    CSVParser *new_parser = malloc(sizeof(CSVParser));
    new_parser->csv_file = try_open_file;
    new_parser->max_fields_per_line = max_fields_per_line;
    new_parser->delimiter = delimiter;

    new_parser->fields = malloc(sizeof(*new_parser->fields) * max_fields_per_line);
    for (i = 0; i < max_fields_per_line; i++) {
        new_parser->fields[i] = malloc(sizeof(**new_parser->fields) * max_field_size + 1);
    }

    return new_parser;
}

void csv_free(CSVParser *parser) {
    int i;

    fclose(parser->csv_file);

    for (i = 0; i < parser->max_fields_per_line; i++) {
        free(parser->fields[i]);
    }
    free(parser->fields);
    free(parser);
} 

char csv_parse(CSVParser *parser) {
    // char (int because of EOF) for read file loop
    int c;
    // iterator for buffers
    int i = 0, j = 0;
    // flag for comma-escaping backslash
    int found_backslash = 0;
    // delimiter character
    char delim = parser->delimiter;

    while ((c = fgetc(parser->csv_file)) != EOF) {
        // `!found_backslash` allows for literal backslashes
        if (c == '\\' && !found_backslash) {
            found_backslash = 1;
        }
        
        else {
            if (found_backslash) {
                // insert character literally
                parser->fields[i][j++] = c;
                found_backslash = 0;
            }

            else {
                // next field
                if (c == delim || c == '\n') {
                    parser->fields[i++][j] = '\0';
                    j = 0;
                
                    // unescaped newline char = end of csv line
                    if (c == '\n') {
                        break;
                    }
                }

                else {
                    parser->fields[i][j++] = c;
                }
            }
        }
    }

    if (c == EOF) {
        csv_free(parser);
    }

    return c;
}

char * csv_get_field(CSVParser *parser, int field) {
    return parser->fields[field - 1];
}

