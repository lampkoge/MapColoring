#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#define MAXCOUNTRIES 100  // Μέγιστος αριθμός χωρών
#define MAXCOLORS 11      // Μέγιστος αριθμός χρωμάτων
#define MAXSTRING 50      // Μέγιστο μήκος ονόματος χώρας

// Δομή που αναπαριστά μια χώρα
typedef struct {
    char onoma[MAXSTRING];            // Όνομα της χώρας
    int color;                        // Χρώμα της χώρας
    int geitones[MAXCOUNTRIES];       // Πίνακας με τους δείκτες γειτονικών χωρών
    int gsize;                        // Μέγεθος των γειτόνων (αριθμός γειτόνων)
    int choices[MAXCOLORS];           // Επιλογές χρωμάτων (1 = διαθέσιμο, 0 = μη διαθέσιμο)
} country;

// Δομή που αναπαριστά το χάρτη
typedef struct {
    country array[MAXCOUNTRIES];      // Πίνακας χωρών
    int size;                         // Αριθμός χωρών στον πίνακα
    int max_colors;                   // Μέγιστος αριθμός διαθέσιμων χρωμάτων
} map;

// Δηλώσεις βασικών συναρτήσεων

void map_init(map *m, int colors);
void map_read(FILE *f, map *m);
map map_color(map m);
int map_is_correct(map *m);
void map_print_errors(map *m);
int map_is_colored(map *m);
int map_colors_used(map *m);
void map_print(FILE *f, map *m);
int map_get_countryid(map *m, char *onoma);
void map_init_choices(map *m);  // Προσθήκη της δήλωσης
// Επιστρέφει το όνομα ενός χρώματος με βάση τον αριθμό του χρώματος
char *color_name(int color);

#endif // MAP_H
