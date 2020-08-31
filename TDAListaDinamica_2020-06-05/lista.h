#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "comparacion.h"

#define TODO_OK 0
#define DUPLICADO 1
#define SIN_MEM 2

#define FALSO 0
#define VERDADERO 1

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAXIMO(X, Y) ((X) > (Y) ? (X) : (Y))

void crearLista(Lista* pl);

int insertarAlInicioLista(Lista* pl, const void* d, unsigned tamElem);
int insertarAlFinalLista(Lista* pl, const void* d, unsigned tamElem);
int insertarEnPosicionLista(Lista* pl, const void* d, unsigned tamElem, unsigned posicion);
int insertarEnOrdenLista(Lista* pl, const void* d, unsigned tamElem, Cmp cmp, Actualizar actualizar); ///d = DATO.

int eliminarPrimeroLista(Lista* pl, void* d, unsigned tamElem);
int eliminarSegundoLista(Lista* pl, void* d, unsigned tamElem);
int eliminarListaOrdenada(Lista* pl, void* d, unsigned tamElem, Cmp cmp); ///LE CARGO EN d, EL CAMPO DE LA CLAVE.

int buscarListaOrdenada(Lista* pl, void* d, unsigned tamElem, Cmp cmp);
int buscarLista(Lista* pl, void* d, unsigned tamElem, Cmp cmp);

int ordenarLista(Lista* pl, Cmp cmp);
int listaVacia(const Lista* pl);
int listaLlena(const Lista* pl, unsigned tamElem);

void vaciarLista(Lista* pl);

#endif // LISTA_H_INCLUDED
