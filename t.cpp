#include <iostream>
#include <stdlib.h>

int main()
{
    char *array  = (char *)malloc(10);
    delete[] array;
}