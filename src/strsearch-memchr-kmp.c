
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    Initializes the prefix table for the KMP, containing the shift factors for
    the substring when comparing in the superstring to find matches when
    memchr() returns a non-null address.
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

/**
    Helper function, performs KMP as an alternative to the bruteforce approach after
    memchr() returns a non-null address

    @param str the superstring to search within
    @param subs the substring to look for
    @param pos the starting index to start looking from in the superstring
    @param varr the optional array of integer values used with some algorithms
    @return the index of the first instance of the substring, or -1 if none exists
*/
int findSubsHelper( String const* str, String const* subs, int pos, int const* varr ) {
    // fetch the string and substring lengths
    int slen = pos + subs->len;
    int sslen = subs->len;

    /* Section 2: Conduct KMP Algorithm */

    // initialize values to go through the haystack (i) and the needle (j) respectively
    int i = pos;
    int j = 0;

    // loop through both strings and search to see if the substring pattern is found
    // anywhere in the superstring, using values from the prefix table to increment
    // across the substring instead of just incrementing by one
    while ( ( slen - i ) >= ( sslen - j ) ) {
        // if the bytes match at both positions in the superstring and substring,
        // increment both indices by one
        if ( str->bytes[ i ] == subs->bytes[ j ] ) {
            i++;
            j++;
        }

        // if we make it to the end of the substring, it means we found a match! and we can
        // return the difference between the two indices to get the index of the match in
        // the superstring
        if ( j == sslen ) { // pattern found at str->bytes[ i - j ]!
            return i - j;
        }

        else if ( i < slen && str->bytes[ i ] != subs->bytes[ j ] ) {
            // if the substring's end has not been reached, set the substring index
            // to its new proper value in the prefix table, if it isn't currently zero
            if ( j )
                j = varr[ j - 1 ];

            // if the substring index is zero, just increment the superstring index
            else
                i++;
        }
    }

    return -1;
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

        // use kmp to loop through the substring segment
        int ind = findSubsHelper( str, subs, cpos, varr );
        
        if ( ind != -1 )
            return ind;

        // if there was mismatch, set the offset index again and reloop
        offs = cpos + 1;
    }

    // return -1 if the end of the string was reached and no matches were found
    return -1;
}