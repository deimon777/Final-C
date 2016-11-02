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

char *funcion = NULL;
int funcion_estado = 0;

/****************************************************************/
/*======================================================
Carga la expresión matematica,
Precondición:
Poscondición: La variable "funcion" queda con la expresión matematica cargada.
=====================================================*/
boolean definicion(void) {
  printf("Los métodos de Runge-Kutta son un conjunto de métodos genéricos iterativos, explícitos e implícitos, de resolución numérica de ecuaciones diferenciales ordinarias. Este conjunto de métodos fue inicialmente desarrollado alrededor del año 1900 por los matemáticos C. Runge y M. W. Kutta.\n");
  printf("\nComo se menciono existen varios métodos Runge-Kutta, con este trabajo se busca implementar el método de orden cuarto, generalmente llamada RK4.\n");
  printf("\nEn este programa para el método de Runge Kutta en C, se define una función f(x,y) para calcular la pendiente cada vez que se llama.\n");
  getchar();
  return TRUE;
}


/****************************************************************/
/*======================================================
Carga la expresión matematica,
Precondición:
Poscondición: La variable "funcion" queda con la expresión matematica cargada.
=====================================================*/
boolean cargar_funcion(void) {
  printf("Ingrese una ecuación diferencial del tipo f(x,y), para calcular la pendiente.\n");
  printf("EJ: f(x,y) = (x-y)/(x+y)\n");//borrar
  do {
    printf("Ingresar la función:\n");
    scanf("%*c"); // Limpia posible basura residual
    funcion = read_line(stdin);
    remove_spaces(funcion);
  } while(!strcmp(funcion,""));
  str_lower(funcion);
  printf("La función es: %s\n", funcion);
  //getchar();
  return TRUE;
}

/****************************************************************/
/*======================================================
Muestra a funcion en la salisa estandar si ésta existe.
Precondición: La funcion debe existir.
Poscondición: Muestra la funcion.
=====================================================*/
boolean mostrar_funcion(void) {
  if(!no_existe_funcion((char*)funcion)){
    printf("La función es: %s\n", funcion);
  }
  getchar();
  return TRUE;
}

/****************************************************************/
/*======================================================
Carga los valores para ejecutar el metodo y lo ejecuta.
Precondición:
Poscondición:
=====================================================*/
boolean funcRK_Ejecutar(void) {
  if(no_existe_funcion((char*)funcion)){
    getchar();
    return TRUE;
  }
  lista = crear_lista();
  eliminar_lista(&lista,liberar_punto); //esto lo hace por si ejecuta la funcion dos veces
  funcion_estado = 0;

  double x0,y0,xn,h;
  printf("(x0)\nIntroducir el valor inicial de la función en X.\n");
  printf("Ej: 0\n"); //x
  ingresar_valor(&x0,"x0");

  printf("(y0)\nIntroducir el valor inicial de la función en Y.\n");
  printf("Ej: 2\n"); //y
  ingresar_valor(&y0,"y0");

  printf("(xn)\nIntroducir el valor final de la función, en X, para cerrar el intervalo.\n");
  printf("Ej: 2\n"); //x final
  ingresar_valor(&xn,"xn");

  printf("(h)\nIntroducir el valor con el cual se divide el intervalo.\n");
  printf("Ej: 0.5\n"); //h
  ingresar_valor(&h,"h");

  printf("Ejecutando Metodo\n");
  funcion_estado = runge_kutta(funcion,&lista,x0,y0,xn,h);
  printf("Metodo Terminado\n");

  if(funcion_estado != 0)
  printf("Metodo con error\nRevisar la función");

  getchar();
  return TRUE;
}

/****************************************************************/
/*======================================================

Precondición:
Poscondición:
=====================================================*/
boolean funcRK_Mostrar(void) {
  if(lista_vacia(lista)){
    printf("La lista no existe\nO no se ejecuto el metodo\n");
    getchar();
    return TRUE;
  }
  if(funcion_estado != 0){
    printf("Metodo con error\nRevisar la función");
    getchar();
    return TRUE;
  }

  printf("Los puntos para poder graficar la función son:\n");
  printf("\nX\t\tY\n");
  imprimir_lista(stdout,lista,mostrar_runge_kutta);
  getchar();
  return TRUE;
}

/****************************************************************/
/*======================================================

Precondición:
Poscondición:
=====================================================*/
boolean funcRK_Guardar(void) {
  if(lista_vacia(lista)){
    printf("La lista no existe\nO no se ejecuto el metodo\n");
    getchar();
    return TRUE;
  }
  if(funcion_estado != 0){
    printf("Metodo con error\nRevisar la función");
    getchar();
    return TRUE;
  }

  FILE *fp;
  char * nombre;
  do {
    printf("Ingresar el nombre del archivo:\n");
    scanf("%*c"); // Limpia posible basura residual
    nombre = read_line(stdin);
    remove_spaces(nombre);
  } while(!strcmp(nombre,""));
  strcat(nombre,".txt");
  printf("El nombre del archivo es: %s\n",nombre);
  fp = fopen (nombre, "w");
  fprintf(fp,"\nX\t\tY\n");
  imprimir_lista(fp,lista,mostrar_runge_kutta);
  fclose(fp);
  printf("Metodo Guardado\n");
  free(nombre);
  //getchar();
  return TRUE;
}

/****************************************************************/
/*======================================================
Vuelve al menu principal
Precondición:
Poscondición:
=====================================================*/
boolean volverRK(void) {
  free(funcion);
  eliminar_lista(&lista,liberar_punto);
  free(lista);
  return (boolean)main(); //WARNING //-Wimplicit-function-declaration
}

/******************************/
MENU myMenuRK[] = { //
  { "Definición", definicion }, //
  { "Escribir la función", cargar_funcion }, //
  { "Mostrar función", mostrar_funcion }, //
  { "Ejecutar Metodo", funcRK_Ejecutar }, //
  { "Mostrar en pantalla", funcRK_Mostrar }, //
  { "Guardar en un archivo", funcRK_Guardar }, //
  { "Volver", volverRK }, //
  { NULL }
};

void sub_menu_rk(void){
  forever
  do_menu(myMenuRK, '1');
}
