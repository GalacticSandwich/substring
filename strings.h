
#ifndef STRINGS_H
#define STRINGS_H

typedef struct {
    /** the array of bytes used in the string */
    char* bytes;
    /** the length of the string */
    int len;
} String;

String* makeString( char const* lit );

void freeString( String* str );

#endif
