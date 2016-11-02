#ifndef _LISTA_H
#define _LISTA_H

/*-------------------------------------------------------------------*/
/*                      ESTRUCTURAS DE DATOS                         */
/*-------------------------------------------------------------------*/
typedef void *TipoL;

typedef struct Nodo {
	TipoL info;
  struct Nodo *sig;
} Nodo, *Lista;

/*-------------------------------------------------------------------*/
/*                          CONTRUCTORA                              */
/*-------------------------------------------------------------------*/
Lista crear_lista(void);

/*-------------------------------------------------------------------*/
/*                         MODIFICADORAS                             */
/*-------------------------------------------------------------------*/
void agregar_nodo(Lista *lst, TipoL elem);

/*-------------------------------------------------------------------*/
/*                          ANALIZADORAS                             */
/*-------------------------------------------------------------------*/
int lista_vacia(Lista lst);
int lista_longitud(Lista lst);
void imprimir_lista(FILE *s,Lista lst,void (*f)(FILE *s,TipoL));

/*-------------------------------------------------------------------*/
/*                          DESTRUCTORAS                             */
/*-------------------------------------------------------------------*/
void eliminar_lista(Lista *lst, void (*f)(TipoL));
//void eliminar_lista_simple(Lista *lst);

#endif	/* _LISTA_H */
