/**
    @file substring.c
    @author Aaron N. (GalacticSandwich)

    Contains the entry point of a program meant to test implementations
    of string-searching algorithms. Along with functions to handle inputs.
*/

#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

/**
    Reads a file using a provided filename into a heap-allocated string, then
    returns a reference to this string, or exits with an error if the file
    cannot be opened.

    @param fileName the name of the file to open
    @return a reference to the string containing the file text
*/
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

/**
    Prints out the template for program usage

    @param progName the name of the program to display
*/
static void usage( char const* progName ) {
    printf( "usage: %s <file> <string> <flags>\n", progName );
}

/**
    Program entry point, reads in a source file, and searches for an instance of a string
    inside the file, using the substring search template, and whatever searching algorithm
    implementation has been compiled.

    @param argc the number of command-line arguments passed
    @param argv the vector of command-line arguments passed
    @return the program exit status
*/
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
