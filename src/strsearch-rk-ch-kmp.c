
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

// the prime number to use in the hashing function
#define PRIME_NUMBER 17

/**
    Hashing function, hashes a string to get an unsigned integer value for 
    the string searching algorithm to use.

    @param str the string to hash
    @param pos the starting position to hash from
    @param len the length to hash up to
    @return a hash value from the row of bytes used
*/
static ulong hash( String const* str, int pos, int len ) {
    // this iteration uses a simple character additive + modulo hash, it adds the ascii value
    // of each character to the hash, multiplied by its position in the string, relative to
    // the initial starting position, before modulo'ing by a selected prime number.

    ulong hashVal = 0;

    int offs = str->len - pos;
    int alen = len > offs ? offs : len; 

    for ( int i = 0; i < alen; i++ )
        hashVal += str->bytes[ i + pos ] * i;

    return hashVal % PRIME_NUMBER;
}

/**
    Initializes the prefix table for KMP, containing the shift factors for
    the substring when comparing in the superstring to find
    matches after two hashes match.
*/
void preprocess( String const* subs, int* varr ) {
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
    Helper function, performs KMP as an alternative to the bruteforce approach after the
    substring and superstring section hashes match

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

int findSubstring( String const* str, String const* subs, int pos, int const* varr ) {
    // fetch the string and substring lengths
    int slen = str->len;
    int sslen = subs->len;

    // fail if the substring length is long than that of the superstring
    if ( sslen > slen )
        return -1;

    // fetch the hash value for the substring
    ulong sshash = hash( subs, 0, sslen );

    for ( int i = pos; i < ( slen - sslen ) + 1; i++ ) {
        // fetch the hash value for the superstring section
        ulong shash = hash( str, i, sslen );

        // check to see if the hashes match
        if ( shash == sshash ) {
            // conduct KMP on the subsection if the hashes match, and return the index
            // if a match is found
            int ind = findSubsHelper( str, subs, i, varr );

            // return the current index if no mismatches were found
            if ( ind > -1 )
                return ind;
        }
    }

    return -1;
}