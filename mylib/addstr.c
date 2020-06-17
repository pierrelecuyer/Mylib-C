#include "addstr.h"

#include <stdio.h>
#include <string.h>


#define LEN1 63


/* ========================== functions  ================================= */

void  addstr_long (char *to, const char *add, long n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1ld", n);
   strcat (to, str);
}

void  addstr_uint (char *to, const char *add, unsigned int n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1u", n);
   strcat (to, str);
}

void  addstr_int (char *to, const char *add, int n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1d", n);
   strcat (to, str);
}

void  addstr_ulong (char *to, const char *add, unsigned long n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1lu", n);
   strcat (to, str);
}

void  addstr_int64 (char *to, const char *add, int64_t n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1" PRIdLEAST64, n);
   strcat (to, str);
}

void  addstr_uint64 (char *to, const char *add, uint64_t n)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%1" PRIuLEAST64, n);
   strcat (to, str);
}

void  addstr_char (char *to, const char *add, char c)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%c", c);
   strcat (to, str);
}

void  addstr_double (char *to, const char *add, double x)
{
   char str[LEN1 + 1];
   strcat (to, add);
   sprintf (str, "%.16G", x);
   strcat (to, str);
}

void  addstr_bool (char *to, const char *add, int b)
{
   strcat (to, add);
   if (b)
      strcat (to, "TRUE");
   else
      strcat (to, "FALSE");
}

void  addstr_array_long (char *to, const char *add, int high, long val[])
{
   int j;
   strcat (to, add);
   addstr_long (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_long (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_int64 (char *to, const char *add, int high, int64_t val[])
{
   int j;
   strcat (to, add);
   addstr_int64 (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_int64 (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_ulong (char *to, const char *add,
                         int high, unsigned long val[])
{
   int j;
   strcat (to, add);
   addstr_ulong (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_ulong (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_uint64 (char *to, const char *add,
                         int high, uint64_t val[])
{
   int j;
   strcat (to, add);
   addstr_uint64 (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_uint64 (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_uint (char *to, const char *add, int high,
		        unsigned int val[])
{
   int j;
   strcat (to, add);
   addstr_uint (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_uint (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_int (char *to, const char *add, int high, int val[])
{
   int j;
   strcat (to, add);
   addstr_int (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_int (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_double (char *to, const char *add, int high, double val[])
{
   int j;
   strcat (to, add);
   addstr_double (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_double (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}

void  addstr_array_char (char *to, const char *add, int high, char val[])
{
   int j;
   strcat (to, add);
   addstr_char (to, "(", val[0]);
   for (j = 1; (j < high) && (j < 5); j++)
      addstr_char (to, ", ", val[j]);
   if (high > 5)
      strcat (to, ", ... )");
   else
      strcat (to, ")");
}
