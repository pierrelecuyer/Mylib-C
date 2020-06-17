#include "tables.h"
#include "util.h"
#include "mystr.h"
#include "num.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>



tables_StyleType Style = tables_Plain;

static char OuvrantMat = ' ';     /* Matrix delimitors */
static char FermantMat = ' ';

static char OuvrantVec = ' ';     /* Vector delimitors */
static char FermantVec = ' ';

static char SepareVec = ' ';      /* Element separators */
static char SepareElem = ' ';

#define MaxInd 60
static long HacheTab[MaxInd + 1] = {
	8191, 12109, 16381, 24373, 32749, 48871, 65521, 97777, 131071, 195659,
	262139, 393203, 524287, 786407, 1048573, 1572803, 2097143, 2500097,
	3145711, 3600097, 4194301, 5300003, 6291403, 7300003, 8388593, 9500021,
	10500013, 11500003, 12582917, 13500007, 14500001, 15500011, 16777213,
	17500013, 18500017, 19500101, 20500097, 21300101, 22200001,
	23200097, 24200101, 25165807, 28000097, 30000001, 33554393, 39000001,
	45000097, 50331653, 55000013, 61000001, 67108859, 76000091, 85000007,
	94906247, 134217689, 189812501, 268435399, 379625003, 2147483647, -1
};


long ** tables_CreateMatrix_long  (int m, int n)
{
	int i;
	long **T;
	/* Note: the memory must be allocated in a contiguous way for the matrix
	   to be later used properly, without problems. Source: comp.lang.c -
	   Answers to Frequently Asked Questions
	   http://www.faqs.org/faqs/C-faq/faq/ Questions 6.18, 6.19, 6.20 */

	T = (long **) util_Malloc (n * sizeof (long *));
	T[0] = (long *) util_Malloc (n * m * sizeof (long));
	for (i = 1; i < n; i++)
		T[i] = T[0] + i * m;
	return T;
}


unsigned long ** tables_CreateMatrix_ulong (int m, int n)
{
	int i;
	unsigned long **T;

	T = (unsigned long **) util_Malloc (n * sizeof (unsigned long *));
	T[0] = (unsigned long *) util_Malloc (n * m * sizeof (unsigned long));
	for (i = 1; i < n; i++)
		T[i] = T[0] + i * m;
	return T;
}


double ** tables_CreateMatrix_double  (int m, int n)
{
	int i;
	double **T;

	T = (double **) util_Malloc (n * sizeof (double *));
	T[0] = (double *) util_Malloc (n * m * sizeof (double));
	for (i = 1; i < n; i++)
		T[i] = T[0] + i * m;
	return T;
}


int64_t ** tables_CreateMatrix_int64  (int m, int n)
{
	int i;
	int64_t **T;

	T = (int64_t **) util_Malloc (n * sizeof (int64_t *));
	T[0] = (int64_t *) util_Malloc (n * m * sizeof (int64_t));
	for (i = 1; i < n; i++)
		T[i] = T[0] + i * m;
	return T;
}


uint64_t ** tables_CreateMatrix_uint64 (int m, int n)
{
	int i;
	uint64_t **T;

	T = (uint64_t **) util_Malloc (n * sizeof (uint64_t *));
	T[0] = (uint64_t *) util_Malloc (n * m * sizeof (uint64_t));
	for (i = 1; i < n; i++)
		T[i] = T[0] + i * m;
	return T;
}


void tables_DeleteMatrix_long  (long *** mat)
{
	free ((*mat)[0]);
	free (*mat);
	*mat = NULL;
}


void tables_DeleteMatrix_ulong (unsigned long *** mat)
{
	free ((*mat)[0]);
	free (*mat);
	*mat = NULL;
}


void tables_DeleteMatrix_double  (double *** mat)
{
	free ((*mat)[0]);
	free (*mat);
	*mat = NULL;
}


void tables_DeleteMatrix_int64  (int64_t *** mat)
{
	free ((*mat)[0]);
	free (*mat);
	*mat = NULL;
}


void tables_DeleteMatrix_uint64 (uint64_t *** mat)
{
	free ((*mat)[0]);
	free (*mat);
	*mat = NULL;
}


void tables_CopyTab_double (double mat1[], double mat2[], int n1, int n2)
{
	int i;
	for (i = n1; i <= n2; i++) {
		mat1[i] = mat2[i];
	}
}


void tables_CopyTab_long (long mat1[], long mat2[], int n1, int n2)
{
	int i;
	for (i = n1; i <= n2; i++) {
		mat1[i] = mat2[i];
	}
}


void tables_CopyTab_int64 (int64_t mat1[], int64_t mat2[], int n1, int n2)
{
	int i;
	for (i = n1; i <= n2; i++) {
		mat1[i] = mat2[i];
	}
}


void tables_CopyTab_uint64 (uint64_t mat1[], uint64_t mat2[], int n1, int n2)
{
	int i;
	for (i = n1; i <= n2; i++) {
		mat1[i] = mat2[i];
	}
}


void tables_QuickSort_double (double mat[], int n1, int n2)
{
	int j;
	int i;
	double w;
	double x;
	i = n1;
	j = n2;
	x = mat[(n1 + n2) / 2];
	do {
		while (mat[i] < x)
			++i;
		while (x < mat[j])
			--j;
		if (i <= j) {
			w = mat[i];
			mat[i] = mat[j];
			mat[j] = w;
			++i;
			--j;
		}
	} while (i <= j);
	if (n1 < j)
		tables_QuickSort_double (mat, n1, j);
	if (i < n2)
		tables_QuickSort_double (mat, i, n2);
}


void tables_QuickSort_long (long mat[], int n1, int n2)
{
	int j;
	int i;
	long w;
	long x;
	i = n1;
	j = n2;
	x = mat[(n1 + n2) / 2];
	do {
		while (mat[i] < x)
			++i;
		while (x < mat[j])
			--j;
		if (i <= j) {
			w = mat[i];
			mat[i] = mat[j];
			mat[j] = w;
			++i;
			--j;
		}
	} while (i <= j);
	if (n1 < j)
		tables_QuickSort_long (mat, n1, j);
	if (i < n2)
		tables_QuickSort_long (mat, i, n2);
}


void tables_QuickSort_int64 (int64_t mat[], int n1, int n2)
{
	int j;
	int i;
	int64_t w;
	int64_t x;
	i = n1;
	j = n2;
	x = mat[(n1 + n2) / 2];
	do {
		while (mat[i] < x)
			++i;
		while (x < mat[j])
			--j;
		if (i <= j) {
			w = mat[i];
			mat[i] = mat[j];
			mat[j] = w;
			++i;
			--j;
		}
	} while (i <= j);
	if (n1 < j)
		tables_QuickSort_int64 (mat, n1, j);
	if (i < n2)
		tables_QuickSort_int64 (mat, i, n2);
}


void tables_QuickSort_uint64 (uint64_t mat[], int n1, int n2)
{
	int j;
	int i;
	uint64_t w;
	uint64_t x;
	i = n1;
	j = n2;
	x = mat[(n1 + n2) / 2];
	do {
		while (mat[i] < x)
			++i;
		while (x < mat[j])
			--j;
		if (i <= j) {
			w = mat[i];
			mat[i] = mat[j];
			mat[j] = w;
			++i;
			--j;
		}
	} while (i <= j);
	if (n1 < j)
		tables_QuickSort_uint64 (mat, n1, j);
	if (i < n2)
		tables_QuickSort_uint64 (mat, i, n2);
}


/*=======================================================================*/

void tables_WriteTab_long (long mat[], int n1, int n2, int k, int p,
                           char desc[])
{
	int i;
	printf ("---------------------------------------\n");
	printf ("%s\n", desc);
	if (k > 1) {
		printf ("Elements  %d  to  %d\n\n", n1, n2);
		for (i = n1; i <= n2; i++) {
			printf ("%*ld ", p, mat[i]);
			if (((i + 1 - n1) % k) == 0)
				printf ("\n");
		}
		printf ("\n");
	} else {
		printf ("\n Index        Element\n");
		for (i = n1; i <= n2; i++)
			printf ("%6d   %12ld\n", i, mat[i]);
	}
	printf ("\n");
}


void tables_WriteTab_int64 (int64_t mat[], int n1, int n2, int k, int p,
                            char desc[])
{
	int i;
	printf ("---------------------------------------\n");
	printf ("%s\n", desc);
	if (k > 1) {
		printf ("Elements  %d  to  %d\n\n", n1, n2);
		for (i = n1; i <= n2; i++) {
			printf ("%*lld ", p, mat[i]);
			if (((i + 1 - n1) % k) == 0)
				printf ("\n");
		}
		printf ("\n");
	} else {
		printf ("\n Index        Element\n");
		for (i = n1; i <= n2; i++)
			printf ("%6d   %12lld\n", i, mat[i]);
	}
	printf ("\n");
}


void tables_WriteTab_uint64 (uint64_t mat[], int n1, int n2, int k, int p,
                             char desc[])
{
	int i;
	printf ("---------------------------------------\n");
	printf ("%s\n", desc);
	if (k > 1) {
		printf ("Elements  %d  to  %d\n\n", n1, n2);
		for (i = n1; i <= n2; i++) {
			printf ("%*llu ", p, mat[i]);
			if (((i + 1 - n1) % k) == 0)
				printf ("\n");
		}
		printf ("\n");
	} else {
		printf ("\n Index        Element\n");
		for (i = n1; i <= n2; i++)
			printf ("%6d   %12llu\n", i, mat[i]);
	}
	printf ("\n");
}


void tables_WriteTab_double (double mat[], int n1, int n2, int k,
                             int p1, int p2, int p3, char desc[])
{
	int i;
	printf ("---------------------------------------\n");
	printf ("%s\n", desc);
	if (k > 1) {
		printf ("Elements  %d  to  %d\n\n", n1, n2);
		for (i = n1; i <= n2; i++) {
			/* printf ("%*.*G", p1, p2, V[i]); */
			num_WriteD (mat[i], p1, p2, p3);
			if (((i + 1 - n1) % k) == 0)
				printf ("\n");
		}
		printf ("\n");
	} else {
		printf ("\n Index            Element\n");
		for (i = n1; i <= n2; i++) {
			printf ("%6d", i);
			num_WriteD (mat[i], p1, p2, p3);
			printf ("\n");
		}
	}
	printf ("\n");
}

/*=========================================================================*/


static void FixeDelim (tables_StyleType style)
{
	/* Fixe les delimiteurs pour imprimer une matrice selon un format
	   approprie */
	Style = style;
	switch (style) {
	case tables_Mathematica:
		OuvrantMat = '{';
		FermantMat = '}';
		OuvrantVec = '{';
		FermantVec = '}';
		SepareVec = ',';
		SepareElem = ',';
		break;
	case tables_Matlab:
		OuvrantMat = '[';
		FermantMat = ']';
		OuvrantVec = ' ';
		FermantVec = ' ';
		SepareVec = ' ';
		SepareElem = ' ';
		break;
	default:
		OuvrantMat = ' ';
		FermantMat = ' ';
		OuvrantVec = ' ';
		FermantVec = ' ';
		SepareVec = ' ';
		SepareElem = ' ';
		break;
	}
}


void tables_WriteSubmatrix_long (long** mat, int i1, int i2, int j1, int j2,
                                 int w, tables_StyleType style, char name[])
{
	int i;
	int j;

	FixeDelim (style);
	if (strlen (name) > 0) {
		printf ("%s = ", name);
	}
	printf ("%c\n", OuvrantMat);
	for (i = i1; i <= i2; i++) {
		printf ("%c", OuvrantVec);
		for (j = j1; j <= j2; j++) {
			printf ("%*ld", (int) w, mat[i][j]);
			if (j < j2)
				printf ("%c", SepareElem);
		}
		printf ("%c", FermantVec);
		if (i < i2)
			printf ("%c\n", SepareVec);
	}
	printf ("%c\n\n", FermantMat);
}


void tables_WriteSubmatrix_double (double** mat, int i1, int i2, int j1, int j2,
                                   int w, int p, tables_StyleType style, char name[])
{
	int k;
	int m;
	int j;
	int i;
	unsigned int bidon;
	double prec;
	double x;
	int trouve;
	char S[32];

	FixeDelim (style);
	if (strlen (name) > 0) {
		printf ("%s = ", name);
	}
	prec = pow (10.0, (double) p);
	printf ("%c\n", OuvrantMat);
	for (i = i1; i <= i2; i++) {
		printf ("%c", OuvrantVec);
		for (j = j1; j <= j2; j++) {
			printf (" ");
			switch (style) {
			case tables_Mathematica:
				x = mat[i][j];
				if (((x != 0.0) && (fabs (x) < 0.1)) || (fabs (x) > prec)) {
					sprintf (S, "%.*G", (int) p, x);
					/* automatique avec %G ... : myst_Subst(S, "e", "E"); */
					mystr_Position ("E", S, 0, &bidon, &trouve);
					if (trouve) {
						mystr_Subst (S, "E", "*10^(");
						strncat (S, ")", (size_t) 2);
					}
				} else
					sprintf (S, "%.*f", (int) p, x);
				m = (int) strlen (S);
				for (k = 1; k <= w - m; k++) {
					printf (" ");
				}
				printf ("%s", S);
				break;
			default:
				/* tables_Matlab, Default */
				printf ("%*.*G", (int) w, (int) p, mat[i][j]);
				break;
			}
			if (j < j2)
				printf ("%c", SepareElem);
		}
		printf ("%c", FermantVec);
		if (i < i2)
			printf ("%c\n", SepareVec);
	}
	printf ("%c\n\n", FermantMat);
}


void tables_WriteSubmatrix_int64 (int64_t** mat, int i1, int i2, int j1, int j2,
                                  int w, tables_StyleType style, char name[])
{
	int i;
	int j;

	FixeDelim (style);
	if (strlen (name) > 0) {
		printf ("%s = ", name);
	}
	printf ("%c\n", OuvrantMat);
	for (i = i1; i <= i2; i++) {
		printf ("%c", OuvrantVec);
		for (j = j1; j <= j2; j++) {
			printf ("%*lld", (int) w, mat[i][j]);
			if (j < j2)
				printf ("%c", SepareElem);
		}
		printf ("%c", FermantVec);
		if (i < i2)
			printf ("%c\n", SepareVec);
	}
	printf ("%c\n\n", FermantMat);
}


void tables_WriteSubmatrix_uint64 (uint64_t** mat, int i1, int i2, int j1, int j2,
                                   int w, tables_StyleType style, char name[])
{
	int i;
	int j;

	FixeDelim (style);
	if (strlen (name) > 0) {
		printf ("%s = ", name);
	}
	printf ("%c\n", OuvrantMat);
	for (i = i1; i <= i2; i++) {
		printf ("%c", OuvrantVec);
		for (j = j1; j <= j2; j++) {
			printf ("%*llu", (int) w, mat[i][j]);
			if (j < j2)
				printf ("%c", SepareElem);
		}
		printf ("%c", FermantVec);
		if (i < i2)
			printf ("%c\n", SepareVec);
	}
	printf ("%c\n\n", FermantMat);
}


int64_t tables_HashPrime (int64_t n, double load)
{
	int i;
	double nD;
	util_Assert (n > 0, "tables_HashPrime : n <= 0");
	nD = (double) n;
	i = 1;
	while (i < MaxInd && HacheTab[i] < n)
		++i;
	while (i < MaxInd && load * (double) (HacheTab[i]) < nD)
		++i;
	util_Assert (HacheTab[i] > 0, "tables_HashPrime failed");
	return HacheTab[i];
}


long tables_HashPrime32 (long n, double load)
{
	int i;
	double nD;
	util_Assert (n > 0, "tables_HashPrime32 : n <= 0");
	nD = (double) n;
	i = 1;
	while (i < MaxInd && HacheTab[i] < n)
		++i;
	while (i < MaxInd && load * (double) (HacheTab[i]) < nD)
		++i;
	util_Assert (HacheTab[i] > 0, "tables_HashPrime32 failed");
	return HacheTab[i];
}
