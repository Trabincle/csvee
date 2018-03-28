csvee
=====
Sequential CSV-style file parser for the **C** language.

Example usage
-------------
#### file.csv
```
John,24
Mary,19
Mark,21
Courtney,18
```

#### parse.c
```C
#import "csvee.h"

int main(void) {
    CSVParser *parser = csv_new("file.csv", 2, 100, ',');

    while (csv_parse(parser) != EOF) {
        printf("Field 1: %s\n", csv_get_field(parser, 0));
        printf("Field 2: %s\n", csv_get_field(parser, 1));
        putc('\n');
    }
}
```

#### Output
```
Field 1: John
Field 2: 24

Field 1: Mary
Field 2: 19

Field 1: Mark
Field 2: 21

Field 1: Courtney
Field 2: 18

```
