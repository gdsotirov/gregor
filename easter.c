/* File       : easter.c
 * Description: A test programm for the Gregorian Calendar Functions.
 * Written by : George D. Sotirov <gdsotirov@dir.bg>
 * CVS Id     : $Id: easter.c,v 1.3 2017/10/16 12:40:13 gsotirov Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int handleRequest(int year, int opt) {
  unsigned short month, day;

  if ( !isGregorian(year) ) {
    printf("Error: '%d' is not a valid Gregorian calendar year (between %d and %d)!\n", year, GREGORIAN_MIN, GREGORIAN_MAX);
    return 1;
  }

  switch (opt) {
    case 'c':
      CatholicEasterDay(&month, &day, year);
      printf("Catholic Easter day is on %d %s %d.\n", day, months[month], year);
      break;
    case 'l':
      if ( isLeapYear(year) ) {
        printf("Year %d is a leap year.\n", year);
      }
      else {
        printf("Year %d is not a leap year.\n", year);
      }
      break;
    case 'o':
      EasterDay(&month, &day, year);
      printf("Orthodox Easter day is on %d %s %d.\n", day, months[month], year);
      break;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int opt = 0;
  int year = 0;

  while ( (opt = getopt(argc, argv, "c:l:o:")) != -1 ) {
    switch (opt) {
      case 'c':
      case 'l':
      case 'o':
        year = atoi(optarg);
        handleRequest(year, opt);
        break;
      default:
        printf("Usage: %s -c <year> -l <year> -o <year>\n", argv[0]);
        printf("  -c <year> Calculate and print Catholic Easter date for given year.\n");
        printf("  -l <year> Check and print whether the given year is leap or not.\n");
        printf("  -o <year> Calculate and print Orthodox Easter date for given year.\n");
        printf("       %s <year>\n", argv[0]);
        printf("  Print everything for given year.\n");
    }
  }

  if ( argc > 1 && (year = atoi(argv[1])) != 0) {
    year = atoi(argv[1]);
  }
  else {
    printf("Please, enter year: ");
    scanf("%d", &year);
  }

  if ( !isGregorian(year) ) {
    printf("Error: %d is not a valid Gregorian calendar year (between %d and %d)!\n", year, GREGORIAN_MIN, GREGORIAN_MAX);
  }

  handleRequest(year, 'c');
  handleRequest(year, 'l');
  handleRequest(year, 'o');

  return 0;
}

