#include <stdio.h>

#include "dyarray_test.h"
#include "array_test.h"
#include "arraylist_test.h"

typedef struct client
{
    u32 id;
    char* name;
}client;

typedef struct server
{
    dyarray clients;
}server;


int main(void)
{   
    //test_dyarray();
    test_arraylist();
}

