#include "country.h"





void map_init(map *m, int colors);
void map_read(FILE *f, map *m);
void map_init_choices(map *m);

int map_is_correct(map *m);

int map_print_errors(map *m); 

int map_is_colored(map *m);

int map_select_country(map *m);


void map_disable_color(map *m, int i);


map map_color(map m);

int map_get_countryid(map *m, char *onoma);

int map_colors_used(map *m);

void map_print(FILE *f, map *m);

void  map_print_choices(map *m);


