/***********************************************************************\
 *
 * File:           RngStream.c for multiple streams of Random Numbers
 * Language:       ANSI C
 * Copyright:      Pierre L'Ecuyer and Université de Montréal 
 *
 * If you use this software for work leading to publications, 
 * please cite the following relevant articles in which MRG32k3a 
 * and the package with multiple streams were proposed:

 * P. L'Ecuyer, ``Good Parameter Sets for Combined Multiple Recursive Random Number Generators'', 
 * Operations Research, 47, 1 (1999), 159--164.

 * P. L'Ecuyer, R. Simard, E. J. Chen, and W. D. Kelton, 
 * ``An Objected-Oriented Random-Number Package with Many Long Streams and Substreams'', 
 * Operations Research, 50, 6 (2002), 1073--1075
 *
\***********************************************************************/


#include "rngstream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------*/
/* Private part.                                                       */
/*---------------------------------------------------------------------*/


#define norm  2.328306549295727688e-10
#define m1    4294967087
#define m2    4294944443
#define a12      1403580
#define a13n      810728
#define a21       527612
#define a23n     1370589

#define two17   131072
#define two53   9007199254740992
#define fact  5.9604644775390625e-8    /* 1 / 2^24 */


/* Default initial seed of the package. Will be updated to become
   the seed of the next created stream. */
static double nextSeed[6] = { 12345, 12345, 12345, 12345, 12345, 12345 };


/* The following are the transition matrices of the two MRG components */
/* (in matrix form), raised to the powers -1, 1, 2^76, and 2^127, resp.*/
static double InvA1[3][3] = {          /* Inverse of A1p0 */
          { 184888585.0,   0.0,  1945170933.0 },
          {         1.0,   0.0,           0.0 },
          {         0.0,   1.0,           0.0 }
          };

static double InvA2[3][3] = {          /* Inverse of A2p0 */
          {      0.0,  360363334.0,  4225571728.0 },
          {      1.0,          0.0,           0.0 },
          {      0.0,          1.0,           0.0 }
          };

static double A1p0[3][3] = {
          {       0.0,        1.0,       0.0 },
          {       0.0,        0.0,       1.0 },
          { -810728.0,  1403580.0,       0.0 }
          };

static double A2p0[3][3] = {
          {        0.0,        1.0,       0.0 },
          {        0.0,        0.0,       1.0 },
          { -1370589.0,        0.0,  527612.0 }
          };

static double A1p76[3][3] = {
          {      82758667.0, 1871391091.0, 4127413238.0 }, 
          {    3672831523.0,   69195019.0, 1871391091.0 }, 
          {    3672091415.0, 3528743235.0,   69195019.0 }
          };

static double A2p76[3][3] = {
          {    1511326704.0, 3759209742.0, 1610795712.0 }, 
          {    4292754251.0, 1511326704.0, 3889917532.0 }, 
          {    3859662829.0, 4292754251.0, 3708466080.0 }
          };

static double A1p127[3][3] = {
          {    2427906178.0, 3580155704.0,  949770784.0 }, 
          {     226153695.0, 1230515664.0, 3580155704.0 },
          {    1988835001.0,  986791581.0, 1230515664.0 }
          };

static double A2p127[3][3] = {
          {    1464411153.0,  277697599.0, 1610723613.0 },
          {      32183930.0, 1464411153.0, 1022607788.0 },
          {    2824425944.0,   32183930.0, 2093834863.0 }
          };



/*-------------------------------------------------------------------------*/


static double MultModM (double a, double s, double c, double m)
   /* Compute (a*s + c) % m. m must be < 2^35.  Works also for s, c < 0 */
{
   double v;
   long a1;
   v = a * s + c;
   if ((v >= two53) || (v <= -two53)) {
      a1 = (long) (a / two17);
      a -= a1 * two17;
      v = a1 * s;
      a1 = (long) (v / m);
      v -= a1 * m;
      v = v * two17 + a * s + c;
   }
   a1 = (long) (v / m);
   if ((v -= a1 * m) < 0.0)
      return v += m;
   else
      return v;
}


/*-------------------------------------------------------------------------*/

static void MatVecModM (double A[3][3], double s[3], double v[3], double m)
   /* Returns v = A*s % m.  Assumes that -m < s[i] < m. */
   /* Works even if v = s. */
{
   int i;
   double x[3];
   for (i = 0; i < 3; ++i) {
      x[i] = MultModM (A[i][0], s[0], 0.0, m);
      x[i] = MultModM (A[i][1], s[1], x[i], m);
      x[i] = MultModM (A[i][2], s[2], x[i], m);
   }
   for (i = 0; i < 3; ++i)
      v[i] = x[i];
}


/*-------------------------------------------------------------------------*/

static void MatMatModM (double A[3][3], double B[3][3], double C[3][3],
                        double m)
   /* Returns C = A*B % m. Work even if A = C or B = C or A = B = C. */
{
   int i, j;
   double V[3], W[3][3];
   for (i = 0; i < 3; ++i) {
      for (j = 0; j < 3; ++j)
         V[j] = B[j][i];
      MatVecModM (A, V, V, m);
      for (j = 0; j < 3; ++j)
         W[j][i] = V[j];
   }
   for (i = 0; i < 3; ++i) {
      for (j = 0; j < 3; ++j)
         C[i][j] = W[i][j];
   }
}


/*-------------------------------------------------------------------------*/

static void MatTwoPowModM (double A[3][3], double B[3][3], double m, long e)
  /* Compute matrix B = (A^(2^e) % m);  works even if A = B */
{
   int i, j;

   /* initialize: B = A */
   if (A != B) {
      for (i = 0; i < 3; i++) {
         for (j = 0; j < 3; ++j)
            B[i][j] = A[i][j];
      }
   }
   /* Compute B = A^{2^e} */
   for (i = 0; i < e; i++)
      MatMatModM (B, B, B, m);
}


/*-------------------------------------------------------------------------*/

static void MatPowModM (double A[3][3], double B[3][3], double m, long n)
   /* Compute matrix B = A^n % m ;  works even if A = B */
{
   int i, j;
   double W[3][3];

   /* initialize: W = A; B = I */
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; ++j) {
         W[i][j] = A[i][j];
         B[i][j] = 0.0;
      }
   }
   for (j = 0; j < 3; ++j)
      B[j][j] = 1.0;

   /* Compute B = A^n % m using the binary decomposition of n */
   while (n > 0) {
      if (n % 2)
         MatMatModM (W, B, B, m);
      MatMatModM (W, W, W, m);
      n /= 2;
   }
}


/*-------------------------------------------------------------------------*/

/* This part is slightly adapted from the code written by Sebastiano Vigna (vigna@acm.org)

static double U01 (RngStream g) {
   const int64_t m1 = INT64_C(4294967087);
   const int64_t m2 = INT64_C(4294944443);
   const int32_t a12 = INT32_C(1403580);
   const int32_t a13 = INT32_C(810728);
   const int32_t a21 = INT32_C(527612);
   const int32_t a23 = INT32_C(1370589);
   const int64_t corr1 = (m1 * a13);
   const int64_t corr2 = (m2 * a23);
   const double norm = 0x1.000000d00000bp-32;

   int64_t p, r;
   r = g->Cg[2] - g->Cg[5];
	 r -= m1 * ((r - 1) >> 63);

   p = (a12 * g->Cg[1] - a13 * g->Cg[0] + corr1) % m1;
   g->Cg[0] = g->Cg[1];
   g->Cg[1] = g->Cg[2];
   g->Cg[2] = p;
   p = (a21 * g->Cg[5] - a23 * g->Cg[3] + corr2) % m2;
   g->Cg[3] = g->Cg[4];
   g->Cg[4] = g->Cg[5];
   g->Cg[5] = p;

   return r * norm;
}

/*-------------------------------------------------------------------------*/

static int CheckSeed (unsigned long seed[6]) {
   /* Check that the seeds are legitimate values. Returns 0 if legal seeds,
     -1 otherwise */
   int i;

   for (i = 0; i < 3; ++i) {
      if (seed[i] >= m1) {
	 fprintf (stderr, "****************************************\n"
		 "ERROR: Seed[%1d] >= m1, Seed is not set.\n"
		 "****************************************\n\n", i);
	 return (-1);
       }
   }
   for (i = 3; i < 6; ++i) {
      if (seed[i] >= m2) {
	 fprintf (stderr, "****************************************\n"
		 "ERROR: Seed[%1d] >= m2, Seed is not set.\n"
		 "****************************************\n\n", i);
	 return (-1);
       }
   }
   if (seed[0] == 0 && seed[1] == 0 && seed[2] == 0) {
      fprintf (stderr, "****************************\n"
	      "ERROR: First 3 seeds = 0.\n"
	      "****************************\n\n");
      return (-1);
   }
   if (seed[3] == 0 && seed[4] == 0 && seed[5] == 0) {
      fprintf (stderr, "****************************\n"
	      "ERROR: Last 3 seeds = 0.\n"
	      "****************************\n\n");
      return (-1);
   }

   return 0;
}


/*---------------------------------------------------------------------*/
/* Public part.                                                        */
/*---------------------------------------------------------------------*/


RngStream RngStream_CreateStream () {
   int i;
   RngStream g;

   g = (RngStream) malloc (sizeof (struct RngStream_InfoState));
   if (g == NULL) {
      printf ("RngStream_CreateStream: No more memory\n\n");
      exit (EXIT_FAILURE);
   }
   for (i = 0; i < 6; ++i) {
      g->Cg[i] = g->Ig[i] = nextSeed[i];
   }
   MatVecModM (A1p127, nextSeed, nextSeed, m1);
   MatVecModM (A2p127, &nextSeed[3], &nextSeed[3], m2);
   return g;
}

/*-------------------------------------------------------------------------*/

void RngStream_DeleteStream (RngStream * p)
{
   if (*p == NULL)
      return;
   free (*p);
   *p = NULL;
}

/*-------------------------------------------------------------------------*/

void RngStream_ResetStartStream (RngStream g)
{
   int i;
   for (i = 0; i < 6; ++i)
      g->Cg[i] = g->Ig[i];
}

/*-------------------------------------------------------------------------*/

int RngStream_SetPackageSeed (uint64_t seed[6])
{
   int i;
   if (CheckSeed (seed))
      return -1;                    /* FAILURE */
   for (i = 0; i < 6; ++i)
      nextSeed[i] = seed[i];
   return 0;                       /* SUCCESS */
}

/*-------------------------------------------------------------------------*/

int RngStream_SetSeed (RngStream g, uint64_t seed[6])
{
   int i;
   if (CheckSeed (seed))
      return -1;                    /* FAILURE */
   for (i = 0; i < 6; ++i)
      g->Cg[i] = g->Ig[i] = seed[i];
   return 0;                       /* SUCCESS */ 
}

/*-------------------------------------------------------------------------*/

void RngStream_GetState (RngStream g, unsigned long seed[6])
{
   int i;
   for (i = 0; i < 6; ++i)
      seed[i] = g->Cg[i];
}

/*-------------------------------------------------------------------------*/

void RngStream_WriteState (RngStream g)
{
   int i;
   if (g == NULL)
      return;
   printf ("The current state of the Rngstream");
   if (g->name && (strlen (g->name) > 0))
      printf (" %s", g->name);
   printf (":\n   Cg = { ");

   for (i = 0; i < 5; i++) {
      printf ("%lu, ", (unsigned long) g->Cg[i]);
   }
   printf ("%lu }\n\n", (unsigned long) g->Cg[5]);
}

/*-------------------------------------------------------------------------*/

void RngStream_WriteStateFull (RngStream g)
{
   int i;
   if (g == NULL)
      return;
   printf ("The RngStream");
   printf ("   Ig = { ");
   for (i = 0; i < 5; i++) {
      printf ("%lu, ", (unsigned long) (g->Ig[i]));
   }
   printf ("%lu }\n", (unsigned long) g->Ig[5]);

   printf ("   Cg = { ");
   for (i = 0; i < 5; i++) {
      printf ("%lu, ", (unsigned long) (g->Cg[i]));
   }
   printf ("%lu }\n\n", (unsigned long) g->Cg[5]);
}

/*-------------------------------------------------------------------------*/

double RngStream_RandU01 (RngStream g)
{
   return U01 (g);
}

/*-------------------------------------------------------------------------*/

int RngStream_RandInt (RngStream g, int i, int j)
{
   return i + (int) ((j - i + 1.0) * RngStream_RandU01 (g));
}

   