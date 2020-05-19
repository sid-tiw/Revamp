#ifndef _COLORS_H_
#define _COLORS_H_

// Colors used in the command line.
#include <string>
#define string std::string
#define num_of_colors 12

string colors[] = {"red", "green", "yellow", //A basic one-one map
                   "blue", "magenta", "cyan", "white", "gray", "dark red",
                   "dark green", "dark yellow", "brown"};
int ind[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 130};

int get_color(string name)
{
    int i = 0;
    for (int i = 0; i < num_of_colors; i++)
        if (colors[i] == name)
            return ind[i];
    return 7; //default white.
}

#endif