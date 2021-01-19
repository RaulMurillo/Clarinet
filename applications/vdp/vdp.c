#include <stdio.h>
//for read_cycle
#include "riscv_counters.h"
// for PRIu64
#include <inttypes.h>
#include "clarinet.h"
#include "data.h"

int main (void) {
   float acc;

#ifdef POSIT
#ifdef PWIDTH_8
   unsigned char acc3;
#endif
#ifdef PWIDTH_16
   unsigned short acc3;
#endif
#ifdef PWIDTH_24
   unsigned int acc3;
#endif
#ifdef PWIDTH_32
   unsigned int acc3;
#endif
#endif

   uint32_t start = 0;
   uint32_t end = 0;
   uint32_t elapsed = 0;

   printf ("Starting VDP benchmarks...\n");

   // Basic VDPs are working
   // Now lets do some cycle analysis
#ifdef OPT_FLOAT
   start=read_cycle();
   acc = fn_float_optimized_vdp (VSZ, v_a, v_b);
   end=read_cycle();
#endif

#ifdef FLOAT
   start=read_cycle();
   acc = fn_float_vdp (VSZ, v_a, v_b);
   end=read_cycle();
#endif

#ifdef FLOAT_POSIT
   start=read_cycle();
   acc = fn_posit_vdp (VSZ, v_a, v_b);
   end=read_cycle();
#endif

#ifdef POSIT
   start=read_cycle();
   acc3 = fn_posit_p_vdp (VSZ, v_a, v_b);
   end=read_cycle();
#endif

   elapsed = end - start;
   printf ("VDP Cycle Report. Size: %d. Cycles: %d\n", VSZ, elapsed);

   return (0);
}