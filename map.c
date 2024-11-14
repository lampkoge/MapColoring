#include "map.h"
#include <stdio.h>
#include <string.h>

extern int tries;

// Αρχικοποίηση του χάρτη
void map_init(map *m, int colors) {
    m->size = 0;
    m->max_colors = colors > 0 ? colors : 4; // Προεπιλογή σε 4 αν το colors είναι 0
    for (int i = 0; i < MAXCOUNTRIES; i++) {
        m->array[i].color = 0;
        m->array[i].gsize = 0;
    }
}

// Ανάγνωση δεδομένων από αρχείο και αποθήκευση γειτόνων
void map_read(FILE *f, map *m) {
    char line[1024];

    while (fgets(line, sizeof(line), f)) {
        char *token = strtok(line, " \n");

        // Η πρώτη λέξη είναι η χώρα
        if (token == NULL) continue;

        // Αναζητούμε αν η χώρα υπάρχει ήδη
        int current_country_index = map_get_countryid(m, token);
        if (current_country_index == -1) {
            current_country_index = m->size;
            strcpy(m->array[current_country_index].onoma, token);
            m->array[current_country_index].color = 0;
            m->array[current_country_index].gsize = 0;
            m->size++;
            printf("Added country: %s (index: %d)\n", m->array[current_country_index].onoma, current_country_index);
        } else {
            printf("Country %s already exists (index: %d)\n", m->array[current_country_index].onoma, current_country_index);
        }

        // Εισάγουμε τους γείτονες
        while ((token = strtok(NULL, " \n")) != NULL) {
            int neighbor_index = map_get_countryid(m, token);
            if (neighbor_index == -1) {
                neighbor_index = m->size;
                strcpy(m->array[neighbor_index].onoma, token);
                m->array[neighbor_index].color = 0;
                m->array[neighbor_index].gsize = 0;
                m->size++;
                printf("  Added neighbor country: %s (index: %d)\n", m->array[neighbor_index].onoma, neighbor_index);
            }

            // Ελέγχει αν ο γείτονας είναι ήδη καταχωρημένος για να μην τον προσθέσει διπλά
            int already_neighbor = 0;
            for (int k = 0; k < m->array[current_country_index].gsize; k++) {
                if (m->array[current_country_index].geitones[k] == neighbor_index) {
                    already_neighbor = 1;
                    break;
                }
            }

            if (!already_neighbor) {
                m->array[current_country_index].geitones[m->array[current_country_index].gsize++] = neighbor_index;
                printf("    Neighbor added for %s: %s (neighbor index: %d)\n", 
                       m->array[current_country_index].onoma, m->array[neighbor_index].onoma, neighbor_index);
            } else {
                printf("    Neighbor %s already exists for %s\n", 
                       m->array[neighbor_index].onoma, m->array[current_country_index].onoma);
            }
        }
    }
}






// Επιστρέφει το index μιας χώρας με βάση το όνομά της
int map_get_countryid(map *m, char *onoma) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->array[i].onoma, onoma) == 0) {
            return i;
        }
    }
    return -1;
}

// Αρχικοποίηση διαθέσιμων επιλογών χρώματος για κάθε χώρα
void map_init_choices(map *m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 1; j <= m->max_colors; j++) {
            m->array[i].choices[j] = 1;
        }
    }
}

// Χρωματισμός του χάρτη με αυστηρό αλγόριθμο και εκτυπώσεις αποσφαλμάτωσης
map map_color(map m) {
    for (int i = 0; i < m.size; i++) {
        m.array[i].color = 1;  // Αποδίδει το χρώμα 1 σε κάθε χώρα
        printf("Assigning color %d to country %s\n", m.array[i].color, m.array[i].onoma);  // Εκτύπωση για αποσφαλμάτωση
    }

    // Εκτύπωση για να επιβεβαιώσουμε ότι το χρώμα αποθηκεύτηκε
    printf("\n--- Final Color Assignment ---\n");
    for (int i = 0; i < m.size; i++) {
        printf("Country: %s, Assigned Color: %d\n", m.array[i].onoma, m.array[i].color);
    }
    
    return m;
}



// Εκτύπωση του χάρτη με τις χώρες και τα χρώματά τους
void map_print(FILE *f, map *m) {
    for (int i = 0; i < m->size; i++) {
        fprintf(f, "Country: %s, Color: %s\n", m->array[i].onoma, color_name(m->array[i].color));
    }
}

// Ελέγχει αν ο χάρτης είναι πλήρως χρωματισμένος
int map_is_colored(map *m) {
    for (int i = 0; i < m->size; i++) {
        if (m->array[i].color == 0) {
            return 0; // Επιστρέφει 0 αν κάποια χώρα δεν έχει χρώμα
        }
    }
    return 1; // Επιστρέφει 1 αν όλες οι χώρες έχουν χρώμα
}

// Μετρά τα χρώματα που χρησιμοποιήθηκαν στον χάρτη
int map_colors_used(map *m) {
    int colors_used[MAXCOLORS] = {0}; // Πίνακας για τα χρώματα που χρησιμοποιήθηκαν
    int count = 0;

    for (int i = 0; i < m->size; i++) {
        int color = m->array[i].color;
        if (color > 0 && colors_used[color] == 0) {
            colors_used[color] = 1;
            count++;
        }
    }
    return count;
}

// Εκτύπωση λαθών (π.χ., γειτονικές χώρες με ίδιο χρώμα)
void map_print_errors(map *m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->array[i].gsize; j++) {
            int neighbor_id = m->array[i].geitones[j];
            if (m->array[i].color == m->array[neighbor_id].color && m->array[i].color > 0) {
                fprintf(stderr, "Error: %s and %s have the same color.\n",
                        m->array[i].onoma, m->array[neighbor_id].onoma);
            }
        }
    }
}
