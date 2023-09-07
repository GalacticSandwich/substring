
#ifndef STRINGS_H
#define STRINGS_H

typedef struct {
    /** the array of bytes used in the string */
    char* bytes;
    /** the length of the string */
    int len;
} String;

int length( String const* str );

String* makeString( char const* lit );

// String* remakeString( String* str, char const* lit );

void freeString( String* str );

// void outString( String const* str );

#endif
