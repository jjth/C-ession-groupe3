#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>
#include "../globals.h"
#include "colors.h"

/**
 * Initialise the ColorList array.
 */
void initColors() {
    // Try to make rand() a bit randomized.
    srand(time(NULL));
    // Allocate our color index
    p_terminal_color_list = malloc(sizeof(ColorList));

    p_terminal_color_list->used_count = 0;
    for (int i = 0; i < 256; i++) {
        p_terminal_color_list->used[i] = FALSE;
    }

    // Too dark to be read:
    p_terminal_color_list->used[0] = TRUE;
    p_terminal_color_list->used[16] = TRUE;
    for (int i = 232; i < 236; i++) p_terminal_color_list->used[i] = TRUE;

    // Too white to understand it is colorized:
    p_terminal_color_list->used[15] = TRUE;
    for (int i = 245; i < 256; i++) p_terminal_color_list->used[i] = TRUE;
}

/**
 * Get a random (unused) color between 0 and 255.
 */
int getRandomColor() {
    ColorList colors = *p_terminal_color_list;

    int color = rand()%256;

    // All colors already used, reset the index.
    if (colors.used_count > 255) {
        free(p_terminal_color_list);
        initColors();
    }

    // Search for an unused color.
    while(colors.used[color] == TRUE) {
        color = rand()%256;
    }

    p_terminal_color_list->used_count += 1;
    
    return color;
}

/**
 * Set terminal's color.
 */
void setColor(int color) {
    printf("\x1b[38;5;%dm", color);
}

/**
 * Reset terminal's color.
 */
void resetColor() {
    printf("\x1b[m");
}
