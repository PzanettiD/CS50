// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"



//Creates a node.
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



//Hash function
int hashF(const char *s)
{
    //Takes the first letter of a string.
    //Subtracts 96 to turn lowecase ASCII values into 1 to 26.
    int i = s[0];
    if (islower(s[0]))
    {
        i -= 96;
    }
    //Subtracts 64 to turn uppercase ASCII values into 1 to 26.
    else if (isupper(s[0]))
    {
        i -= 64;
    }

    return i;
}

//Creates a hashtable.
node *hashtable[27] = {NULL};

//Size of the dictionary.
int SIZE;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    //Creates a cursor to iterate over the hashtable.
    node *cursor = hashtable[hashF(word)];

    //While this cursor is not null.
    while (cursor != NULL)
    {
        //Compares the word given by the text and the one in the dictionary.
        //If the words are the same, then return true.
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        //If they arent, keep looking.
        else
        {
            cursor = cursor->next;
        }
    }
    return false;

}




// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //Opens the dictionary file .
    FILE *file = fopen(dictionary, "r");

    //Mallocs space for each index of the hashtable.


    char word[LENGTH + 1];
    //Searches for a string and puts it in a variable "word", until EOF.
    while (fscanf(file, "%s", word) != EOF)
    {
        //Creates a new_node.
        node *new_node = malloc(sizeof(node));

        //Check if malloc succeeded
        //If new_node == NULL, there is no more memory left.
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //If malloc succeeded, then copy the new word found into the new_node.
        else
        {
            strcpy(new_node->word, word);
        }


        //If a branch of the hashtable points to another node.
        if (hashtable[hashF(word)] != NULL)
        {
            //Make the new node point to wathever the head of the hash branch is pointing to.

            new_node->next = hashtable[hashF(word)];

            //Then the head of the hash branch points at the new node.

            hashtable[hashF(word)] = new_node;
        }
        //If a branch of the hashtable does not point to another node.
        else if (hashtable[hashF(word)] == NULL)
        {
            //Make it point to the new_node.

            hashtable[hashF(word)] = new_node;
        }
        //Increase this int to keep track on the size of the dictionary.
        SIZE++;
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //Returns the size of the dictionary.
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 27; i++)
    {
        //Creates a cursor to iterate over the hashtables.
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            //Creates a temporary node, to keep track of the previous cursor position.
            node *temp = cursor;
            //Move the cursor to the next position.
            cursor = cursor->next;
            //Free the temporary node.
            free(temp);
        }
    }
    return true;
}
