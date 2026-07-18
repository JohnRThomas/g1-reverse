#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006f4a0 @ 0x0006f4a0
 * public-name: lc3_spec_analyze
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_bwdet_get_nbits                      <= FUN_00068b14 @ 0x00068b14
 *   lc3_ltpf_get_nbits                       <= FUN_0006b36c @ 0x0006b36c
 *   lc3_sns_get_nbits                        <= FUN_0006efd8 @ 0x0006efd8
 *   lc3_spec_quantize                        <= FUN_0006f164 @ 0x0006f164
 *   lc3_spec_compute_nbits                   <= FUN_0006f28c @ 0x0006f28c
 *   lc3_spec_analyze                         <= FUN_0006f4a0 @ 0x0006f4a0
 *   lc3_tns_get_nbits                        <= FUN_000709d8 @ 0x000709d8
 *   log10f                                   <= FUN_00075d5c @ 0x00075d5c
 * address symbols (name @ address):
 *   lc3_spec_iq_table                        @ 0x0008d350
 */
/* lc3_spec_analyze @ 0x0006f4a0 (NCS 2.5.1 libLC3). */
#include <stdint.h>
#include <stdbool.h>

typedef struct { float nbits_off; int nbits_spare; } lc3_spec_analysis_t;
typedef struct { int g_idx, nq; bool lsb_mode; } lc3_spec_side_t;

extern int lc3_bwdet_get_nbits(int sr);
extern int lc3_ltpf_get_nbits(bool pitch);
extern int lc3_sns_get_nbits(void);
extern int lc3_tns_get_nbits(const void *tns);
extern void lc3_spec_quantize(int dt,int sr,int gain,float *x,uint16_t *xq,int *nq);
extern int lc3_spec_compute_nbits(int dt,int sr,int nbytes,const uint16_t *xq,int *nq,
                       int budget,bool *lsb_mode);
extern float log10f(float x);

static inline float maxnum(float a,float b) { return __builtin_fmaxf(a,b); }
static inline float minnum(float a,float b) { return __builtin_fminf(a,b); }

static inline int fast_db_q16(float x)
{
    const uint16_t *t=(const uint16_t *)((unsigned long)&lc3_spec_iq_table) /*=0x8d350*/;
    union { float f; uint32_t u; } v={x};
    unsigned n=(v.u>>18)&31, r=(v.u>>2)&0xffff;
    return ((int)(v.u>>22)-254)*0xc0a9 + t[2*n] + ((int)t[2*n+1]*(int)r>>16);
}

static int resolve_gain_offset(int sr,int nbytes)
{
    int x=(nbytes*8)/(10*(1+sr));
    return 105+5*(1+sr)+(x<115?x:115);
}

static int estimate_gain(int dt,int sr,const float *x,int budget,float off,
                         int goff,bool *reset)
{
    int ne=20*(3+dt)*(1+sr)/4, e[ne]; float xmax=0;
    for(int i=0;i<ne;i++,x+=4){
        float a=x[0]*x[0],b=x[1]*x[1],c=x[2]*x[2],d=x[3]*x[3];
        xmax=maxnum(maxnum(xmax,a),maxnum(b,maxnum(c,d)));
        e[i]=fast_db_q16(maxnum(a+b+c+d,1e-10f));
    }
    int nbits=(int)(budget+off+0.5f), g=255-goff;
    const int k20=0xb6db,k27=0x2b333,k14=0x16666;
    for(int step=128,j,j0=ne-1,j1;step;step>>=1){
        int gn=(g-step)*k20,v=0;
        for(j=j0;j>=0&&e[j]<gn;j--); j1=j;
        for(;j>=0;j--){int d=e[j]-gn;v+=d<0?k27:(d<(43<<16)?d+(7<<16):2*d-(36<<16));}
        if(v>nbits*k14)j0=j1;else g-=step;
    }
    int gmin;
    if(xmax==0) gmin=-goff;
    else {
        float z=log10f(__builtin_sqrtf(xmax)*(1.0f/(32768.0f-0.375f)));
        gmin=(int)__builtin_ceilf(28.0f*z);
    }
    *reset=g<gmin||xmax==0; if(*reset)g=gmin; return g;
}

static int adjust_gain(int sr,int idx,int nbits,int budget)
{
    static const int t[5][3]={{80,500,850},{230,1025,1700},{380,1550,2550},
      {530,2075,3400},{680,2600,4250}};
    int delta,den=48;
    if(nbits<t[sr][0]) delta=3*(nbits+48);
    else if(nbits<t[sr][1]) {int n0=3*(t[sr][0]+48),r=t[sr][1]-t[sr][0];
      delta=n0*r+(nbits-t[sr][0])*(t[sr][1]-n0);den*=r;}
    else delta=nbits<t[sr][2]?nbits:t[sr][2];
    delta=(delta+den/2)/den;
    if(nbits<budget-(delta+2))return -(idx>0);
    if(nbits>budget)return (idx<255)+(idx<254&&nbits>=budget+delta);
    return 0;
}

void lc3_spec_analyze(int dt,int sr,int nbytes,bool pitch,const void *tns,
                  lc3_spec_analysis_t *spec,float *x,uint16_t *xq,
                  lc3_spec_side_t *side)
{
    int nqbits=4+(20*(3+dt)*(1+sr)>32)+(20*(3+dt)*(1+sr)>64)+
      (20*(3+dt)*(1+sr)>128)+(20*(3+dt)*(1+sr)>256);
    int ac=nqbits+3+((nbytes-1)/160<2?(nbytes-1)/160:2);
    int budget=8*nbytes-ac-lc3_bwdet_get_nbits(sr)-lc3_ltpf_get_nbits(pitch)-lc3_sns_get_nbits()-
      lc3_tns_get_nbits(tns)-8-3;
    float off=minnum(maxnum(spec->nbits_off+spec->nbits_spare,-40),40);
    off=.8f*spec->nbits_off+.2f*off;
    int goff=resolve_gain_offset(sr,nbytes); bool reset;
    int gint=estimate_gain(dt,sr,x,budget,off,goff,&reset);
    lc3_spec_quantize(dt,sr,gint,x,xq,&side->nq);
    int nbits=lc3_spec_compute_nbits(dt,sr,nbytes,xq,&side->nq,0,0);
    spec->nbits_off=reset?0:off; spec->nbits_spare=reset?0:budget-nbits;
    int adj=adjust_gain(sr,gint+goff,nbits,budget);
    if(adj)lc3_spec_quantize(dt,sr,adj,x,xq,&side->nq);
    side->g_idx=gint+adj+goff;
    lc3_spec_compute_nbits(dt,sr,nbytes,xq,&side->nq,budget,&side->lsb_mode);
}
