// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int denominator = fraction[2] - '0';  //Takes the denominator of a given fraction.
    int nominator = fraction[0] - '0';   //Takes the nominator of a given fraction.

    if (denominator == 8)
    {
        return nominator;
    }
    if (denominator == 4)
    {
        return nominator * 2;
    }
    if (denominator == 2)
    {
        return nominator * 4;
    }
    return 0; //Returns a value of eights.
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    double octave = note[strlen(note) - 1] - '0'; //Gets the octave and the -'0' is used to convert a char into an int.
    double constant = 1.0 / 12.0; //The constant.
    double freqnum = 0.0; //The frequency of a given note.

    if (note[0] == 'A') //If the first character was A
    {
        freqnum = 440.0;
    }
    if (note[0] == 'B') //If the first character was B
    {
        freqnum = 440.0 * pow(2.0, 2.0 / 12.0);
    }
    if (note[0] == 'G')//If the first character was G
    {
        freqnum = 440.0 / pow(2.0, 2.0 / 12.0);
    }
    if (note[0] == 'F') //If the first character was F
    {
        freqnum = 440.0 / pow(2.0, 4.0 / 12.0);
    }
    if (note[0] == 'E') //If the first character was E
    {
        freqnum = 440.0 / pow(2.0, 5.0 / 12.0);
    }
    if (note[0] == 'D') //If the first character was D
    {
        freqnum = 440.0 / pow(2.0, 7.0 / 12.0);
    }
    if (note[0] == 'C') //If the first character was C
    {
        freqnum = 440.0 / pow(2.0, 9.0 / 12.0);
    }

    if (octave > 4) //If the octave is bigger than 4
    {
        for (int i = 0; i < octave - 4; i++) //It repeats the number of octaves - 4, times.
        {
            freqnum *= (2.0);
        }
    }
    else if (octave < 4) //If the octave is smaller than 4
    {
        for (int j = 0; j < 4 - octave; j++) //It repeats the number 4 - octaves, times.
        {
            freqnum /= (2.0);
        }

    }

    if (note[1] == '#') //Checks for accidentals '#' or 'b'
    {
        freqnum *= pow(2.0, 1.0 / 12.0);
    }
    else if (note[1] == 'b')
    {
        freqnum /= pow(2.0, 1.0 / 12.0);
    }



    return round(freqnum);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }

}
