#include <stdio.h>

int main(int argc, char **argv){
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
       for(int i = 0;i < argc;i++)
        printf("arg %d : %s\n",i,argv[i]);
    
    break;

    default:
        printf("ERROR: INVALID INPUT - Too many arguments");
        return -1;
    }

    return 0;
    
}