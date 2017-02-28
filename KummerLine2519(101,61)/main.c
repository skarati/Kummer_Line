#include "basics.h"
#include "kummer.h"
#include "measurement.h"

int main(){
	int i,j,k,bit;
	unsigned int dep=0;
	char c;
	//unsigned char bit;
	gfe4x npi,np,npt,temp2;
	gfe temp,work[4],re[4],x,z,xinvz;
	
	//sample scalar: you can change it and also can pass it as an argument of the main
	unsigned char n[31] = { 18, 232, 169, 34, 110, 104, 220, 202, 204, 35, 37, 193, 125, 218, 178, 157, 
112, 8, 122, 27, 75, 7, 183, 10, 125, 205, 76, 116, 77, 216, 201};
	unsigned char m1[32]={175, 132, 35, 17, 8, 254, 199, 203, 111, 44, 126, 130, 18, 233, 80, 70, 154, 158, 226, 47, 247, 20, 39, 37, 180, 134, 135, 25, 151, 185, 138, 7};
	unsigned char n1[32]={183, 52, 167, 93, 12, 151, 15, 24, 93, 162, 222, 25, 71, 130, 200, 88, 187, 41, 199, 163, 165, 111, 179, 139, 94, 219, 57, 149, 206, 90, 252 };
	unsigned char op[32];
	
	convert_ctoi(&work[0],base);
	convert_ctoi(&work[1],base+32);
		
	gfe4_f_gfe_part1(&npi, work);
	gfe4x_hadamard(&npi, &npi);
	sq_gfe4(&npi, &npi);
	mulconst_gfe4(&npi, &npi, &BABA);
	gfe4x_hadamard(&npi, &npi);
	sq_gfe4(&npi, &npi);
	mulconst_gfe4(&npi, &npi, &ab11);
	gfe4_f_gfe_part2(&npi, work);



	MEASURE({
		scalar_mult_fixed_base(op, npi, n);
	});

	printf("Total CPU cycles for fixed-base scalar multiplication: %.2f.\n", RDTSC_total_clk);
	print_c(op);

	unsigned char base_rand[64];
	for(i=0;i<32;i++) base_rand[i]=op[i];
	base_rand[32] = 1;
	for(i=33;i<64;i++) base_rand[i]=0;
	MEASURE({
		scalar_mult_var_base(op, base_rand, n);
	});
	printf("Total CPU cycles for variable-base scalar multiplication: %.2f.\n", RDTSC_total_clk);
	print_c(op);

	return 0;
}

