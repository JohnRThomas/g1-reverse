#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004588c @ 0x0004588c
 * public-name: resource_manger_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_clock_digit_glyph_offset_large       <= FUN_00045764 @ 0x00045764
 *   get_clock_digit_glyph_offset_small       <= FUN_000457b0 @ 0x000457b0
 *   get_font_style3_glyph_offset             <= FUN_000457f4 @ 0x000457f4
 *   get_default_font_glyph_offset            <= FUN_00045840 @ 0x00045840
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ff41                              @ 0x0000ff41
 *   rodata_a1ce0                             @ 0x000a1ce0
 *   rodata_bbfee                             @ 0x000bbfee
 *   rodata_bc04c                             @ 0x000bc04c
 *   rodata_bc083                             @ 0x000bc083
 *   rodata_bc097                             @ 0x000bc097
 *   rodata_bc181                             @ 0x000bc181
 *   rodata_bc26b                             @ 0x000bc26b
 *   rodata_bc355                             @ 0x000bc355
 *   rodata_bc43f                             @ 0x000bc43f
 *   rodata_bc529                             @ 0x000bc529
 *   rodata_bc613                             @ 0x000bc613
 *   rodata_bc6fd                             @ 0x000bc6fd
 *   rodata_bc7ca                             @ 0x000bc7ca
 *   rodata_bc7e0                             @ 0x000bc7e0
 *   rodata_bc7f1                             @ 0x000bc7f1
 *   rodata_bccd3                             @ 0x000bccd3
 *   rodata_bd1b5                             @ 0x000bd1b5
 *   rodata_bd697                             @ 0x000bd697
 *   rodata_bdb79                             @ 0x000bdb79
 *   rodata_be05b                             @ 0x000be05b
 *   rodata_be53d                             @ 0x000be53d
 *   rodata_bea1f                             @ 0x000bea1f
 *   rodata_bef01                             @ 0x000bef01
 *   rodata_bf3e3                             @ 0x000bf3e3
 *   rodata_bf8c5                             @ 0x000bf8c5
 *   rodata_bfda7                             @ 0x000bfda7
 *   rodata_c0289                             @ 0x000c0289
 *   rodata_c076b                             @ 0x000c076b
 *   rodata_c0c4d                             @ 0x000c0c4d
 *   rodata_c112f                             @ 0x000c112f
 *   rodata_c1611                             @ 0x000c1611
 *   rodata_c1af3                             @ 0x000c1af3
 *   rodata_c1fd5                             @ 0x000c1fd5
 *   rodata_c24b7                             @ 0x000c24b7
 *   rodata_c2999                             @ 0x000c2999
 *   rodata_c2e7b                             @ 0x000c2e7b
 *   rodata_c335d                             @ 0x000c335d
 *   rodata_c383f                             @ 0x000c383f
 *   rodata_c3d21                             @ 0x000c3d21
 *   rodata_c4203                             @ 0x000c4203
 *   rodata_c46e5                             @ 0x000c46e5
 *   rodata_c4bc7                             @ 0x000c4bc7
 *   rodata_c50a9                             @ 0x000c50a9
 *   rodata_c558b                             @ 0x000c558b
 *   rodata_c5a6d                             @ 0x000c5a6d
 *   rodata_c5f4f                             @ 0x000c5f4f
 *   rodata_c6431                             @ 0x000c6431
 *   rodata_c6913                             @ 0x000c6913
 *   rodata_c6df5                             @ 0x000c6df5
 *   rodata_c72d7                             @ 0x000c72d7
 *   rodata_c7309                             @ 0x000c7309
 *   rodata_c733b                             @ 0x000c733b
 *   rodata_c736d                             @ 0x000c736d
 *   rodata_c739f                             @ 0x000c739f
 *   rodata_c73fa                             @ 0x000c73fa
 *   rodata_c74c2                             @ 0x000c74c2
 *   rodata_c758a                             @ 0x000c758a
 *   rodata_c760a                             @ 0x000c760a
 *   rodata_c768a                             @ 0x000c768a
 *   rodata_c77c4                             @ 0x000c77c4
 *   rodata_c7956                             @ 0x000c7956
 *   rodata_c7a90                             @ 0x000c7a90
 *   rodata_c7c22                             @ 0x000c7c22
 *   rodata_c7e92                             @ 0x000c7e92
 *   rodata_c7f5a                             @ 0x000c7f5a
 *   rodata_c805e                             @ 0x000c805e
 *   rodata_c8162                             @ 0x000c8162
 *   rodata_c81a3                             @ 0x000c81a3
 *   rodata_c82db                             @ 0x000c82db
 *   rodata_c83a3                             @ 0x000c83a3
 *   rodata_c846b                             @ 0x000c846b
 *   rodata_c8533                             @ 0x000c8533
 *   rodata_c85fb                             @ 0x000c85fb
 *   rodata_c86c3                             @ 0x000c86c3
 *   rodata_c87c7                             @ 0x000c87c7
 *   rodata_c88cb                             @ 0x000c88cb
 *   rodata_c89cf                             @ 0x000c89cf
 *   rodata_c8a97                             @ 0x000c8a97
 *   rodata_c8b5f                             @ 0x000c8b5f
 *   rodata_c8c27                             @ 0x000c8c27
 *   rodata_c8cef                             @ 0x000c8cef
 *   rodata_c8db7                             @ 0x000c8db7
 *   rodata_c8e7f                             @ 0x000c8e7f
 *   rodata_c8f47                             @ 0x000c8f47
 *   rodata_c900f                             @ 0x000c900f
 *   rodata_c9113                             @ 0x000c9113
 *   rodata_c9217                             @ 0x000c9217
 *   rodata_c931b                             @ 0x000c931b
 *   rodata_c941f                             @ 0x000c941f
 *   rodata_c9523                             @ 0x000c9523
 *   rodata_c9627                             @ 0x000c9627
 *   rodata_c972b                             @ 0x000c972b
 *   rodata_c982f                             @ 0x000c982f
 *   rodata_c9933                             @ 0x000c9933
 *   rodata_c9a37                             @ 0x000c9a37
 *   rodata_c9b3b                             @ 0x000c9b3b
 *   rodata_c9c3f                             @ 0x000c9c3f
 *   rodata_c9d43                             @ 0x000c9d43
 *   rodata_c9e47                             @ 0x000c9e47
 *   rodata_c9f4b                             @ 0x000c9f4b
 *   rodata_ca04f                             @ 0x000ca04f
 *   rodata_ca153                             @ 0x000ca153
 *   rodata_cb7fb                             @ 0x000cb7fb
 *   rodata_cc863                             @ 0x000cc863
 *   rodata_cd5ab                             @ 0x000cd5ab
 *   rodata_ce483                             @ 0x000ce483
 *   rodata_cff13                             @ 0x000cff13
 *   rodata_d06cf                             @ 0x000d06cf
 *   rodata_d0e9f                             @ 0x000d0e9f
 *   rodata_d15a7                             @ 0x000d15a7
 *   rodata_d215f                             @ 0x000d215f
 *   rodata_d328f                             @ 0x000d328f
 *   rodata_d43bf                             @ 0x000d43bf
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_glyph_bitmap_cache_buf                 @ 0x2001ce57
 */
/* Reconstructed resource_manger_get @ 0x4588c  (parity: 120/120 trials, PROVEN) */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;
static inline int CARRY4(uint a, uint b){return (a+b)<a;}
static inline int CARRY1(uint a, uint b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(uint a, uint b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SBORROW4(int a,int b){int r=(int)((uint)a-(uint)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
#define CONCAT44(a,b) ((ulonglong)(((ulonglong)(uint)(a)<<32)|(uint)(b)))
#define CONCAT13(a,b) ((uint)(((uint)(uint8_t)(a)<<24)|((uint)(b)&0xffffff)))
#define CONCAT31(a,b) ((uint)(((uint)(a)<<8)|(uint8_t)(b)))
#define CONCAT12(a,b) ((uint)(((uint)(uint8_t)(a)<<16)|(ushort)(b)))
#define CONCAT21(a,b) ((uint)(((uint)(ushort)(a)<<8)|(uint8_t)(b)))
#define CONCAT111(a,b,c) ((uint)(((uint)(uint8_t)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define CONCAT411(a,b,c) ((ulonglong)(((ulonglong)(uint)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define SUB84(x,o) ((uint)((ulonglong)(x)>>((o)*8)))
#define SUB82(x,o) ((ushort)((ulonglong)(x)>>((o)*8)))
#define SUB81(x,o) ((uint8_t)((ulonglong)(x)>>((o)*8)))
#define SUB41(x,o) ((uint8_t)((uint)(x)>>((o)*8)))
#define SUB42(x,o) ((ushort)((uint)(x)>>((o)*8)))
#define SUB21(x,o) ((uint8_t)((ushort)(x)>>((o)*8)))
#define SUBF(v,o,s) ((ulonglong)((ulonglong)(v)>>((o)*8)) & ((s)>=8?~0ULL:((1ULL<<((s)*8))-1)))
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern long long DEBUG_PRINT(uintptr_t, ...);
extern int get_device_info(void);
extern void debug_print(uintptr_t, uintptr_t, uintptr_t, uintptr_t);
extern int get_clock_digit_glyph_offset_large(uint16_t, uint32_t *, uint32_t *);
extern int get_clock_digit_glyph_offset_small(uint16_t, uint32_t *, uint32_t *);
extern int get_font_style3_glyph_offset(uint16_t, uint32_t *, uint32_t *);
extern int get_default_font_glyph_offset(uint16_t, uint32_t *, uint32_t *);
extern void *memset_bytes(void *, int, uint32_t);

#define DAT_00045bac ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00045bb0 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00045bb4 (((unsigned long)&rodata_bc083) /*=0xbc083*/)
#define DAT_00045bb8 (((unsigned long)&rodata_bbfee) /*=0xbbfee*/)
#define DAT_00045bbc (((unsigned long)&g_glyph_bitmap_cache_buf) /*=0x2001ce57*/)
#define DAT_00045bc0 (((unsigned long)&rodata_a1ce0) /*=0xa1ce0*/)
#define DAT_00045bc4 (0xa1be90UL)
#define DAT_00045bc8 (0x4f40b8UL)
#define DAT_00045bcc (0xa145c0UL)
#define DAT_00045bd0 (0xa141bcUL)
#define DAT_00045bd4 (0xa13ff8UL)
#define DAT_00045f24 (0x9f59f8UL)
#define DAT_00045f28 (0x4ed328UL)
#define DAT_00045f2c (0x4dd104UL)
#define DAT_00045f30 (0x9eba14UL)
#define DAT_00045f34 (((unsigned long)&g_glyph_bitmap_cache_buf) /*=0x2001ce57*/)
#define DAT_00045f38 (0x4f3bf0UL)
#define DAT_00045f3c (0x4d58f8UL)
#define DAT_00045f40 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00045f44 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00045f48 (((unsigned long)&rodata_bc083) /*=0xbc083*/)
#define DAT_00045f4c (0xbc006UL)
#define DAT_0004627c ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00046280 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00046284 (((unsigned long)&rodata_bc083) /*=0xbc083*/)
#define DAT_00046288 (((unsigned long)&rodata_bc04c) /*=0xbc04c*/)
#define DAT_0004628c (((unsigned long)&rodata_c8162) /*=0xc8162*/)
#define DAT_00046290 (((unsigned long)&rodata_c8f47) /*=0xc8f47*/)
#define DAT_00046294 (((unsigned long)&rodata_c8e7f) /*=0xc8e7f*/)
#define DAT_00046298 (((unsigned long)&rodata_c8db7) /*=0xc8db7*/)
#define DAT_0004629c (((unsigned long)&rodata_c805e) /*=0xc805e*/)
#define DAT_000462a0 (((unsigned long)&rodata_c87c7) /*=0xc87c7*/)
#define DAT_000462a4 (((unsigned long)&rodata_c8b5f) /*=0xc8b5f*/)
#define DAT_000462a8 (((unsigned long)&rodata_c8c27) /*=0xc8c27*/)
#define DAT_000462ac (((unsigned long)&rodata_c8cef) /*=0xc8cef*/)
#define DAT_000462b0 (((unsigned long)&rodata_c89cf) /*=0xc89cf*/)
#define DAT_000462b4 (((unsigned long)&rodata_c8a97) /*=0xc8a97*/)
#define DAT_000462b8 (((unsigned long)&rodata_c88cb) /*=0xc88cb*/)
#define DAT_000462bc (((unsigned long)&rodata_bc613) /*=0xbc613*/)
#define DAT_000462c0 (((unsigned long)&rodata_bc529) /*=0xbc529*/)
#define DAT_000462c4 (((unsigned long)&rodata_bc43f) /*=0xbc43f*/)
#define DAT_000462c8 (((unsigned long)&rodata_bc355) /*=0xbc355*/)
#define DAT_000462cc (((unsigned long)&rodata_bc26b) /*=0xbc26b*/)
#define DAT_000462d0 (((unsigned long)&rodata_bc181) /*=0xbc181*/)
#define DAT_000462d4 (((unsigned long)&rodata_bc097) /*=0xbc097*/)
#define DAT_000462d8 (((unsigned long)&rodata_ca04f) /*=0xca04f*/)
#define DAT_000462dc (((unsigned long)&rodata_c9f4b) /*=0xc9f4b*/)
#define DAT_000462e0 (((unsigned long)&rodata_c9e47) /*=0xc9e47*/)
#define DAT_000462e4 (((unsigned long)&rodata_c9d43) /*=0xc9d43*/)
#define DAT_0004657c (((unsigned long)&rodata_c9c3f) /*=0xc9c3f*/)
#define DAT_00046580 (((unsigned long)&rodata_c9b3b) /*=0xc9b3b*/)
#define DAT_00046584 (((unsigned long)&rodata_c9a37) /*=0xc9a37*/)
#define DAT_00046588 (((unsigned long)&rodata_c9933) /*=0xc9933*/)
#define DAT_0004658c (((unsigned long)&rodata_c982f) /*=0xc982f*/)
#define DAT_00046590 (((unsigned long)&rodata_c972b) /*=0xc972b*/)
#define DAT_00046594 (((unsigned long)&rodata_c9627) /*=0xc9627*/)
#define DAT_00046598 (((unsigned long)&rodata_c9523) /*=0xc9523*/)
#define DAT_0004659c (((unsigned long)&rodata_c941f) /*=0xc941f*/)
#define DAT_000465a0 (((unsigned long)&rodata_c931b) /*=0xc931b*/)
#define DAT_000465a4 (((unsigned long)&rodata_c9217) /*=0xc9217*/)
#define DAT_000465a8 (((unsigned long)&rodata_c9113) /*=0xc9113*/)
#define DAT_000465ac (((unsigned long)&rodata_c900f) /*=0xc900f*/)
#define DAT_000465b0 (((unsigned long)&rodata_c7f5a) /*=0xc7f5a*/)
#define DAT_000465b4 (((unsigned long)&rodata_c7e92) /*=0xc7e92*/)
#define DAT_000465b8 (((unsigned long)&rodata_c81a3) /*=0xc81a3*/)
#define DAT_000465bc (((unsigned long)&rodata_c7c22) /*=0xc7c22*/)
#define DAT_000465c0 (((unsigned long)&rodata_c7a90) /*=0xc7a90*/)
#define DAT_000465c4 (((unsigned long)&rodata_c7956) /*=0xc7956*/)
#define DAT_000465c8 (((unsigned long)&rodata_c77c4) /*=0xc77c4*/)
#define DAT_000465cc (((unsigned long)&rodata_c768a) /*=0xc768a*/)
#define DAT_000465d0 (((unsigned long)&rodata_c760a) /*=0xc760a*/)
#define DAT_000465d4 (((unsigned long)&rodata_c758a) /*=0xc758a*/)
#define DAT_000465d8 (((unsigned long)&rodata_c74c2) /*=0xc74c2*/)
#define DAT_000465dc (((unsigned long)&rodata_c73fa) /*=0xc73fa*/)
#define DAT_000465e0 (((unsigned long)&rodata_c86c3) /*=0xc86c3*/)
#define DAT_000465e4 (((unsigned long)&rodata_c85fb) /*=0xc85fb*/)
#define DAT_000465e8 (((unsigned long)&rodata_c8533) /*=0xc8533*/)
#define DAT_000465ec (((unsigned long)&rodata_c846b) /*=0xc846b*/)
#define DAT_000465f0 (((unsigned long)&rodata_c83a3) /*=0xc83a3*/)
#define DAT_000465f4 (((unsigned long)&rodata_c82db) /*=0xc82db*/)
#define DAT_000465f8 (((unsigned long)&rodata_c739f) /*=0xc739f*/)
#define DAT_000465fc (((unsigned long)&rodata_c736d) /*=0xc736d*/)
#define DAT_00046600 (((unsigned long)&rodata_c733b) /*=0xc733b*/)
#define DAT_00046604 (((unsigned long)&rodata_c7309) /*=0xc7309*/)
#define DAT_00046608 (((unsigned long)&rodata_c72d7) /*=0xc72d7*/)
#define DAT_0004660c (((unsigned long)&rodata_c6df5) /*=0xc6df5*/)
#define DAT_00046610 (((unsigned long)&rodata_c6913) /*=0xc6913*/)
#define DAT_00046614 (((unsigned long)&rodata_c6431) /*=0xc6431*/)
#define DAT_00046618 (((unsigned long)&rodata_c5f4f) /*=0xc5f4f*/)
#define DAT_0004661c (((unsigned long)&rodata_c5a6d) /*=0xc5a6d*/)
#define DAT_00046620 (((unsigned long)&rodata_c558b) /*=0xc558b*/)
#define DAT_00046624 (((unsigned long)&rodata_c50a9) /*=0xc50a9*/)
#define DAT_0004689c (((unsigned long)&rodata_c4bc7) /*=0xc4bc7*/)
#define DAT_000468a0 (((unsigned long)&rodata_c46e5) /*=0xc46e5*/)
#define DAT_000468a4 (((unsigned long)&rodata_c4203) /*=0xc4203*/)
#define DAT_000468a8 (((unsigned long)&rodata_c3d21) /*=0xc3d21*/)
#define DAT_000468ac (((unsigned long)&rodata_c383f) /*=0xc383f*/)
#define DAT_000468b0 (((unsigned long)&rodata_c335d) /*=0xc335d*/)
#define DAT_000468b4 (((unsigned long)&rodata_c2e7b) /*=0xc2e7b*/)
#define DAT_000468b8 (((unsigned long)&rodata_c2999) /*=0xc2999*/)
#define DAT_000468bc (((unsigned long)&rodata_c24b7) /*=0xc24b7*/)
#define DAT_000468c0 (((unsigned long)&rodata_c1fd5) /*=0xc1fd5*/)
#define DAT_000468c4 (((unsigned long)&rodata_c1af3) /*=0xc1af3*/)
#define DAT_000468c8 (((unsigned long)&rodata_c1611) /*=0xc1611*/)
#define DAT_000468cc (((unsigned long)&rodata_c112f) /*=0xc112f*/)
#define DAT_000468d0 (((unsigned long)&rodata_c0c4d) /*=0xc0c4d*/)
#define DAT_000468d4 (((unsigned long)&rodata_c076b) /*=0xc076b*/)
#define DAT_000468d8 (((unsigned long)&rodata_c0289) /*=0xc0289*/)
#define DAT_000468dc (((unsigned long)&rodata_bfda7) /*=0xbfda7*/)
#define DAT_000468e0 (((unsigned long)&rodata_bf8c5) /*=0xbf8c5*/)
#define DAT_000468e4 (((unsigned long)&rodata_bf3e3) /*=0xbf3e3*/)
#define DAT_000468e8 (((unsigned long)&rodata_bef01) /*=0xbef01*/)
#define DAT_000468ec (((unsigned long)&rodata_bea1f) /*=0xbea1f*/)
#define DAT_000468f0 (((unsigned long)&rodata_be53d) /*=0xbe53d*/)
#define DAT_000468f4 (((unsigned long)&rodata_be05b) /*=0xbe05b*/)
#define DAT_000468f8 (((unsigned long)&rodata_bdb79) /*=0xbdb79*/)
#define DAT_000468fc (((unsigned long)&rodata_bd697) /*=0xbd697*/)
#define DAT_00046900 (((unsigned long)&rodata_bd1b5) /*=0xbd1b5*/)
#define DAT_00046904 (((unsigned long)&rodata_bccd3) /*=0xbccd3*/)
#define DAT_00046908 (((unsigned long)&rodata_bc7f1) /*=0xbc7f1*/)
#define DAT_0004690c (((unsigned long)&rodata_bc7e0) /*=0xbc7e0*/)
#define DAT_00046910 (((unsigned long)&rodata_bc7ca) /*=0xbc7ca*/)
#define DAT_00046914 (((unsigned long)&rodata_bc6fd) /*=0xbc6fd*/)
#define DAT_00046918 (((unsigned long)&rodata_d43bf) /*=0xd43bf*/)
#define DAT_0004691c (((unsigned long)&rodata_d328f) /*=0xd328f*/)
#define DAT_00046920 (((unsigned long)&rodata_d215f) /*=0xd215f*/)
#define DAT_00046924 (((unsigned long)&rodata_d15a7) /*=0xd15a7*/)
#define DAT_00046928 (((unsigned long)&rodata_d0e9f) /*=0xd0e9f*/)
#define DAT_0004692c (((unsigned long)&rodata_d06cf) /*=0xd06cf*/)
#define DAT_00046930 (((unsigned long)&rodata_cff13) /*=0xcff13*/)
#define DAT_00046934 (((unsigned long)&rodata_ce483) /*=0xce483*/)
#define DAT_00046998 (((unsigned long)&rodata_cd5ab) /*=0xcd5ab*/)
#define DAT_0004699c (((unsigned long)&rodata_cc863) /*=0xcc863*/)
#define DAT_000469a0 (((unsigned long)&rodata_cb7fb) /*=0xcb7fb*/)
#define DAT_000469a4 (((unsigned long)&rodata_ca153) /*=0xca153*/)


undefined4
resource_manger_get(uint param_1,uint param_2,uint *param_3,uint *param_4,int *param_5,undefined1 *param_6)

{
  uint uVar1;
  ulonglong uVar2;
  ushort uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  code *pcVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  undefined4 local_28;
  undefined4 local_24;

  uVar11 = CONCAT44(param_2,param_1);
  local_28 = param_1;
  local_24 = param_2;
  switch(param_1) {
  case 0:
    if ((int)param_2 < 0x2714) {
      uVar11 = get_default_font_glyph_offset(param_2 & 0xffff,&local_28,&local_24);
      *param_5 = (int)uVar11;
      if ((int)uVar11 != 0) {
        *param_3 = local_28;
        *param_4 = local_24;
        return 0;
      }
    }
    if (((unsigned long)&rodata_ff41) /*=0xff41*/ < param_2 - 0xa4) goto LAB_00045caa;
    iVar8 = get_device_info();
    pcVar10 = *(code **)(iVar8 + 0x1030);
    uVar4 = get_device_info();
    iVar9 = (param_2 - 0xa4) * 4;
    uVar5 = (*pcVar10)(uVar4,iVar9 + 0x140000,&local_24);
    iVar8 = DAT_00045bbc;
    if (uVar5 == 0) {
      uVar1 = local_24 >> 0x10;
      if (uVar1 == 0xffff) {
        if (param_2 - 0x1100 < 0xfa) {
          local_28 = uVar5;
          local_24 = uVar5;
          iVar8 = get_device_info();
          pcVar10 = *(code **)(iVar8 + 0x1030);
          uVar4 = get_device_info();
          iVar9 = (*pcVar10)(uVar4,DAT_00045bc4 + iVar9,&local_24);
          iVar8 = DAT_00045bbc;
          if (iVar9 != 0) goto LAB_00045902;
          uVar5 = ((*(volatile uint16_t*)((char*)&local_24 + 2)) & 0xff) << 8 | (uint)((*(volatile uint16_t*)((char*)&local_24 + 2)) >> 8);
          local_28 = CONCAT22((short)uVar5,(ushort)((local_24 & 0xff) << 8) | (ushort)local_24 >> 8)
          ;
          if ((*(volatile uint16_t*)((char*)&local_24 + 2)) != 0xffff) {
            memset_bytes(DAT_00045bbc,0,0x138);
            iVar9 = get_device_info();
            pcVar10 = *(code **)(iVar9 + 0x1030);
            uVar4 = get_device_info();
            param_2 = (*pcVar10)(uVar4,uVar5 * 0x138 + 0xa40000,iVar8,0x138);
LAB_000459fc:
            if (param_2 == 0) {
              uVar5 = 0x18;
              goto LAB_0004597a;
            }
            goto LAB_00045958;
          }
LAB_00045cb8:
          if (0x5d < param_2 - 0xff01) {
            if (0x2e < param_2 - 0x2010) goto LAB_00045b4e;
            uVar12 = get_device_info();
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              iVar9 = (*pcVar10)(uVar4,(param_2 - 0x2010) * 4 + 0x500000,&local_24);
              goto LAB_00045dfa;
            }
            goto LAB_00045e48;
          }
          uVar12 = get_device_info();
          uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
          if (*(int *)((int)uVar12 + 0x1030) != 0) {
            iVar8 = get_device_info();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = get_device_info();
            iVar9 = (*pcVar10)(uVar4,DAT_00045f30 + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            if (uVar5 != 0xffff) {
              memset_bytes(DAT_00045f34,0,0x138);
              iVar9 = get_device_info();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = get_device_info();
              param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0x138 +
                                         0xa40000,iVar8,0x138);
              goto LAB_000459fc;
            }
            uVar11 = 0;
            uVar2 = 0;
            if (0x19c < param_2 - 0x3231) goto LAB_00045c68;
            goto LAB_00045d4a;
          }
LAB_00045e4e:
          iVar8 = get_device_info();
          if (*(int *)(iVar8 + 0x1030) != 0) {
            iVar8 = get_device_info();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = get_device_info();
            iVar9 = (*pcVar10)(uVar4,DAT_00045f3c + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar5 = ((*(volatile uint16_t*)((char*)&local_24 + 2)) & 0xff) << 8 | (uint)((*(volatile uint16_t*)((char*)&local_24 + 2)) >> 8);
            if ((*(volatile uint16_t*)((char*)&local_24 + 2)) != 0xffff) {
              memset_bytes(DAT_00045f34,0,0x138);
              iVar9 = get_device_info();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = get_device_info();
LAB_00045db4:
              param_2 = (*pcVar10)(uVar4,uVar5 * 0xd0 + 0x520000,iVar8);
              goto LAB_00045e3c;
            }
          }
        }
        else {
          if (param_2 - 0x302e < 2) {
            uVar12 = get_device_info();
            iVar8 = (int)((ulonglong)uVar12 >> 0x20);
            iVar6 = (int)uVar12 + 0x1000;
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              iVar8 = (*pcVar10)(uVar4,DAT_00045bcc + iVar9,&local_24);
              if (iVar8 != 0) goto LAB_00045902;
              uVar5 = local_24 >> 0x10;
              if (uVar5 != 0xffff) goto LAB_00045a8a;
LAB_00045b4e:
              iVar6 = 0;
              uVar11 = 0;
              iVar8 = iVar6;
              if (0xfd < param_2 - 0x3001) goto LAB_00045caa;
            }
            uVar12 = get_device_info();
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
            iVar8 = get_device_info();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = get_device_info();
            iVar9 = (*pcVar10)(uVar4,DAT_00045bc8 + param_2 * 4,&local_24);
LAB_00045dfa:
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar2 = 0;
            if (uVar5 == 0xffff) goto LAB_00045e48;
            memset_bytes(DAT_00045f34,0,0x138);
            iVar9 = get_device_info();
            pcVar10 = *(code **)(iVar9 + 0x1030);
            uVar4 = get_device_info();
            param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0xd0 + 0x520000,
                                 iVar8);
LAB_00045e3c:
            if (param_2 == 0) {
              uVar5 = 0x10;
LAB_0004597a:
              *param_3 = uVar5;
              *param_4 = 0x1a;
              *param_5 = iVar8;
              return 0;
            }
            goto LAB_00045958;
          }
          if (param_2 - 0x3131 < 0x5e) {
            uVar12 = get_device_info();
            uVar11 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              iVar8 = (*pcVar10)(uVar4,DAT_00045bd0 + iVar9,&local_24);
              if (iVar8 == 0) {
                uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
                uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
                if (uVar5 == 0xffff) goto LAB_00045b4e;
                memset_bytes(DAT_00045bbc,0,0x138);
                iVar8 = get_device_info();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = get_device_info();
                param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0x138 +
                                           0xa40000,DAT_00045bbc,0x138);
                if (param_2 == 0) {
                  *param_3 = 0x18;
                  *param_4 = 0x1a;
                  *param_5 = DAT_00045bbc;
                  return 0;
                }
                goto LAB_00045958;
              }
              goto LAB_00045902;
            }
LAB_00045caa:
            if (param_2 - 0x3231 < 0x19d) {
LAB_00045d4a:
              uVar12 = get_device_info();
              uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              iVar8 = DAT_00045f38;
            }
            else {
LAB_00045c26:
              uVar2 = uVar11;
              if (0x5177 < param_2 - 0x4e00) goto LAB_00045c68;
              uVar12 = get_device_info();
              uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              iVar8 = DAT_00045f28;
            }
LAB_00045d74:
            iVar9 = (*pcVar10)(uVar4,iVar8 + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            if (uVar5 != 0xffff) {
              memset_bytes(DAT_00045f34,0,0x138);
              iVar9 = get_device_info();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = get_device_info();
              uVar5 = (uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8);
              goto LAB_00045db4;
            }
          }
          else {
            if (param_2 - 0x3200 < 0x80) {
              uVar12 = get_device_info();
              uVar11 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) != 0) {
                iVar8 = get_device_info();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = get_device_info();
                uVar11 = (*pcVar10)(uVar4,DAT_00045bd4 + iVar9,&local_24);
                if ((int)uVar11 != 0) goto LAB_00045902;
                uVar5 = local_24 >> 0x10;
                uVar11 = uVar11 & 0xffffffff00000000;
                if (uVar5 != 0xffff) {
LAB_00045a8a:
                  iVar8 = DAT_00045bbc;
                  memset_bytes(DAT_00045bbc,0,0x138);
                  iVar9 = get_device_info();
                  pcVar10 = *(code **)(iVar9 + 0x1030);
                  uVar4 = get_device_info();
                  param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | uVar5 >> 8) * 0x138 + 0xa40000,
                                       iVar8,0x138);
                  goto LAB_000459fc;
                }
              }
              goto LAB_00045caa;
            }
            if (0x2bab < param_2 - 0xac00) goto LAB_00045cb8;
            uVar12 = get_device_info();
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = get_device_info();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = get_device_info();
              uVar11 = (*pcVar10)(uVar4,DAT_00045f24 + iVar9,&local_24);
              if ((int)uVar11 != 0) goto LAB_00045902;
              uVar5 = local_24 >> 0x10;
              if (uVar5 != 0xffff) goto LAB_00045a8a;
              uVar11 = uVar11 & 0xffffffff00000000;
              goto LAB_00045c26;
            }
LAB_00045c68:
            if (param_2 - 0xe001 < 0xfd) {
              iVar8 = get_device_info();
              if (*(int *)(iVar8 + 0x1030) != 0) {
                iVar8 = get_device_info();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = get_device_info();
                iVar8 = DAT_00045f2c;
                goto LAB_00045d74;
              }
            }
            else {
LAB_00045e48:
              if (param_2 - 0xff01 < 0x9f) goto LAB_00045e4e;
            }
          }
        }
        if (*DAT_00045f40 < 3) {
          return 0xffffffff;
        }
        iVar8 = *DAT_00045f44;
        uVar4 = DAT_00045f4c;
        uVar7 = DAT_00045f48;
      }
      else {
        memset_bytes(DAT_00045bbc,0,0x138);
        iVar9 = get_device_info();
        pcVar10 = *(code **)(iVar9 + 0x1030);
        uVar4 = get_device_info();
        param_2 = (*pcVar10)(uVar4,uVar1 * 0xea + 0x200000,iVar8);
        if (param_2 == 0) {
          uVar5 = 0x12;
          goto LAB_0004597a;
        }
LAB_00045958:
        if (*DAT_00045bac < 1) {
          return 0xffffffff;
        }
        iVar8 = *DAT_00045bb0;
        uVar4 = DAT_00045bc0;
        uVar7 = DAT_00045bb4;
      }
      if (iVar8 == 0) {
        DEBUG_PRINT(uVar4,uVar7,param_2);
        return 0xffffffff;
      }
      debug_print(uVar4,uVar7,param_1 == 4 ? param_2 - 0x16 : param_2,iVar8);
      return 0xffffffff;
    }
LAB_00045902:
    if (*DAT_00045bac < 1) {
      return 0xffffffff;
    }
    iVar8 = *DAT_00045bb0;
    uVar4 = DAT_00045bb8;
    uVar7 = DAT_00045bb4;
    goto LAB_00045912;
  case 1:
    iVar8 = get_clock_digit_glyph_offset_small(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    if (iVar8 != 0) {
      *param_3 = local_28;
      *param_4 = local_24;
      return 0;
    }
    break;
  case 2:
    iVar8 = get_clock_digit_glyph_offset_large(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    if (iVar8 != 0) {
      *param_3 = local_28;
      *param_4 = local_24;
      return 0;
    }
    break;
  case 3:
    iVar8 = get_font_style3_glyph_offset(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    *param_3 = local_28;
    *param_4 = local_24;
    return 0;
  case 4:
    if (param_2 - 0x16 < 0x67) {
      switch(param_2) {
      case 0x16:
        *param_5 = DAT_000465b8;
        *param_3 = 0x18;
        *param_4 = 0x1a;
        return 0;
      case 0x17:
        *param_5 = DAT_0004628c;
        *param_3 = 10;
        *param_4 = 0xd;
        return 0;
      case 0x18:
        *param_5 = DAT_00046290;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x19:
        *param_5 = DAT_00046294;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x1a:
        *param_5 = DAT_00046298;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x1b:
        *param_5 = DAT_0004629c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x1c:
        *param_5 = DAT_000462bc;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1d:
        *param_5 = DAT_000462c0;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1e:
        *param_5 = DAT_000462c4;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1f:
        *param_5 = DAT_000462c8;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x20:
        *param_5 = DAT_000462cc;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x21:
        *param_5 = DAT_000462d0;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x22:
        *param_5 = DAT_000462d4;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x23:
        *param_5 = DAT_000462d8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x24:
        *param_5 = DAT_000462dc;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x25:
        *param_5 = DAT_000462e0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x26:
        *param_5 = DAT_000462e4;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x27:
        *param_5 = DAT_0004657c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x28:
        *param_5 = DAT_00046580;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x29:
        *param_5 = DAT_00046584;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2a:
        *param_5 = DAT_00046588;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2b:
        *param_5 = DAT_0004658c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2c:
        *param_5 = DAT_00046590;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2d:
        *param_5 = DAT_00046594;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2e:
        *param_5 = DAT_00046598;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2f:
        *param_5 = DAT_0004659c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x30:
        *param_5 = DAT_000465a0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x31:
        *param_5 = DAT_000465a4;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x32:
        *param_5 = DAT_000465a8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x33:
        *param_5 = DAT_000465ac;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      default:
        return 0xffffffff;
      case 0x36:
        *param_5 = DAT_000462ac;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x37:
        *param_5 = DAT_000462a8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x38:
        *param_5 = DAT_000462a4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x39:
        *param_5 = DAT_000462b4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x3a:
        *param_5 = DAT_000462b0;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x3b:
        *param_5 = DAT_000462b8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3c:
        *param_5 = DAT_000462a0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3e:
        *param_5 = DAT_000465b0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3f:
        *param_5 = DAT_000465b4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x41:
        *param_5 = DAT_000465bc;
        *param_3 = 0x30;
        *param_4 = 0x1a;
        return 0;
      case 0x42:
        *param_5 = DAT_000465e0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x43:
        *param_5 = DAT_000465e4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x44:
        *param_5 = DAT_000465e8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x45:
        *param_5 = DAT_000465ec;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x46:
        *param_5 = DAT_000465f0;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x47:
        *param_5 = DAT_000465f4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x48:
        *param_5 = DAT_000465d8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x49:
        *param_5 = DAT_000465dc;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x4a:
        *param_5 = DAT_000465c0;
        *param_3 = 0x192;
        *param_4 = 2;
        return 0;
      case 0x4b:
        *param_5 = DAT_000465c4;
        *param_3 = 0x13a;
        *param_4 = 2;
        return 0;
      case 0x4c:
        *param_5 = DAT_000465c8;
        *param_3 = 0x192;
        *param_4 = 2;
        return 0;
      case 0x4d:
        *param_5 = DAT_000465cc;
        *param_3 = 0x13a;
        *param_4 = 2;
        return 0;
      case 0x4e:
        *param_5 = DAT_000465d0;
        *param_3 = 2;
        *param_4 = 0x80;
        return 0;
      case 0x4f:
        *param_5 = DAT_000465d4;
        *param_3 = 2;
        *param_4 = 0x80;
        return 0;
      case 0x50:
        *param_5 = DAT_000465fc;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x51:
        *param_5 = DAT_00046600;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x52:
        *param_5 = DAT_00046604;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x53:
        *param_5 = DAT_00046608;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x54:
        *param_5 = DAT_000465f8;
        *param_3 = 0xe;
        *param_4 = 0xd;
        return 0;
      case 0x56:
        *param_5 = DAT_0004660c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x57:
        *param_5 = DAT_00046610;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x58:
        *param_5 = DAT_00046614;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x59:
        *param_5 = DAT_00046618;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5a:
        *param_5 = DAT_0004661c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5b:
        *param_5 = DAT_00046620;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5c:
        *param_5 = DAT_00046624;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5d:
        *param_5 = DAT_0004689c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5e:
        *param_5 = DAT_000468a0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5f:
        *param_5 = DAT_000468a4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x60:
        *param_5 = DAT_000468a8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x61:
        *param_5 = DAT_000468ac;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x62:
        *param_5 = DAT_000468b0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 99:
        *param_5 = DAT_000468b4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 100:
        *param_5 = DAT_000468b8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x65:
        *param_5 = DAT_000468bc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x66:
        *param_5 = DAT_000468c0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x67:
        *param_5 = DAT_000468c4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x68:
        *param_5 = DAT_000468c8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x69:
        *param_5 = DAT_000468cc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6a:
        *param_5 = DAT_000468d0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6b:
        *param_5 = DAT_000468d4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6c:
        *param_5 = DAT_000468d8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6d:
        *param_5 = DAT_000468dc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6e:
        *param_5 = DAT_000468e0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6f:
        *param_5 = DAT_000468e4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x70:
        *param_5 = DAT_000468e8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x71:
        *param_5 = DAT_000468ec;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x72:
        *param_5 = DAT_000468f0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x73:
        *param_5 = DAT_000468f4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x74:
        *param_5 = DAT_000468f8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x75:
        *param_5 = DAT_000468fc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x76:
        *param_5 = DAT_00046900;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x77:
        *param_5 = DAT_00046904;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x78:
        *param_5 = DAT_00046908;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x7a:
        *param_5 = DAT_0004690c;
        *param_3 = 0x22;
        *param_4 = 1;
        return 0;
      case 0x7b:
        *param_5 = DAT_00046910;
        *param_3 = 0x2c;
        *param_4 = 1;
        return 0;
      case 0x7c:
        *param_5 = DAT_00046914;
        *param_3 = 0x19a;
        *param_4 = 1;
        return 0;
      }
    }
    if (*DAT_0004627c < 2) {
      return 0xffffffff;
    }
    iVar8 = *DAT_00046280;
    uVar4 = DAT_00046288;
    uVar7 = DAT_00046284;
LAB_00045912:
    if (iVar8 == 0) {
      DEBUG_PRINT(uVar4,uVar7);
    }
    else {
      debug_print(uVar4,uVar7,(uintptr_t)param_3,iVar8);
    }
    break;
  case 5:
    switch(param_2) {
    case 1:
      *param_5 = DAT_00046918;
      *param_3 = 0x14;
      *param_4 = 0x1a;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x2d;
      }
      break;
    case 2:
      iVar8 = DAT_0004691c;
      goto LAB_00046816;
    case 3:
      iVar8 = DAT_00046920;
LAB_00046816:
      *param_5 = iVar8;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x16;
      }
      break;
    case 4:
      *param_5 = DAT_00046924;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0xf;
      }
      break;
    case 5:
      *param_5 = DAT_00046928;
      *param_3 = 0x14;
      goto LAB_00046850;
    case 6:
      *param_5 = DAT_0004692c;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 10;
      }
      break;
    case 7:
      *param_5 = DAT_00046930;
      *param_3 = 0x16;
LAB_00046850:
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 9;
      }
      break;
    case 8:
      *param_5 = DAT_00046934;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x22;
      }
      break;
    case 9:
      *param_5 = DAT_00046998;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x13;
      }
      break;
    case 10:
      *param_5 = DAT_0004699c;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x11;
      }
      break;
    case 0xb:
      *param_5 = DAT_000469a0;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x15;
      }
      break;
    case 0xc:
      *param_5 = DAT_000469a4;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x1d;
      }
      break;
    default:
      goto switchD_0004589e_caseD_6;
    }
    return 0;
  }
switchD_0004589e_caseD_6:
  return 0xffffffff;
}
