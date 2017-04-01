/*
   This file is adapted from amd64-51/fe25519.h:
   'fe25519' is renamed as 'fe51';
   All the redundant functions are removed;
   New function fe51_nsquare is introduced.
*/

#ifndef FE51_H
#define FE51_H

#define crypto_uint64 unsigned long int

extern void mul_gfe54(gfe54 *, const gfe54 *, const gfe54 *);
extern void nsq_gfe54(gfe54 *, const gfe54 *, int);


#endif
