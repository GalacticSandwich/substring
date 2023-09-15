/**
    @file strsearch.h
    @author Aaron N. (GalacticSandwich)

    Header containing the definition of the substring search function, which will be defined
    differently depending on the algorithm used.
*/

#ifndef STRSEARCH_H
#define STRSEARCH_H

#include "strings.h"

/**
    Searches for an instance of a substring in a larger string, and returns the index
    of the first instance if one exists, and if not, returns -1

    @param str the superstring to search within
    @param subs the substring to look for
    @param pos the starting index to start looking from in the superstring
    @return the index of the first instance of the substring, or -1 if none exists
*/
int findSubstring( String const* str, String const* subs, int pos );

#endif
