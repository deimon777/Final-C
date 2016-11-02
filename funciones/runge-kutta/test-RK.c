#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../menu/mydefs.h"
#include "../../menu/menumgr.h"
#include "../../lista/lista.h"
#include "../../extras/string_extra.h"
#include "rungeKutta4.h"
#include "submenu-rungeKutta.h"

Lista lista = NULL;
char funcion[20];
int funcion_estado;

boolean correcto1(void) {
  lista = crear_lista();
  eliminar_lista(&lista,liberar_punto); //esto lo hace por si ejecuta la funcion dos veces
  strcpy(funcion,"(x-y)/(x+y)");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 2;  xn = 2;  h = 0.5;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n",x0,y0,xn,h);
  printf("Ejecutando Metodo\n");
  runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  imprimir_lista(stdout,lista,mostrar_runge_kutta);
  getchar();
  return TRUE;
}

boolean correcto2(void) {
  eliminar_lista(&lista,liberar_punto); //esto lo hace por si ejecuta la funcion dos veces
  strcpy(funcion,"2*x*y");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 1;  xn = 0.5;  h = 0.1;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n",x0,y0,xn,h);
  printf("Ejecutando Metodo\n");
  runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  imprimir_lista(stdout,lista,mostrar_runge_kutta);
  getchar();
  return TRUE;
}

boolean correcto3(void) {
  eliminar_lista(&lista,liberar_punto); //esto lo hace por si ejecuta la funcion dos veces
  strcpy(funcion,"x+y");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 2;  y0 = 4;  xn = 1;  h = 0.1;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n",x0,y0,xn,h);
  printf("Ejecutando Metodo\n");
  runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  imprimir_lista(stdout,lista,mostrar_runge_kutta);
  getchar();
  return TRUE;
}


boolean const_extra(void) {
  strcpy(funcion,"x+y+m");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 2;  xn = 2;  h = 0.5;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n", x0,y0,xn,h);
  funcion_estado = runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  if(funcion_estado != 0)
    printf("Metodo con error\nRevisar la funcion");
  getchar();
  return TRUE;
}

boolean error_parentesis1(void) {
  funcion_estado = 0;
  strcpy(funcion,"(x-y/(x+y)");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 2;  xn = 2;  h = 0.5;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n", x0,y0,xn,h);
  funcion_estado = runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  if(funcion_estado != 0)
    printf("Metodo con error\nRevisar la funcion");
  getchar();
  return TRUE;
}

boolean error_parentesis2(void) {
  funcion_estado = 0;
  strcpy(funcion,"(x-y))/(x+y)");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 2;  xn = 2;  h = 0.5;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n", x0,y0,xn,h);
  funcion_estado = runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  if(funcion_estado != 0)
    printf("Metodo con error\nRevisar la funcion");
  getchar();
  return TRUE;
}


boolean div_cero(void) {
  strcpy(funcion,"(x+y)/(x-x)");
  printf("La función es: %s\n", funcion);
  double x0,y0,xn,h;
  x0 = 0;  y0 = 2;  xn = 2;  h = 0.5;
  printf("x0:%lf, y0=%lf, xn=%lf, h=%lf\n", x0,y0,xn,h);
  funcion_estado = runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");
  if(funcion_estado != 0)
    printf("Metodo con error\nRevisar la funcion");

  getchar();
  return TRUE;
}

boolean bye(void) {
  exit(0);
  return FALSE;
}
/******************************/
MENU myMenu[] = { //
  { "Metodo correcto: f((x-y)/(x+y))", correcto1 }, //
  { "Metodo correcto: f(2*x*y)", correcto2 }, //
  { "Metodo correcto: f(x+y)", correcto3 }, //
  { "Error constante extra", const_extra }, //
  { "Error paréntesis (faltante)", error_parentesis1 }, //
  { "Error paréntesis (sobrante)", error_parentesis2 }, //
  { "División por 0", div_cero }, //
  { "Salir", bye }, //
  { NULL }
};

int main(void){
  forever
  do_menu(myMenu, '1');
}
