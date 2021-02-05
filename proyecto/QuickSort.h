#ifndef QuickSort_INC

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "Roots.h"

void swap( Roots* val1, Roots* val2);

void QuickSort(Roots** list, size_t first, size_t last);

#endif