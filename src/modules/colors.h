#ifndef COLORS_H
#define COLORS_H
typedef struct {
    int used[256];
    int used_count;
} ColorList;

ColorList* p_terminal_color_list;
ColorList terminal_color_list;

extern void initColors();
extern int getRandomColor();
extern void setColor(int color);
extern void resetColor();
#endif
