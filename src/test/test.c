#include <stdio.h>
#include "../libce/memtypes.h"
#include "../libce/containers/array.h"



int main(void)
{   
    array myArray = array_create(int, 10);
    
    int myCoolNum = 10;
    array_set(myArray, 0, myCoolNum);
    array_set(myArray, 1, 83);
    array_set(myArray, 2, 12);
    array_set(myArray, 3, 755);

    for(int i = 0; i < 4; i++)
    {   
        int* num = (array_get(myArray, i));

        printf("myArray[%d] = %d\n", i, *num);
    }

    printf("myArray->length = %lld\n", array_get_length(myArray));
    printf("myArray->stride = %lld\n", array_get_stride(myArray));
    
    myArray = array_resize(myArray, 20);

    puts("===After Resize===");
    printf("myArray->length = %lld\n", array_get_length(myArray));
    printf("myArray->stride = %lld\n", array_get_stride(myArray));

    array_destroy(myArray);
}