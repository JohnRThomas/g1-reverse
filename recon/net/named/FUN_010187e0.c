/* readable reconstruction; identity: FUN_010187e0 @ 0x010187e0
 * public-name: FUN_010187e0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 *   g_sdc_ll_ctx_field_308                   @ 0x21000308
 *   g_net_link_ctx_field_buf                 @ 0x21000fec
 */
/* net-core FUN_010187e0 @ 0x10187e0  (parity 300 trials PROVEN) */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;

extern int FUN_0100aa3c(int,...);
extern int FUN_010162e0(int);
extern int FUN_01016828(void);
extern int FUN_01016cc8(void*,int);
extern int FUN_0101709c(void*,int);
extern int FUN_0101746c(void*,int,int);
extern int FUN_01017658(void*,void*,void*,void*);
extern int FUN_01019660(void);
extern int FUN_010196e0(void);
extern int FUN_01019aa0(void*,int,int,int,int,int,int,int);
extern int FUN_01019eb4(void*,int);
extern int FUN_01019ef8(int,int);
extern int FUN_0101a070(int,void*);
extern int FUN_0101fca8(void);
extern int FUN_010208b0(void);
extern int FUN_0102961a(int);

#define G8(o)  (*(volatile signed char*)(0x21000f90+(o)))
#define G16(o) (*(volatile short*)(0x21000f90+(o)))

/* DAT pointers */
#define P_ac0 ((void*)0x21000fd6)
#define P_ac4 ((volatile signed char*)0x2100001c)
#define P_ac8 ((void*)0x21000fec)
#define P_acc ((void*)0x21001014)
#define P_abc ((volatile u32*)0x21000308)
#define P_bec ((volatile signed char*)0x2100001c)
#define P_bf0 ((void*)0x21000fd6)
#define P_bf4 ((void*)0x21001014)

unsigned int FUN_010187e0(u32 param_1, u32 param_2)
{
    unsigned char buf[0x30];
    signed char local_4b=0, local_4a=0, local_49=0;
    signed char cVar2,cVar4,cVar5;
    u8 bVar9;
    int iVar6;
    u32 uVar7;
    unsigned int uVar8;

    FUN_0101a070(param_1, buf);

    signed char *p48 = (signed char*)&buf[0];
    u8 *p47 = (u8*)&buf[1];
    int *p40 = (int*)&buf[8];
    u8 *p36 = (u8*)&buf[0x12];
    u8 **p34 = (u8**)&buf[0x14];
    int *p2c = (int*)&buf[0x1c];
    u32 *p24 = (u32*)&buf[0x24];

    if (G8(0xa9) != 0) { *p47 &= 0xfe; *(int*)&buf[4]=0; }
    if (G8(0xaa) != 0) { *p47 &= 0xfd; *p40=0; }

    if ( (*p48 != G8(0x88)) ||
         ( ( (iVar6=FUN_01019eb4(&buf[0],param_2), iVar6==0 &&
              ( (-1 < (int)((u32)*p47 << 0x1c)) ||
                (iVar6=FUN_01019ef8((*p34)[1]>>4, (u32)(*p34)[0] | ((*p34)[1]&0xf)<<8), iVar6==0) ) )
           ) || (FUN_0101746c(&buf[0],7,param_2), G16(0x82)==0) ) ) {
        uVar8=1;
        FUN_010196e0();
        goto L_882e;
    }

    local_4b=0; local_4a=0; local_49=0;
    if (*p40==0) { bVar9=0xff; }
    else {
        FUN_01017658(&buf[0],&local_4a,&local_4b,&local_49);
        bVar9=(u8)G8(0x45);
        if (local_4b!=0) bVar9 |= 2;
    }
    cVar5=local_49; cVar4=local_4a; cVar2=local_4b;

    if (*p48==1) {
        uVar7=(u32)*p47;
        if ((uVar7 & 9)==9) {
            if (G8(0x54)==3) {
                if (G8(0xa9)==0) {
                    iVar6=FUN_0100aa3c((u8)G8(0x90), (u32)P_ac8+0x2d, (u8)G8(0x5b));
                    if ((G8(0x56)!=1) && ((G8(0x56)!=0) || ((iVar6==0) && (G8(0x78)!=G8(0x7b)))))
                        goto L_8932;
                }
L_8a84:
                if ( ( (*p40==0) || (cVar2!=0) ||
                       ( (cVar5!=0) && (iVar6=FUN_0100aa3c((u8)G8(0x45),(u32)P_ac0,*p36), iVar6!=0) ) )
                     && (iVar6=FUN_0102961a((u32)P_acc), iVar6!=0) ) {
                    uVar8=0xe; goto L_882e;
                }
                goto L_8932;
            }
        }
        else {
            if ((G8(0xa9)==0) || (-1 < (int)(uVar7<<0x1c))) goto L_8932;
            if (G8(0x54)==3) goto L_8a84;
        }
        uVar7 = uVar7 & 2;
        if ((*p47 & 2)==0) {
            iVar6=(int)*P_bec;
            if (iVar6==0x7f) goto L_8be8;
            *P_bec=0x7f;
            if (G8(0x70)!=5) { if (G8(0x70)==8) uVar7=3; else uVar7=1; }
            {
                u8 uVar1=(u8)G8(0x79);
L_8b26:
                iVar6=FUN_01019aa0(&buf[0],0xff,(u32)P_bf0,(u8)G8(0xb9),(u8)G8(0x8f),uVar1,iVar6,uVar7);
            }
        }
        else {
            if ((local_4b==0) && (iVar6=FUN_0100aa3c((u8)G8(0x45),(u32)P_ac0,*p36,*p40), iVar6==0)) {
L_8980:
                if (((u8)((u8)G8(0x55)-2) < 2) && (cVar4!=0)) {
                    uVar8=1; FUN_01016cc8(&buf[0],0xfe); goto L_882e;
                }
                goto L_8932;
            }
            iVar6=(int)*P_bec;
            if (iVar6==0x7f) goto L_8be8;
            *P_bec=0x7f;
            if (G8(0x70)==5) uVar8=0; else { uVar8=1; if (G8(0x70)==8) uVar8=3; }
L_89f0:
            iVar6=FUN_01019aa0(&buf[0],bVar9,(u32)P_ac0,(u8)G8(0xb9),(u8)G8(0x8f),(u8)G8(0x79),iVar6,uVar8);
        }
        if (iVar6!=0) { uVar8=1; FUN_01019660(); goto L_882e; }
    }
    else if (*p48==2) {
        if ((G8(0x54)!=3) && (uVar7=(u32)*p47, (uVar7&9)==9)) {
            if (G8(0x54)!=2) {
                uVar7=uVar7&2;
                if ((*p47 & 2)!=0) {
                    if ((local_4b==0) && (iVar6=FUN_0100aa3c((u8)G8(0x45),(u32)P_ac0,*p36,*p40), iVar6==0))
                        goto L_8980;
                    iVar6=(int)*P_ac4;
                    if (iVar6==0x7f) goto L_8be8;
                    *P_ac4=0x7f;
                    if (G8(0x70)==5) uVar8=0; else if (G8(0x70)==8) uVar8=3; else uVar8=1;
                    goto L_89f0;
                }
                iVar6=(int)*P_bec;
                if (iVar6==0x7f) goto L_8be8;
                *P_bec=0x7f;
                if (G8(0x70)!=5) { if (G8(0x70)==8) uVar7=3; else uVar7=1; }
                {
                    u8 uVar1=(u8)G8(0x79);
                    iVar6=FUN_01019aa0(&buf[0],0xff,(u32)P_bf0,(u8)G8(0xb9),(u8)G8(0x8f),uVar1,iVar6,uVar7);
                }
            } else {
                if (((int)(uVar7<<0x1e)<0) && (local_4b==0) &&
                    ((local_49==0) || (iVar6=FUN_0100aa3c((u8)G8(0x45),(u32)P_bf0,*p36,*p40), iVar6==0)))
                    goto L_8980;
                cVar2=*P_bec;
                if (cVar2==0x7f) goto L_8be8;
                *P_bec=0x7f;
                FUN_010162e0(3);
                iVar6=FUN_01019aa0(&buf[0],bVar9,(u32)P_bf0,(u8)G8(0xb9),(u8)G8(0x8f),(u8)G8(0x79),(int)cVar2,1);
                if ((iVar6!=0) && (iVar6=FUN_0102961a((u32)P_bf4), iVar6!=0)) {
                    uVar8=0xd; goto L_882e;
                }
            }
        }
    }
    else {
        if (*p48!=0) { uVar8=1; FUN_010196e0(); goto L_882e; }
        if (G8(0x54)!=3) {
            if ((int)((u32)*p47<<0x1e)<0) {
                if ((local_4b==0) && (iVar6=FUN_0100aa3c((u8)G8(0x45),(u32)P_ac0,*p36,*p40), iVar6==0)) {
                    if (((u8)((u8)G8(0x55)-2) > 1) || (cVar4==0)) goto L_8932;
                    bVar9=0xfe;
                }
            } else {
                bVar9=0xff;
            }
            if ((G8(0x83)!=0) && (*P_abc != 0) && (*p2c != 0)) {
                ((void(*)(int,u32))(u32)*P_abc)(*p2c, *p24);
            }
            iVar6=FUN_0101709c(&buf[0], bVar9);
            if (iVar6!=0) { uVar8=3; goto L_882e; }
        }
    }
L_8932:
    uVar8=1;
L_882e:
    if (G8(0x7c)!=0) {
        FUN_010208b0(); FUN_0101fca8(); *(volatile signed char*)(0x21000f90+0x7c)=0;
        return uVar8;
    }
    return uVar8;

L_8be8:
    FUN_01016828();
    return uVar8;
}
