#include <stdio.h>
#include "clarinet.h"

// --------
// FMA macros
// the _p_ indicates that the input values are posit type
#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_fma (unsigned char a, unsigned char b) {
#endif
#ifdef PWIDTH_16
void fn_posit_p_fma (unsigned short a, unsigned short b) {
#endif
#ifdef PWIDTH_24
void fn_posit_p_fma (unsigned int a, unsigned int b) {
#endif
#ifdef PWIDTH_32
void fn_posit_p_fma (unsigned int a, unsigned int b) {
#endif
   // input posit values in GPR
   register unsigned int gA asm ("a0") = a;
   register unsigned int gB asm ("a1") = b;

   // intermediate posit values in PPR
   register float pA asm ("ft0");
   register float pB asm ("ft1");

   asm ("pmv.w.x ft0, a0" : "=f" (pA) : "r" (gA));
   asm ("pmv.w.x ft1, a1" : "=f" (pB) : "r" (gB));

   // for instrns which do not have a rd, using zeros for the rd
   // field is necessary as that is the instruction encoding.
   asm ("fma.p    ft0, ft0, ft1" : "=f" (pA) : "f" (pA), "f" (pB));
   return;
}
#endif

void fn_posit_fma (float a, float b) {
   // input float values
   register float fA asm ("fa0") = a;
   register float fB asm ("fa1") = b;

   // intermediate posit values
   register float pA asm ("ft0");
   register float pB asm ("ft1");

   asm ("fcvt.p.s ft0, fa0" : "=f" (pA) : "f" (fA));
   asm ("fcvt.p.s ft1, fa1" : "=f" (pB) : "f" (fB));
   // for instrns which do not have a rd, using zeros for the rd
   // field is necessary as that is the instruction encoding.
   asm ("fma.p    ft0, ft0, ft1" : "=f" (pA) : "f" (pA), "f" (pB));
   return;
}

float fn_float_fma (float a, float b, float acc) {
   // input float values
   register float f_a asm ("fa0") = a;
   register float f_b asm ("fa1") = b;
   register float f_acc asm ("fa2") = acc;
   register float f_prod asm ("fa3");
   register float f_res asm ("fa4");

   asm ("fmul.s    fa3, fa0, fa1" : "=f" (f_prod) : "f" (f_a), "f" (f_b));
   asm ("fadd.s    fa4, fa3, fa2" : "=f" (f_res)  : "f" (f_prod), "f" (f_acc));
   return (f_res);
}

// --------
// Quire initialization macros
// the _p_ indicates that the input values are posit type
void fn_init_p_quire (unsigned int initVal) {
   register unsigned int gI asm ("a0") = initVal;
   register float pI asm ("ft1");
   register float q  asm ("ft0");
   asm ("pmv.w.x ft1, a0" : "=f" (pI) : "r" (gI));
   // for instrns which do not have a rd, using zeros for the rd
   // field is necessary as that is the instruction encoding.
   asm ("fcvt.r.p ft0, ft1" : "=f" (q) : "f" (pI));
   return;
}

void fn_init_quire (float initVal) {
   register float fI asm ("fa0") = initVal;
   register float pQ asm ("ft1");
   register float qQ asm ("ft0");
   asm ("fcvt.p.s ft1, fa0" : "=f" (pQ) : "f" (fI));
   // for instrns which do not have a rd, using zeros for the rd
   // field is necessary as that is the instruction encoding.
   asm ("fcvt.r.p ft0, ft1" : "=f" (qQ) : "f" (pQ));
   return;
}

// --------
// Quire read macros
#ifdef POSIT
#ifdef PWIDTH_8
unsigned char fn_read_p_quire (void) {
#endif
#ifdef PWIDTH_16
unsigned short fn_read_p_quire (void) {
#endif
#ifdef PWIDTH_24
unsigned int fn_read_p_quire (void) {
#endif
#ifdef PWIDTH_32
unsigned int fn_read_p_quire (void) {
#endif
   register float pQ asm ("f0");
   register float gO asm ("a0");
   asm ("fcvt.p.r f0, f0" : "=f" (pQ) : "f" (pQ));
   asm ("pmv.x.w  a0, f0" : "=r" (gO) : "f" (pQ));
   return (gO);
}
#endif

float fn_read_quire (void) {
   register float pQ asm ("f0");
   register float fO asm ("fa0");
   asm ("fcvt.p.r f0, f0" : "=f" (pQ) : "f" (pQ));
   asm ("fcvt.s.p fa0, f0" : "=f" (fO) : "f" (pQ));
   return (fO);
}

// --------
// VDP Routines
// Posit input, posit compute, posit output
#ifdef POSIT
#ifdef PWIDTH_8
unsigned char fn_posit_p_vdp (int r, unsigned char p_a[], unsigned char p_b[]) {
#endif
#ifdef PWIDTH_16
unsigned short fn_posit_p_vdp (int r, unsigned short p_a[], unsigned short p_b[]) {
#endif
#ifdef PWIDTH_24
unsigned int fn_posit_p_vdp (int r, unsigned int p_a[], unsigned int p_b[]) {
#endif
#ifdef PWIDTH_32
unsigned int fn_posit_p_vdp (int r, unsigned int p_a[], unsigned int p_b[]) {
#endif
   unsigned int acc = 0;
   int idx = 0;
   int rep = 0;
   fn_init_p_quire (acc);

   for (idx=0; idx < r; idx ++) fn_posit_p_fma (p_a[idx], p_b[idx]);

   acc = fn_read_p_quire ();
   return (acc);
}
#endif

#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_gemv (unsigned char  v_acc[], int r, unsigned char  m_a[][VSZ], unsigned char  p_b[]) {
#endif
#ifdef PWIDTH_16
void fn_posit_p_gemv (unsigned short v_acc[], int r, unsigned short m_a[][VSZ], unsigned short p_b[]) {
#endif
#ifdef PWIDTH_24
void fn_posit_p_gemv (unsigned int   v_acc[], int r, unsigned int   m_a[][VSZ], unsigned int   p_b[]) {
#endif
#ifdef PWIDTH_32
void fn_posit_p_gemv (unsigned int   v_acc[], int r, unsigned int   m_a[][VSZ], unsigned int   p_b[]) {
#endif
   int idx = 0;
   for (idx=0; idx < r; idx ++)
      v_acc[idx] = fn_posit_p_vdp (r, m_a[idx], p_b);

   return;
}
#endif

#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_gemm (unsigned char  m_acc[][VSZ], int dimension, unsigned char  m_a[][VSZ], unsigned char  m_b[][VSZ]) {
   unsigned char v_acc[VSZ];
#endif
#ifdef PWIDTH_16
void fn_posit_p_gemm (unsigned short m_acc[][VSZ], int dimension, unsigned short m_a[][VSZ], unsigned short m_b[][VSZ]) {
   unsigned short v_acc[VSZ];
#endif
#ifdef PWIDTH_24
void fn_posit_p_gemm (unsigned int   m_acc[][VSZ], int dimension, unsigned int   m_a[][VSZ], unsigned int   m_b[][VSZ]) {
   unsigned int v_acc[VSZ];
#endif
#ifdef PWIDTH_32
void fn_posit_p_gemm (unsigned int   m_acc[][VSZ], int dimension, unsigned int   m_a[][VSZ], unsigned int   m_b[][VSZ]) {
   unsigned int v_acc[VSZ];
#endif
   int ridx = 0; int cidx = 0;

   for (ridx=0; ridx < dimension; ridx++) {
      fn_posit_p_gemv (v_acc, dimension, m_a, m_b[ridx]);
      // implement a transpose to get the result matrix
      for (cidx=0; cidx < dimension; cidx++) {
         m_acc[cidx][ridx] = v_acc[cidx];
      }
   }

   return;
}
#endif

// Float input, posit compute, float output
float fn_posit_vdp (int r, float v_a[], float v_b[]) {
   float acc = 0.0;
   int idx = 0;
   fn_init_quire (acc);
   for (idx=0; idx < r; idx ++) fn_posit_fma (v_a[idx], v_b[idx]);
   acc = fn_read_quire ();
   return (acc);
}

// Float input, posit compute, float output
void fn_posit_gemv (float v_acc[], int r, float m_a[][VSZ], float v_b[]) {
   int idx = 0;
   for (idx=0; idx < r; idx ++)
      v_acc[idx] = fn_posit_vdp (r, m_a[idx], v_b);
   return;
}

// Float input, float compute, float output. Code written to allow compiler optimization wrt
// function calls.
void fn_posit_gemm (float m_acc[][VSZ], int dimension, float m_a[][VSZ], float m_b[][VSZ]) {
   int ridx = 0; int cidx = 0;
   float v_acc[VSZ];

   for (ridx=0; ridx < dimension; ridx++) {
      fn_posit_gemv (v_acc, dimension, m_a, m_b[ridx]);
      // implement a transpose to get the result matrix
      for (cidx=0; cidx < dimension; cidx++) {
         m_acc[cidx][ridx] = v_acc[cidx];
      }
   }

   return;
}

// Float input, float compute, float output
float fn_float_vdp (int r, float v_a[], float v_b[]) {
   float acc = 0.0;
   int idx = 0;

   for (idx=0; idx < r; idx ++) acc += fn_float_fma (v_a[idx], v_b[idx], acc);

   return (acc);
}

// Float input, float compute, float output
void fn_float_gemv (float v_acc[], int r, float m_a[][VSZ], float v_b[]) {
   int idx = 0;
   for (idx=0; idx < r; idx ++)
      v_acc[idx] = fn_float_vdp (r, m_a[idx], v_b);

   return;
}

// Float input, float compute, float output. The second matrix is the transposed version
void fn_float_gemm (float m_acc[][VSZ], int dimension, float m_a[][VSZ], float m_b[][VSZ]) {
   int ridx = 0; int cidx = 0;
   float v_acc[VSZ];
   for (ridx=0; ridx < dimension; ridx++) {
      fn_float_gemv (v_acc, dimension, m_a, m_b[ridx]);
      // implement a transpose to get the result matrix
      for (cidx=0; cidx < dimension; cidx++) {
         m_acc[cidx][ridx] = v_acc[cidx];
      }
   }

   return;
}

// Float input, float compute, float output. Code written to allow compiler optimization wrt
// function calls.
float fn_float_optimized_vdp (int r, float v_a[], float v_b[]) {
   float acc = 0.0;
   int idx = 0;

   for (idx=0; idx < r; idx ++) acc += (v_a[idx] * v_b[idx]);

   return (acc);
}

// Float input, float compute, float output. Code written to allow compiler optimization wrt
// function calls.
void fn_float_optimized_gemv (float v_acc[], int r, float m_a[][VSZ], float v_b[]) {
   int idx = 0;
   for (idx=0; idx < r; idx ++)
      v_acc[idx] = fn_float_optimized_vdp (r, m_a[idx], v_b);

   return;
}

// Float input, float compute, float output. Code written to allow compiler optimization wrt
// function calls.
void fn_float_optimized_gemm (float m_acc[][VSZ], int dimension, float m_a[][VSZ], float m_b[][VSZ]) {
   int ridx = 0; int cidx = 0;
   float v_acc[VSZ];

   for (ridx=0; ridx < dimension; ridx++) {
      fn_float_optimized_gemv (v_acc, dimension, m_a, m_b[ridx]);
      // implement a transpose to get the result matrix
      for (cidx=0; cidx < dimension; cidx++) {
         m_acc[cidx][ridx] = v_acc[cidx];
      }
   }

   return;
}

// --------