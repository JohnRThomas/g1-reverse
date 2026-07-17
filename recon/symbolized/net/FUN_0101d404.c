#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101d404 @ 0x0101d404
 * public-name: FUN_0101d404
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_pdu_type_bits_set                    <= FUN_0100e5dc @ 0x0100e5dc
 *   controller_packet_type29_init            <= FUN_01029bda @ 0x01029bda
 *   controller_packet_type30_init            <= FUN_01029bea @ 0x01029bea
 * address symbols (name @ address):
 *   g_210001e8                               @ 0x210001e8
 *   g_210004b0                               @ 0x210004b0
 *   g_210004b4                               @ 0x210004b4
 *   g_210004c8                               @ 0x210004c8
 *   g_net_link_ctx_b                         @ 0x21001124
 */
/* net-core FUN_0101d404 @ 0x101d404  true code extent: 0x478 bytes */
#include <stdint.h>
#include <stddef.h>

#define EXT(name) extern intptr_t name(intptr_t, ...)
EXT(FUN_0100a8f8); EXT(FUN_0100a904); EXT(FUN_0100a934); EXT(FUN_0100a954);
EXT(FUN_0100b170); EXT(FUN_0100b180); EXT(FUN_0100d3c0); EXT(FUN_0100d5d0);
EXT(FUN_0100d64c); EXT(FUN_0100d688); EXT(FUN_0100dc1c); EXT(sdc_pdu_type_bits_set);
EXT(FUN_0100e5f4); EXT(FUN_0100e608); EXT(FUN_0100e634); EXT(FUN_0100e68c);
EXT(FUN_0100e708); EXT(FUN_0100e72c); EXT(FUN_0100e744); EXT(FUN_0100e754);
EXT(FUN_0100e774); EXT(FUN_0100e7b0); EXT(FUN_0100e7b8); EXT(FUN_0100e7c0);
EXT(FUN_0100e7c8); EXT(FUN_0100e808); EXT(FUN_0100e83c); EXT(FUN_0100e8ac);
EXT(FUN_0100e8b4); EXT(FUN_0100e8bc); EXT(FUN_0100e8e8); EXT(FUN_0100e8f0);
EXT(FUN_010100f4); EXT(FUN_01010110); EXT(FUN_0101bf30); EXT(FUN_0101c6d0);
EXT(FUN_01025a84); EXT(FUN_010298a8); EXT(controller_packet_type29_init); EXT(controller_packet_type30_init);
extern void sdc_assertion_fail(uint32_t module, uint32_t line);
static __attribute__((noreturn)) void fatal_loop(uint32_t line)
{ for (;;) sdc_assertion_fail(0x36, line); }

typedef struct {
    uint8_t active;
    uint8_t pad01[3];
    uint8_t *connection;
    uint8_t pad08[2];
    uint16_t counter;
    uint8_t pad0c[8];
    uint8_t pending;
} build_state_t;

static inline uint16_t rd16(const uint8_t *p, size_t n)
{ return *(const volatile uint16_t *)(p + n); }
static inline uint32_t rd32(const uint8_t *p, size_t n)
{ return *(const volatile uint32_t *)(p + n); }
static inline void wr16(uint8_t *p, size_t n, uint16_t v)
{ *(volatile uint16_t *)(p + n) = v; }
static inline void wr32(uint8_t *p, size_t n, uint32_t v)
{ *(volatile uint32_t *)(p + n) = v; }

int FUN_0101d404(uint16_t *input)
{
    build_state_t *const state = (build_state_t *)UINT32_C(0x21001124);
    uint8_t *connection = (uint8_t *)input;
    state->active = 0;
    state->counter = 0;
    ((volatile uint8_t *)state)[8] = 0;
    state->pending = 0;
    state->connection = connection;

    FUN_0100a8f8(*input);
    FUN_0100a954(*(uint16_t *)state->connection);
    if (FUN_0100dc1c((intptr_t)(connection + 0xa8), (intptr_t)connection,
                     rd16(connection, 0x302) + 1) != 0)
        fatal_loop(0x18e);

    wr16(connection, 0x302, 0);
    uint8_t marker = connection[0xc6];
    if (marker == 0x26) {
        if ((int16_t)(rd16(connection, 0xbc) - rd16(connection, 0x318)) >= 0) {
            connection[0xc6] = 0;
            if (FUN_0101bf30(0) == 0) {
                FUN_0101c6d0(0);
                return 0;
            }
        }
    } else if ((uint8_t)(connection[0xc5] - 0x26) <= 2 &&
               (int16_t)(rd16(connection, 0xbc) - rd16(connection, 0x318)) >= 0) {
        connection[0xc5] = 0;
        if (FUN_0101bf30(0) == 0) {
            FUN_0101c6d0(0);
            return 0;
        }
    }

    connection = state->connection;
    if (connection[0x100] && rd16(connection, 0xfc) >= rd16(connection, 0xfe))
        return 1;
    if ((int8_t)connection[0x104] && rd16(connection, 0x102) >= rd16(connection, 0xfe))
        return 1;
    if (rd16(connection, 0xfa) >= rd16(connection, 0xf8))
        return 1;
    if (connection[0xc9] == 0) {
        if (rd16(connection, 0xf6) > 5) return 1;
    } else if (rd16(connection, 0xf6) >= rd16(connection, 0xf8)) {
        return 1;
    }

    uint8_t attribute = connection[0x14e];
    uint8_t *packet = NULL;
    if (attribute != 0xfe) {
        if (FUN_0100a904((intptr_t)&packet) == 0)
            fatal_loop(0x810);
        FUN_01025a84((intptr_t)packet, 0, 0x32);
        sdc_pdu_type_bits_set((intptr_t)packet, 3);
        packet[0] &= 0xef;
        FUN_0100e634((intptr_t)packet, attribute);

        switch (attribute) {
        case 0: {
            packet[4] = (uint8_t)FUN_0100d64c(rd16(connection,0x320), rd32(connection,0x328));
            uint16_t v = (uint16_t)FUN_0100d688(rd32(connection,0x324), rd32(connection,0x328));
            wr16(packet,5,v);
            v = (uint16_t)FUN_0100d5d0(rd32(connection,0x328));
            wr16(packet,7,v); wr16(packet,9,rd16(connection,0x32c));
            FUN_0100e68c((intptr_t)packet, rd16(connection,0x32e)); break;
        }
        case 1: FUN_0100e708((intptr_t)packet, rd32(connection,0x310)+1); break;
        case 2: packet[4]=connection[0x161]; break;
        case 3:
            FUN_0100e72c((intptr_t)packet,(intptr_t)(connection+0x331));
            FUN_0100e744((intptr_t)packet,(intptr_t)(connection+0x339));
            FUN_0100e754((intptr_t)packet,(intptr_t)(connection+0x34b));
            FUN_0100e774((intptr_t)packet,(intptr_t)(connection+0x140)); break;
        case 6: case 10: case 11: case 18: case 19: break;
        case 7: packet[4]=connection[0x150]; break;
        case 8: FUN_010100f4((intptr_t)packet); break;
        case 9: FUN_01010110((intptr_t)state,(intptr_t)packet); break;
        case 12: wr32(packet,4,UINT32_C(0x0200590d)); packet[8]=0x21; break;
        case 17:
            if (connection[0x150] == 0) {
                FUN_0100e8e8((intptr_t)packet,connection[0x14b]);
                FUN_0100e8f0((intptr_t)packet,connection[0x14a]);
            } else {
                FUN_0100e8e8((intptr_t)packet,connection[0x14d]);
                FUN_0100e8f0((intptr_t)packet,connection[0x14c]);
            } break;
        case 20: case 21:
            FUN_0100e7c0((intptr_t)packet,rd16(connection,0x4c));
            FUN_0100e7c8((intptr_t)packet,rd16(connection,0x150));
            FUN_0100e7b0((intptr_t)packet,rd16(connection,0x50));
            FUN_0100e7b8((intptr_t)packet,rd16(connection,0x152)); break;
        case 22: wr16(packet,4,rd16(connection,0x16e)); break;
        case 24: {
            intptr_t v=FUN_010298a8(connection[0x31b]); FUN_0100e8b4((intptr_t)packet,v);
            uint8_t a=connection[0x31a], b=connection[0x6e];
            v=FUN_010298a8(((a&0xc)&&(b&0xc)&&a!=b)?0:a);
            FUN_0100e8ac((intptr_t)packet,v); break;
        }
        case 27: {
            uint8_t flags=0; FUN_0100e5f4((intptr_t)packet,1);
            uint8_t mode=connection[0x10]; if(mode==3) mode=0;
            flags=(connection[0x11]&0x1f)|(mode<<6)|(flags&0x20);
            FUN_0100e608((intptr_t)packet,(intptr_t)&flags); break;
        }
        case 28: FUN_0100e808((intptr_t)packet,(intptr_t)(connection+0x179)); break;
        case 29: controller_packet_type29_init((intptr_t)packet); break;
        case 30: controller_packet_type30_init((intptr_t)packet); break;
        case 31: { void (*cb)(uint8_t*,uint8_t*)=*(void (**)(uint8_t*,uint8_t*))UINT32_C(0x210004b4); if(cb) cb(packet,connection); break; }
        case 33: { void (*cb)(uint8_t*,uint8_t*)=*(void (**)(uint8_t*,uint8_t*))UINT32_C(0x210004b0); if(cb) cb(packet,connection); break; }
        case 34: { void (*cb)(uint8_t*,uint8_t*)=*(void (**)(uint8_t*,uint8_t*))UINT32_C(0x210001e8); if(cb) cb(packet,connection+0x160); break; }
        case 35: case 36: case 37: { void (*cb)(uint8_t,uint8_t*,build_state_t*)=*(void (**)(uint8_t,uint8_t*,build_state_t*))UINT32_C(0x210004c8); cb(attribute,packet,state); break; }
        case 42: FUN_0100e83c((intptr_t)packet,(intptr_t)(connection+0x179),(intptr_t)(connection+0x19b)); break;
        default: fatal_loop(0x8ec);
        }

        if (FUN_0100a934(0) == 0) fatal_loop(0x8f2);
        if (packet[3]==1) wr16(packet,9,rd16(connection,0x316));
        else if(packet[3]==0) wr16(packet,0xd,rd16(connection,0x31e));
        else if(packet[3]==0x18) FUN_0100e8bc((intptr_t)packet,rd16(connection,0x318));
    }

    FUN_0100b180(rd32((const uint8_t *)state,0),(intptr_t)state->connection,
                  UINT32_C(0x0101cb19),UINT32_C(0x0101ca35),
                  UINT32_C(0x0101ced1));
    int status=(int)FUN_0100d3c0((intptr_t)(state->connection+0xa8),5,state->connection[0xc5],0);
    if(status){ FUN_0100b170(0); return status; }
    return 1;
}
