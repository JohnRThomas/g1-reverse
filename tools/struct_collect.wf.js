export const meta = {
  name: 'g1-struct-collect',
  description: 'Collect + propose structs from 684 Ghidra-derived clusters (20 sonnet agents)',
  phases: [{ title: 'Collect', detail: 'one sonnet agent per shard of clusters' }],
}

const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NSHARD = 20

const SCHEMA = {
  type: 'object',
  additionalProperties: false,
  required: ['proposals'],
  properties: {
    proposals: {
      type: 'array',
      items: {
        type: 'object',
        additionalProperties: false,
        required: ['cid', 'struct_name', 'purpose', 'is_library', 'confidence', 'fields'],
        properties: {
          cid: { type: 'string', description: 'cluster id from the bundle header, e.g. param_0007' },
          struct_name: { type: 'string', description: 'valid C identifier, snake_case, for the struct type' },
          purpose: { type: 'string', description: 'one sentence: what this object is' },
          is_library: { type: 'boolean', description: 'true if this is a stock SDK/library struct, not G1-original' },
          library_name: { type: 'string', description: 'the stock struct name (e.g. bt_conn, k_sem, net_buf) if is_library, else empty' },
          is_array: { type: 'boolean', description: 'true if the object is really an array/matrix, not a heterogeneous struct' },
          confidence: { type: 'string', enum: ['high', 'medium', 'low'] },
          fields: {
            type: 'array',
            description: 'one entry per NON-PAD field in the candidate layout, offsets UNCHANGED',
            items: {
              type: 'object',
              additionalProperties: false,
              required: ['offset', 'type', 'name'],
              properties: {
                offset: { type: 'string', description: 'hex offset exactly as in the candidate layout, e.g. 0x1c' },
                type: { type: 'string', description: 'refined C type for this field' },
                name: { type: 'string', description: 'field name (snake_case) or field_0xNN if unknown' },
                note: { type: 'string' },
              },
            },
          },
        },
      },
    },
  },
}

function prompt(i) {
  const ss = String(i).padStart(2, '0')
  return `You are a firmware reverse-engineering STRUCT-RECOVERY agent for the Even Realities G1 smart-glasses firmware (Nordic nRF5340 CPUAPP, ARM Cortex-M33).

Working dir: ${BASE}

Each "cluster" is a distinct in-memory object (a pointer parameter shared across functions, a global, or a stack frame) whose field OFFSETS and access SIZES were extracted mechanically from Ghidra — that layout is GROUND TRUTH. Your job is the semantic layer: name the struct, name/type its fields, state its purpose, and decide whether it is a stock library struct or a G1-original.

1. Read recon/structs/bundles/shard_${ss}.json — a JSON array of cluster ids.
2. For EACH cluster id, read recon/structs/bundles/<cid>.md — it has the candidate C layout, the member functions (readable names) and which parameter the object is, a merged access table, and a library hint.
3. Produce a proposal per cluster:
   - struct_name: concise snake_case C identifier reflecting purpose (e.g. batt_model_state, ble_conn_ctx, dmic_stream_cfg).
   - fields: one entry PER NON-PAD field, keeping each offset EXACTLY as given. Refine the type (e.g. pointer, float, a nested struct/enum) and give a field name when the surrounding evidence (member function names, access pattern, r/w) suggests one; otherwise keep field_0xNN.
   - is_library + library_name: if members are stock code (bt_/k_/z_/nrfx_/net_buf/lc3_/cJSON/log_/settings_ ...), identify the real struct (bt_conn, k_sem, k_timer, net_buf, k_work, etc.). You do NOT need to verify offsets — an Opus review pass verifies library offsets against the pinned headers. Just make your best identification.
   - is_array: set true when the accesses are uniform-stride element reads/writes (a matrix/buffer), not a heterogeneous record.
   - purpose, confidence.

Rules: never invent a field at an offset not present in the candidate layout; never change an offset. Read member function source under recon/named/<name>.c only if a bundle is ambiguous and you need more signal. Cover every cluster in the shard.

Return your structured proposals.`
}

phase('Collect')
const results = await parallel(
  Array.from({ length: NSHARD }, (_, i) => () =>
    agent(prompt(i), {
      label: `struct:shard_${String(i).padStart(2, '0')}`,
      phase: 'Collect', model: 'sonnet', effort: 'medium', schema: SCHEMA,
    })
  )
)

const all = []
results.forEach((r, i) => {
  if (r && Array.isArray(r.proposals)) for (const p of r.proposals) all.push({ ...p, shard: i })
})
log(`collected ${all.length} struct proposals from ${results.filter(Boolean).length}/${NSHARD} shards`)
return { proposals: all }
