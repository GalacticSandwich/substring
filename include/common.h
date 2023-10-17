
#ifndef COMMON_H
#define COMMON_H

// check to see if the EOP constant has been defined, and if it has
// set the flag for debug printing to true, or false otherwise
#ifdef _VERBOSE
    #define PRINTING 1
#else
    #define PRINTING 0
#endif

// define a shorthand for unsigned long
#define ulong unsigned long

#endif
