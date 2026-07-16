/* Double absolute-value helper FUN_000869cc @ 0x869cc. */
double FUN_000869cc(double x){union{double d; unsigned long long u;}v={x};v.u&=0x7fffffffffffffffull;return v.d;}
