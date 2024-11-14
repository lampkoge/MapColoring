#include "map.h" // Περιλαμβάνει τον πλήρη ορισμό της δομής map

char* country_get_onoma(map *m, int i) {
    return m->array[i].onoma;
}

int country_add_geitona(map *m, int i, int code) {
    int x = m->array[i].gsize;
    m->array[i].geitones[x] = code;
    m->array[i].gsize++;
    return x;
}

void country_disable_color(map *m, int i, int color) {
    if (color > 0 && color <= m->max_colors) {
        m->array[i].choices[color] = 0;
    }
}

void country_enable_color(map *m, int i, int color) {
    if (color > 0 && color <= m->max_colors) {
        m->array[i].choices[color] = 1;
    }
}

 
