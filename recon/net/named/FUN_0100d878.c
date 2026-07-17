/* readable reconstruction; identity: FUN_0100d878 @ 0x0100d878
 * public-name: FUN_0100d878
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_0100d878 @ 0x100d878  (parity 500 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned char byte;
extern void sdc_assertion_fail(uint,uint,uint,uint,uint);

static inline __attribute__((always_inline)) uint rev8(byte b){
  return ((((((((((uint)(b&1)<<1)|(b>>1&1))<<1|(b>>2&1))<<1|(b>>3&1))<<1|(b>>4&1))<<1|(b>>5&1))<<1|(b>>6&1))<<1)|(b>>7));
}
#define CAT(h,l) (((rev8((byte)(h)))<<8)|(rev8((byte)(l))))
#define B(o) (*(volatile byte *)(RIP + (o)))

uint FUN_0100d878(int param_1,uint param_2,uint param_3,uint param_4)
{
  int RIP = param_1;
  uint R0,R1,R2,R3,LR,uVar6,uVar3,prod;
  byte b1,b2;

  /* --- hash (verified) --- */
  R1 = (param_2 ^ param_2 >> 0x10) & 0xffff;      /* hash seed */
  R2 = param_3 ^ R1;
  b1 = (byte)R2; b2 = (byte)(R2 >> 8);
  R3 = (uint)(unsigned short)CAT(b2,b1) * 0x11 + R1;
  b1 = (byte)R3; b2 = (byte)(R3 >> 8);
  R3 = (uint)(unsigned short)CAT(b2,b1) * 0x11 + R1;
  b1 = (byte)R3; b2 = (byte)(R3 >> 8);
  uVar6 = ((uint)(unsigned short)CAT(b2,b1) * 0x11 + R1 ^ R1) & 0xffff;
  {
    unsigned long long p = (unsigned long long)0xbacf914dU * (unsigned long long)uVar6;
    int hi = (int)(p >> 32);
    uint q = ((uint)hi + ((uVar6 - (uint)hi) >> 1)) >> 5;
    uVar3 = uVar6 - q * 0x25;
  }
  /* early-return: bit uVar3 already present in bitmap at param_1+1 */
  if ((B((uVar3 * 0x1000000 >> 0x1b) + 1) & (1u << (uVar3 & 7))) != 0)
    return uVar3 & 0xff;

  /* --- dispatch (transcribed from asm) --- */
  prod = (uint)B(0xb) * uVar6;
  LR = prod >> 16;
  R3 = (uint)((int)prod >> 16);
  R2 = (LR + 1) & 0xff;
  if (R2 <= B(6)) goto L0d9e0;
  R2 = (R2 - B(6)) & 0xff;

L0d92c:
  if (B(7) >= R2) goto L0da6a;
  R2 = (R2 - B(7)) & 0xff;
L0d93a:
  if (R2 <= B(8)) goto L0daf6;
  R2 = (R2 - B(8)) & 0xff;
L0d948:
  if (R2 <= B(9)) goto L0d966;
  R2 = (R2 - B(9)) & 0xff;
L0d954:
  if (B(0xa) >= R2) goto L0db84;
  /* call (noreturn in HW; oracle returns -> falls into +4 block) */
  sdc_assertion_fail(0x46,0x9d,R2,B(0xa),param_4);
L0d966:
  R3 = B(4);
  if ((int)(R3 << 0x1f) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da7e; } }
  if ((int)(R3 << 0x1e) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0d9fc; } }
  if ((int)(R3 << 0x1d) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da12; } }
  if ((int)(R3 << 0x1c) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da22; } }
  if ((int)(R3 << 0x1b) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da32; } }
  if ((int)(R3 << 0x1a) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da42; } }
  if ((int)(R3 << 0x19) < 0) goto L0dc00;
  if ((int)(R3 << 0x18) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da66; } }
  goto L0d954;

L0d9e0:
  R1 = B(1);
  if ((int)(R1 << 0x1f) < 0){
    if (R3 == 0) goto L0dc0e;
    R2 = LR;
  }
  if ((int)(R1 << 0x1e) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0d9fc; }
  if ((int)(R1 << 0x1d) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da12; }
  if ((int)(R1 << 0x1c) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da22; }
  if ((int)(R1 << 0x1b) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da32; }
  if ((int)(R1 << 0x1a) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da42; }
  if ((int)(R1 << 0x19) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da52; }
  if ((int)(R1 << 0x18) < 0){ R2=(R2-1)&0xff; if(R2==0) goto L0da66; }
  goto L0d92c;

L0da6a:
  R3 = B(2);
  R1 = R3 & 1;
  if (R1 != 0){ R2=(R2-1)&0xff; if(R2==0){ R2=R1; goto L0da7e; } }
  if ((int)(R3 << 0x1e) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0d9fc; } }
  if ((int)(R3 << 0x1d) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da12; } }
  if ((int)(R3 << 0x1c) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da22; } }
  if ((int)(R3 << 0x1b) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da32; } }
  if ((int)(R3 << 0x1a) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da42; } }
  if ((int)(R3 << 0x19) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da52; } }
  if ((int)(R3 << 0x18) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=1; goto L0da66; } }
  goto L0d93a;

L0daf6:
  R3 = B(3);
  if ((int)(R3 << 0x1f) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da7e; } }
  if ((int)(R3 << 0x1e) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0d9fc; } }
  if ((int)(R3 << 0x1d) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da12; } }
  if ((int)(R3 << 0x1c) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da22; } }
  if ((int)(R3 << 0x1b) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da32; } }
  if ((int)(R3 << 0x1a) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da42; } }
  if ((int)(R3 << 0x19) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da52; } }
  if ((int)(R3 << 0x18) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=2; goto L0da66; } }
  goto L0d948;

L0db84:
  R3 = B(5);
  if ((int)(R3 << 0x1f) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da7e; } }
  if ((int)(R3 << 0x1e) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0d9fc; } }
  if ((int)(R3 << 0x1d) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da12; } }
  if ((int)(R3 << 0x1c) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da22; } }
  if ((int)(R3 << 0x1b) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da32; } }
L0dbcc:
  if ((int)(R3 << 0x1a) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da42; } }
  if ((int)(R3 << 0x19) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=4; goto L0da52; } }
  if ((int)(R3 << 0x18) < 0){ if (R2 == 1){ R2=4; goto L0da66; } }
  goto L0d95e;
L0d95e:
  sdc_assertion_fail(0x46,0x9d,R2,B(0xa),param_4);
  goto L0d966;

L0dc00:
  R2=(R2-1)&0xff;
  if(R2!=0){ if ((int)(R3 << 0x18) < 0){ R2=(R2-1)&0xff; if(R2==0){ R2=3; goto L0da66; } } goto L0d954; }
  R2=3; goto L0da52;

L0dc0e:
  R2 = R3;
  goto L0da7e;

L0d9fc:  R0 = 1; goto L0d9fe;
L0da12:  R0 = 2; goto L0d9fe;
L0da22:  R0 = 3; goto L0d9fe;
L0da32:  R0 = 4; goto L0d9fe;
L0da42:  R0 = 5; goto L0d9fe;
L0da52:  R0 = 6; goto L0d9fe;
L0da66:  R0 = 7; goto L0d9fe;
L0da7e:  R0 = 0;
L0d9fe:
  return (R0 + R2 * 8) & 0xff;
}
