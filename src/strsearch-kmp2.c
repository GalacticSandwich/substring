
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    Initializes the prefix table, containing the shift factors for
    the substring when comparing in the superstring to find
    matches.
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

int findSubstring( String const* str, String const* subs, int pos, int const* varr ) {
    int slen = str->len;
    int sslen = subs->len;

    for ( int i = pos; i < slen; i++ ) {
        int sval = 0;
        int mismatch = 0;

        for ( int j = sval; j < sslen; j++ ) {
            if ( str->bytes[ i + j ] != subs->bytes[ j ] ) {
                mismatch = 1;
                sval = varr[ j ];
                break;
            }
        }

        if ( !mismatch )
            return i;
    }

    return -1;
}
