#include <stdio.h>
#include <stdlib.h>

#include <ListaDinamica.h>
#include <lista.h>

int cmpInt(const void* pv1, const void* pv2);

int main(int argc, char* argv[])
{
    Lista numerosL;

    crearLista(&numerosL);

    int d;

    for(int i  = 1; i < argc; i++)
    {
        d = atoi(argv[i]);
        insertarAlFinalLista(&numerosL, &d, sizeof(int));
    }

/*  d = 12;///LE INGRESO EL DATO PARA ELIMINARLO CON LA FUNCION.
    eliminarListaOrdenada(&numerosL, &d, sizeof(int), cmpInt); ///LE PASO LA DIRECCION DE LA LISTA?

    d = 3;
    eliminarListaOrdenada(&numerosL, &d, sizeof(int), cmpInt);

    d = 23;
    eliminarListaOrdenada(&numerosL, &d, sizeof(int), cmpInt);
*/
    ordenarLista(&numerosL, cmpInt);

    while(!listaVacia(&numerosL))
    {
        eliminarPrimeroLista(&numerosL, &d, sizeof(int));
        printf("%d ", d);
    }

    return 0;
}

int cmpInt(const void* pv1, const void* pv2)
{
    int* n1 = (int*)pv1;
    int* n2 = (int*)pv2;

    return *n1 - *n2;
}
