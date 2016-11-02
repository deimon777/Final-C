#ifndef _MENUMGR_H
#define	_MENUMGR_H

#define OPRIMA_UNA_TECLA "Oprima una tecla para continuar."
#define OPCION "Ingrese opcion: "

typedef struct menu {
	char *text;
	boolean (*func)(void);
} MENU;

void do_menu(MENU *p, int begchar);

#endif	/* _MENUMGR_H */
