/**
 * @file BinarySearch.c
 * @brief Contiene el codigo del metodo BinarySearchR para hacer busqueda binaria recursiva.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/**Para acceder a BinarySearch.h*/
#include "BinarySearch.h"

Roots* BinarySearchR(Roots **list, size_t inf, size_t sup, size_t key) 
{
    size_t mid = (sup + inf) / 2;

    if (list[mid]->weight == key) {
        //Ro_Print( list[mid] );
	    return list[mid];
    }

    if (sup == inf) {
        //printf("\n==>No se encontro\n");
	    return NULL;
    }

    if ( key < list[mid]->weight) {
	    return BinarySearchR(list, inf, mid, key );
    } else {
	    return BinarySearchR(list, mid+1, sup, key );
    }
}