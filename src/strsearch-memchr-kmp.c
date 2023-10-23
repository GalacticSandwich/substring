/**
    @file strsearch-memchr.c
    @author Aaron N. (GalacticSandwich)

    Contains a definition for string searches, defined using the
    C Standard Library Function memchr() in combination with the KMP
    Algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    Initializes the prefix table, containing the shift factors for
    the substring when comparing in the superstring after a match
    from memchr().
*/
void preprocess( String const* subs, int* varr )
{
    // the first prefix value is always zero
    varr[ 0 ] = 0;

    // initialize a variable for the start of the substring to
    // examine potential mutual circumfixes, while using the iterator
    // in the following loop as the variable further along in the substring, 
    // and along the prefix value array
    int bi = 0;

    // cycle through the substring, examine mutual circumfixes leading up to
    // the end of the substring, and update the prefix table values as
    // you go along
    for ( int i = 1; i < subs->len; i++ ) {
        // if the bytes at the two positions match, increment the
        // earlier index and assign that to the table position at
        // the later index
        if ( subs->bytes[ bi ] == subs->bytes[ i ] )
            varr[ i ] = ++bi;
        
        // if they don't match, but the earlier index is not zero, update
        // the earlier index to whatever is at it's position minus one, and
        // decrement the later index to keep it where it is for the next iteration
        else if ( bi > 0 ) {
            bi = varr[ bi - 1 ];
            i--;
        }

        // if they don't match, and the earlier index is zero, set the value
        // at the later index in the table to zero.
        else if ( bi == 0 )
            varr[ i ] = 0;
    }

    if ( PRINTING ) {
        printf( "[substring/strsearch] table: \n" );

        for ( int i = 0; i < subs->len; i++ )
            printf( "\t0x%x\t\'%c\'\t%d\n", subs->bytes[ i ], subs->bytes[ i ], varr[ i ] );
    }
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
        int i = 0;
        while ( i < subs->len ) {
            if ( str->bytes[ i + cpos ] != subs->bytes[ i ] ) {
                mismatch = 1;
                break;
            }

            i++;
        }

        // if no mismatches were found, return the original character index found
        if ( !mismatch )
            return cpos;
        
        // if there was mismatch, set the offset index again and reloop
        offs = cpos + varr[ i ] + 1;
    }

    // return -1 if the end of the string was reached and no matches were found
    return -1;
}