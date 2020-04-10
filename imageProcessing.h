
//If a header file happens to be included twice, the compiler will process its contents twice and it will result in an error. The standard way to prevent this is to enclose the entire real contents of the file in a conditional  site:   https://www.tutorialspoint.com/cprogramming/c_header_files.htm
#ifndef imageProcessing_h
#define imageProcessing_h

#include "./helpingMethods/helpingMethods.h"
#include "./filters/filters.h"
#include "./transformations/transformations.h"
#include "./clustring/cluster.h"

#endif
