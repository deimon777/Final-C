//#define WIN

#include <stdio.h>
#include <stdlib.h>
#include "menu/mydefs.h"
#include "menu/menumgr.h"
/*AGREGO LOS SUB MENUS*/
#include "funciones/runge-kutta/submenu-rungeKutta.h"

boolean funcRK(void) {
  sub_menu_rk();
  getchar();
  return TRUE;
}

boolean bye(void) {
  exit(0);
  return FALSE;
}

/******************************/
MENU myMenu[] = { //
  { "Metodo Runge-Kutta 4to Orden", funcRK }, //
  { "Salir", bye }, //
  { NULL }
};

int main(void) {
    forever
    do_menu(myMenu, '1');
}
