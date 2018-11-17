#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Checks if there is more or less arguments than 2
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    string key = argv[1];
    int n[strlen(key)];
    int i = 0;

    // This loop checks if the argument in the terminal is alphabetical
    for (i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Usage: ./vigenere k\n");

            return 1;
        }
        //Translates the key given by the user to a integer between 0 and 25
        if (isupper(key[i]))
        {
            n[i] = key[i] - 65; //if the key is uppercase
        }
        else if (islower(key[i]))
        {
            n[i] = key[i] - 97; //if the key is lowercase
        }
    }

    int j = 0;

    string s = get_string("plaintext: ");
    int slength = strlen(s);
    int p;
    int c;
    int w = 0;
    printf("ciphertext: ");

    //Loop to cipher the plain text

    for (j = 0; j < slength; j++)
    {
        if (isalpha(s[j])) //If the given character of the string is alphabetical
        {
            //Translates that character to an integer between 0 and 25
            if (isupper(s[j]))
            {

                p = s[j] - 65;   //If its uppercase
            }
            else if (islower(s[j]))
            {

                p = s[j] - 97; //If its lowercase
            }

            //Algorithm to cipher the plaintext
            c = (p + n[(j - w) % strlen(key)]) % 26;

            if (isupper(s[j])) // CHeck if its capital or not
            {
                printf("%c", c + 65); //Prints out the uppercase ciphertext
            }
            else
            {
                printf("%c", c + 97); //Prints out the lowercase ciphertext
            }

        }
        else //If the given character is not alphabetical
        {
            w += 1;
            printf("%c", s[j]); //Just print it the way it was typed
        }


    }
    printf("\n");
}