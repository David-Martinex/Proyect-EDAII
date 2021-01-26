#include "Node.h"

NodePtr newNode( int data )
{
    NodePtr n = (NodePtr)malloc( sizeof( Node ) );
    if( n ){
        n->data = data;
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}