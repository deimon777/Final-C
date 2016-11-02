#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_extra.h"

/****************************************************************/
/*======================================================
Remplaza una cadena de caracteres por otra.
Precondición: La cadena a reemplazar debe contener la parte para reemplazar.
Poscondición: Devuelve una cadena modificada.
=====================================================*/
char * str_replace(char *orig, char *en, char *con){
  char *result; // the return string
  char *ins;    // the next insert point
  char *tmp;    // varies
  int len_rep;  // length of en
  int len_with; // length of con
  int len_front; // distance between en and end of last rep
  int count;    // number of replacements

  if (!orig)
  return NULL;
  if (!en)
  en = "";
  len_rep = strlen(en);
  if (!con)
  con = "";
  len_with = strlen(con);

  ins = orig;
  for (count = 0; (tmp = strstr(ins, en)); ++count) {
    ins = tmp + len_rep;
  }
  tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

  if (!result)
  return NULL;

  while (count--) {
    ins = strstr(orig, en);
    len_front = ins - orig;
    tmp = strncpy(tmp, orig, len_front) + len_front;
    tmp = strcpy(tmp, con) + len_with;
    orig += len_front + len_rep; // move to next "end of rep"
  }
  strcpy(tmp, orig);

  return result;
}

/****************************************************************/
/*======================================================
Remueve los espacios en blanco de una cadena de caracteres.
Precondición: Devuelve una cadena de caracteres sin espacios en blanco.
Poscondición:
=====================================================*/
void remove_spaces(char *source){
  char *i = source;
  char *j = source;
  while(*j != 0){
    *i = *j++;
    if(*i != ' ')
    i++;
  }
  *i = 0;
}

/****************************************************************/
/*======================================================
Convierte las letras en mayuscula a minuscula.
Precondición: El string tiene que existir.
Poscondición: La cadena de caracteres que devuelve tendra todas sus letras minusculas.
=====================================================*/
void str_lower(char* s){
  for ( ; *s; ++s) *s = tolower(*s);
}

/****************************************************************/
/*======================================================
Lee una linea.
Precondición:
Poscondición: Devuelve la linea completa, con la memoria necesaria.
=====================================================*/
char *read_line(FILE *fp) {
  char *str;
  int ch;
  size_t len = 0;
  size_t size = 10;
  str = realloc(NULL, sizeof(char)*size);//size is start size
  if(!str)return str;
  while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
    str[len++]=ch;
    if(len==size){
      str = realloc(str, sizeof(char)*(size+=16));
      if(!str)return str;
    }
  }
  str[len++]='\0';

  return realloc(str, sizeof(char)*len);
}
