#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

typedef struct {
    int hours, minutes;
} Hour;

typedef struct {
    int day, month, year;
} Date;

struct Reserve{
    char *name;
    int type; // type 1: Manutencao 2: Lavagem
    long number;
    Hour hour;
    Date date;
};

#endif
