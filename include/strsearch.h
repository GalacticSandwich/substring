/**
    @file strsearch.h
    @author Aaron N. (GalacticSandwich)

    Header containing the definition of the substring search function, which will be defined
    differently depending on the algorithm used.
*/

#ifndef STRSEARCH_H
#define STRSEARCH_H

#include "strings.h"

// check to see if the EOP constant has been defined, and if it has
// set the flag for debug printing to true, or false otherwise
#ifdef _VERBOSE
    #define PRINTING 1
#else
    #define PRINTING 0
#endif

/**
    Some string searching algorithms require the usage of a table of values that
    need to be preprocessed from the substring before any searching takes place. This
    functions does this, and populates an integer array passed via a pointer, using
    whatever substring is passed. The size of the integer array passed must be equal to
    the length of the substring being used to generate the table.

    @param subs the substring to use in the generation of the table
    @param varr the integer array to populate with values
*/
void preprocess( String const* subs, int* varr );

/**
    Searches for an instance of a substring in a larger string, and returns the index
    of the first instance if one exists, and if not, returns -1

    @param str the superstring to search within
    @param subs the substring to look for
    @param pos the starting index to start looking from in the superstring
    @param varr the optional array of integer values used with some algorithms
    @return the index of the first instance of the substring, or -1 if none exists
*/
int findSubstring( String const* str, String const* subs, int pos, int const* varr );

#endif
