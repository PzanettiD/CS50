# Questions

## What's `stdint.h`?

Its a header file in which its determined a certain width of a certain type of int.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

This commands are used to determine the specif 'length' of a signed or unsigned integer.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

'BYTE' = 1 byte, 'DWORD' = 4 bytes, 'LONG' = 4 bytes, 'WORD' = 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

In hexadecimal, the first two bytes are respectively, 0x42 and 0x4d.

## What's the difference between `bfSize` and `biSize`?

bfSize refers to the BITMAPFILEHEADER, whereas biSize refers to the BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

If the value of 'biHeight' is negative, then, the buffer of the bitmap starts in the upper-left corner of the image, making it a 'top-down' bitmap, in which the buffer starts at the top and ends at the bottom.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The field biBitCount. In the RGB system, in each pixel there must be 3 bytes (24 bits), one for each color.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

This result may occur if the file doesn't exist.

## Why is the third argument to `fread` always `1` in our code?

The third argument of 'fread' indicates the number of files to read, and, because we only need to read the input file, that number is 1.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

If the value is 3, then we must multiply by the number of bytes per pixerl, 3 pixels x 3 bytes = 9 bytes, wich is not a multiple of 4, and the nearest one is 12, so we must add 3 bytes of padding.

## What does `fseek` do?

Within our file, the fseek function allow us to move our position, just like a cursor.

## What is `SEEK_CUR`?

SEEK_CUR is a argument within the fseek function that indicates the current position.

## Whodunit?

It was Professor Plum with the candlestick in the library.
