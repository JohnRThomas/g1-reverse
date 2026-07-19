export const meta = {
  name: 'g1-struct-merge',
  description: 'Dedup/merge + sanity-review + library-offset verify structs (10 opus agents)',
  phases: [{ title: 'Merge', detail: 'one opus agent per shard of review groups' }],
}

const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NSHARD = 10
const HEADERS = '~/ncs251/{zephyr,nrf,nrfxlib} and ~/zephyr_sigwork_v2.5.1/{zephyr,nrf,nrfxlib}'

const SCHEMA = {
  type: 'object',
  additionalProperties: false,
  required: ['structs'],
  properties: {
    structs: {
      type: 'array',
      items: {
        type: 'object',
        additionalProperties: false,
        required: ['cid', 'struct_name', 'purpose', 'is_library', 'confidence', 'fields'],
        properties: {
          cid: { type: 'string', description: 'representative cluster id (canonical for this merged group)' },
          merged_cids: { type: 'array', items: { type: 'string' }, description: 'all cluster ids folded into this struct' },
          struct_name: { type: 'string' },
          purpose: { type: 'string' },
          is_library: { type: 'boolean' },
          library_name: { type: 'string', description: 'real stock struct name if is_library, else empty' },
          library_header: { type: 'string', description: 'path to the pinned header where you verified it, else empty' },
          library_verified: { type: 'boolean', description: 'true only if you checked the real member offsets against the header and they match' },
          is_array: { type: 'boolean' },
          is_union: { type: 'boolean', description: 'true if offsets overlap (accessed both wide and in parts)' },
          confidence: { type: 'string', enum: ['high', 'medium', 'low'] },
          fields: {
            type: 'array',
            items: {
              type: 'object',
              additionalProperties: false,
              required: ['offset', 'type', 'name'],
              properties: {
                offset: { type: 'string' },
                type: { type: 'string' },
                name: { type: 'string' },
                library_member: { type: 'string', description: 'the real struct member name at this offset, if library' },
                note: { type: 'string' },
              },
            },
          },
          review_note: { type: 'string', description: 'what you changed vs the sonnet proposal and why' },
        },
      },
    },
  },
}

function prompt(i) {
  const ss = String(i).padStart(2, '0')
  return `You are a senior firmware reverse-engineering STRUCT-REVIEW agent for the Even Realities G1 firmware (Nordic nRF5340 CPUAPP, ARM Cortex-M33). NCS 2.5.1 / Zephyr 3.4.99 pinned.

Working dir: ${BASE}

A first pass (Sonnet) proposed struct names/fields for Ghidra-derived clusters. Your job: DEDUP, MERGE, SANITY-CHECK, and for library structs VERIFY OFFSETS against the real pinned headers.

1. Read recon/structs/mgroup_shard_${ss}.json — a JSON array of groups, each {"rep": "<cid>", "cids": [...]}.
2. For EACH group, read recon/structs/review/<rep>.md — it contains every proposal in the group plus the ground-truth Ghidra bundle (candidate layout, members, access table) for each cid.
3. Multi-cid groups were grouped only because they share a footprint signature — they are DUPLICATE CANDIDATES, not confirmed. Merge into ONE struct (all cids in merged_cids) ONLY if they are genuinely the same object (same purpose/members/library). If a footprint collision is coincidental (e.g. md5_context vs a QSPI register block that happen to share a 4-word shape), emit them as SEPARATE structs. You MUST output a struct record covering every cid in your shard (each cid appears in exactly one struct's merged_cids).
4. Produce each canonical struct record:
   - Correct obviously-wrong names/types from the sonnet pass; keep every OFFSET exactly as ground truth (offsets are non-negotiable). A field width must not exceed the gap to the next field — if the code accesses the same bytes both wide and in parts, set is_union=true.
   - is_library + library_name: if this is a stock struct (bt_conn, k_sem, k_timer, k_work, net_buf, k_mutex, k_queue, sys_dnode/sys_slist, onoff_manager, nrfx_* config, log_msg, settings_handler, cJSON, lc3 state, mbedtls/tinycrypt ctx, etc.), IDENTIFY it, then OPEN the real header under ${HEADERS} and CHECK that the real member offsets match the observed offsets. Set library_header to the file you read, library_verified=true only if offsets actually line up, and fill each field's library_member with the real member name. If you cannot locate/verify, set library_verified=false and say why in review_note.
   - purpose, is_array, confidence, review_note.

Rules: never invent a field at an unobserved offset; never change an offset. Read member sources under recon/named/<name>.c or the pinned headers as needed. Cover every representative in the shard.

Return your structured canonical structs.`
}

phase('Merge')
const results = await parallel(
  Array.from({ length: NSHARD }, (_, i) => () =>
    agent(prompt(i), {
      label: `merge:shard_${String(i).padStart(2, '0')}`,
      phase: 'Merge', model: 'opus', effort: 'high', schema: SCHEMA,
    })
  )
)

const all = []
results.forEach((r, i) => {
  if (r && Array.isArray(r.structs)) for (const s of r.structs) all.push({ ...s, shard: i })
})
log(`merged ${all.length} canonical structs from ${results.filter(Boolean).length}/${NSHARD} shards`)
return { structs: all }
