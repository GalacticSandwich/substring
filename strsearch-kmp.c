
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

typedef struct {
    /** the array of values for each substring character */
    int* values;
    /** the substring to search for */
    String* subs;
} PrefixTable;

static void initValues( PrefixTable* table, String const* subs )
{
    /* ... */
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
    // check to see if the superstring length is shorter than that
    // of the substring, and if it is, fail and return -1 (error)
    if ( length( str ) < length( subs ) )
        return -1;

    // make the prefix table using the passed substring
    PrefixTable* pt = makePrefixTable( subs );

    /* ... */
}
