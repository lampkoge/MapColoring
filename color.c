
#include "color.h"

// Πίνακας που αντιστοιχίζει αριθμούς σε ονόματα χρωμάτων
char *colorstr[MAXCOLORS] = {"nocolor", "red", "green", "blue", "yellow", 
                             "orange", "violet", "cyan", "pink", "brown", "grey"};

char *color_name(int color) {
    if (color >= 0 && color < MAXCOLORS) {
        return colorstr[color];
    }
    return "unknown";
}
