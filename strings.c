/**
    @file strings.c
    @author Aaron N. (GalacticSandwich)

    Contains the definitions for functions needed to work with the custom String
    definition, notably for building the struct-type using a string-literal, or
    freeing memory associated with a String.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"

String* makeString( char const* lit )
{
    // fetch the length of the byte literal for initialization, and 
    // allocate the memory on the heap for the String struct
    int len = strlen( lit );
    String* str = ( String* ) malloc( sizeof( String ) );

    if ( str == NULL )
        fprintf( stderr, "[substring/strings] error: Could not allocate string memory!\n" );

    // allocate heap memory for the array of bytes which will comprise the string
    str->bytes = ( char* ) malloc( len * sizeof( char ) );

    if ( str->bytes == NULL )
        fprintf( stderr, "[substring/strings] error: Could not allocate byte array memory!\n" );

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
