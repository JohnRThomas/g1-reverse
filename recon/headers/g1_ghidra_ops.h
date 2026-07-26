/*
 * g1_ghidra_ops.h -- Ghidra decompiler pseudo-operation helpers, single definition site.
 *
 * G7-B1 / cluster G7-C04 of recon/analysis/prerefactor_plan.md.
 *
 * Ghidra emits the CARRY, SCARRY and SBORROW families as pseudo-operations when
 * it cannot express an ARM flag computation in C.  Every reconstructed function that
 * needed one carried its own private `static inline` copy; this header is the
 * single definition site those copies collapse onto.
 *
 * CODEGEN CONTRACT.  The bodies below are the byte-verified dominant variant
 * measured over all 743 helper definitions in the corpus:
 *
 *   CARRY1  46 copies, 1 family      SBORROW1  46 copies, 1 family
 *   CARRY2  46 copies, 1 family      SBORROW2  46 copies, 1 family
 *   CARRY4  49 of 55 copies          SBORROW4  46 of 52 copies
 *   SCARRY4 34 copies, 1 family
 *
 * Only files whose local copy was textually identical to the definition here
 * (after normalising spellings of the SAME type -- `unsigned`, `unsigned int`,
 * `uint`, `u32`, `uint32_t` all denote one type on arm-zephyr-eabi) were
 * converted.  Files carrying a DIFFERENT body keep their private copy and are
 * listed as deferred in the batch report; in particular the
 * `__builtin_add_overflow` / `__builtin_sub_overflow` variants (6 + 3 copies)
 * are NOT assumed equivalent, because an `-Os` codegen difference there is
 * exactly the class the parity harness cannot see.
 *
 * Do not "simplify" these bodies.  They are compared against the shipped
 * image's instruction stream, not against a specification.
 */
#ifndef G1_GHIDRA_OPS_H
#define G1_GHIDRA_OPS_H

static inline int CARRY1(unsigned a,unsigned b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(unsigned a,unsigned b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}
static inline int SCARRY4(int a,int b){int r=(int)((unsigned)a+(unsigned)b);return (((a^r)&(b^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
static inline int SBORROW4(int a,int b){int r=(int)((unsigned)a-(unsigned)b);return (((a^b)&(a^r))<0);}

#endif /* G1_GHIDRA_OPS_H */
