/* net-core FUN_0102ea40 @ 0x102ea40  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern void FUN_0102e284(unsigned int,unsigned int,void*,unsigned int);
extern void FUN_010359b8(unsigned int, unsigned int*);

void FUN_0102ea40(unsigned int param_1, unsigned int *param_2)
{
    if (param_2 != 0) {
        struct { unsigned int a0,a1,a2,a3,a4; } blk;
        blk.a3 = param_2[0];
        blk.a4 = param_2[1];
        unsigned int t = param_2[2];
        blk.a1 = 0x0103d82au; /* DAT_0102eaf8 */
        blk.a0 = 5;
        {
            struct { unsigned int a0,a1,a2,a3,a4; } b2 = { blk.a0, blk.a1, blk.a3, blk.a4, t };
            FUN_0102e284(0x0103c0c4u /* DAT_0102eafc */, 0x2840, &b2, 0);
        }
        blk.a3 = param_2[3];
        blk.a4 = param_2[4];
        t = param_2[5];
        blk.a1 = 0x0103d859u; /* DAT_0102eb00 */
        blk.a0 = 5;
        {
            struct { unsigned int a0,a1,a2,a3,a4; } b2 = { blk.a0, blk.a1, blk.a3, blk.a4, t };
            FUN_0102e284(0x0103c0c4u, 0x2840, &b2, 0);
        }
        t = param_2[7];
        blk.a4 = 0x0103d888u; /* DAT_0102eb04 */
        blk.a3 = 3;
        {
            struct { unsigned int a3,a4,tt; } b3 = { blk.a3, blk.a4, t };
            FUN_0102e284(0x0103c0c4u, 0x1840, &b3, 0);
        }
        t = param_2[6];
        blk.a3 = 3;
        blk.a4 = 0x0103d897u; /* DAT_0102eb08 */
        {
            struct { unsigned int a3,a4,tt; } b3 = { blk.a3, blk.a4, t };
            FUN_0102e284(0x0103c0c4u, 0x1840, &b3, 0);
        }
    }
    FUN_010359b8(param_1, param_2);
}

