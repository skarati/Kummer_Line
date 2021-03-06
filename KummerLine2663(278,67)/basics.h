#ifndef BASICS_H_
#define BASICS_H_

#include <immintrin.h>

#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <inttypes.h>
#include <stdint.h>



#define align __attribute__ ((aligned (32)))

#if !defined (ALIGN16)
	# if defined (__GNUC__)
		# define ALIGN32 __attribute__ ( (aligned (32)))
	# else
		# define ALIGN32 __declspec (align (32))
	# endif
#endif

#define CRYPTO_SCALARBYTES 32
#define CRYPTO_BYTES 48

typedef unsigned char u8;
typedef unsigned long long u64;
typedef unsigned __int128 u128;
typedef __m256i vec;

typedef struct{
	unsigned long long v[10];
}gfe;

typedef struct{
	u64 v[5];
}gfe54;


typedef struct {
  	vec v[10];
}gfe4x;

const unsigned char base[68] = {
  105,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
} ;
//gfe p = {134217725ULL, 134217727ULL, 134217727ULL, 134217727ULL, 134217727ULL, 134217727ULL, 134217727ULL, 134217727ULL, 134217727ULL, 8388607ULL}

// gfe adjust_invert = {1ULL, 149130802ULL, 59652323ULL, 238609294ULL, 149130808ULL, 59652323ULL, 238609294ULL, 149130808ULL, 59652323ULL, 104391566ULL};

const vec zero = {0,0,0,0};
const vec plusminusplusminus = {0,-1,0,-1};
const vec and01 = {0x00000000ffffffff,0x00000000ffffffff,0x00000000ffffffff,0x00000000ffffffff};
const vec BABA = {211,345,211,345};//{20,81,20,81};
const vec bazx = {67,278,1,361};//{61,101,1,4};
const vec ab11 = {1,1,67,278};//{1,1,61,101};
const vec zxba = {1,361,67,278};//{1,4,61,101};
const vec abxz[2] = {{67,278,1,361}, {1,361,67,278}};//{{61,101,1,4}, {1,4,61,101}};

const u64 mask27 = 0x7ffffff;
const u64 mask23 = 0x07fffff;
const u64 mask54 = 0x3fffffffffffff;
const u64 mask50 = 0x3ffffffffffff;

inline void makeUnique(gfe54 *op, gfe54 *inp) {
        gfe t[2];
        u8 i;

        for(i=0;i<5;i++) t[0].v[i] = inp->v[i];
        for(i=1;i<5;i++) t[1].v[i] = 0; t[1].v[0] = inp->v[0] - ((1ULL<<54)-3);
        if (
                ((inp->v[4]&mask27)==mask50) &&
                ((inp->v[3]&mask27)==mask54) &&
                ((inp->v[2]&mask27)==mask54) &&
                ((inp->v[1]&mask27)==mask54) &&
                (inp->v[0]>=((1ULL<<54)-3))
        ) {
                for(i=0;i<5;i++) op->v[i] = t[1].v[i];
        } else {
                for(i=0;i<5;i++) op->v[i] = t[0].v[i];
        }
}


void convert_ctoi(gfe *r64, const unsigned char r[34]){
	r64->v[0]  = r[0];				/*8*/
	r64->v[0] |= ((u64)r[1] << 8);			/*16*/
	r64->v[0] |= ((u64)r[2] << 16);			/*24*/
	r64->v[0] |= (((u64)(r[3]&0x07)) << 24);	/*27*/

	r64->v[1]  = ((u64)(r[3]&0xf8)>>3);		/*5*/
	r64->v[1] |= ((u64)r[4] << 5);			/*13*/
	r64->v[1] |= ((u64)r[5] << 13);			/*21*/
	r64->v[1] |= (((u64)(r[6])&0x3f)<< 21);		/*27*/

	r64->v[2]  = (((u64)(r[6])&0xc0)>> 6);		/*2*/
	r64->v[2] |= ((u64)r[7] << 2);			/*10*/
	r64->v[2] |= ((u64)r[8] << 10);			/*18*/
	r64->v[2] |= ((u64)r[9] << 18);			/*26*/
	r64->v[2] |= (((u64)(r[10]&0x01)) << 26);	/*27*/

	r64->v[3]  = ((u64)(r[10]&0xfe)>>1);		/*7*/
	r64->v[3] |= ((u64)r[11] << 7);			/*15*/
	r64->v[3] |= ((u64)r[12] << 15);		/*23*/
	r64->v[3] |= (((u64)r[13]&0x0f)<< 23);		/*27*/

	r64->v[4]  = (((u64)r[13]&0xf0)>>4);		/*4*/
	r64->v[4] |= ((u64)r[14] << 4);			/*12*/
	r64->v[4] |= ((u64)r[15] << 12);		/*20*/
	r64->v[4] |= (((u64)(r[16]&0x7f)) << 20);	/*27*/

	r64->v[5]  = ((u64)(r[16]&0x80)>>7);		/*1*/
	r64->v[5] |= ((u64)r[17] << 1);			/*9*/
	r64->v[5] |= ((u64)r[18] << 9);			/*17*/
	r64->v[5] |= ((u64)(r[19])<< 17);		/*25*/
	r64->v[5] |= (((u64)(r[20])&0x03)<< 25);	/*27*/

	r64->v[6]  = (((u64)(r[20])&0xfc)>>2);		/*6*/
	r64->v[6] |= ((u64)r[21] << 6);			/*14*/
	r64->v[6] |= ((u64)r[22] << 14);		/*22*/
	r64->v[6] |= (((u64)(r[23]&0x1f)) << 22);	/*27*/

	r64->v[7]  = ((u64)(r[23]&0xe0)>>5);		/*3*/
	r64->v[7] |= ((u64)r[24] << 3);			/*11*/
	r64->v[7] |= ((u64)r[25] << 11);		/*19*/
	r64->v[7] |= ((u64)r[26]<< 19);			/*27*/

	r64->v[8]  = r[27];				/*8*/
	r64->v[8] |= ((u64)r[28] << 8);			/*16*/
	r64->v[8] |= ((u64)r[29] << 16);		/*24*/
	r64->v[8] |= (((u64)(r[30]&0x07)) << 24);	/*27*/

	r64->v[9]  = ((u64)(r[30]&0xf8)>>3);		/*5*/
	r64->v[9] |= ((u64)r[31] << 5);			/*13*/
	r64->v[9] |= ((u64)r[32] << 13);		/*21*/
	r64->v[9] |= (((u64)(r[33])&0x03)<< 21);	/*23*/


}

void pack54(gfe *r64, gfe54 *r54){
	r54->v[0]  = (r64->v[0]&0x7ffffff);		/*27*/
	r54->v[0] |= (r64->v[1]&0x7ffffff)<<27;		/*54*/

	r54->v[1]  = (r64->v[2]&0x7ffffff);		/*27*/
	r54->v[1] |= (r64->v[3]&0x7ffffff)<<27;		/*54*/ 
 
	r54->v[2]  = (r64->v[4]&0x7ffffff);		/*27*/
	r54->v[2] |= (r64->v[5]&0x7ffffff)<<27;		/*54*/ 

	r54->v[3]  = (r64->v[6]&0x7ffffff);		/*27*/
	r54->v[3] |= (r64->v[7]&0x7ffffff)<<27;		/*54*/ 

	r54->v[4]  = (r64->v[8]&0x7ffffff);		/*27*/
	r54->v[4] |= (r64->v[9]&0x7fffff)<<27;		/*54*/ 

}

void unpack54(gfe *r64, gfe54 *r54){
	r64->v[0] = r54->v[0]&0x7ffffff;		/*27*/
	r64->v[1] = (r54->v[0]>>27)&0x7ffffff;		/*54*/

	r64->v[2] = r54->v[1]&0x7ffffff;		/*27*/
	r64->v[3] = (r54->v[1]>>27)&0x7ffffff;		/*54*/

	r64->v[4] = r54->v[2]&0x7ffffff;		/*27*/
	r64->v[5] = (r54->v[2]>>27)&0x7ffffff;		/*54*/

	r64->v[6] = r54->v[3]&0x7ffffff;		/*27*/
	r64->v[7] = (r54->v[3]>>27)&0x7ffffff;		/*54*/

	r64->v[8] = r54->v[4]&0x7ffffff;		/*27*/
	r64->v[9] = (r54->v[4]>>27)&0x7fffff;		/*50*/
}



void convert_itoc(gfe *r64, unsigned char r[34]){
	r[0] = r64->v[0] & 0xff;		/*8*/
	r64->v[0] = r64->v[0]>>8;	
	r[1] = r64->v[0] & 0xff;		/*16*/
	r64->v[0] = r64->v[0]>>8;
	r[2] = r64->v[0] & 0xff;		/*24*/
	r64->v[0] = r64->v[0]>>8;
	r[3] = r64->v[0] & 0x7;			/*27*/

	r[3] = r[3]|(r64->v[1] & 0x1f) << 5;	/*5*/
	r64->v[1] = r64->v[1] >> 5;
	r[4] = r64->v[1] & 0xff;		/*13*/
	r64->v[1] = r64->v[1]>>8;
	r[5] = r64->v[1] & 0xff;		/*21*/
	r64->v[1] = r64->v[1]>>8;
	r[6] = r64->v[1] & 0x3f;		/*27*/

	r[6] = r[6]|(r64->v[2] & 0x3) << 6;	/*2*/
	r64->v[2] = r64->v[2] >> 2;
	r[7] = r64->v[2] & 0xff;		/*10*/
	r64->v[2] = r64->v[2]>>8;
	r[8] = r64->v[2] & 0xff;		/*18*/
	r64->v[2] = r64->v[2]>>8;
	r[9] = r64->v[2] & 0xff;		/*26*/
	r64->v[2] = r64->v[2]>>8;		
	r[10] = r64->v[2] & 0x1;		/*27*/

	r[10] = r[10]|(r64->v[3] & 0x7f) << 1;	/*7*/
	r64->v[3] = r64->v[3] >> 7;
	r[11] = r64->v[3] & 0xff;		/*15*/
	r64->v[3] = r64->v[3]>>8;	
	r[12] = r64->v[3] & 0xff;		/*23*/
	r64->v[3] = r64->v[3]>>8;
	r[13] = r64->v[3] & 0xf;		/*27*/

	r[13] = r[13]|(r64->v[4] & 0xf) << 4;	/*4*/
	r64->v[4] = r64->v[4] >> 4;
	r[14] = r64->v[4] & 0xff;		/*12*/
	r64->v[4] = r64->v[4]>>8;
	r[15] = r64->v[4] & 0xff;		/*20*/
	r64->v[4] = r64->v[4]>>8;
	r[16] = r64->v[4] & 0x7f;		/*27*/

	r[16] = r[16]|(r64->v[5] & 0x1) << 7;	/*1*/
	r64->v[5] = r64->v[5] >> 1;
	r[17] = r64->v[5] & 0xff;		/*9*/
	r64->v[5] = r64->v[5] >> 8;
	r[18] = r64->v[5] & 0xff;		/*17*/
	r64->v[5] = r64->v[5]>>8;
	r[19] = r64->v[5] & 0xff;		/*25*/
	r64->v[5] = r64->v[5]>>8;
	r[20] = r64->v[5] & 0x3;		/*27*/

	r[20] = r[20]|(r64->v[6] & 0x3f) << 2;	/*6*/
	r64->v[6] = r64->v[6] >> 6;
	r[21] = r64->v[6] & 0xff;		/*14*/
	r64->v[6] = r64->v[6]>>8;
	r[22] = r64->v[6] & 0xff;		/*22*/
	r64->v[6] = r64->v[6]>>8;
	r[23] = r64->v[6] & 0x1f;		/*27*/
	
	r[23] = r[23]|(r64->v[7] & 0x7) << 5;	/*3*/
	r64->v[7] = r64->v[7] >> 3;
	r[24] = r64->v[7] & 0xff;		/*11*/
	r64->v[7] = r64->v[7] >> 8;
	r[25] = r64->v[7] & 0xff;		/*19*/
	r64->v[7] = r64->v[7]>>8;
	r[26] = r64->v[7] & 0xff;		/*27*/

	r[27] = r64->v[8] & 0xff;		/*8*/
	r64->v[8] = r64->v[8]>>8;	
	r[28] = r64->v[8] & 0xff;		/*16*/
	r64->v[8] = r64->v[8]>>8;
	r[29] = r64->v[8] & 0xff;		/*24*/
	r64->v[8] = r64->v[8]>>8;
	r[30] = r64->v[8] & 0x7;		/*27*/

	r[30] = r[30]|(r64->v[9] & 0x1f) << 3;	/*5*/
	r64->v[9] = r64->v[9] >> 5;
	r[31] = r64->v[9] & 0xff;		/*13*/
	r64->v[9] = r64->v[9]>>8;
	r[32] = r64->v[9] & 0xff;		/*21*/
	r64->v[9] = r64->v[9]>>8;
	r[33] = r64->v[9] & 0x3;		/*23*/
}

void convert_i54toc(gfe54 *r54, unsigned char r[34]){
	r[0] = r54->v[0] & 0xff;		/*8*/
	r54->v[0] = r54->v[0]>>8;	
	r[1] = r54->v[0] & 0xff;		/*16*/
	r54->v[0] = r54->v[0]>>8;
	r[2] = r54->v[0] & 0xff;		/*24*/
	r54->v[0] = r54->v[0]>>8;
	r[3] = r54->v[0] & 0xff;		/*32*/
	r54->v[0] = r54->v[0]>>8;
	r[4] = r54->v[0] & 0xff;		/*40*/
	r54->v[0] = r54->v[0]>>8;
	r[5] = r54->v[0] & 0xff;		/*48*/
	r54->v[0] = r54->v[0]>>8;
	r[6] = r54->v[0] & 0x3f;		/*54*/

	r[6] = r[6]|(r54->v[1] & 0x3) << 6;	/*2*/
	r54->v[1] = r54->v[1] >> 2;
	r[7] = r54->v[1] & 0xff;		/*10*/
	r54->v[1] = r54->v[1]>>8;
	r[8] = r54->v[1] & 0xff;		/*18*/
	r54->v[1] = r54->v[1]>>8;
	r[9] = r54->v[1] & 0xff;		/*26*/
	r54->v[1] = r54->v[1]>>8;		
	r[10] = r54->v[1] & 0xff;		/*34*/
	r54->v[1] = r54->v[1]>>8;
	r[11] = r54->v[1] & 0xff;		/*42*/
	r54->v[1] = r54->v[1]>>8;	
	r[12] = r54->v[1] & 0xff;		/*50*/
	r54->v[1] = r54->v[1]>>8;
	r[13] = r54->v[1] & 0xf;		/*54*/

	r[13] = r[13]|(r54->v[2] & 0xf) << 4;	/*4*/
	r54->v[2] = r54->v[2] >> 4;
	r[14] = r54->v[2] & 0xff;		/*12*/
	r54->v[2] = r54->v[2]>>8;
	r[15] = r54->v[2] & 0xff;		/*20*/
	r54->v[2] = r54->v[2]>>8;
	r[16] = r54->v[2] & 0xff;		/*28*/
	r54->v[2] = r54->v[2]>>8;
	r[17] = r54->v[2] & 0xff;		/*36*/
	r54->v[2] = r54->v[2]>>8;
	r[18] = r54->v[2] & 0xff;		/*44*/
	r54->v[2] = r54->v[2]>>8;
	r[19] = r54->v[2] & 0xff;		/*52*/
	r54->v[2] = r54->v[2]>>8;
	r[20] = r54->v[2] & 0x3;		/*54*/

	r[20] = r[20]|(r54->v[3] & 0x3f) << 2;	/*6*/
	r54->v[3] = r54->v[3] >> 6;
	r[21] = r54->v[3] & 0xff;		/*14*/
	r54->v[3] = r54->v[3]>>8;
	r[22] = r54->v[3] & 0xff;		/*22*/
	r54->v[3] = r54->v[3]>>8;
	r[23] = r54->v[3] & 0xff;		/*30*/
	r54->v[3] = r54->v[3]>>8;
	r[24] = r54->v[3] & 0xff;		/*38*/
	r54->v[3] = r54->v[3]>>8;
	r[25] = r54->v[3] & 0xff;		/*46*/
	r54->v[3] = r54->v[3]>>8;
	r[26] = r54->v[3] & 0xff;		/*54*/

	r[27] = r54->v[4] & 0xff;		/*8*/
	r54->v[4] = r54->v[4]>>8;	
	r[28] = r54->v[4] & 0xff;		/*16*/
	r54->v[4] = r54->v[4]>>8;
	r[29] = r54->v[4] & 0xff;		/*24*/
	r54->v[4] = r54->v[4]>>8;
	r[30] = r54->v[4] & 0xff;		/*32*/
	r54->v[4] = r54->v[4]>>8;
	r[31] = r54->v[4] & 0xff;		/*40*/
	r54->v[4] = r54->v[4]>>8;
	r[32] = r54->v[4] & 0xff;		/*48*/
	r54->v[4] = r54->v[4]>>8;
	r[33] = r54->v[4] & 0x3;		/*50*/
}


void gfe4_f_gfe(gfe4x *r64, gfe *m){
  	int i;

  	for (i = 0;i < 10;++i) {
	    	0[(u64 *) &r64->v[i]] = m[0].v[i];
	   	1[(u64 *) &r64->v[i]] = m[1].v[i];
	    	2[(u64 *) &r64->v[i]] = m[2].v[i];
	    	3[(u64 *) &r64->v[i]] = m[3].v[i];
  	}
}

void gfe4_f_gfe_part1(gfe4x *r64, gfe *m){
	int i;
	
	for (i = 0;i < 10;++i){
		0[(u64 *) &r64->v[i]] = 0;
		1[(u64 *) &r64->v[i]] = 0;
		2[(u64 *) &r64->v[i]] = m[0].v[i];
		3[(u64 *) &r64->v[i]] = m[1].v[i];
  	}
}
void gfe4_f_gfe_part2(gfe4x *r64, gfe *m){
	int i;
	
	for (i = 0;i < 10;++i){
		0[(u64 *) &r64->v[i]] = m[0].v[i];
		1[(u64 *) &r64->v[i]] = m[1].v[i];
  	}
}


void gfe4_t_gfe(gfe4x *r64, gfe *m){
	int i;

  	for (i = 0;i < 10;++i) {
	    	m[0].v[i] = 0[(u64 *) &r64->v[i]];
	    	m[1].v[i] = 1[(u64 *) &r64->v[i]];
	    	m[2].v[i] = 2[(u64 *) &r64->v[i]];
	    	m[3].v[i] = 3[(u64 *) &r64->v[i]];
  	}
}

/*
void set_base_point(gfe4x *r64_1, gfe4x *r64_2, gfe *m){
	int i;

		0[(u64 *) &r64_1->v[0]] = 61;
		1[(u64 *) &r64_1->v[0]] = 101;
		2[(u64 *) &r64_1->v[0]] = m[1].v[0];
		3[(u64 *) &r64_1->v[0]] = m[0].v[0];
	
	for (i = 1;i < 9;++i){
		0[(u64 *) &r64_1->v[i]] = 0;
		1[(u64 *) &r64_1->v[i]] = 0;
		2[(u64 *) &r64_1->v[i]] = m[1].v[i];
		3[(u64 *) &r64_1->v[i]] = m[0].v[i];
  	}

		0[(u64 *) &r64_2->v[0]] = m[1].v[0];
		1[(u64 *) &r64_2->v[0]] = m[0].v[0];
		2[(u64 *) &r64_2->v[0]] = 61;
		3[(u64 *) &r64_2->v[0]] = 101;
	
	for (i = 1;i < 9;++i){
		0[(u64 *) &r64_2->v[i]] = m[1].v[i];
		1[(u64 *) &r64_2->v[i]] = m[0].v[i];
		2[(u64 *) &r64_2->v[i]] = 0;
		3[(u64 *) &r64_2->v[i]] = 0;
  	}

}
*/

void set_base_point(gfe4x *r64, gfe *m){
	int i;

		0[(u64 *) &r64[0].v[0]] = 67;
		1[(u64 *) &r64[0].v[0]] = 278;
		2[(u64 *) &r64[0].v[0]] = m[1].v[0];
		3[(u64 *) &r64[0].v[0]] = m[0].v[0];
	
	for (i = 1;i < 10;++i){
		0[(u64 *) &r64[0].v[i]] = 0;
		1[(u64 *) &r64[0].v[i]] = 0;
		2[(u64 *) &r64[0].v[i]] = m[1].v[i];
		3[(u64 *) &r64[0].v[i]] = m[0].v[i];
  	}

		0[(u64 *) &r64[1].v[0]] = m[1].v[0];
		1[(u64 *) &r64[1].v[0]] = m[0].v[0];
		2[(u64 *) &r64[1].v[0]] = 67;
		3[(u64 *) &r64[1].v[0]] = 278;
	
	for (i = 1;i < 10;++i){
		0[(u64 *) &r64[1].v[i]] = m[1].v[i];
		1[(u64 *) &r64[1].v[i]] = m[0].v[i];
		2[(u64 *) &r64[1].v[i]] = 0;
		3[(u64 *) &r64[1].v[i]] = 0;
  	}

}

vec setVec(u8 *charStr) {

	vec *vecVal;
	vecVal = (vec *)charStr;
	return *vecVal;

}

void printVec(vec *inputVec) {

	u8 *val,i,j;
	val = (u8 *)inputVec;
	for(i=0;i<3;i++) {for(j=0;j<9;j++) printf("%3u, ",val[i*8+j]); printf("\n");}
	for(i=24;i<31;i++) printf("%3u, ",val[i]); printf("%3u ",val[31]); printf("\n");
}

void printVecFirst64Bits(vec *inputVec) { // prints only the first 64 bits

	u8 *val,i,j;
	val = (u8 *)inputVec;
	for(i=0;i<8;i++) printf("%3u, ",val[i]); printf("%3u ",val[8]); printf("\n");
}


void print_c(char *n){
	int i;
	for(i=0; i<34; i++)
		printf("%hhu, ",n[i]);
	printf("\n");

}
void print_gfe(gfe *r64){
	int i;
	for(i=0; i<10; i++)
		printf("%llu, ",r64->v[i]);
	printf("\n");
}

void print_gfe54(gfe54 *r54){
	int i;
	for(i=0; i<5; i++)
		printf("%llu, ",(u64)r54->v[i]);
	printf("\n");
}

#endif


