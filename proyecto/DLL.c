
#include "DLL.h"

static NodePtr newNode( int data )
{
    NodePtr n = (NodePtr) malloc(sizeof( Node ) );
    if( n ){
        n->data = data;
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

static void reset(DLL* this)
{
    this->first = this->last = this->cursor = NULL;
    this->len = 0;
}

DLL* DLL_New()
{
    DLL* list = (DLL*)malloc(sizeof ( DLL ) );
    if( list ){
        reset( list );
    }
    return list;
}

void DLL_Delete( DLL** this )
{
    if( !*this ){
        
        DLL* list = *this;
        while( DLL_Len( list ) != 0 ){
            
            NodePtr next = list->first->next;
            free( list-> first );
            list->first = next;
            --list->len;
        }
        
        free( list );
        *this = NULL;
    }
}

bool DLL_InsertBack( DLL* this, int data )
{
    assert( this );
    
    bool done = false;
    
    NodePtr n = newNode( data );
    if( n ){
        done = true;
        
        if( DLL_IsEmpty( this ) == false ){
            this->last->next = n;
            n->prev = this->last;
            this->last = n;
        }else{
            this->first = this->last = n;
        }
        ++this->len;
    }
    return done;
}

bool DLL_InsertFront( DLL* this, int data )
{
    assert( this );
    
    bool done = false;
    
    NodePtr n = newNode( data );
    if( n ){
        done = true;
        
        if( DLL_IsEmpty( this ) == false ){
            this->first->prev = n;
            n->next = this->first;
            this->first = n;
        }else{
            this->first = this->last = n;
        }
        ++this->len;
    }
    return done;
}

bool DLL_InsertAfter( DLL* this, int data )
{
    assert( this );
    
    bool done = false;
    
    if( DLL_IsEmpty( this ) || this->cursor == this->last ){
        done = DLL_InsertBack( this, data);
    }else{
        NodePtr n= newNode( data );
        if( n ){
            done = true;
            
            n->next = this->cursor->next;
            this->cursor->next->prev = n;
            this->cursor->next = n;
            n->prev = this->cursor;
            ++this->len;
        }
    }
    return done;
}

bool DLL_InsertBefore( DLL* this, int data )
{
    assert( this );
    
    bool done = false;
    
    if( DLL_IsEmpty( this ) || this->cursor == this->first ){
        done = DLL_InsertFront( this, data);
    }else{
        NodePtr n= newNode( data );
        if( n ){
            done = true;
            
            n->prev = this->cursor->prev;
            this->cursor->prev->next = n;
            this->cursor->prev = n;
            n->next = this->cursor;
            ++this->len;
        }
    }
    return done;
}

bool DLL_Remove( DLL* this, int* data_back )
{
    assert( this );
     
    bool done = false;
     
    if( !DLL_IsEmpty( this ) && NULL != this->cursor ){
        done = true;
         
        *data_back = this->cursor->data;
         
        NodePtr left = this->cursor->prev;
        NodePtr rigth = this->cursor->next;
        free( this->cursor );
         
        if( left == NULL && rigth == NULL ){
            reset( this );
        }else{
            this->cursor = left;
            this->cursor->next = rigth;
            rigth->prev = this->cursor;
            --this->len;
        }
    }
    return done;
}

bool DLL_RemoveFront( DLL* this, int* data_back )
{
    assert( this );
    
    bool done = false;
    
    if( !DLL_IsEmpty( this ) ){
        done = true;
        
        *data_back = this->first->data;
        
        NodePtr tmp = this->first->next;
        free( this->first );
        this->first = tmp;
        
        if( NULL != this->first ){
            this->first->prev = NULL;
            --this->len;
        }else{
            reset( this );
        }
    }
    return done;
}

bool DLL_RemoveBack( DLL* this, int* data_back )
{
    assert( this );
    
    bool done = false;
    
    if( !DLL_IsEmpty( this ) ){
        done = true;
        
        *data_back = this->last->data;
        
        NodePtr tmp = this->last->prev;
        free( this->last );
        this->last = tmp;
        
        if( NULL != this->last ){
            this->last->next = NULL;
            --this->len;
        }else{
            reset( this );
        }
    }
    return done;
}

bool DLL_RemoveAfter( DLL* this, int* data_back )
{
    assert( this );
    
    bool done = false;
       //lista no vacia              y existe un nodo a la derecha y el cursor no es NULL 
    if(DLL_IsEmpty( this ) == false && this->cursor != this->last && this->cursor != NULL ){
        done = true;    
        NodePtr tmp1 = this->cursor->next;
        *data_back = tmp1->data;
        
        NodePtr tmp2 = tmp1->next;
        free( tmp1 );
        this->cursor->next = tmp2;
        
        if( tmp2 != NULL ){
            tmp2->prev = this->cursor;
        }
    }
    
    return done;
}

bool DLL_RemoveBefore( DLL* this, int* data_back )
{
    assert( this );
    
    bool done = false;
       //lista no vacia              y existe un nodo a la Izquierda y el cursor no es NULL 
    if(DLL_IsEmpty( this ) == false && this->cursor != this->first && this->cursor != NULL ){
        done = true;    
        NodePtr tmp1 = this->cursor->prev;
        *data_back = tmp1->data;
        
        NodePtr tmp2 = tmp1->prev;
        free( tmp1 );
        this->cursor->prev = tmp2;
        
        if( tmp2 != NULL ){
            tmp2->next = this->cursor;
        }
    }
    
    return done;
}

size_t DLL_Len( DLL* this )
{
    return this->len;
}

bool DLL_IsEmpty( DLL* this )
{
    assert( this );
    return this->first == NULL;
}

void DLL_MakeEmpty( DLL* this )
{
    assert( this );
    while( NULL  != this->first ){
        NodePtr tmp = this->first->next;
        free( this->first );
        this->first = tmp;
    }
    reset( this );
}

bool DLL_Peek( DLL* this, int* data_back )
{
    assert( this );
    *data_back = this->cursor->data;
}

void DLL_CursorFirst( DLL* this )
{
    assert( this );
    this->cursor = this->first;
}

void DLL_CursorLast( DLL* this )
{
    assert( this );
    this->cursor = this->last;
}

void DLL_CursorNext( DLL* this )
{
    assert( this );
    if( this->cursor != NULL ){
        this->cursor = this->cursor->next;
    }
}

void DLL_CursorPrev( DLL* this )
{
    assert( this );
    if( this->cursor != NULL ){
        this->cursor = this->cursor->prev;
    }
}

bool DLL_FindIf( DLL* this, int key )
{
    assert( this );
    
    bool found = false;
    
    for( NodePtr it = this->first; it != NULL && found == false; it = it->next ){
        if( key == it->data ){
            found = true;
        }
    }
    return found;
}

bool DLL_Search( DLL* this, int key )
{
    assert( this );
    
    bool found = false;
    
    for( NodePtr it = this->first; it != NULL && found == false; it = it->next ){
        if( key == it->data ){
            this->cursor = it;
            found = true;
        }
    }
    return found;
}

void DLL_Traverse( DLL* this, void (*pfun)( int ) )
{
    assert( this );
    
    for( NodePtr it = this->first; it != NULL; it = it->next ){
        pfun( it->data );
    }
}
