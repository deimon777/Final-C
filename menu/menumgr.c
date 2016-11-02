#include <stdio.h>
#include "mydefs.h"
#include "screen.h"
#include "menumgr.h"

/*funciones*/
#define XMENU		10
#define YMENU		5
/**/
#define XIN			10
#define YIN			15
/**/
#define XSTATUS		XIN+16
#define YSTATUS		YIN

/*	Static functions	*/
static
unsigned show_menu(MENU *p, int begchar) {
	unsigned i;
	clrscr();
	gotoxy(10, 10);
	for (i = 0; p->text != NULL ; ++p, ++i) {
		gotoxy(XMENU, YMENU + i);
		printf("%c.-%s\n", begchar + i, p->text);
	}
	return i;
}

static
unsigned get_option(unsigned size, int begchar) {
	unsigned opt;

	gotoxy(XIN, YIN);
	printf("%s", OPCION);
	do {
		opt = getchar() - begchar;
		if (opt >= size)
			putchar('\a');
	} while (opt >= size);
	return opt;
}

//static
void sak(void) {
	gotoxy(XSTATUS, YSTATUS);
	printf("%s", OPRIMA_UNA_TECLA);
	getchar();
}

/*	Public functions	*/
void do_menu(MENU *p, int begchar) {
	int size;
	unsigned opt;

	clrscr();
	size = show_menu(p, begchar);
	opt = get_option(size, begchar);
	clrscr();
	if ((*(p + opt)->func)())
		sak();
}
