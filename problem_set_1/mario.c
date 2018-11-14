#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do {
        printf("Height:");
        n = get_int();
    }
    while (n < 0 || n > 23);

    int i = 0;
    int a = 0;
    int b = 0;
    int c = 0;

    for(i = 0; i < n; i++){
        for(a = 0; a < n-(i+1); a++){
            printf(" ");
        }
        for(b = 0; b < n-a; b++){
            printf("#");
        }

        printf("  ");

        for(c = 0; c < n-a; c++){
            printf("#");
        }

        printf("\n");
    }



}