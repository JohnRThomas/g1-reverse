/* Float absolute-value helper FUN_000868ee @ 0x868ee. */
float FUN_000868ee(float x){union{float f; unsigned u;}v={x};v.u&=0x7fffffffu;return v.f;}
