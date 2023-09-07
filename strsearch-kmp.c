
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

static void buildPrefixTable( String const* subs, int* arr, int len )
{
    // the first prefix value is always zero
    arr[ 0 ] = 0;

    // initialize a variable for the start of the substring to
    // examine potential mutual circumfixes, while using the iterator
    // in the following loop as the variable further along in the substring, 
    // and along the prefix value array
    int bi = 0;

    // cycle through the substring, examine mutual circumfixes leading up to
    // the end of the substring, and update the prefix table values as
    // you go along
    for ( int i = 1; i < len; i++ ) {
        // if the bytes at the two positions match, increment the
        // earlier index and assign that to the table position at
        // the later index
        if ( subs->bytes[ bi ] == subs->bytes[ i ] )
            arr[ i ] = ++bi;
        
        // if they don't match, but the earlier index is not zero, update
        // the earlier index to whatever is at it's position minus one, and
        // decrement the later index to keep it where it is for the next iteration
        else if ( bi > 0 ) {
            bi = arr[ bi - 1 ];
            i--;
        }

        // if they don't match, and the earlier index is zero, set the value
        // at the later index in the table to zero
        else if ( bi == 0 )
            arr[ i ] = 0;
    }
}

int findSubstring( String const* str, String const* subs, int pos )
{

    // fetch the string and substring lengths
    int slen = length( str );
    int sslen = length( subs );

    // initialize an array to hold prefix table values for the substring
    int pvals[ sslen ];

    /* Section 1: Build Prefix Table */

    buildPrefixTable( subs, pvals, sslen ); // see comments in the above helper function

    /* Section 2: Conduct KMP Algorithm */

    // initialize values to go through the haystack (i) and the needle (j) respectively
    int i = 0;
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
                j = pvals[ j - 1 ];

            // if the substring index is zero, just increment the superstring index
            else
                i++;
        }
    }

    return -1;
}