
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

typedef struct {
    /** the array of values for each substring character */
    int* values;
    /** the substring to search for */
    String const* subs;
} PrefixTable;

static void initValues( PrefixTable* table, String const* subs )
{
    int p = 1;
    int np = 0;

    int len = length( subs );

    table->values[ 0 ] = -1;

    while ( p < len ) {
        if ( subs->bytes[ p ] == subs->bytes[ np ] )
            table->values[ p ] = table->values[ np ];

        else {
            table->values[ p ] = np;
            while ( np >= 0 && subs->bytes[ p ] != subs->bytes[ np ] )
                np = subs->bytes[ np ];
        }

        p++; 
        np++;
    }

    table->values[ p ] = np;
}

static PrefixTable* makePrefixTable( String const* subs )
{
    // Allocate heap memory for the PrefixTable struct
    PrefixTable* table = ( PrefixTable* ) malloc( sizeof( PrefixTable ) );

    // fetch the length of the substring
    int len = length( subs );

    // set the address of the substring to the one passed in, and allocate
    // heap memory for the prefix values of each byte in the substring
    table->subs = subs;
    table->values = ( int* ) malloc( len * sizeof( int ) );

    // Initialize the PrefixTable values using the substring passed
    initValues( table, subs );

    // Return the address of the PrefixTable struct created
    return table;
}

static void freePrefixTable( PrefixTable* table )
{
    // use free() from the standard library to free the heap memory
    // associated with prefix-value array, along with the actual PrefixTable struct itself
    free( table->values );
    free( table );
}

int getSubstring( String const* str, String const* subs )
{
    // fetch the lengths of the superstring and the substring
    int slen = length( str );
    int sslen = length( subs );

    // check to see if the superstring length is shorter than that
    // of the substring, and if it is, fail and return -1 (error)
    if ( slen < sslen )
        return -1;

    // make the prefix table using the passed substring
    PrefixTable* pt = makePrefixTable( subs );

    // initialize indeces to keep track of positions in the superstring and substring
    int i = 0;
    int j = 0;

    // conduct the kmp algorithm
    while ( i < slen ) {
        if ( subs->bytes[ j ] == str->bytes[ i ] ) {
            i++;
            j++;
            if ( j == sslen ) {
                freePrefixTable( pt );
                return i - j;
            }
        }
        else {
            j = pt->values[ j ];
            if ( j < 0 ) {
                i++;
                j++;
            }
        }
    }

    // if no substrings were found, free the prefix table memory to avoid
    // a memory leak, and fail and return -1 (failure)
    freePrefixTable( pt );
    return -1;
}
