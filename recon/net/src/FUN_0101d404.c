/* net-core FUN_0101d404 @ 0x101d404  (parity 300 trials PROVEN) */

int FUN_0101d404(unsigned short *param_1){
  volatile unsigned char *b0=(volatile unsigned char*)0x21001124;
  volatile unsigned short *b10=(volatile unsigned short*)0x2100112e;
  volatile unsigned char *b8=(volatile unsigned char*)0x2100112c;
  volatile unsigned char *b14=(volatile unsigned char*)0x21001138;
  volatile unsigned int *b4=(volatile unsigned int*)0x21001128;
  extern void FUN_0100a8f8(int); extern void FUN_0100a954(int);
  extern int FUN_0100dc1c(void); extern void FUN_01008d00(int,int);
  volatile int s;
  unsigned uVar7;
  *b0=0;
  uVar7=*param_1;
  *b10=0; *b8=0; *b14=0; *b4=(unsigned)param_1;
  FUN_0100a8f8(uVar7);
  FUN_0100a954(*param_1);
  s=FUN_0100dc1c();
  for(;;){ FUN_01008d00(0,0); }
  return 0;
}

