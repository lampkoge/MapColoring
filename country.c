#include "country.h"	

 
char* country_get_onoma(map *m, int i) {	 
	return m->array[i].onoma;
}

 
int country_add_geitona(map *m, int i, int code) {
	 
	int x;						
	x = m->array[i].gsize;
	m->array[i].geitones[x] = code;
	m->array[i].gsize++;
	return x;
}

 
void country_disable_color(map *m, int i, int color){
	if (color>0 && color<=m->max_colors) {
		m->array[i].choices[color]=0;
	}
}

 
void country_enable_color(map *m, int i, int color) {
	if (color>0 && color<=m->max_colors) {  
		m->array[i].choices[color]=1;
	}
}

 
int country_choices(map *m, int i) {
	int j, count=0;
	if (m->array[i].color>0)	 
		return -1;	

	for (j=1; j <= m->max_colors; j++) {		 
		if (m->array[i].choices[j]==1) 
			count++;
	}
	return count;
}



int country_try_color(map *m, int i) {
	int j;
	
	if (m->array[i].color>0)	
		return -1;
	
	for (j=1; j <= m->max_colors; j++) {
		if (m->array[i].choices[j]==1) 
			return j;
	}	
	return -1;
}

/* debugging */
void country_print_choices(map *m, int i) {
	int j;	
	
	for (j=1; j <= m->max_colors; j++) {	
		if (m->array[i].choices[j]==1) 
			printf("%s ", color_name(j));
	}
}
