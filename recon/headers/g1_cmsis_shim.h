/*
 * g1_cmsis_shim.h -- CMSIS core-register helper wrappers, single definition site.
 *
 * G7-B1 / cluster G7-C03 of recon/analysis/prerefactor_plan.md.
 *
 * Ghidra names the Cortex-M special-register accesses with its own helper
 * spellings (getBasePriority, InstructionSynchronizationBarrier, ...).  Each
 * reconstructed function that used one carried a private `static inline` copy;
 * this header is the single definition site those copies collapse onto.  Every
 * body is a thin wrapper over the real CMSIS intrinsic, so the emitted
 * instruction is the CMSIS one.
 *
 * CODEGEN CONTRACT -- READ BEFORE EDITING.
 *
 * The 743 helper definitions in the corpus do NOT all agree, and the
 * disagreements are load-bearing, not cosmetic:
 *
 *   - a STUB family (6 copies each) defines getBasePriority as `return 0;`,
 *     setBasePriority as `(void)p;` and isCurrentModePrivileged as `return 1;`.
 *     Those are deliberately *not* the CMSIS read: collapsing them onto this
 *     header would inject real MRS/MSR BASEPRI instructions into functions that
 *     do not have them in the shipped image.
 *   - a BARRIER family (6 copies) defines InstructionSynchronizationBarrier via
 *     `__atomic_signal_fence(__ATOMIC_SEQ_CST)`, a compiler-only barrier that
 *     emits no instruction, and 3 more define it as an empty body.  This header
 *     emits a real `isb`.
 *   - an ALWAYS_INLINE family spells several helpers
 *     `static inline __attribute__((always_inline))`.  At -Os that changes
 *     whether a call is emitted, which changes the call trace the parity
 *     harness compares.
 *   - getBasePriority / setBasePriority / rd_basepri also differ in RETURN and
 *     PARAMETER TYPE (int vs unsigned), which is a real type change downstream.
 *
 * Only files whose local copies were textually identical to the definitions
 * here -- after normalising spellings of the SAME type (`unsigned`,
 * `unsigned int`, `uint`, `u32`, `uint32_t` all denote one type on
 * arm-zephyr-eabi; `&1u` and `&1` are identical in unsigned context) -- were
 * converted.  Every file carrying a divergent body keeps its private copy and
 * is recorded as deferred in the batch report.  `readIPSR` is deliberately
 * ABSENT: its two families are an exact 3/3 split between the always_inline and
 * the plain spelling, so there is no dominant variant to host.
 *
 * If you add a helper here, first prove every copy it replaces is identical.
 */
#ifndef G1_CMSIS_SHIM_H
#define G1_CMSIS_SHIM_H

#include <stdint.h>
#include <cmsis_gcc.h>

/* BASEPRI, int-typed spelling (52 of 73 copies) */
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void raiseBasePriority(int p){ __set_BASEPRI_MAX((uint32_t)p); }

/* BASEPRI, uint32_t-typed spelling used by the kernel-lock reconstructions */
static inline uint32_t rd_basepri(void){return __get_BASEPRI();}
static inline void wr_basepri(uint32_t v){__set_BASEPRI(v);}
static inline void wr_basepri_max(uint32_t v){__set_BASEPRI_MAX(v);}

/* CONTROL / PRIMASK / IPSR */
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int isIRQinterruptsEnabled(void){return (int)__get_PRIMASK();}
static inline unsigned int getCurrentExceptionNumber(void){return __get_IPSR();}
static inline void enableIRQinterrupts(void){__enable_irq();}
static inline void disableIRQinterrupts(void){__disable_irq();}

/* Instruction Synchronization Barrier -- emits a real `isb` */
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}
static inline void isb(void){__ISB();}
static inline void isb_(void){__ISB();}

#endif /* G1_CMSIS_SHIM_H */
