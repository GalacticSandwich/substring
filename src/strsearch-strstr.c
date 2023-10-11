/**
    @file strsearch-strstr.c
    @author Aaron N. (GalacticSandwich)

    Contains a definition for substring searches, defined using the
    C Language standard library function strstr(), which uses a version the two-way algorithm
    to perform substring searches.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "strsearch.h"

/**
    This implementation does not require anything on this end to be preprocessed,
    so the function in this context will only set the varr to null, since it won't
    be used
*/
void preprocess( String const* subs, int* varr )
{
    varr = NULL;
}

int findSubstring( String const* str, String const* subs, int pos, int const* varr )
{
    char* socc = strstr( str->bytes + pos, subs->bytes );

    if ( socc == NULL )
        return -1;

    return ( int ) ( socc - str->bytes );
}
