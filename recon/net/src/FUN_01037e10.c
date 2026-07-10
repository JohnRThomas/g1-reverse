/* net-core FUN_01037e10 @ 0x1037e10  (parity 300 trials PROVEN) */
static inline unsigned int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return b;}
static inline void setBasePriority(unsigned p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void isb(void){__asm__ volatile("isb":::"memory");}

#define C_01037e9c 0x21004b68
#define C_01037ea0 0x0103d3b6
#define C_01037ea4 0x0103d2a7

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);
extern void FUN_01037814(int *);
extern void FUN_010380d8(int *);
extern void FUN_01036fcc(int *);

int FUN_01037e10(int *param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int sb;
  int r0;
  int r1;
  int r5;
  int *r4;

  sb = getBasePriority();
  setBasePriority(0x40);
  isb();
  r5 = FUN_0103610c(C_01037e9c);
  if (r5 != 0) goto L_e46;

  r1 = C_01037ea0;
  FUN_01039bbe(C_01037ea4, r1, 0x72);
  r1 = 0x72;
  r0 = C_01037ea0;
L_e40:
  FUN_01039bb0(r0, (unsigned int)r1);
  goto L_e46;

L_e46:
  FUN_01036144(C_01037e9c);
  r4 = (int *)*param_1;
  if (param_1 == r4) {
    r5 = 0;
    goto L_e6e;
  }
  if (r4 == (int *)0) {
    r5 = 0;
    goto L_e6e;
  }
  r4[0x24] = param_2;
  r4[5] = param_3;
  FUN_01037814(r4);
  FUN_010380d8(r4 + 6);
  FUN_01036fcc(r4);

L_e6e:
  r0 = FUN_01036128(C_01037e9c);
  if (r0 != 0) {
    setBasePriority(sb);
    isb();
    return r5;
  }
  r1 = C_01037ea0;
  FUN_01039bbe(C_01037ea4, r1, 0xf0);
  r1 = 0xf0;
  r0 = C_01037ea0;
  goto L_e40;
}

