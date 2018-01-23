#include <stdio.h>
#include "config.h"
#include "colors.h"

#define SUCCESS "\033[32m[OK]\033[0m\n"
#define ERROR "\033[31m[ERROR]\033[0m\n"

int main(int argc, char* argv[])
{
    int status = 0;
    printf("Testing configuration: ");
    if (test_config() == 0) {
        printf(SUCCESS);
    } else {
        printf(ERROR);
        status = -1;
    }

    printf("Testing colors: ");
    if (test_colors() == 0) {
        printf(SUCCESS);
    } else {
        printf(ERROR);
        status = -1;
    }

    return status;
}
