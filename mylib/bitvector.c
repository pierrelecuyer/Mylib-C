#include <stdio.h>
#include <stdlib.h>
#include "bitvector.h"

#define MASK64 0xFFFFFFFFFFFFFFFFULL
#define MC 0x8000000000000000ULL /* 2^63 */


void bitvector_allocate (bitvector_vector *v, int b)
{
	int n;
	n=(b-1)/bitvector_WL+1;
	v->vect = (uint64_t *) calloc ((size_t)n, sizeof(uint64_t));
	v->n = n;
}


void bitvector_free (bitvector_vector *v)
{
	if(v->vect!=NULL) {
		free(v->vect);
	}
	v->n=0;
}


void bitvector_display (bitvector_vector *v, int b)
{
	char *bitvector_string= (char *)malloc(b * sizeof(char));
	unsigned Un;
	Un = 1ULL;
	int j;
	j = 0;
	while (j < b) {
		printf ("%llu", (v->vect[j / bitvector_WL] >> (((bitvector_WL*v->n) - j - 1) % bitvector_WL)) & Un);
		j++;
	}
}


void bitvector_copy (bitvector_vector *v1, bitvector_vector *v2)
{
	int i;

	if(v1->n!=v2->n) {
		printf("Error in bitvector_copy(): vectors of different dimensions! (%d and %d bits)\n",v1->n*bitvector_WL,v2->n*bitvector_WL);
		exit(1);
	}

	if(v2->n==0) {
		printf("Nothing to copy!\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i];
}


void bitvector_copyPart (bitvector_vector *v1, bitvector_vector *v2, int b)
{
	int i,n;

	n=(b-1)/bitvector_WL+1;

	if(v1->n<n) {
		printf("Error in bitvector_copyPart() : The vector A is not large enough!\n");
		exit(1);
	}

	if(v2->n==0) {
		printf("Nothing to copy!\n");
		exit(1);
	}

	for(i=0; i<n; i++)
		v1->vect[i] = v2->vect[i];

	if(b%bitvector_WL) {
		bitvector_vector v3;
		bitvector_allocate(&v3,v1->n*bitvector_WL);
		bitvector_setMaskLow(&v3,b);
		bitvector_andSelf(v1,&v3);
		bitvector_free(&v3);
	}
}


void bitvector_clearVector (bitvector_vector *v)
{
	int i;
	for (i = 0; i < v->n; i++)
		v->vect[i] = 0ULL;
}


void bitvector_setBit (bitvector_vector *v, int b)
{
	int k;
	uint64_t mask;
	k = b/bitvector_WL;
	mask = MC >> (b-k*bitvector_WL);
	v->vect[k] |= mask;
}


int bitvector_getBit (bitvector_vector *v, int b)
{
	int k;
	uint64_t mask;
	k=b/bitvector_WL;
	mask=MC >> (b-k*bitvector_WL);
	if(v->vect[k] & mask)
		return 1;
	else
		return 0;
}


void bitvector_clearBit (bitvector_vector *v, int b)
{
	int k;
	uint64_t mask;
	k = b/bitvector_WL;
	mask = MASK64 ^ (MC >> (b-k*bitvector_WL));
	v->vect[k] &= mask;
}


void bitvector_canonical (bitvector_vector *v, int t)
{
	int n;
	bitvector_clearVector(v);
	n = t/bitvector_WL;
	if(n>v->n-1) {
		printf("Error in  bitvector_canonical(): vector A is not long enough to store BVCanonic[%d].\n",t);
		exit(1);
	}
	v->vect[n] = MC >> (t-n*bitvector_WL);
}


void bitvector_setAllOnes (bitvector_vector *v)
{
	int i;
	for(i=0; i<v->n; i++)
		v->vect[i]=MASK64;
}


lebool bitvector_isZero (bitvector_vector *v)
{
	int j=0;
	while(j<v->n)
		if(v->vect[j++]!=0ULL)
			return FALSE;
	return TRUE;
}


lebool bitvector_areEqual (bitvector_vector *v1, bitvector_vector *v2)
{
	int i;

	if(v1->n!=v2->n) {
		printf("Error in bitvector_areEqual(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v1->n; i++)
		if (v1->vect[i] != v2->vect[i])
			return FALSE;
	return TRUE;
}


lebool bitvector_haveCommonBit (bitvector_vector *v1, bitvector_vector *v2)
{
	int i;
	uint64_t temp = 0ULL;
	if(v1->n != v2->n) {
		printf("Error in bitvector_haveCommonBit(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v1->n; i++)
		temp |= (v1->vect[i] & v2->vect[i]);
	if (temp)
		return TRUE;
	else
		return FALSE;
}


void bitvector_xor (bitvector_vector *v1, bitvector_vector *v2, bitvector_vector *v3)
{
	int i;

	if((v1->n != v2->n) || (v2->n != v3->n)) {
		printf("Error in bitvector_xor(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i] ^ v3->vect[i];
}


void bitvector_xor3 (bitvector_vector *v1, bitvector_vector *v2,
                     bitvector_vector *v3, bitvector_vector *v4)
{
	int i;

	if((v1->n != v2->n) || (v2->n != v3->n) || (v3->n != v4->n)) {
		printf("Error in bitvector_xor3(): Vectors of different sizes\n");
		exit(1);

	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i] ^ v3->vect[i] ^ v4->vect[i];
}


void bitvector_xorSelf (bitvector_vector *v1, bitvector_vector *v2)
{
	int i;

	if((v1->n != v2->n) ) {
		printf("Error in bitvector_xorSelf(): Vectors of different sizes\n");
		exit(1);

	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] ^= v2->vect[i];
}


void bitvector_and (bitvector_vector *v1, bitvector_vector *v2, bitvector_vector *v3)
{
	int i;

	if((v1->n != v2->n) || (v2->n != v3->n)) {
		printf("Error in bitvector_and(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i] & v3->vect[i];
}


void bitvector_andSelf (bitvector_vector *v1, bitvector_vector *v2)
{
	int i;

	if((v1->n != v2->n) ) {
		printf("Error in bitvector_andSelf(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] &= v2->vect[i];
}


void bitvector_andMaskLow (bitvector_vector *v1, bitvector_vector *v2, int t)
{
	int n,m,j;
	if(v1->n != v2->n) {
		printf("Error in bitvector_andMaskLow(): Vectors of different sizes\n");
		exit(1);
	}

	if(t>v2->n*bitvector_WL)
		bitvector_copy(v1,v2);
	else if(t==0)
		bitvector_clearVector(v1);
	else{
		n=t/bitvector_WL;
		m=t-n*bitvector_WL;

		for(j=0; j<n; j++) {
			v1->vect[j] = v2->vect[j];
		}

		if(m!=0) {
			v1->vect[j] = v2->vect[j] & (MASK64 << (bitvector_WL-m));
			j++;
		}

		for(; j<v1->n; j++) {
			v1->vect[j] = 0ULL;
		}
	}
}


void bitvector_andInvMaskLow (bitvector_vector *v1, bitvector_vector *v2, int t)
{
	int n,m,j;
	if(v1->n != v2->n) {
		printf("Error in bitvector_andInvMaskLow(): Vectors of different sizes\n");
		exit(1);
	}

	if(t>v2->n*bitvector_WL)
		bitvector_clearVector(v1);
	else if(t==0)
		bitvector_copy(v1,v2);
	else{
		n=t/bitvector_WL;
		m=t-n*bitvector_WL;
		for(j=0; j<n; j++)
			v1->vect[j] = 0ULL;
		if(m==0)
			v1->vect[j] = v2->vect[j];
		else{
			v1->vect[j] = v2->vect[j] & (MASK64 >> m);
		}
		j++;
		for(; j<v1->n; j++)
			v1->vect[j] = v2->vect[j];
	}
}


void bitvector_leftShift (bitvector_vector *v1, bitvector_vector *v2, int b)
{
	int i;
	int WLmb;
	uint64_t temp;

	if((v1->n != v2->n) ) {
		printf("Error in bitvector_leftShift(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i];
	while (b >= bitvector_WL) {
		for (i = 1; i < v2->n; i++)
			v1->vect[i - 1] = v1->vect[i];
		v1->vect[v2->n - 1] = 0ULL;
		b -= bitvector_WL;
	}

	if (b > 0) {
		WLmb = bitvector_WL - b;
		v1->vect[0] <<= b;
		for (i = 1; i < v2->n; i++) {
			temp = v1->vect[i] >> WLmb;
			v1->vect[i - 1] |= temp;
			v1->vect[i] <<= b;
		}
	}
}


void bitvector_rightShift (bitvector_vector *v1, bitvector_vector *v2, int b)
{
	int i;
	int WLmb;
	uint64_t temp;
	if((v1->n != v2->n) ) {
		printf("Error in bitvector_rightShift(): Vectors of different sizes\n");
		exit(1);
	}

	for (i = 0; i < v2->n; i++)
		v1->vect[i] = v2->vect[i];
	while (b >= bitvector_WL) {
		for (i = v2->n; i > 1; i--)
			v1->vect[i - 1] = v1->vect[i - 2];
		v1->vect[0] = 0ULL;
		b -= bitvector_WL;
	}
	if (b > 0) {
		WLmb = bitvector_WL - b;
		v1->vect[v2->n - 1] >>= b;
		for (i = v2->n - 2; i >= 0; i--) {
			temp = v1->vect[i] << WLmb;
			v1->vect[i + 1] |= temp;
			v1->vect[i] >>= b;
		}
	}
}


void bitvector_leftShiftSelf (bitvector_vector *v, int b)
{
	int i;
	int WLmb;
	uint64_t temp;

	while (b >= bitvector_WL) {
		for (i = 1; i < v->n; i++)
			v->vect[i - 1] = v->vect[i];
		v->vect[v->n - 1] = 0ULL;
		b -= bitvector_WL;
	}
	if (b > 0) {
		WLmb = bitvector_WL - b;
		v->vect[0] <<= b;
		for (i = 1; i < v->n; i++) {
			temp = v->vect[i] >> WLmb;
			v->vect[i - 1] |= temp;
			v->vect[i] <<= b;
		}
	}
}


void bitvector_leftShift1Self (bitvector_vector *v)
{
	int i;
	v->vect[0] <<= 1;
	for (i = 1; i < v->n; i++) {
		if (v->vect[i] & MC)
			v->vect[i - 1] |= 0x1ULL;
		v->vect[i] <<= 1;
	}
}


void bitvector_rightShiftSelf (bitvector_vector *v, int b)
{
	int i;
	int WLmb;
	uint64_t temp;

	while (b >= bitvector_WL) {
		for (i = v->n - 1; i > 0; i--)
			v->vect[i] = v->vect[i - 1];
		v->vect[0] = 0ULL;
		b -= bitvector_WL;
	}
	if (b > 0) {
		WLmb = bitvector_WL - b;
		v->vect[v->n - 1] >>= b;
		for (i = v->n - 2; i >= 0; i--) {
			temp = v->vect[i] << WLmb;
			v->vect[i + 1] |= temp;
			v->vect[i] >>= b;
		}
	}
}


void bitvector_flip (bitvector_vector *v)
{
	int i;
	for(i=0; i<v->n; i++)
		v->vect[i]=~v->vect[i];
}


void bitvector_setInvMaskLow (bitvector_vector *v, int t)
{
	bitvector_setAllOnes(v);
	bitvector_rightShiftSelf(v,t);
}


void bitvector_setMaskLow (bitvector_vector *v, int t)
{
	bitvector_setInvMaskLow(v,t);
	bitvector_flip(v);
}
