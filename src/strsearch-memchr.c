/**
    @file strsearch-memchr.c
    @author Aaron N. (GalacticSandwich)

    Contains a definition for string searches, defined using the
    C Standard Library Function memchr() in combination with a bruteforce
    approach of the substring length upon any character matches.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    This implementation does not require anything on this end to be preprocessed,
    so the function in this context will only set the varr to null, since it won't
    be used
*/
void preprocess( String const* subs, int* varr )
{
    varr = NULL;
}

int findSubstring( String const* str, String const* subs, int pos, int const* varr )
{
    // set the initial offset position to start searching from
    int offs = pos;

    // loop while the offset is less than the string length
    while ( offs < str->len ) {
        // use memchr() to look for an instance of the first substring character
        char* socc = memchr( str->bytes + offs, subs->bytes[ 0 ], str->len - offs );

        // if memchr() returns null, return -1, since no init character was found
        if ( socc == NULL )
            return -1;

        // set the index that the character instance was found at
        int cpos = ( int ) ( socc - str->bytes );

        int mismatch = 0;   // mismatch flag, set to 1 if a mismatch is found

        // loop through the substring and use the bruteforce approach to see if
        // the superstring segment matches the substring, and set the mismatch flag
        // if a character mismatch is found
        for ( int i = 0; i < subs->len; i++ ) {
            if ( str->bytes[ i + cpos ] != subs->bytes[ i ] ) {
                mismatch = 1;
                break;
            }
        }

        // if no mismatches were found, return the original character index found
        if ( !mismatch )
            return cpos;
        
        // if there was mismatch, set the offset index again and reloop
        offs = cpos + 1;
    }

    // return -1 if the end of the string was reached and no matches were found
    return -1;
}