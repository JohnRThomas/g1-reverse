#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_lc3_bits_state__param_0367             [param_0367; library]
 * Raw function identity: 0x000685f4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000685f4 @ 0x000685f4
 * public-name: lc3_flush_bits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_flush_bits                           <= FUN_000685f4 @ 0x000685f4
 */
/* Full reconstruction FUN_000685f4 @ 0x000685f4 (788-byte exact extent). */
#include <stdint.h>

typedef struct {
    uint32_t unused0;
    uint32_t low;
    uint32_t range;
    int32_t cached_byte;
    uint32_t carry;
    int32_t pending_ff;
    uint32_t unused18;
    uint32_t bit_buffer;
    int32_t bit_count;
    uint8_t unused24[8];
    uint8_t *output_end;
    uint8_t *output;
    uint8_t *reverse_output;
} coder_state;

static inline __attribute__((always_inline)) void put_back_bytes(volatile coder_state *s, uint32_t count)
{
    while (count != 0) {
        uint32_t value = s->bit_buffer;
        uint8_t *p = s->reverse_output;
        s->reverse_output = p - 1;
        *(volatile uint8_t *)(p - 1) = (uint8_t)value;
        s->bit_buffer = value >> 8;
        count--;
    }
}

static inline __attribute__((always_inline)) void emit_pending(volatile coder_state *s)
{
    uint8_t *p = s->output;
    uint8_t *end = s->output_end;

    if (s->cached_byte >= 0 && p < end) {
        s->output = p + 1;
        *(volatile uint8_t *)p = (uint8_t)(s->cached_byte + s->carry);
        p++;
    }

    while (s->pending_ff > 0) {
        if (p >= end) {
            s->pending_ff--;
            if (s->pending_ff > 0)
                s->pending_ff = 0;
            break;
        }
        s->output = p + 1;
        *(volatile uint8_t *)p = s->carry ? 0 : 0xff;
        p++;
        s->pending_ff--;
    }
    s->carry = 0;
    s->cached_byte = (int32_t)(s->low >> 16);
}

void lc3_flush_bits(volatile coder_state *s)
{
    int32_t bits = s->bit_count;
    uint8_t *begin = s->output;
    uint8_t *out = s->reverse_output;
    int32_t available = (int32_t)(out - begin);
    int32_t excess = available * 8 - bits;

    if (excess > 0) {
        int32_t remaining = excess;
        int32_t marker = excess - 32;
        int32_t stop = marker - ((excess - 1) & ~31);
        do {
            int32_t chunk = remaining > 31 ? 32 : remaining;
            int32_t total = chunk + bits;
            if (total > 32) {
                int32_t consumed = 32 - bits;
                if (consumed > chunk)
                    consumed = chunk;
                uint32_t bytes = consumed == 0 ? (uint32_t)(bits >> 3) : 4;
                uint32_t present = available < 0 ? 0u : (uint32_t)available;
                if (bytes > present)
                    bytes = present;
                if (bytes != 0) {
                    put_back_bytes(s, bytes);
                    begin = s->output;
                    out = s->reverse_output;
                    available = (int32_t)(out - begin);
                }
                s->bit_buffer = 0;
                total = chunk - consumed;
            }
            bits = total;
            if (marker == stop)
                break;
            remaining = marker;
            marker -= 32;
        } while (1);
    } else {
        available = available < 0 ? 0 : available;
    }

    {
        uint32_t bytes = (uint32_t)(bits >> 3);
        uint32_t present = available < 0 ? 0u : (uint32_t)available;
        if (bytes > present)
            bytes = present;
        bits -= (int32_t)(bytes * 8);
        s->bit_count = bits;
        if (bytes != 0) {
            put_back_bytes(s, bytes);
            bits = s->bit_count;
            begin = s->output;
        }
    }
    if (bits > 7) {
        bits = 0;
        s->bit_count = 0;
    }

    uint32_t range = s->range;
    uint32_t shift;
    uint32_t mask;
    uint32_t width;
    if (range == 0) {
        mask = 0;
        shift = 25;
        width = 0;
    } else {
        width = 0;
        uint32_t v = range;
        do {
            v >>= 1;
            width++;
        } while (v != 0);
        shift = 25 - width;
        mask = 0x00ffffffu >> (shift & 31);
    }

    uint32_t old_low = s->low;
    uint32_t low = (old_low + mask) & ~mask & 0x00ffffffu;
    if (((old_low + mask) >> 24 != 0) == ((range + old_low) >> 24 != 0)) {
        if (((range + old_low) & 0x00ffffffu) <= low + mask) {
            shift = 26 - width;
            low = (old_low + (mask >> 1)) & ~(mask >> 1) & 0x00ffffffu;
        }
        uint32_t carry = s->carry;
        if (low < old_low)
            carry |= 1;
        s->carry = carry;
    }
    s->low = low;

    int32_t cached = s->cached_byte;
    uint8_t *end = s->output_end;
    out = s->output;
    uint32_t left = shift;
    if ((int32_t)shift > 8) {
        do {
            if (low < 0x00ff0000u || s->carry != 0) {
                emit_pending(s);
                end = s->output_end;
                out = s->output;
                cached = s->cached_byte;
            } else {
                s->pending_ff++;
            }
            left -= 8;
            low = (low & 0xffffu) << 8;
            s->low = low;
        } while ((int32_t)left > 8);
        shift = (shift - 8) - ((shift - 9) & ~7u);
    }

    if (low < 0x00ff0000u || s->carry != 0) {
        emit_pending(s);
        end = s->output_end;
        out = s->output;
        cached = s->cached_byte;
    } else {
        s->pending_ff++;
    }
    low = s->low;
    s->low = (low & 0xffffu) << 8;

    int32_t tail;
    if (s->pending_ff == 0) {
        tail = cached >> ((8 - shift) & 31);
    } else {
        if (out < end) {
            s->output = out + 1;
            *(volatile uint8_t *)out = (uint8_t)cached;
            out++;
        }
        while (s->pending_ff > 1) {
            if (out >= end) {
                int32_t n = s->pending_ff - 1;
                if (s->pending_ff != 2)
                    n = 1;
                s->pending_ff = n;
                break;
            }
            s->output = out + 1;
            *(volatile uint8_t *)out = 0xff;
            out++;
            s->pending_ff--;
        }
        tail = shift == 8 ? 0xff : 0;
    }

    out = s->output;
    end = s->output_end;
    if (out < end) {
        uint8_t keep = (uint8_t)(0xffu >> (shift & 31));
        *(volatile uint8_t *)out &= keep;
        *(volatile uint8_t *)out |= (uint8_t)(tail << ((8 - shift) & 31));
    }
}
