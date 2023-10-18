/**
    @file common.h
    @author Aaron N. (GalacticSandwich)

    Contains any flags and definitions common to all
    headers/source files in the repo. This mostly consists
    of debugging flags and type/quick method shorthands.
*/

#ifndef COMMON_H
#define COMMON_H

// check to see if the _VERBOSE constant has been defined, and if it has
// set the flag for debug printing to true, or false otherwise
#ifdef _PRINTING
    #define PRINTING 1
#else
    #define PRINTING 0
#endif

// define a shorthand for unsigned long
#define ulong unsigned long

#endif
