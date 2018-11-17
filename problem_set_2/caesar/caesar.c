#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) //Checks if the number of arguments is not equal to 2
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    string cmd = argv[1];
    int k = atoi(cmd);  //Converts the string to an integer

    string s = get_string("plaintext: ");
    int c;
    int p;

    printf("ciphertext: ");
    for (int i = 0; i < strlen(s); i++) //Looping to convert plaintext to ciphertext.
    {
        if (isalpha(s[i])) //If a given char of the string s is alphabetical;
        {
            if (isupper(s[i])) //If the alphabetical char is uppercase
            {
                p = s[i] - 65;
            }
            if (islower(s[i])) //If the alphabetical char is lowercase
            {
                p = s[i] - 97;
            }

            c = (p + k) % 26; //Algorithm of the cryptography

            if (isupper(s[i]))
            {
                printf("%c", c + 65);
            }
            else
            {
                printf("%c", c + 97);
            }

        }
        else
        {
            printf("%c", s[i]);
        }

    }
    printf("\n");
}