
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

int main( int argc, char** argv )
{
    int numArgs = argc;
    char** argArr = argv;

    // open up the source text file
    FILE* text = fopen( argArr[ 1 ], "r" );

    if ( text == NULL ) {
        fprintf( stderr, "Error: Invalid file!\n" );
        return EXIT_FAILURE;
    }

    // initialize a value for the text-string length
    int n = 0;

    // initialize the file text byte array
    char* rawData = ( char* ) malloc( sizeof( char ) );

    // read the file text into a character pointer
    int c = fgetc( text );
    while ( c != EOF ) {
        rawData[ n++ ] = c;
        rawData = ( char* ) realloc( rawData, n * sizeof( char ) + 1 );
        c = fgetc( text );
    }

    // null-terminate the raw file text string
    rawData[ n ] = '\0';

    // construct a string for the text and pattern using the created text string
    // and the word to search for passed in through the command line
    String* haystack = makeString( rawData );
    String* needle = makeString( argArr[ 2 ] );
    free( rawData );

    // outString( data );
    // printf( "\n" );
    // outString( word );
    // printf( "\n" );

    int pos = findSubstring( haystack, needle, 0 );

    printf( "%d\n", pos );

    // exit the program
    return EXIT_SUCCESS;
}