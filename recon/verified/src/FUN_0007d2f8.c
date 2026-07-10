/* Reconstructed FUN_0007d2f8 @ 0x7d2f8  (parity: 300/300 trials, PROVEN) */

extern void* FUN_000167a8(void);

void FUN_0007d2f8(unsigned int param_1)
{
  if (param_1 <= 2) {
    void *p = FUN_000167a8();
    int *ptr = *(int**)((char*)p + 0x1010);
    unsigned char b = *(unsigned char*)((char*)ptr + 2);
    int mismatch = (b != (unsigned char)param_1);
    if (!mismatch) {
      void *p2 = FUN_000167a8();
      unsigned char b2 = *(unsigned char*)((char*)p2 + 0xd5);
      mismatch = (b2 != 7);
    }
    if (mismatch) {
      void *p3 = FUN_000167a8();
      int *ptr3 = *(int**)((char*)p3 + 0x1010);
      *(unsigned char*)((char*)ptr3 + 2) = (unsigned char)param_1;
      void *p4 = FUN_000167a8();
      int *ptr4 = *(int**)((char*)p4 + 0x1010);
      *(unsigned char*)((char*)ptr4 + 1) = 1;
    }
  }
}

