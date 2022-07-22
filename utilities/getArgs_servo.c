#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int degrees;
    if(argc == 1){
        printf("ERROR: INVALID INPUT - No arguments");
        return -1;
    }else if(argc > 2){
                printf("ERROR: INVALID INPUT - No arguments");

    }
    switch (argc)
    {
    case 1:
        printf("ERROR: INVALID INPUT - No arguments");
        return -1;
    break;

    case 2:
        degrees = strtol(argv[1], NULL, 10);
        if(degrees <0 || degrees > 180){
            printf("ERROR: INVALID INPUT - Please, enter a number between 0 and 180 degrees");
            return -1;
        }
        printf("Degrees: %d\n",degrees);

    
    break;

    default:
        printf("ERROR: INVALID INPUT - Too many arguments");
        return -1;
    }

    return 0;
    
}