/***********************************************************************\
*
* File:           RngStream.c for multiple streams of Random Numbers
* Language:       ANSI C
* Copyright:      Université de Montréal
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

/* Default initial seed of the package. Will be updated to become
   the seed of the next created stream. */
static int64_t nextSeed[6] = { 12345, 12345, 12345, 12345, 12345, 12345 };


/* The following are the transition matrices of the two MRG components */
/* (in matrix form), raised to the power 2^127. */
static int64_t A1p127[3][3] = {
	{    2427906178, 3580155704,  949770784 },
	{     226153695, 1230515664, 3580155704 },
	{    1988835001,  986791581, 1230515664 }
};
static int64_t A2p127[3][3] = {
	{    1464411153,  277697599, 1610723613 },
	{      32183930, 1464411153, 1022607788 },
	{    2824425944,   32183930, 2093834863 }
};

/*-------------------------------------------------------------------------*/

static void MatVecModM (int64_t A[3][3], int64_t s[3], int64_t v[3], int64_t m)
/* Returns v = A*s % m.  Assumes that -m < s[i] < m. */
/* Works even if v = s. */
{
	int i;
	int64_t x[3];
	for (i = 0; i < 3; ++i) {
		x[i] = num_MultMod (A[i][0], s[0], 0.0, m);
		x[i] = num_MultMod (A[i][1], s[1], x[i], m);
		x[i] = num_MultMod (A[i][2], s[2], x[i], m);
	}
	for (i = 0; i < 3; ++i)
		v[i] = x[i];
}

/* This part is adapted from the code written by Sebastiano Vigna (vigna@acm.org) */
static double U01 (rngstream g) {
	int64_t p, r;
	r = g->Cg[2] - g->Cg[5];
	r -= m1 * ((r - 1) >> 63);
	p = (a12 * g->Cg[1] - a13n * g->Cg[0] + (m1 * a13n)) % m1;
	g->Cg[0] = g->Cg[1];
	g->Cg[1] = g->Cg[2];
	g->Cg[2] = p;
	p = (a21 * g->Cg[5] - a23n * g->Cg[3] + (m2 * a23n)) % m2;
	g->Cg[3] = g->Cg[4];
	g->Cg[4] = g->Cg[5];
	g->Cg[5] = p;

	return r * norm;
}

static int CheckSeed (int64_t seed[6]) {
	/* Check that the seeds are legitimate values. Returns 0 if legal seeds,
	   exits otherwise */
	int i;
	char str[80];

	for (i = 0; i < 3; ++i) {
		sprintf(str, "Seed[%1d] >= m1, Seed is not set.\n", i);
		util_Assert(seed[i] < m1,str);
	}

	for (i = 3; i < 6; ++i) {
        sprintf(str, "Seed[%1d] >= m2, Seed is not set.\n", i);
		util_Assert(seed[i] < m2,str);
	}

    util_Assert(!(seed[0] == 0 && seed[1] == 0 && seed[2] == 0),"First 3 seeds = 0.");
    util_Assert(!(seed[3] == 0 && seed[4] == 0 && seed[5] == 0),"Last 3 seeds = 0.");

    return 0;
}


/*---------------------------------------------------------------------*/
/* Public part.                                                        */
/*---------------------------------------------------------------------*/


rngstream rngstream_CreateStream () {
	int i;
	rngstream g;

	g = (rngstream) malloc (sizeof (struct rngstream_InfoState));
	if (g == NULL) {
		printf ("rngstream_CreateStream: No more memory\n\n");
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

void rngstream_DeleteStream (rngstream * p)
{
	if (*p == NULL)
		return;
	free (*p);
	*p = NULL;
}

/*-------------------------------------------------------------------------*/

void rngstream_ResetStartStream (rngstream g)
{
	int i;
	for (i = 0; i < 6; ++i)
		g->Cg[i] = g->Ig[i];
}

/*-------------------------------------------------------------------------*/

int rngstream_SetPackageSeed (int64_t seed[6])
{
	int i;
	CheckSeed(seed);
	for (i = 0; i < 6; ++i)
		nextSeed[i] = seed[i];
	return 0;                  /* SUCCESS */
}

/*-------------------------------------------------------------------------*/

int rngstream_SetSeed (rngstream g, int64_t seed[6])
{
	int i;
	CheckSeed(seed);
	for (i = 0; i < 6; ++i)
		g->Cg[i] = g->Ig[i] = seed[i];
	return 0;                  /* SUCCESS */
}

/*-------------------------------------------------------------------------*/

void rngstream_GetState (rngstream g, int64_t seed[6])
{
	int i;
	for (i = 0; i < 6; ++i)
		seed[i] = g->Cg[i];
}

/*-------------------------------------------------------------------------*/

void rngstream_WriteState (rngstream g)
{
	int i;
	if (g == NULL)
		return;
	printf ("The current state of the rngstream");
	printf (":\n   Cg = { ");

	for (i = 0; i < 5; i++) {
		printf ("%lld, ", (int64_t) g->Cg[i]);
	}
	printf ("%lld }\n\n", (int64_t) g->Cg[5]);
}

/*-------------------------------------------------------------------------*/

double rngstream_RandU01 (rngstream g)
{
	return U01 (g);
}

/*-------------------------------------------------------------------------*/

int rngstream_RandInt (rngstream g, int i, int j)
{
	return i + (int) ((j - i + 1.0) * rngstream_RandU01 (g));
}
