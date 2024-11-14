#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"	 

 
char *colorstr[11] = {"nocolor", "red", "green", "blue", "yellow", "orange",
                    "violet", "cyan", "pink", "brown", "grey"};         

char geitones_names[MAXCOUNTRIES][MAXCOUNTRIES][MAXSTRING];
 
int tries=0;



 
int main(int argc, char *argv[]) {
	map m;
	int i, n;
	FILE *inputfile=stdin; 	 	
	int map_check=0;	 
	int map_colors=0;	 
	
	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "-c")==0) {
			map_check = 1;
		}		
		else if ( (strcmp(argv[i], "-i")==0) && ((i+1)<argc) ) {
			inputfile = fopen(argv[i+1], "r");
			if (!inputfile) {
				fprintf(stderr, "Cannot open file %s.\n" , argv[i+1]);
				exit(1);
			}
			i++;
		}
		else if ( (strcmp(argv[i], "-n")==0) && ((i+1)<argc) ) {
			n = atoi(argv[i+1]);
			if (n>0) {
				map_colors = n;
			}
			else {
				fprintf(stderr, "Invalid <colornum> %s.\n", argv[i+1]);
				exit(1);
			}
			i++;
		}
		else {
			fprintf(stderr, "Usage: mapcol -c -i <filename> -n <colornum>\n");
			fprintf(stderr, "\t <filename> : input file\n");
			fprintf(stderr, "\t <colornum> : number of color to use\n");
			exit(1);
		}

		
	}

	/* fprintf(stderr, "Initializing...");		 */
	map_init(&m, map_colors);
	/* fprintf(stderr, "Reading...");		 */
	map_read(inputfile, &m);
	/* fprintf(stderr, "Initializing choices...");		 */
	map_init_choices(&m);
	/* fprintf(stderr, "Coloring..."); */
	
	if(map_check==1) {			 
		map_print(stdout, &m);		 
		map_print_errors(&m);		 
	}
	else {					 
		m = map_color(m);			 
		map_print(stdout, &m);	 
		map_print_errors(&m);		 
		
		if (map_is_colored(&m)==0)	 
			fprintf(stderr, "Not enough colors\n");
			
			
		else {						 
			fprintf(stderr, "\nMap colored succesfully! %d recursion needed. ", tries);
			n = map_colors_used(&m);
			if (n<m.max_colors)
				fprintf(stderr, "ONLY ");
			else 
				fprintf(stderr, "All ");
			fprintf(stderr, "%d colors used.", n);			
		}
		
	}
	
	
	return 0;
}
