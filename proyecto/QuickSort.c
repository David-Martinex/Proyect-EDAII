/**
 * @file QuickSort.c
 * @brief Contiene los codigos a ejecutar de los metodos de QuickSort.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "QuickSort.h"

void swap(Roots* val1, Roots* val2) {
    Roots aux = *val1;
    *val1 = *val2;
    *val2 = aux;
}

void QuickSort( Roots**list, size_t first, size_t last )
{
	size_t x0 = first;
    size_t x1 = last;
    size_t mid = ( first + last )/2;
    int piv = list[ mid ]->weight; // int piv = roots[mid]

    while( x0 <= x1 ){

        while (  list[ x0 ]->weight < piv ) {
            ++x0;
        }
		
        while( list[ x1 ]->weight > piv ){
            --x1;
        }
        if( x0 <= x1 ){
            swap( list[ x0 ], list[ x1 ] );
            ++x0;
            --x1;
        }
    }

	if( first < x1 ){
        QuickSort( list, first, x1 );
    }	
	if(x0 < last ){
        QuickSort( list, x0, last );
    }
}