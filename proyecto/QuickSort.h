#ifndef QuickSort_INC
/**
 * @file QuickSort.h
 * @brief COntiene las funcionas para usar QuickSort.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
/** Para usar Roots*/
#include "Roots.h"

/**
 * @brief funcion que se encargara de intercambiar las Roots de pocicion.
 * 
 * @param val1 Tipo Roots a procesar.
 * @param val2 Tipo Roots a procesar.
 */
void swap( Roots* val1, Roots* val2);

/**
 * @brief Algoritmo QuickSort.
 * 
 * @param list Arreglo de tipo Roots a procesar.
 * @param first Indice del primer elemento del arreglo.
 * @param last Indice del ultimo elemento del arreglo.
 */
void QuickSort(Roots** list, size_t first, size_t last);

#endif