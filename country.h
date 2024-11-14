#ifndef COUNTRY_H
#define COUNTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h" // Για το MAXCOLORS

#define MAXSTRING 30
#define MAXCOUNTRIES 300

// Προώθηση δήλωσης της δομής map
struct map_struct;
typedef struct map_struct map;

extern char geitones_names[MAXCOUNTRIES][MAXCOUNTRIES][MAXSTRING];

struct country {
    char onoma[MAXSTRING];
    short int color;
    short int choices[MAXCOLORS];
    short int geitones[MAXCOUNTRIES];
    short int gsize;
};

// Δηλώσεις συναρτήσεων που χρησιμοποιούν τον τύπο map
char* country_get_onoma(map *m, int i);
int country_add_geitona(map *m, int i, int code);
void country_disable_color(map *m, int i, int color);
void country_enable_color(map *m, int i, int color);
int country_choices(map *m, int i);
int country_try_color(map *m, int i);
void country_print_choices(map *m, int i);

#endif // COUNTRY_H


