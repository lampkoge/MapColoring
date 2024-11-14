#include "map.h" 
extern int tries;



void map_init(map *m, int colors) {
	int i,j;
	
	m->size=0;					
	if (colors==0) 				
		m->max_colors=4;		
	else if (colors<MAXCOLORS) 
		m->max_colors=colors;
	else
		m->max_colors=MAXCOLORS-1;	
		
	for (i=0; i<MAXCOUNTRIES; i++) {
		m->array[i].color=0;		
		m->array[i].gsize=0;			
		country_disable_color(m, i, 0);
		for (j=1; j <= m->max_colors; j++) {	
			country_enable_color(m, i, j);		
		}
	}

	return;
}



void map_read(FILE *f, map *m) {  
	char line[1024];
	char s[MAXSTRING];		
	int i;  
	int c; 	
	int w;	
	int j;  
	int color;	
	int x;	
	
	
	i=0;
	while (fgets(line, 1024, f)) {
		c=0;	
		w=0;	
		j=0;
		do {
			sscanf(line+c, "%s", s);
			switch (w) {
				case 0:	 
					color = color_id(s);
					break;
				case 1:  
					 
					strcpy(m->array[i].onoma, s);
					m->array[i].color = color;
					break;
				default:  
					strcpy(geitones_names[i][j],s);
					j++;
					break;
			}
			c = c + strlen(s) + 1;  
			w++;		 
			
			
		} while (c<strlen(line));
		i++;	 
	}
	m->size=i;
	fclose(f);

 
	for(i=0; i<m->size; i++) {
		m->array[i].gsize = 0;
		for (j=0; j<m->size; j++) {
			x = map_get_countryid(m, geitones_names[i][j]);
			if (x>=0) {
				country_add_geitona(m, i, x);				
			}
		}
	}
	return ;
}

 
void map_init_choices(map *m) {
	int i,j,x;
	int color;
	
	for (i=0; i < m->size; i++) {
		if (m->array[i].color == 0 ) {
			for (j=0; j < m->array[i].gsize; j++) {
				x = m->array[i].geitones[j];
				color = m->array[x].color;
				country_disable_color(m, i, color);
			}
		}
	}
	
	
}


 
int map_is_correct(map *m){ 
	int i,j,x;
	int isok = 1;
	
	 
	x=0;
	for (i=0; i<m->size; i++) {
		if (m->array[i].color > x) {
			x = m->array[i].color;
		}
	}
	if (x > m->max_colors) {
		isok = 0;
	}
	
	 	
	for (i=0; i<m->size; i++) {
		for (j=0; j<m->array[i].gsize; j++) {
			x = m->array[i].geitones[j];
			if ((m->array[i].color>0) && (m->array[i].color==m->array[x].color)) {
				isok = 0;
			}
		}
	}
	return isok;
}

 
int map_print_errors(map *m){ 
	int i,j,x;
	int isok = 1;
	
		
	x=0;
	for (i=0; i<m->size; i++) {		
		if (m->array[i].color > x) 
			x = m->array[i].color;
	}
	if (x > m->max_colors) {
		fprintf(stderr, "More than %d colors used.\n", m->max_colors);
		isok = 0;
	}
	
	 
	for (i=0; i<m->size; i++) {
		for (j=0; j<m->array[i].gsize; j++) {
			x = m->array[i].geitones[j];
			if (m->array[i].color>0 && m->array[i].color==m->array[x].color) {
				fprintf(stderr, "%s - %s: Should have different color.\n", country_get_onoma(m, i), country_get_onoma(m,x));
				isok = 0;
			}
		}
	}

	return isok;	
}

 
int  map_is_colored(map *m) {
	int i;
	int isok = 1;
		
 
	for (i=0; i<m->size; i++) {
		if (m->array[i].color == 0) {
			isok = 0;
		}
	}
	
	return isok;
}


 
int map_select_country(map *m) {
	int i,x;
	int min; 
	int max;  
	
	 
	min=-1;	 
	for (i=0; i<m->size; i++) {
		x = country_choices(m,i);
		if (min==-1 && x>0)	{ 
			min = i;
		}
		if (x>0 && x<country_choices(m,min) ) {
			min = i;
		}
	}

	 
	max = min;
	for (i=0; i<m->size; i++) {
		if (country_choices(m,i)==country_choices(m,min)) 
			if (m->array[i].gsize > m->array[max].gsize) 
				max = i;
	}
	
	return max;	
}


 
void map_disable_color(map *m, int i) {
	int j;
	for (j=0; j < m->array[i].gsize; j++) {
		country_disable_color(m, m->array[i].geitones[j], m->array[i].color);
	}
}


 
map map_color(map m) { 
	int i;   
	int j;   
	map tmp;	 
	
	tries++;
		
	while (1) {
		i = map_select_country(&m);	 
		if (i==-1) {
			return m;  
		}
		else {
			j = country_try_color(&m, i);	
			if (j==-1) {
				return m;  
			}
			 
			if (country_choices(&m, i)==1) {
				m.array[i].color = j;
				map_disable_color(&m, i);
			}
			else { 
			
				tmp = m;					
				tmp.array[i].color = j;		 
				map_disable_color(&tmp, i);  
				tmp = map_color(tmp);		 
				if (map_is_correct(&tmp)==1)	 
					return tmp;
				else
					country_disable_color(&m, i, j); 
			}
		}
	}

}


 
int map_get_countryid(map *m, char *onoma) {
	int i;
	for (i=0; i<m->size; i++) {
		if (strcmp(m->array[i].onoma, onoma)==0)
			return i;
	}
	return -1;
}
 
void  map_print(FILE *f, map *m){ 
	int i,j;
	struct country *p;
	int x;
	for (i=0; i<m->size; i++) {
		p = &(m->array[i]);
		fprintf(f, "%s %s", color_name(p->color), p->onoma);
		for (j=0; j<p->gsize; j++) {
			x = p->geitones[j];
			fprintf(f, " %s", m->array[x].onoma);
		}
		fprintf(f,"\n");
	}
	return;
}

 
void  map_print_choices(map *m){ 
	int i;
	struct country *p;

	for (i=0; i<m->size; i++) {
		p = &(m->array[i]);	
		fprintf(stderr, "%s %s ", color_name(p->color), p->onoma);
		if (p->color==0) 
			country_print_choices(m, i);
		fprintf(stderr,"\n");
	}
	return;
}

 
int map_colors_used(map *m) {
	int i, x;
	int a[MAXCOLORS];
	int count;
	
	for (i=0; i<MAXCOLORS; i++)
		a[i]=0;
	
	for (i=0; i<m->size; i++) {
		x = m->array[i].color;
		if ( x > 0) 
			a[x]=1;
	}
	
	count=0;
	for (i=1; i<MAXCOLORS; i++)
		count += a[i];
	
	return count;
}


