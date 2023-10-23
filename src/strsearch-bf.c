
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

void preprocess( String const* subs, int* varr ) {
    varr = NULL;
}

int findSubstring( String const* str, String const* subs, int pos, int const* varr ) {
    int slen = str->len;
    int sslen = subs->len;

    for ( int i = pos; i < slen; i++ ) {
        int mismatch = 0;

        for ( int j = 0; j < sslen; j++ ) {
            if ( str->bytes[ i + j ] != subs->bytes[ j ] ) {
                mismatch = 1;
                break;
            }
        }

        if ( !mismatch )
            return i;
    }

    return -1;
}
