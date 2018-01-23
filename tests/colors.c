#include <stdio.h>
#include "../src/modules/colors.h"

int test_colors()
{
    initColors();

    if (p_terminal_color_list->used_count != 0) {
        fprintf(stderr, "Unable to reset the color index!\n");
        return -1;
    }

    int color = getRandomColor();

    if (p_terminal_color_list->used_count == 0 || color < 0 || color > 256) {
        fprintf(stderr, "Unable to generate a random color (%d) %d!\n", color, p_terminal_color_list->used_count);
        return -1;
    }

    setColor(color);
    resetColor();

    return 0;
}
