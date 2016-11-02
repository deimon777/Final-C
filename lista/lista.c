#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/****************************************************************/
/*======================================================
Crea una lista.
Precondición:
Poscondición: Devuelve una lista.
=====================================================*/
Lista crear_lista (void){
  return NULL;
}
/****************************************************************/
/*======================================================
Inserta un elemento a la lista.
Precondición:
Poscondición: La lista queda con un elemento nuevo.
=====================================================*/
void agregar_nodo(Lista *lst, TipoL elem){
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  nuevo->info = elem;
  nuevo->sig = NULL;
	// si la lista esta vacia entonces hacemos que p apunte al nuevo nodo
  if (*lst == NULL )
		*lst = nuevo;
	else {
		Nodo* aux = *lst;
			// avanzamos a aux al proximo nodo
		while (aux->sig != NULL ){
			aux = aux->sig;
    }
		// como aux apunta al ultimo entonces su siguiente sera el nuevo nodo
		aux->sig = nuevo;
	}
}
/****************************************************************/
/*======================================================
Devulve una lista vacia
Precondición: La lista debe estar creada.
Poscondición: La lista queda vacia.
=====================================================*/
int lista_vacia(Lista lst){
	return (lst == NULL );
}
/*======================================================
Cuanta la cantidad de nodos que tiene la lista.
Precondición:
Poscondición:
=====================================================*/
int lista_longitud(Lista lst){
	int lg = 0;
	while (lst) {
		lg++;
		lst = lst->sig;
	}
	return lg;
}
/*======================================================
Muestra todos los elementos de la lista.
Precondición:
Poscondición:
=====================================================*/
void imprimir_lista(FILE *s,Lista lst,void (*f)(FILE *,TipoL)){
	while (lst) {
		f(s,lst->info);
		lst = lst->sig;
	}
}
/****************************************************************/
/*======================================================
Borra todos los elementos de la lista l dejándola vacía.
Precondición: La lista debe estar creada.
Poscondición: La lista queda vacia.
=====================================================*/
//void eliminar_lista(Lista *lst){
void eliminar_lista(Lista *lst, void (*f)(TipoL)){
  while (*lst != NULL) {
		Nodo* prox = (*lst)->sig;
		f((*lst)->info);
		free(*lst);
		*lst = prox;
	}
}
