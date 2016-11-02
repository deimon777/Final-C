#ifndef _RK4_H
#define _RK4_H

typedef struct punto_rk {
	double x;
  double y;
} PUNTO_RK;

int runge_kutta(char *f,void *p,double x0,double y0,double xn,double h);
void mostrar_runge_kutta(FILE * salida,void *p);

void liberar_punto(void* p);

/*VALIDAR RK4*/
int no_existe_funcion(void * f);
void ingresar_valor(void * v, char* c);

#endif	/* _RK_H */
