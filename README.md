
*********************************** Kummer Line (101,61)*************************************
Implemented Code of Kummer Line K(101,61) using avx2 intrinsic in Haswell architecture

Implementors: Sabyasachi Karati and Palash Sarkar
contact:      sabyasachi.karati@gmail.com
*********************************************************************************************

Description:
============
1. basics.h contains all the conversion and packing-unpacking modules.
2. kummer.h includes all the implementation related to field arithmetic and Kummer line operations.
3. All the timings are measured using measurment.h.

Steps:
======

1. Extract the file.
2. Go to the directory.
3. run the commands:

    gcc -m64 -mavx2 -O3 -fomit-frame-pointer main.c consts.S mul_gfe*.S nsq_gfe*.S
    
    ./a.out


