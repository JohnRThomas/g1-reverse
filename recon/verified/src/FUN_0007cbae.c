/* Reconstructed FUN_0007cbae @ 0x7cbae  (parity: 300/300 trials, PROVEN) */
extern char* FUN_000167a8(void);
extern int FUN_0007ce00(void);
extern char* ext3cebc(void);
char* FUN_0007cbae(int p1,int p2,int p3){
  char *r; int iv;
  (void)p1;(void)p2;(void)p3;
  r = (char*)FUN_000167a8();
  if (*r == 1){
    iv = (int)FUN_000167a8();
    if (*(char*)(*(int*)(iv+0x1010)+1) != 0){
      if (FUN_0007ce00() != 0) goto tail;
    }
  }
  r = (char*)FUN_000167a8();
  if (*r != 2) return r;
  iv = (int)FUN_000167a8();
  if (*(char*)(*(int*)(iv+0x1010)+1) == 0) return (char*)(iv+0x1000);
 tail:
  iv = (int)FUN_000167a8();
  { volatile char c = *(char*)(*(int*)(iv+0x1010)+2); (void)c; }
  return ext3cebc();
}

