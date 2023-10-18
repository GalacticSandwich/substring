
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

// the prime number to use in the hashing function
#define PRIME_NUMBER 101
// the base used for the rolling hash
#define BASE_NUMBER 256

/**
    Hashing function, hashes a string to get an unsigned integer value for 
    the string searching algorithm to use.

    @param str the string to hash
    @param pos the starting position to hash from
    @param len the length to hash up to
    @return a hash value from the row of bytes used
*/
static ulong hash( String const* str, int pos, int len ) {
    // this iteration uses the Rabin Fingerprint rolling hash, which treats substrings
    // as a number in some base, in this case 256 ( the maximum 8-bit value )

    ulong hashVal = 0;

    int offs = str->len - pos;
    int alen = len > offs ? offs : len; 

    for ( int i = 0; i < alen; i++ ) {
        hashVal *= BASE_NUMBER;
        hashVal %= PRIME_NUMBER;
        hashVal += str->bytes[ pos + i ];
    }

    return hashVal;
}

/**
    This implementation does not require anything on this end to be preprocessed,
    so the function in this context will only set the varr to null, since it won't
    be used
*/
void preprocess( String const* subs, int* varr ) {
    varr = NULL;
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
            int mismatch = 0;   // set to 1 if a mismatch is found

            // move across the string if the hashes match, and set the mismatch
            // flag and break if any two characters don't match
            for ( int j = 0; j < sslen; j++ )
                if ( str->bytes[ i + j ] != subs->bytes[ j ] ) {
                    mismatch = 1;
                    break;
                }

            // return the current index if no mismatches were found
            if ( !mismatch )
                return i;
        }
    }

    return -1;
}