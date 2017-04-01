#include "basics.h"
#include "kummer.h"
#include "measurement.h"
#include "gfe51.h"
int main(){
	int i,j,k,bit;
	unsigned int dep=0;
	char c;
	//unsigned char bit;
	gfe4x npi,np,npt,temp2;
	gfe temp,work[4],re[4],x,z,xinvz;
	
	//sample scalar: you can change it and also can pass it as an argument of the main
	unsigned char n[31] = { 18, 232, 169, 34, 110, 104, 220, 202, 204, 35, 37, 193, 125, 218, 178, 157, 112, 8, 122, 27, 75, 7, 183, 10, 125, 205, 76, 116, 77, 216, 201};
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

