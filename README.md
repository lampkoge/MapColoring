# Map Coloring Project

This project is a map coloring tool that reads data about countries and their neighbors, then assigns colors to each country so that no two neighboring countries share the same color.

## Files

- `main.c` - Main program file
- `map.c` - Functions related to reading and coloring the map
- `country.c` - Functions related to managing country data
- `color.c` - Helper functions for color assignment
- `map.h`, `country.h`, `color.h` - Header files

## Compilation

To compile the project, run:

```bash
make

To run the program, use the following command:
./mapcol -c -i <input_file> -n <number_of_colors>

example:
./mapcol -c -i countries.txt -n 4
