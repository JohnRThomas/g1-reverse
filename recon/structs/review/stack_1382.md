## review group stack_1382  (1 cluster(s), kinds=stack)

### proposal for stack_1382
struct_name: lc3_sns_analysis_buffer | is_library: True | library_name: liblc3 internal (lc3_sns_analyze working buffer) | is_array: True | confidence: medium
purpose: Large stack-local array (65 uint32 words, 0x104 bytes) of spectral/energy coefficients read during LC3 SNS (spectral noise shaping) analysis.
fields:
  0x0  uint32_t     coef_0  
  0x4  uint32_t     coef_1  
  0x8  uint32_t     coef_2  
  0xc  uint32_t     coef_3  
  0x10  uint32_t     coef_4  
  0x14  uint32_t     coef_5  
  0x18  uint32_t     coef_6  
  0x1c  uint32_t     coef_7  
  0x20  uint32_t     coef_8  
  0x24  uint32_t     coef_9  
  0x28  uint32_t     coef_10  
  0x2c  uint32_t     coef_11  
  0x30  uint32_t     coef_12  
  0x34  uint32_t     coef_13  
  0x38  uint32_t     coef_14  
  0x3c  uint32_t     coef_15  
  0x40  uint32_t     coef_16  
  0x44  uint32_t     coef_17  
  0x48  uint32_t     coef_18  
  0x4c  uint32_t     coef_19  
  0x50  uint32_t     coef_20  
  0x54  uint32_t     coef_21  
  0x58  uint32_t     coef_22  
  0x5c  uint32_t     coef_23  
  0x60  uint32_t     coef_24  
  0x64  uint32_t     coef_25  
  0x68  uint32_t     coef_26  
  0x6c  uint32_t     coef_27  
  0x70  uint32_t     coef_28  
  0x74  uint32_t     coef_29  
  0x78  uint32_t     coef_30  
  0x7c  uint32_t     coef_31  
  0x80  uint32_t     coef_32  
  0x84  uint32_t     coef_33  
  0x88  uint32_t     coef_34  
  0x8c  uint32_t     coef_35  
  0x90  uint32_t     coef_36  
  0x94  uint32_t     coef_37  
  0x98  uint32_t     coef_38  
  0x9c  uint32_t     coef_39  
  0xa0  uint32_t     coef_40  
  0xa4  uint32_t     coef_41  
  0xa8  uint32_t     coef_42  
  0xac  uint32_t     coef_43  
  0xb0  uint32_t     coef_44  
  0xb4  uint32_t     coef_45  
  0xb8  uint32_t     coef_46  
  0xbc  uint32_t     coef_47  
  0xc0  uint32_t     coef_48  
  0xc4  uint32_t     coef_49  
  0xc8  uint32_t     coef_50  
  0xcc  uint32_t     coef_51  
  0xd0  uint32_t     coef_52  
  0xd4  uint32_t     coef_53  
  0xd8  uint32_t     coef_54  
  0xdc  uint32_t     coef_55  
  0xe0  uint32_t     coef_56  
  0xe4  uint32_t     coef_57  
  0xe8  uint32_t     coef_58  
  0xec  uint32_t     coef_59  
  0xf0  uint32_t     coef_60  
  0xf4  uint32_t     coef_61  
  0xf8  uint32_t     coef_62  
  0xfc  uint32_t     coef_63  
  0x100  uint32_t     coef_64  

<ground-truth bundle for stack_1382>
### cluster stack_1382  (stack, 1 members, 65 fields, size>=0x104)

Stack-frame local local_168 in lc3_sns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as local_168  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1382 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x70;   /* +0x70  sz=4 rw=r types=idx4 */
    uint32_t   field_0x74;   /* +0x74  sz=4 rw=r types=idx4 */
    uint32_t   field_0x78;   /* +0x78  sz=4 rw=r types=idx4 */
    uint32_t   field_0x7c;   /* +0x7c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=r types=idx4 */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=r types=idx4 */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=r types=idx4 */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=r types=idx4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=r types=idx4 */
    uint32_t   field_0x9c;   /* +0x9c  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xac;   /* +0xac  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb4;   /* +0xb4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb8;   /* +0xb8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xbc;   /* +0xbc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc4;   /* +0xc4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc8;   /* +0xc8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xcc;   /* +0xcc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd0;   /* +0xd0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd4;   /* +0xd4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xdc;   /* +0xdc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe0;   /* +0xe0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe4;   /* +0xe4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe8;   /* +0xe8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xec;   /* +0xec  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf0;   /* +0xf0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf4;   /* +0xf4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf8;   /* +0xf8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xfc;   /* +0xfc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x100;   /* +0x100  sz=4 rw=r types=idx4 */
};
```
