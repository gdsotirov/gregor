/******************************************************************************
 *                        Gregorian Calendar Functions                        *
 ******************************************************************************
 * File         : gregor.c                                                    *
 * Version      : 0.3.1                                                       *
 * Date started : 2001-12-14 12:00 GMT                                        *
 * Date modified: 2003-05-04 14:00 GMT                                        *
 * Author       : Georgi D. Sotirov <gdsotirov@gmail.com>                     *
 ******************************************************************************/

#include "gregor.h"

/******************************************************************************
 * Function     : isGregorian                                                 *
 * Purpose      : To find if a specific year is a gregorian calendar year.    *
 * Returns      : 1 if year is gregorian, and 0 if not                        *
 ******************************************************************************/

int isGregorian(year)
    unsigned short year; /* specific year */
{
    if ( year >= GREGORIAN_MIN && year <= GREGORIAN_MAX )
        return 1;
    return 0;
}

/******************************************************************************
 * Function     : isLeapYear                                                  *
 * Purpose      : Finds whether specific year is leap or not.                 *
 * Returns      : 1 if the year is leap or 0 otherwise.                       *
 ******************************************************************************/

int isLeapYear(year)
    unsigned short year;    /* specific year */
{
    if ( isGregorian(year) )
        return ( (year % 4 == 0) && ((year / 100 != 0) || (year % 400 == 0)) );
    return 0;
}

/******************************************************************************
 * Function     : CatholicEasterDay                                           *
 * Purpose      : Finds the date of catholic easter day with the J. M. Oudin  *
 *                algorithm (1940).                                           *
 * Returns      : One on successful operation otherwise zero.                 *
 ******************************************************************************

 Notes:
       See Meeus, "Astronomical Algorithms", p 67.  He  in  turn  states  that
    the  following  method  has  been  given  by  Spencer  Jones  in  his book
    "General   Astronomy"   (p 73-74  of  the  1922  edition).  It   has  been
    published again in  the "Journal of the British Astronomical Association",
    vol 88, page 91 (December 1977),  where it is said that  it was devised in
    1876 and appeared in Butcher's "Astronomical Calendar".
       Unlike  the  formula  given  by  Gauss,  this method has  no  exception
    and is valid for all years in the Gregorian calendar,  hence from 1583 on.
*/

int CatholicEasterDay(month, day, year)
    unsigned short *month;  /* month of easter */
    unsigned short *day;    /* day of easter */
    unsigned short year;    /* specific year */
{
    if ( isGregorian(year) ) {
        int c; /* algorithm variables */
        int n;
        int k;
        int i;
        int j;
        int l;

        c = year / 100;
        n = year - 19 * (year / 19);
        k = (c - 17) / 25;

        i = c - c / 4 - (c - k) / 3 + 19 * n + 15;
        i = i - 30 * (i / 30);
        i = i - (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));

        j = year + year / 4 + i + 2 - c + c / 4;
        j = j - 7 * (j / 7);

        l = i - j;

        *month = 3 + (l + 40) / 44;
        *day   = l + 28 - 31 * (*month / 4);
    }
    else {
        *month = *day = 0;
        return 0;
    }

    return 1;
}

/******************************************************************************
 * Function     : EasterDay                                                   *
 * Purpose      : Finds the date of easter day with the modified Gauss        *
 *                algorithm.                                                  *
 * Returns      : One on successful operation otherwise zero.                 *
 ******************************************************************************

 Notes:
    See "Universe", 2000, book 2, p 30 and the correction in "Universe", 2000,
    book 3, p 37.
*/

int EasterDay(month, day, year)
    unsigned short *month;
    unsigned short *day;
    unsigned short year;
{
    if ( isGregorian(year) ) {
        int n1; /* algorithm variables */
        int n2;
        int n3;
        int n4;
        int n5;
        int na;
        int nb;
        int nc;

        n1 = year % 19;
        n2 = year % 4;
        n3 = year % 7;

        na = 19 * n1 + 16;
        n4 = na % 30;
        nb = 2 * n2 + 4 * n3 + 6 * n4;
        n5 = nb % 7;
        nc = n4 + n5;

        *month = EASTER_START_DATE_MONTH;

        if ( nc > 30 - EASTER_START_DATE_DAY ) {
            *day = nc - (30 - EASTER_START_DATE_DAY);
            *month = *month + 1;
        }
        else *day = EASTER_START_DATE_DAY + nc;
    }
    else {
        *month = *day = 0;
        return 0;
    }

    return 1;
}

