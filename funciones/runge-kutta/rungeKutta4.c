#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rungeKutta4.h"
#include "../../lista/lista.h"
#include "../../extras/string_extra.h"
#include "../../shunting-yard/shunting-yard.h"

/****************************************************************/
/*======================================================
Ejecuta el metodo Runge-Kutta 4.
Precondición: Tener una expresión matematica y una lista valida.
Poscondición: Devuelve una lista con los valores obtenidos el ejecutar el metodo matematico.
=====================================================*/
int runge_kutta(char *funcion,void *lst,double x0,double y0,double xn,double h){
  double m,m1,m2,m3,m4;
  double x,y;
  x = x0;
  y = y0;
  Status estado = OK;
  PUNTO_RK *pto;

  while(x<xn && estado == OK){
    pto = (PUNTO_RK*)malloc(sizeof(PUNTO_RK));
    char *str_x = (char *)malloc(sizeof(double));
    char *str_y = (char *)malloc(sizeof(double));
    char *t = malloc(sizeof(strlen(funcion)));
    //m1 = f(x0,y0);
    sprintf(str_x,"%lf",x0);
    sprintf(str_y,"%lf",y0);
    t = str_replace(funcion,"x",str_x);
    t = str_replace(t,"y",str_y);
    estado = shunting_yard(t,&m1);

    //m2 = f((x0+h/2.0),(y0+m1*h/2.0));
    sprintf(str_x,"%lf",x0+h/2.0);
    sprintf(str_y,"%lf",y0+m1*h/2.0);
    t = str_replace(funcion,"x",str_x);
    t = str_replace(t,"y",str_y);
    estado = shunting_yard(t,&m2);

    //m3 = f((x0+h/2.0),(y0+m2*h/2.0));
    //sprintf(str_x,"%lf",x0+h/2.0);
    sprintf(str_y,"%lf",y0+m2*h/2.0);
    t = str_replace(funcion,"x",str_x);
    t = str_replace(t,"y",str_y);
    estado = shunting_yard(t,&m3);

    //m4 = f((x0+h),(y0+m3*h));
    sprintf(str_x,"%lf",x0+h);
    sprintf(str_y,"%lf",y0+m3*h);
    t = str_replace(funcion,"x",str_x);
    t = str_replace(t,"y",str_y);
    estado = shunting_yard(t,&m4);

    m  = ((m1+2*m2+2*m3+m4)/6);
    pto->x = x = x+h;
    pto->y = y = y+m*h;

    free(str_x);
    free(str_y);
    free(t);

    agregar_nodo(lst,(PUNTO_RK*)pto);
  }
  if (estado != OK) {
    show_error(estado);
    return estado;
  }
  return EXIT_SUCCESS;
}

/****************************************************************/
/*======================================================
Muestra los valores obtenidos al ejecutar el metodo.
Precondición: Haber ejecutado el metodo.
Poscondición: Muestra en la salida los valores del metodo.
=====================================================*/
void mostrar_runge_kutta(FILE * salida,void *p){
  PUNTO_RK *i = (PUNTO_RK*)p;
  fprintf(salida,"%f\t%f\n",i->x,i->y);
}

/****************************************************************/
/*======================================================
Libera el contenido del punto guardado por el metodo.
Precondición: Haber ejecutado el metodo.
Poscondición:
=====================================================*/
void liberar_punto(void *p){
  PUNTO_RK *p2 = (PUNTO_RK *)p;
  free(p2);
}

/*VALIDAR RK4*/
/****************************************************************/
/*======================================================
Verifica si la funcion esta cargada.
Precondición:
Poscondición: Devuelve un valor de verificación si la función esta creada.
=====================================================*/
int no_existe_funcion(void * f){
  if(f == NULL){
    printf("No existe función\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/****************************************************************/
/*======================================================
Carga en una varaible pasada por referencia el valor ingresado.
Precondición: Tener una forma de ingresar el valor.
Poscondición: La variable pasada queda cargada con el valor.
=====================================================*/
void ingresar_valor(void *v, char *c){
  do {
    printf("Ingresar %s: ",c);
    scanf("%*c"); // Limpia posible basura residual
  } while (1 != scanf("%lf", (double*)v));
}
