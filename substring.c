
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

static char* readFile( char const* fileName ) {
    // open up the source text file to read
    FILE* file = fopen( fileName, "r" );

    if ( file == NULL ) {
        fprintf( stderr, "Error: Invalid file!\n" );
        exit( EXIT_FAILURE );
    }

    // initialize a value for the text-string length
    int n = 0;

    // initialize the file text byte array
    char* data = ( char* ) malloc( sizeof( char ) );

    // read the file text into a character pointer
    int c = fgetc( file );
    while ( c != EOF ) {
        data[ n++ ] = c;
        data = ( char* ) realloc( data, n * sizeof( char ) + 1 );
        c = fgetc( file );
    }

    // null-terminate the raw file text string
    data[ n ] = '\0';

    return data;
}

static void usage( char const* progName ) {
    printf( "usage: %s <file> <string> <flags>\n", progName );
}

int main( int argc, char** argv )
{
    int numArgs = argc;
    char** argArr = argv;

    if ( numArgs < 3 ) {
        usage( argArr[ 0 ] );
        return EXIT_FAILURE;
    }

    // read in the input file
    char* data = readFile( argArr[ 1 ] );

    // construct a string for the text and pattern using the created text string
    // and the word to search for passed in through the command line
    String* haystack = makeString( data );
    String* needle = makeString( argArr[ 2 ] );
    free( data );

    // perform a substring search
    int pos = findSubstring( haystack, needle, 0 );

    // free the two strings made after we're done using them
    freeString( haystack );
    freeString( needle );

    // output the index of the first instance of the substring in the text read in, or
    // -1 if no such instance exists
    printf( "%d\n", pos );

    // exit the program
    return EXIT_SUCCESS;
}