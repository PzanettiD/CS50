#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    BYTE buffer[512]; //Sets an array of 512 bytes
    if (argc != 2)    //If there is not 2 arguments on the command line, print an ERROR message and return 1 to main
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r"); //Opens the input file
    if (inptr == NULL) //If there is no input file, print an ERROR message and retur 2 to main
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    char filename[8];
    FILE *img = NULL;
    int i = 0;

    while (fread(buffer, 512, 1, inptr) == 1)  //Reads blocks of 512 bytes
    {
        if (buffer[0] == 0xff &&            // This are conditions to verify if the first 4 bytes started a new JPG file
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (i != 0)         //Checks if this is not the first file opened
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", i);  //Creates a new file
            i++;
            img = fopen(filename, "w");  //Open the new file
        }
        if (i != 0) //You shouldn't write into a file untill the first one is found
        {
            fwrite(buffer, 512, 1, img);
        }

    }
    fclose(inptr);
}