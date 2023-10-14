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
    OP_NOTHING,
    OP_USAGE,
    OP_SEARCH,
    OP_SEARCHALL
} task_t;

// the number of times to repeat a search
long reps = 1;

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
        fprintf( stderr, "[substring] error: Invalid filename\n" );
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
    printf( "\t\t :: output program usages\n" );
    printf( "\t%s <flags> search <file> <string>\n", progName );
    printf( "\t\t :: search for the first instance of <string> in <file>\n" );
    printf( "\t%s <flags> searchall <file> <string>\n", progName );
    printf( "\t\t :: search for all instances of <string> in <file>\n" );
    printf( "[substring] flags: \n" );
    printf( "\t-i <reps> \t :: repeat an operation <reps> times.\n" );
}

static int evalFlags( int argc, char** argv ) {
    int aup = 0;

    for ( int i = 0; i < argc; i++ ) {
        if ( argv[ i ][ 0 ] == '-' ) {
            switch ( argv[ i ][ 1 ] ) {
                case 'i':
                    reps = strtol( argv[ i + 1 ], NULL, 10 );

                    if ( PRINTING ) {
                        printf( "[substring] flags: iteration value parsed - %ld\n", reps );
                    }

                    if ( reps < 0 ) {
                        fprintf( stderr, "[substring] error: Invalid iteration value\n" );
                        usage( argv[ 0 ] );
                        exit( EXIT_FAILURE );
                    }

                    aup += 2;
                    i++;

                    break;
                default:
                    break;
            }
        }
    }

    return aup;
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

    // evaluate the flags passed
    int aup = evalFlags( argc, argv );

    if ( argc == 1 ) {
        fprintf( stderr, "[substring] error: No arguments provided\n" );
        usage( argv[ 0 ] );
        exit( EXIT_FAILURE );
    }


    if ( !strcmp( "search", argv[ aup + 1 ] ) ) {
        if ( argc != ( aup + 4 ) ) {
            fprintf( stderr, "[substring] error: Insufficient arguments provided\n" );
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }

        operation = OP_SEARCH;
    }
    else if ( !strcmp( "searchall", argv[ aup + 1 ] ) ) {
        if ( argc != ( aup + 4 ) ) {
            fprintf( stderr, "[substring] error: Insufficient arguments provided\n" );
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }
        
        operation = OP_SEARCHALL;
    }
    else if ( !strcmp( "usage", argv[ aup + 1 ] ) ) {
        if ( argc != ( aup + 2 ) ) {
            fprintf( stderr, "[substring] error: Redundant arguments provided\n" );
            usage( argv[ 0 ] );
            exit( EXIT_FAILURE );
        }
        
        operation = OP_USAGE;
    }
    else {
        fprintf( stderr, "[substring] error: Invalid Command \"%s\"\n", argv[ aup + 1 ] );
        usage( argv[ 0 ] );
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
        char* data = readFile( argv[ aup + 2 ] );

        // construct a string for the text and pattern using the created text string
        // and the word to search for passed in through the command line
        String* haystack = makeString( data );
        String* needle = makeString( argv[ aup + 3 ] );

        // initialize the value table with appropriate algorithms that need to use it
        int varr[ needle->len ];
        preprocess( needle, varr );

        // perform however many iterations are passed to the driver
        for ( long iter = 0; iter < reps; iter++ ) {
            // if the operation is not the usage display, check to see if the user has
            // prompted a search or searchall
            if ( operation == OP_SEARCH ) {
                // perform a substring search
                int pos = findSubstring( haystack, needle, 0, varr );

                // output the index of the first instance of the substring in the text read in, or
                // an appropriate message if no such instance exists
                if ( pos == -1 ) {
                    printf( "[substring] " );
                    if ( reps > 1 )
                        printf( "(%ld/%ld) ", iter + 1, reps );

                    printf( "search: No substrings found in %s\n", argv[ aup + 2 ] );
                }
                else {
                    printf( "[substring] " );
                    if ( reps > 1 )
                        printf( "(%ld/%ld) ", iter + 1, reps );

                    printf( "search: Substring found in %s at index %d\n", argv[ aup + 2 ], pos );
                }
            }
            else if ( operation == OP_SEARCHALL ) {
                // track the number of substrings found
                int n = 0;
                // perform a substring search
                int pos = findSubstring( haystack, needle, 0, varr );

                // output an appropriate message if no such instance exists, otherwise
                // output the correct index and keep searching until no more substrings can be found
                if ( pos == -1 ) {
                    printf( "[substring] " );
                    if ( reps > 1 )
                        printf( "(%ld/%ld) ", iter + 1, reps );

                    printf( "searchall: No substrings found in %s\n", argv[ aup + 2 ] );
                }
                else {
                    // search for substrings if they exist
                    while ( pos != -1 ) {
                        n++;
                        printf( "[substring] " );
                        if ( reps > 1 )
                            printf( "(%ld/%ld) ", iter + 1, reps );

                        printf( "searchall: Substring found in %s at index %d\n", argv[ aup + 2 ], pos );
                        pos = findSubstring( haystack, needle, pos + 1, varr );
                    }
                }
                printf( "[substring] " );
                if ( reps > 1 )
                    printf( "(%ld/%ld) ", iter + 1, reps );

                printf( "searchall: Total substrings found in %s: %d\n", argv[ aup + 2 ], n );
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
