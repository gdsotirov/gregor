/* File       : easter.c
 * Description: A test programm for the Gregorian Calendar Functions.
 * Written by : George D. Sotirov <gdsotirov@dir.bg>
 * CVS Id     : $Id: easter.c,v 1.1 2005/04/20 18:47:35 gsotirov Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "gregor.h"

char *months[] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"};

int main(int argc, char *argv[]) {
    int year = 0;

    if ( argc > 1 )
        year = atoi(argv[1]);
    else {
        printf("Enter year: ");
        scanf("%d", &year);
    }

    if ( isGregorian(year) ) {
        unsigned short month, day;
        EasterDay(&month, &day, year);
        printf("Easter day is on %d %s %d.\n", day, months[month], year);
    }
    else {
        printf("%s: Error: %d is not a valid Gregorian calendar year!\n", argv[0], year);
        return 1;
    }

    return 0;
}

