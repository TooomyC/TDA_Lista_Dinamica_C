#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "comparacion.h"
#include "ListaDinamica.h"
#include "lista.h"

void intercambiar(void* a, void* b, unsigned tamElem);
Nodo* buscarMenor(Nodo* desde, Cmp cmp);

void crearLista(Lista* pl)
{
    *pl = NULL;
}

int insertarAlInicioLista(Lista* pl, const void* d, unsigned tamElem)
{
    Nodo* nue;

    if((nue = (Nodo*)malloc(sizeof(Nodo))) == NULL || (nue->dato = malloc(tamElem)) == NULL)
    {
        free(nue);
        return FALSO;
    }

    memcpy(nue->dato, d, tamElem);
    nue->tamElem = tamElem;
    nue->sig = *pl;
    *pl = nue;

    return VERDADERO;
}

int insertarAlFinalLista(Lista* pl, const void* d, unsigned tamElem)
{
    while(*pl)
        pl = &(*pl)->sig;

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tamElem);

    if(!nue->dato)
        return SIN_MEM;

    memcpy(nue->dato, d, tamElem);
    nue->tamElem = tamElem;

    nue->sig = NULL;
    *pl = nue;

    return TODO_OK;
}

int insertarEnPosicionLista(Lista* pl, const void* d, unsigned tamElem, unsigned posicion)
{
    int cont = 1;

    while(*pl && cont != posicion)
    {
        pl = &(*pl)->sig;
        cont ++;
    }

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tamElem);

    if(!nue->dato)
        return SIN_MEM;

    memcpy(nue->dato, d, tamElem);
    nue->tamElem = tamElem;

    nue->sig = NULL;
    *pl = nue;

    return TODO_OK;
}

int insertarEnOrdenLista(Lista* pl, const void* d, unsigned tamElem, Cmp cmp, Actualizar actualizar)
{
    while(*pl && cmp(d, (*pl)->dato) > 0) ///"d" TIENE QUE SER MAYOR QUE "dato", POR ESO EL > 0 ///TIENE MAYOR PRIORIDAD LA FLECHA QUE EL PUNTERO. POR ESO SE DESREFENCIO EL PUNTERO, PARA QUE LO EJECUTE PRIMERO.
        pl = &(*pl)->sig; ///AVANZO EL PUNTERO. PARA QUE APUNTE AL PUNTERO SIGUIENTE, DEL NODO DONDE ESTOY.

    if(*pl && cmp(d, (*pl)->dato) == 0) ///SIGNIFICA QUE SON IGUALES LOS DATOS.
    {
        actualizar((*pl)->dato), d); ///SE ACTUALIZA "d", EN BASE AL DATO QUE SE LE PASA POR "*pl->dato".
        return DUPLICADO;
    }

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tamElem);

    if(!nue->dato)
        return SIN_MEM;

    memcpy(nue->dato, d, tamElem);
    nue->tamElem = tamElem;

    nue->sig = *pl; ///(1)
    *pl = nue; ///(2)

    return TODO_OK;
}

int eliminarPrimeroLista(Lista* pl, void* d, unsigned tamElem)
{
    if(!*pl)
        return FALSO;

    Nodo* nae = *pl;

    *pl = nae->sig;

    memcpy(d, nae->dato, MINIMO(nae->tamElem, tamElem)); ///PARA NO PERDER EL DATO "d".

    free(nae->dato);
    free(nae);

    return VERDADERO;
}

int eliminarSegundoLista(Lista* pl, void* d, unsigned tamElem) ///EQUIVALE A eliminarUltimoLista ?
{
    if(*pl == NULL)
        return FALSO;

    while((*pl)->sig)
        pl = &(*pl)->sig;

    memcpy(d, (*pl)->dato, MINIMO(tamElem, (*pl)->tamElem));
    free((*pl)->dato);
    free(*pl);

    *pl = NULL;

    return VERDADERO;
}

int eliminarListaOrdenada(Lista* pl, void* d, unsigned tamElem, Cmp cmp)///LE CARGO EN d, EL CAMPO DE LA CLAVE.
{
   /* if(!*pl)
        return FALSO; ES INNECESARIO. PORQUE SI FUERA FALSO, LA PRIMERA CONDICION DEL WHILE NUNCA SE CUMPLIRIA, POR LO QUE NO ENTRARIA AL CICLO.
   */

    while(*pl && cmp(d, (*pl)->dato) > 0)
        pl = &(*pl)->sig;

    if(!*pl || cmp(d, (*pl)->dato) < 0)
        return FALSO;

    Nodo* nae = *pl; ///(1)
    *pl = nae->sig; ///(2)

    memcpy(d, nae->dato, MINIMO(nae->tamElem, tamElem));

    free(nae->dato);
    free(nae);

    return VERDADERO;
}

int buscarListaOrdenada(Lista* pl, void* d, unsigned tamElem, Cmp cmp)
{
    while(*pl && cmp(d, (*pl)->dato) > 0)
        pl = &(*pl)->sig;

    if(!pl || cmp(d, (*pl)->dato) < 0)
        return FALSO;

    else ///cmp == 0
        return VERDADERO;
}

int buscarLista(Lista* pl, void* d, unsigned tamElem, Cmp cmp)
{
    while(*pl || cmp(d, (*pl)->dato) != 0) ///ENCONTRO EL FIN DE LINEA O EL DATO BUSCADO
        pl = &(*pl)->sig;

    if(!*pl) ///SI LLEGO AL FIN DE LINEA, NO ENCONTRO EL DATO
        return FALSO;

    return VERDADERO;
}

int ordenarLista(Lista* pl, Cmp cmp) ///ORDENAMIENTO (POR SELECCION)
{
    if(!*pl)
        return FALSO;

    Nodo* menor;

    for(Nodo* destinoMenor = *pl; destinoMenor->sig; destinoMenor = destinoMenor->sig)
    {
        menor = buscarMenor(destinoMenor, cmp);
        intercambiar(&destinoMenor->dato, &menor->dato, sizeof(void*)); ///INTERCAMBIA DIRECCION DE PUNTEROS
        intercambiar(&destinoMenor->tamElem, &menor->tamElem, sizeof(unsigned)); ///INTERCAMBIA TAMAÑO DE LOS ELEMENTOS
    }

    return VERDADERO;
}

int listaVacia(const Lista* pl)
{
    return !*pl; ///*pl == NULL
}

int listaLlena(const Lista* pl, unsigned tamElem)
{
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    void *dato = malloc(tamElem);

    free(aux);
    free(dato);

    return aux == NULL || dato == NULL;
}

void vaciarLista(Lista* pl)
{
    while(*pl)
    {
        Nodo* aux = *pl;

        *pl = aux->sig;
        free(aux->dato);
        free(aux);
    }
}

void intercambiar(void* a, void* b, unsigned tamElem)
{
    char aux[tamElem];

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);
}

Nodo* buscarMenor(Nodo* desde, Cmp cmp)
{
    Nodo* menor = desde;
    Nodo* actual = desde->sig;

    while(actual)
    {
        if(cmp(actual->dato, menor->dato) < 0)
            menor = actual;

        actual = actual->sig; ///LO AVANZO AL SIGUIENTE.
    }

    return menor;
}
