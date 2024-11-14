#ifndef COLOR_H
#define COLOR_H

#define MAXCOLORS 11

extern char *colorstr[MAXCOLORS];
int color_id(char *colorname);
char *color_name(int i);

#endif // COLOR_H
