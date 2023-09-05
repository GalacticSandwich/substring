
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "strsearch.h"

// static int compareBytes( char const* str1, char const* str2 )
// {
//     int len1 = strlen( str1 );
//     int len2 = strlen( str2 );

//     int comp = len1 > len2 ? len2 : len1;

//     for ( int i = 0; i < comp; i++ )
//         if ( str1[ i ] != str2[ i ] )
//             return str1[ i ] - str2[ i ];

//     if ( len1 == len2 )
//         return 0;
//     else if ( comp == len1 )
//         return -1;
//     else
//         return 1;
// }

int main( int argc, char* argv[] )
{
    // open up the source text file
    FILE* text = fopen( argv[ 1 ], "r" );

    // initialize a value for the text-string length
    int n = 0;

    // initialize the file text byte array
    char* rawData = ( char* ) malloc( sizeof( char ) );

    // read the file text into a character pointer
    int c = fgetc( text );
    while ( c != EOF ) {
        rawData[ n++ ] = c;
        rawData = ( char* ) realloc( rawData, n * sizeof( char ) );
    }

    // null-terminate the raw file text string
    rawData[ n ] = '\0';

    // construct a string for the text and pattern using the created text string
    // and the word to search for passed in through the command line
    String* data = makeString( rawData );
    String* word = makeString( argv[ 2 ] );
    free( rawData );

    // fetch the instance of the substring in the file text data if it exists
    int mi = getSubstring( data, word );

    // print the index of the first occurrence of the substring to the console,
    // or -1 if it does not exist
    printf( "%d", mi );

    // exit the program
    return EXIT_SUCCESS;
}