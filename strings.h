/**
    @file strings.h
    @author Aaron N. (GalacticSandwich)

    Contains a custom struct definition for a String, consisting of a pointer to
    a character array, along with the length of said array. Additionally contains the
    declarations of functions associated with handling the memory of Strings.
*/

#ifndef STRINGS_H
#define STRINGS_H

/**
    Struct representing a length-tracked string, representative of the way
    strings work in most programming contexts.
*/
typedef struct {
    /** the array of bytes used in the string */
    char* bytes;
    /** the length of the string */
    int len;
} String;

/**
    Constructs a String after allocating memory for it in the heap, then
    returns a reference to it, using a null-terminated string-literal.

    @param lit the string literal to construct a proper String with
    @return a reference to the newly-constructed String in memory
*/
String* makeString( char const* lit );

/**
    Frees the memory associated with a String in heap memory.

    @param str the String to free in memory
*/
void freeString( String* str );

/**
    Prints the byte content of a String to stdout.

    @param str the String to print
*/
void outString( String const* str );

/**
    Prints the byte content of a String to stdout with a
    terminating newline.

    @param str the String to print
*/
void outStringLn( String const* str );

#endif
