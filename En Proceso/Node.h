/**
 * @file Node.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

typedef struc Node
{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef Node* NodePtr;

NodePtr newNode( int data );
