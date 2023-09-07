
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"

int length( String const* str )
{
    // return the length stored in the String struct
    return str->len;
}

String* makeString( char const* lit )
{
    // fetch the length of the byte literal for initialization, and 
    // allocate the memory on the heap for the String struct
    int len = strlen( lit );
    String* str = ( String* ) malloc( sizeof( String ) );

    if ( str == NULL )
        fprintf( stderr, "Error: could not allocate string memory!" );

    // allocate heap memory for the array of bytes which will comprise the string
    str->bytes = ( char* ) malloc( len * sizeof( char ) );

    if ( str->bytes == NULL )
        fprintf( stderr, "Error: could not allocate byte array memory!");

    // use memcpy() to copy the correct number of bytes over to the byte array
    // from the literal passed
    memcpy( str->bytes, lit, len );

    // set the byte length in the String struct
    str->len = len;

    // return the starting address of the completed String
    return str;
}

void freeString( String* str )
{
    // use free() from the standard library to free the heap memory
    // associated with the byte array, along with the actual String struct itself
    free( str->bytes );
    free( str );
}
