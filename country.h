#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define MAXSTRING 30
#define MAXCOUNTRIES 300  
#include "color.h"


extern char geitones_names[MAXCOUNTRIES][MAXCOUNTRIES][MAXSTRING];	

 
struct country {
	char onoma[MAXSTRING] ;		 
	short int color;					 
	short int choices[MAXCOLORS];		 
	short int geitones[MAXCOUNTRIES];	
	short int gsize;					 
} ;	
			
 
struct map_struct {
 	struct country array[MAXCOUNTRIES];	 	
	short int size;							 
	short int max_colors;						 
} ;
typedef struct map_struct map;		 


 
char * country_get_onoma(map *m, int i);
 
int country_add_geitona(map *m, int i, int code);									
 
void country_disable_color(map *m, int i, int color);
 
void country_enable_color(map *m, int i, int color);
 
int country_choices(map *m, int i);
 
int country_try_color(map *m, int i);
 
void country_print_choices(map *m, int i);
