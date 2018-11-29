// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);

    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bio;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bio = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Ouput's dimensions update:
    bio.biWidth = bi.biWidth * n;
    bio.biHeight = bi.biHeight * n;

    //Old padding:
    int paddingI = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //New padding:
    int paddingO = (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //ImageSize and file size
    bio.biSizeImage = (bio.biWidth * sizeof(RGBTRIPLE) + paddingO) * abs(bio.biHeight);
    bfo.bfSize = bf.bfSize - bi.biSizeImage + bio.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate n times
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // Add paddingO
            for (int l = 0; l < paddingO; l++)
            {
                fputc(0x00, outptr);
            }

            // Return to the beginning
            if (j < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }

        }

        // Skip over padding, if any
        fseek(inptr, paddingI, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
