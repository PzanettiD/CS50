#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    //Keeps repeating if the number isn't correct
    do
    {
        printf("Height:");
        n = get_int();
    }
    while (n < 0 || n > 23);
    //Variable Table for the loops
    int i = 0;
    int a = 0;
    int b = 0;
    int c = 0;

    //Loops to print out the pyramids

    for (i = 0; i < n; i++)
    {
        for (a = 0; a < n - (i + 1); a++)   //Adds the spaces
        {
            printf(" ");
        }
        for (b = 0; b < n - a; b++)         // Adds the #
        {
            printf("#");
        }

        printf("  ");   //Adds the spaces between the left and right pyramids

        for (c = 0; c < n - a; c++)     //Prints the # for the right pyramid
        {
            printf("#");
        }

        printf("\n");
    }



}