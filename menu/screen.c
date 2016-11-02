#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"

void clrscr(void) {
	system("clear");
}

int gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	return 0;
}
