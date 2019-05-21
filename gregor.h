/******************************************************************************
 *                        Gregorian Calendar Functions                        *
 ******************************************************************************
 * File         : gregor.h                                                    *
 * Version      : 0.3.1                                                       *
 * Date Started : 2001-12-14 12:00 GMT                                        *
 * Date Modified: 2003-05-04 14:00 GMT                                        *
 * Author       : Georgi D. Sotirov <gdsotirov@dir.bg>                        *
 * CVS Id       : $Id: gregor.h,v 1.1 2005/04/20 18:47:35 gsotirov Exp $
 ******************************************************************************/

#define GREGORIAN_MIN                   1582
#define GREGORIAN_MAX                   4092

#define EASTER_START_DATE_DAY           3
#define EASTER_START_DATE_MONTH         4 /* April */

int isGregorian(unsigned short year);
int isLeapYear(unsigned short year);
int CatholicEasterDay(unsigned short *month, unsigned short *day, unsigned short year);
int EasterDay(unsigned short *month, unsigned short *day, unsigned short year);

