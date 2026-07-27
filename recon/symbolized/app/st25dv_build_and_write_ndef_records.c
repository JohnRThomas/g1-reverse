#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000250f8 @ 0x000250f8
 * public-name: st25dv_build_and_write_ndef_records
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_mailbox_write_with_retry          <= FUN_00024fe8 @ 0x00024fe8
 *   event_record_init                        <= FUN_00025090 @ 0x00025090
 *   fill_record_type8                        <= FUN_000250c4 @ 0x000250c4
 *   st25dv_build_and_write_ndef_records      <= FUN_000250f8 @ 0x000250f8
 *   invoke_optional_op_offset12              <= FUN_0007c3da @ 0x0007c3da
 *   opt_record_decode                        <= FUN_0007c4f4 @ 0x0007c4f4
 *   opt_list_encode                          <= FUN_0007c77e @ 0x0007c77e
 *   opt_list_append_node                     <= FUN_0007c7de @ 0x0007c7de
 * address symbols (name @ address):
 *   g_ndef_build_status_flag                 @ 0x20018c6a
 */
/* Reconstructed FUN_000250f8 @ 0x250f8 */
#include <stdint.h>

extern int st25dv_mailbox_write_with_retry(void *, unsigned int);
extern unsigned int event_record_init(unsigned char *, unsigned int *);
extern unsigned int fill_record_type8(unsigned char *, unsigned int *);
extern unsigned long invoke_optional_op_offset12(unsigned char*, void*);
extern unsigned opt_record_decode(int *, unsigned char *);
extern int opt_list_encode(int *, int *, int, unsigned);
extern unsigned int opt_list_append_node(unsigned int *, unsigned char *);

struct encoded_record {
    uint32_t words[7];
};

struct buffer_view {
    void *data;
    uint32_t length;
};

struct record_builder {
    void *data;
    uint32_t length;
    uint32_t state;
};

int st25dv_build_and_write_ndef_records(const unsigned char *primary,
                 const unsigned char *secondary,
                 const unsigned char *suffix)
{
    unsigned char primary_spec[10];
    unsigned char secondary_spec[9];
    unsigned char output[32];
    unsigned char primary_work[32];
    unsigned char secondary_work[32];
    struct encoded_record primary_record;
    struct encoded_record suffix_record;
    struct encoded_record secondary_record;
    struct encoded_record records[4];
    struct record_builder builder;
    struct buffer_view output_view;
    unsigned int status;
    int record_count;

    primary_spec[0] = 0x20;
    primary_spec[1] = primary[0];
    primary_spec[2] = primary[1];
    primary_spec[3] = primary[2];
    primary_spec[4] = primary[3];
    primary_spec[5] = primary[9];
    primary_spec[6] = primary[4];
    primary_spec[7] = primary[6];
    primary_spec[8] = primary[7];
    primary_spec[9] = primary[8];

    status = (unsigned int)event_record_init(primary_work, primary_spec);
    status |= (unsigned int)invoke_optional_op_offset12(primary_work, &primary_record);
    records[0] = primary_record;
    status &= 0xffff;

    if (secondary[0] == 0) {
        record_count = 1;
    } else {
        secondary_spec[0] = secondary[1];
        secondary_spec[1] = secondary[2];
        secondary_spec[2] = secondary[3];
        secondary_spec[3] = secondary[4];
        secondary_spec[4] = secondary[5];
        secondary_spec[5] = secondary[6];
        secondary_spec[6] = secondary[7];
        secondary_spec[8] = secondary[8];
        record_count = 2;
        unsigned int secondary_status;
        secondary_status = (unsigned int)fill_record_type8(secondary_work, secondary_spec);
        secondary_status |= (unsigned int)invoke_optional_op_offset12(secondary_work, &secondary_record);
        status = (status | secondary_status) & 0xffff;
        records[1] = secondary_record;
    }

    if (suffix[0] != 0) {
        struct buffer_view suffix_view;
        ((uint32_t *)output)[0] = 0x57020651;
        ((uint32_t *)output)[1] = 0x4f46434c;
        output[8] = 0x44;
        output[9] = suffix[1];
        output[10] = suffix[2];
        suffix_view.data = output;
        suffix_view.length = 11;
        status = (unsigned int)opt_record_decode(&suffix_view, &suffix_record);
        if (record_count == 1)
            records[1] = suffix_record;
        else
            records[2] = suffix_record;
        ++record_count;
    }

    builder.data = 0;
    builder.length = 0;
    builder.state = 0;
    *(volatile unsigned char *)((unsigned long)&g_ndef_build_status_flag) /*=0x20018c6a*/ = 0;
    for (int index = 0; index != record_count; ++index) {
        status = (status |
                  (unsigned int)opt_list_append_node(&builder, &records[index])) & 0xffff;
    }

    output_view.data = output;
    output_view.length = 0x20;
    status = ((status |
               ((unsigned int)opt_list_encode(&builder, &output_view,
                                            (void *)((unsigned long)&g_ndef_build_status_flag) /*=0x20018c6a*/, 0x20) & 0xffff)) |
              ((unsigned int)st25dv_mailbox_write_with_retry(output_view.data,
                                          output_view.length) & 0xffff));
    return status == 0 ? 0 : -1;
}
