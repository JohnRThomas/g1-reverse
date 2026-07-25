/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004fa0[];
#define G1N_2100463c ((unsigned long)(g1_net_ram_blk_210045e0 + 0x5c))
#define G1N_21004fa5 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x5))
#define G1N_21004fa6 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x6))
#else
#define G1N_2100463c 0x2100463cul
#define G1N_21004fa5 0x21004fa5ul
#define G1N_21004fa6 0x21004fa6ul
#endif
/* net-core FUN_0102b7d0 @ 0x102b7d0  (parity 300 trials PROVEN) */

typedef void (*fptr_t)(int);
void FUN_0102b7d0(int param_1)
{
  volatile unsigned char *A = (volatile unsigned char*)G1N_21004fa5;
  volatile unsigned char *B = (volatile unsigned char*)G1N_21004fa6;
  fptr_t *Cp = (fptr_t*)G1N_2100463c;
  if (*A == 0) {
    if (param_1 == 0) {
      if (*B != 0) {
        (*Cp)(1);
        *B = 0;
      }
    } else if (*B == 0) {
      (*Cp)(0);
      *B = 1;
    }
  }
}

