/**
    @file substring.c
    @author Aaron N. (GalacticSandwich)

    Contains the entry point of a program meant to test implementations
    of string-searching algorithms. Along with functions to handle inputs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    An enum type to define the operations which the driver application
    will be capable of performing.

    OP_NOTHING: nothing at all, represents a null action

    OP_USAGE:   output the proper usages of the program

    OP_SEARCH:  search for the first instance of the substring in the superstring, and output the
                index at which it occurs

    OP_SEARCHALL:   search for all occurrences of the substring in the superstring, and output the
                    indices at which they occur
*/
typedef enum {
    OP_NOTHING = 0x00,
    OP_USAGE = 0x01,
    OP_SEARCH = 0x02,
    OP_SEARCHALL = 0x03
} task_t;

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
    printf( "[substring] usage: \n" );
    printf( "\t%s usage\n", progName );
    printf( "\t%s search <file> <string>\n", progName );
    printf( "\t%s searchall <file> <string>\n", progName );
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
    // the operation to perform by the driver program
    task_t operation = OP_NOTHING;

    if ( !strcmp( "search", argv[ 1 ] ) ) {
        if ( argc != 4 ) {
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }

        operation = OP_SEARCH;
    }
    else if ( !strcmp( "searchall", argv[ 1 ] ) ) {
        if ( argc != 4 ) {
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }
        
        operation = OP_SEARCHALL;
    }
    else if ( !strcmp( "usage", argv[ 1 ] ) ) {
        if ( argc != 2 ) {
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }
        
        operation = OP_USAGE;
    }
    else {
        fprintf( stderr, "[substring] error: Invalid Command \"%s\"", argv[ 1 ] );
        exit( EXIT_FAILURE );
    }

    if ( operation == OP_NOTHING ) {
        printf( "[substring] (nothing)\n" );
        exit( EXIT_SUCCESS );
    }
    else if ( operation == OP_USAGE ) {
        usage( argv[ 0 ] );
        exit( EXIT_SUCCESS );
    }
    else {
        // read in the input file
        char* data = readFile( argv[ 2 ] );

        // construct a string for the text and pattern using the created text string
        // and the word to search for passed in through the command line
        String* haystack = makeString( data );
        String* needle = makeString( argv[ 3 ] );

        // if the operation is not the usage display, check to see if the user has
        // prompted a search or searchall
        if ( operation == OP_SEARCH ) {
            // perform a substring search
            int pos = findSubstring( haystack, needle, 0 );

            // output the index of the first instance of the substring in the text read in, or
            // an appropriate message if no such instance exists
            if ( pos == -1 ) {
                printf( "[substring] search: No substrings found in %s\n", argv[ 2 ] );
            }
            else {
                printf( "[substring] search: Substring found in %s at index %d\n", argv[ 2 ], pos );
            }
        }
        else if ( operation == OP_SEARCHALL ) {
            // perform a substring search
            int pos = findSubstring( haystack, needle, 0 );

            // output the index of the first instance of the substring in the text read in, or
            // an appropriate message if no such instance exists
            if ( pos == -1 ) {
                printf( "[substring] searchall: No substrings found in %s\n", argv[ 2 ] );
            }
            else {
                printf( "[substring] searchall: Substring found in %s at index %d\n", argv[ 2 ], pos );

                // search for more substrings if they exist
                while ( ( pos = findSubstring( haystack, needle, pos + 1 ) ) != -1 ) {
                    printf( "[substring] searchall: Substring found in %s at index %d\n", argv[ 2 ], pos );
                }
            }
        }

        // free the two strings made after we're done using them
        freeString( haystack );
        freeString( needle );

        // free the string associated with the original data read in
        free( data );

        // exit the program
        return EXIT_SUCCESS;
    }
}
