#include <stdio.h>

#include "dyarray_test.h"
#include "array_test.h"

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
    //test_array();
    
    // server myServer;
    // myServer.clients = dyarray_create(client);

    // dyarray_push(myServer.clients, ((client){.id=0, .name="Mordecai"}));
    // dyarray_push(myServer.clients, ((client){.id=0, .name="Mordecai"}));


}

