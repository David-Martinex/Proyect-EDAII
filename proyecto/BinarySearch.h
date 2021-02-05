#ifndef BinarySearch_INC
/**
 * @file BinarySearch.h
 * @brief Contiene el metodo BinarySearch.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**Para utilizar Roots y sus metodos */
#include "Roots.h"

/**
 * @brief Funcion encargada de realizar una busqueda binaria en busca en busca de algun 
 * Roots con una similitud con key.
 * 
 * @param roots Referencia a nuestro arreglo de Roots.
 * @param inf nos servira para ubicarnos al principio del arreglo.
 * @param sup nos servira para ubicarnos al final del arreglo.
 * @param key Referencia a nuestro valor a buscar.
 * @return Roots* Regresa la ruta con la simulitud en caso de ser encontrada.
 */
Roots* BinarySearchR(Roots** roots, size_t inf, size_t sup, size_t key );

#endif /* ----- #ifndef BinarySearch_INC  ----- */