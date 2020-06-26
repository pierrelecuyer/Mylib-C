#include "bitvector.h"
#include "bitmatrix.h"
#include <stdio.h>
#include <stdlib.h>

#define MC 0x8000000000000000ULL

uint64_t MMC[64] = {MC, MC >> 1, MC >> 2, MC >> 3, MC >> 4, MC >> 5, MC >> 6, MC >> 7,
	            MC >> 8, MC >> 9, MC >> 10, MC >> 11, MC >> 12, MC >> 13, MC >> 14, MC >> 15,
	            MC >> 16, MC >> 17, MC >> 18, MC >> 19, MC >> 20, MC >> 21, MC >> 22, MC >> 23,
	            MC >> 24, MC >> 25, MC >> 26, MC >> 27, MC >> 28, MC >> 29, MC >> 30, MC >> 31,
	            MC >> 32, MC >> 33, MC >> 34, MC >> 35, MC >> 36, MC >> 37, MC >> 38, MC >> 39,
	            MC >> 40, MC >> 41, MC >> 42, MC >> 43, MC >> 44, MC >> 45, MC >> 46, MC >> 47,
	            MC >> 48, MC >> 49, MC >> 50, MC >> 51, MC >> 52, MC >> 53, MC >> 54, MC >> 55,
	            MC >> 56, MC >> 57, MC >> 58, MC >> 59, MC >> 60, MC >> 61, MC >> 62, MC >> 63,};


void bitmatrix_allocate (bitmatrix_matrix* m, int r, int b, int t)
{
	int i,j;
	m->rows = (bitvector_vector **) calloc ((size_t)r, sizeof(bitvector_vector*));

	for (i = 0; i < r; i++) {
		if (!(m->rows[i] = (bitvector_vector*) calloc ((size_t)t, sizeof(bitvector_vector)))) {
			printf ("\n*** Memoire insuffisante pour bitmatrix_allocate() ! r=%d***\n",r);
			exit(1);
		}
		for(j=0; j<t; j++)
			bitvector_allocate(&(m->rows[i][j]),b);
	}

	m->r=r;
	m->t=t;
	m->b=b;
}


void bitmatrix_free (bitmatrix_matrix *m)
{
	int i,j;
	for (i = 0; i < m->r; i++) {
		for(j=0; j<m->t; j++)
			bitvector_free(&(m->rows[i][j]));
		free (m->rows[i]);
	}
	free (m->rows);
	m->r=0;
	m->b=0;
	m->t=0;
}


void bitmatrix_display (bitmatrix_matrix *m, int t, int l, int r)
{
	int i, j;

	printf("    ");
	for(i=0; i<t*l; i++)
		printf("%d",(i/100)%10);
	printf("\n    ");
	for(i=0; i<t*l; i++)
		printf("%d",(i/10)%10);
	printf("\n    ");
	for(i=0; i<t*l; i++)
		printf("%d",i%10);
	printf("\n");


	for (i=0; i<r; i++) {
		printf("%3d[",i);
		for (j = 0; j < t; j++) {
			bitvector_display (&(m->rows[i][j]), l);
		}
		printf ("]\n");
	}
	printf ("\n\n");
}

int bitmatrix_hammingWeight (bitmatrix_matrix *m, int r)
{
	int i;
	int weight = 0;
	for (i=0; i<m->t; i++) {
		weight = bitvector_hammingWeight(&m->rows[r][i])+weight;
	}

	return weight;
}

int bitmatrix_weight (bitmatrix_matrix *m)
{
	int i,j;
	int weight = 0;
	for (i=0; i<m->r; i++) {
		for (j=0; j<m->t; j++) {
			weight = bitvector_hammingWeight(&m->rows[i][j])+weight;
		}
	}

	return weight;
}


void bitmatrix_copypart (bitmatrix_matrix *m1, bitmatrix_matrix *m2,
                         int r, int t)
{
	int i,j;
	if(m1==NULL) {
		bitmatrix_allocate(m1,m2->r,m2->b,m2->t);
	}
	else if((m2->r < r) || (m2->t < t) ) {
		printf("Error in bitmatrix_copypart(): source matrix too small %d\n",m2->r/m2->t);
		exit(1);
	}
	else if((m1->r<r) || (m1->t<t)) {
		printf("Error in bitmatrix_copypart(): destination matrix too small\n");
		exit(1);
	}
	for (i=0; i< r; i++)
		for (j = 0; j < t; j++) {
			bitvector_copy(&(m1->rows[i][j]),&(m2->rows[i][j]));
		}
}


void bitmatrix_copySpecial (bitmatrix_matrix *m1, bitmatrix_matrix *m2,
                            int nl, int *col, int t)
{
	int i, j, k, n;

	if(m1==NULL)
		bitmatrix_allocate(m1,m2->r,m2->b,t);
	else{
		if((m2->r != m1->r) || (m2->b != m1->b) )
			printf("Error in bitmatrix_copySpecial(): matrices of different sizes\n");
	}
	n = (m2->b-1)/bitvector_WL;
	for (i=0; i<nl; i++) {
		for (k = 0; k <= n; k++)
			(m1->rows[i])[0].vect[k] = (m2->rows[i])[0].vect[k];
		for (j = 1; j < t; j++)
			for (k = 0; k <= n; k++)
				(m1->rows[i])[j].vect[k] = (m2->rows[i])[col[j - 1]].vect[k];
	}
}


void bitmatrix_transpose (bitmatrix_matrix *m1, bitmatrix_matrix *m2,
                          int r, int t, int b)
{
	int s, l, m;

	for (s = 0; s < t; s++)
		for (l = 0; l < b; l++) {
			bitvector_clearVector (&m1->rows[l][s]);
			for (m = 0; m < r; m++) {
				if (m2->rows[m][s].vect[0] & (MC >> l)) {
					m1->rows[l][s].vect[0] |= (MC >> m);
				}
			}
		}
}


void bitmatrix_exchangeRows (bitmatrix_matrix *m, int i, int j)
{
	bitvector_vector *p;
	if (i != j) {
		p = m->rows[i];
		m->rows[i] = m->rows[j];
		m->rows[j] = p;
	}
}


void bitmatrix_xorVect (bitmatrix_matrix *m, int r, int s, int min, int max)
{
	int j;
	for (j = min; j < max; j++)
		bitvector_xorSelf(&(m->rows[r][j]),&(m->rows[s][j]));
}


lebool bitmatrix_diagonalize (bitmatrix_matrix *m, int kg, int t, int l, int *gr)
{
	int i, j, cl, rang;

	rang = 0;

	/* On diagonalise la matrice des entrees (i,j) sur l bits          */
	/* avec  0 <= i < kg  et  0 <= j < t .                             */

	for (j = 0; j < t; j++) {
		cl = 1;
		while (cl <= l) {
			/* On cherche dans la j-eme colonne, commencant a la           */
			/* rang-eme ligne, la premiere entree dont le bit le plus      */
			/* significatif est non nul.  Bref, on cherche un pivot.       */
			i = rang;

			while ((i < kg) && (m->rows[i][j].vect[(cl-1)/bitvector_WL] < MMC[(cl-1)%bitvector_WL]))
				i++;
			if (i < kg) {   /* pivot trouve ... */
				bitmatrix_exchangeRows (m, rang, i);
				for (i = rang + 1; i < kg; i++) {
					if (m->rows[i][j].vect[(cl-1)/bitvector_WL] & MMC[(cl-1)%bitvector_WL])
						bitmatrix_xorVect (m, i, rang, j, m->t);
				}
				rang++;
			} else {        /* pas de pivot trouve ... ==> pas de
				           plein rang ... */

				*gr = j; /* no de groupe ou il y a echec moins
				            un  */
				return FALSE; /* c'est j car on indexe a partir de 0
				                 .  */
			}
			cl++;
		}
	}
	return TRUE;                  /* on a trouve tous les pivots ==>
	                                 plein rang ! */
}


int bitmatrix_gaussianElimination (bitmatrix_matrix *m, int r, int l, int t){
	int i, j, cl, rang;
	rang = 0;
	j=0;

	while(j<t) {
		cl = 0;
		while (cl < l) {
			/* On cherche dans la j-eme colonne, commencant a la           */
			/* rang-eme ligne, la premiere entree dont le bit le plus      */
			/* significatif est non nul.  Bref, on cherche un pivot.       */
			i = rang;
			while ((i < r) && ((((m->rows)[i])[j]).vect[(cl)/bitvector_WL] < MMC[(cl)%bitvector_WL]))
				i++;
			if (i < r) {   /* pivot trouve ... */
				bitmatrix_exchangeRows (m, rang, i);
				for (i = rang + 1; i < r; i++)
					if ((((m->rows)[i])[j]).vect[(cl)/bitvector_WL] & MMC[(cl)%bitvector_WL])
						bitmatrix_xorVect (m, i, rang, 0, m->t);

				rang++;
				if(rang == r)
					return rang;
			}
			cl++;
		}
		j++;
	}
	return rang;
}


int bitmatrix_specialGaussianElimination (bitmatrix_matrix *m,
                                          int r, int l, int t, int *indices)
{
	int i, j, cl, rang;
	rang = 0;
	j=0;

	while(j<t) {
		cl = 0;
		while (cl < l) {
			/* On cherche dans la j-eme colonne, commencant a la           */
			/* rang-eme ligne, la premiere entree dont le bit le plus      */
			/* significatif est non nul.  Bref, on cherche un pivot.       */
			i = rang;
			while ((i < r) && ((((m->rows)[i])[indices[j]]).vect[(cl)/bitvector_WL] < MMC[(cl)%bitvector_WL]))
				i++;
			if (i < r) {   /* pivot trouve ... */
				bitmatrix_exchangeRows (m, rang, i);
				for (i = rang + 1; i < r; i++)
					if ((((m->rows)[i])[indices[j]]).vect[(cl)/bitvector_WL] & MMC[(cl)%bitvector_WL])
						bitmatrix_xorVect (m, i, rang, 0, m->t);

				rang++;
				if(rang == r)
					return rang;
			}
			cl++;
		}
		j++;
	}
	return rang;
}


int bitmatrix_completeElimination (bitmatrix_matrix *m, int r, int l, int t)
{
	int i, j, cl, rang;
	rang = 0;
	j=0;

	while(j<t) {
		cl = 0;
		while (cl < l) {
			/* On cherche dans la j-eme colonne, commencant a la           */
			/* rang-eme ligne, la premiere entree dont le bit le plus      */
			/* significatif est non nul.  Bref, on cherche un pivot.       */
			i = rang;
			while ((i < r) && ((((m->rows)[i])[j]).vect[(cl)/bitvector_WL] < MMC[(cl)%bitvector_WL]))
				i++;
			if (i < r) {   /* pivot trouve ... */
				bitmatrix_exchangeRows (m, rang, i);
				for (i = 0; i < r; i++)
					if(i!=rang)
						if ((((m->rows)[i])[j]).vect[(cl)/bitvector_WL] & MMC[(cl)%bitvector_WL])
							bitmatrix_xorVect (m, i, rang, 0, m->t);

				rang++;
				if(rang == r)
					return rang;
			}
			else
				return rang;
			cl++;
		}
		j++;
	}
	return rang;
}


lebool bitmatrix_inverse (bitmatrix_matrix *minv, bitmatrix_matrix *m)
{
	bitmatrix_matrix Temp;
	int j,rang;
	if(m->r != m->b) {
		printf("Matrix m is not square!\n");
		exit(1);
	}
	bitmatrix_allocate(&Temp,m->r,m->b,2);
	for(j=0; j<m->b; j++)
		bitvector_copy(&(Temp.rows[j][0]),&(m->rows[j][0]));
	for(j=0; j<m->b; j++) {
		bitvector_canonical(&(Temp.rows[j][1]),j);
	}
	rang = bitmatrix_completeElimination (&Temp, m->r, m->b, 2);

	for(j=0; j<m->b; j++)
		bitvector_copy(&(minv->rows[j][0]),&(Temp.rows[j][1]));

	bitmatrix_free(&Temp);
	return (rang==m->b);
}


void bitmatrix_productByVector (bitvector_vector *v1, bitmatrix_matrix *m,
                                bitvector_vector *v2)
{
	int i,j,res;
	if(m->t!=1) {
		printf("Error in bitmatrix_productByVector(): Not implemented for m->t > 1\n");
		exit(1);
	}
	if(m->b<v2->n*bitvector_WL) {
		printf("Error in bitmatrix_productByVector(): sizes do not match\n");
		exit(1);
	}
	if(v1->n*bitvector_WL < m->r) {
		printf("Error in bitmatrix_productByVector(): sizes do not match\n");
		exit(1);
	}
	bitvector_clearVector(v1);
	for(i=0; i<m->r; i++) {
		res=0;
		for(j=0; j<m->b; j++)
			res += bitvector_getBit(&(m->rows[i][0]),j) * bitvector_getBit(v2,j);
		res%=2;
		if (res) {
			bitvector_setBit(v1,i);
		}
		else {
			bitvector_clearBit(v1,i);
		}
	}
}


void bitmatrix_product (bitmatrix_matrix *m1, bitmatrix_matrix *m2,
                        bitmatrix_matrix *m3)
{
	int i, j;
	if (m2->b != m3->r) {
		printf ("Tailles de matrices non-compatibles, kaput.\n");
		exit (1);
	}

	if (m1->r != m2->r || m1->b != m3->b) {
		printf ("Matrice preallouee de mauvaise taille.\n");
		exit (1);
	}

	for (i = 0; i < m1->r; i++)
		bitvector_clearVector (m1->rows[i]);

	for (i = 0; i < m2->r; i++)
		for (j = 0; j < m2->b; j++) {
			if (bitvector_getBit (m2->rows[i], j))
				bitvector_xorSelf (m1->rows[i], m3->rows[j]);
		}
}


void bitmatrix_power (bitmatrix_matrix *m1, bitmatrix_matrix *m2, int64_t e)
{
	int i;
	bitmatrix_matrix m3;
	bitmatrix_matrix m4;

	if (m2->r != m2->b) {
		printf ("Matrice non carree.\n");
		exit (1);
	}

	if (m1->r != m2->r || m1->b != m2->b) {
		printf ("Matrice preallouee de mauvaise taille.\n");
		exit (1);
	}

	bitmatrix_allocate (&m3, m2->r, m2->b, 1);

	if (e < 0) {
		bitmatrix_inverse (&m3, m2);
		bitmatrix_power (m1, &m3, -e);
		bitmatrix_free (&m3);
		return;
	}
	bitmatrix_allocate (&m4, m2->r, m2->b, 1);

	/* m1 = I */
	for (i = 0; i < m1->r; i++)
		bitvector_canonical (m1->rows[i], i);

	/* m3 = m2^1 */
	bitmatrix_copypart (&m3, m2, m2->r, 1);

	while (e) {
		if (e & 1) {
			bitmatrix_copypart (&m4, m1, m2->r, 1);
			bitmatrix_product (m1, &m4, &m3);
		}

		e >>= 1;

		if (e) {
			bitmatrix_copypart (&m4, &m3, m2->r, 1);
			bitmatrix_product (&m3, &m4, &m4);
		}
	}

	bitmatrix_free (&m3);
	bitmatrix_free (&m4);
}


void bitmatrix_powerOfTwo (bitmatrix_matrix *m1, bitmatrix_matrix *m2,
                           unsigned int e)
{
	unsigned int i;
	bitmatrix_matrix tempMatrix;
	bitmatrix_matrix *ptr = &tempMatrix;

	if (m2->r != m2->b) {
		printf ("Matrice non carree.\n");
		exit (1);
	}
	if (m1->r != m2->r || m1->b != m2->b) {
		printf ("Matrice preallouee de mauvaise taille.\n");
		exit (1);
	}

	bitmatrix_allocate (ptr, m2->r, m2->b, 1);

	if (e == 0) {
		bitmatrix_copypart (m1, m2, m2->r, 1);
		return;
	}
	/* A = B^(2^1) */
	bitmatrix_product (m1, m2, m2);

	for (i = 1; i < e - 1; i += 2) {
		/* AA = A * A */
		bitmatrix_product (ptr, m1, m1);

		/* A = AA * AA */
		bitmatrix_product (m1, ptr, ptr);
	}

	if (i == e - 1) {
		/* AA = A * A */
		bitmatrix_product (ptr, m1, m1);
		bitmatrix_copypart (m1, ptr, ptr->r, 1);
	}

	bitmatrix_free (ptr);
}
