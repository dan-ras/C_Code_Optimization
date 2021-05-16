/***********************************************************************
* Author:
*    Daniel Rasmussen
* Summary:
*    A summary of the optimizations that you did goes here.
*
*     1.  Removed all of the asserts.
*     2.  Removed "#define buckRodgers 2200"
*     3.  Removed isLeapYear function. Logic for leap years is now 
*         defined as a single ternary function in numDaysInMonth().
*     4.  Changed numDaysInMonth() to use a static array with the 
*         month number being an index that returns that month's 
*         specific number of days.
*     5.  Removed the numDaysInYear() function.
*     6.  Removed the expensive for-loop in computeOffset() and replaced
*         with logic that requires fewer computations.
*     7.  Changed the naming of variables in the second for-loop of 
*         computeOffset() to simplify loop.
*     8.  Changed displayHeader() to use a static array with the month as
*         the index that returns a string containing the name of said month.
*     9.  Consolidated the number of sprintf() statements in displayHeader().
*     10. Replaced the first for-loop in displayTable() with a single sprintf()
*         statement.
*     11. Changed the other for-loops of displayTable() to simpler logic that 
*         resulted in less if-statements.
*     12. Removed assignment instructions.
*
*     Fastest time clocked at: 122.94ms with 100% correctness.
*
************************************************************************/
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include "/home/ecen324/calendarOptimize/lab_consts.h"
using namespace std;
#define yearSeed 1753
/**********************************************************************
 * Return the number of days in a given month.
 ***********************************************************************/
int numDaysInMonth(int month, int year)
{
   static const int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   if (month == 2)
      return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 29 : 28;
   else
      return days[month - 1];
}
/**********************************************************************
 * Compute the offset of where to start the table drawing.
 ***********************************************************************/
int computeOffset(int month, int year)
{
   int numDays = 0;
   numDays  = 365 * (year - yearSeed);
   numDays += ((year -1) / 4)   - (yearSeed / 4);
   numDays -= ((year -1) / 100) - (yearSeed / 100);
   numDays += ((year -1) / 400) - (yearSeed / 400);
   for (int i = 1; i < month; i++)
      numDays += numDaysInMonth(i, year);
   return numDays % 7;
}
/**********************************************************************
 * Display the calendar header.
 ***********************************************************************/
int displayHeader(int month, int year, char *calendar, int pos)
{
   static const char months[12][10] = {"January", "February", "March", 
                                       "April", "May", "June", "July", 
                                       "August", "September", "October", 
                                       "November", "December"};
   pos += sprintf(calendar + pos, "\n%s", months[month - 1]);
   return pos += sprintf(calendar + pos, ", %i\n", year);
}
/********************************************************************
 * Display the calendar table.
 *******************************************************************/
int displayTable(int numDays, int offset, char *calendar, int pos)
{
   pos += sprintf(calendar + pos, "%s", "  Su  Mo  Tu  We  Th  Fr  Sa\n");
   if (offset != 6)
      for (int i = 0; i <= offset; i++)
         pos += sprintf(calendar + pos, "    ");
   for (int i = 1; i <= numDays; i++)
   {
      pos += sprintf(calendar + pos, "% 4i", i);
      if (((offset + i + 1) % 7 == 0) & (i != numDays))
         pos += sprintf(calendar + pos, "\n");
   }
   return pos += sprintf(calendar + pos, "\n");
}  
/**********************************************************************
 * Display the Calendar.
 ***********************************************************************/
void display(int month, int year, char *calendar)
{
   int pos = 0;
   int offset = computeOffset(month, year);
   int numDays = numDaysInMonth(month, year);
   pos += displayHeader(month, year, calendar, pos);
   pos += displayTable(numDays, offset, calendar, pos);
   return;
}
/**********************************************************************
 * YOU MUST HAVE THIS FUNCTION SIGNATURE DEFINED TO COMPILE YOUR CODE
 * This is used by the driver to test your optimizations
 ***********************************************************************/
void make_calendars(int months[], int years[], char *calendars)
{
   for (int i = 0; i < NUM_CALS; i++)
      display(months[i], years[i], calendars + i * CAL_LENGTH);
}