export const meta = {
  name: 'g1-field-name',
  description: 'Name 1008 struct field_0x* placeholders via deep code sweep (20 opus agents)',
  phases: [{ title: 'FieldName', detail: 'one opus agent per shard of structs' }],
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
        required: ['cid', 'fields'],
        properties: {
          cid: { type: 'string' },
          struct_rename: { type: 'string', description: 'optional better struct name if the sweep reveals one; empty to keep' },
          fields: {
            type: 'array',
            items: {
              type: 'object',
              additionalProperties: false,
              required: ['offset', 'name'],
              properties: {
                offset: { type: 'string', description: 'hex offset exactly as in the bundle, e.g. 0x48' },
                name: { type: 'string', description: 'snake_case C identifier for this field; keep field_0xNN if truly undeterminable' },
                type: { type: 'string', description: 'optional refined C type; empty to keep' },
                note: { type: 'string', description: 'evidence: how this field is used in the swept code' },
                confidence: { type: 'string', enum: ['high', 'medium', 'low'] },
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
  return `You are a firmware reverse-engineering agent naming STRUCT FIELDS for the Even Realities G1 CPUAPP (Nordic nRF5340). Recovered structs currently have placeholder field names like field_0x48. Your job: read how each field is actually USED in the fully-named source and give it a meaningful name.

Working dir: ${BASE}

1. Read recon/structs/field_bundles/shard_${ss}.json — a JSON array of struct cluster ids.
2. For EACH cid, read recon/structs/field_bundles/<cid>.md — it has the struct, its purpose, and the list of member functions with paths into recon/readable_sources/app/ (fully named source: no FUN_/DAT_).
3. DIVE INTO THE CODE: open each listed member source file and study every access to this object at the placeholder offsets. Grep the readable_sources/app tree for more call sites if useful. Infer each field's meaning from: what is stored/loaded, comparisons, the surrounding logic, sibling field names, referenced strings, and the struct's purpose. For library structs, use your knowledge of the real SDK type (e.g. bt_conn, k_sem, net_buf) to name fields to match the upstream member names.
4. Propose a name for EVERY field_0xNN placeholder (keep the exact offset). Only leave a name as field_0xNN if the code truly gives no signal — say why in the note and mark confidence low. Optionally refine the C type and/or suggest a better struct_rename.

Rules: never change an offset; names must be valid C identifiers, snake_case, unique within the struct. Prefer domain terms (mtu, handle, state, credits, refcount, seq, len, flags, timestamp_ms, quat_w ...). Cover every struct in the shard.

Return structured proposals.`
}

phase('FieldName')
const results = await parallel(
  Array.from({ length: NSHARD }, (_, i) => () =>
    agent(prompt(i), {
      label: `field:shard_${String(i).padStart(2, '0')}`,
      phase: 'FieldName', effort: 'high', schema: SCHEMA,
    })
  )
)

const all = []
results.forEach((r, i) => {
  if (r && Array.isArray(r.proposals)) for (const p of r.proposals) all.push({ ...p, shard: i })
})
log(`collected field names for ${all.length} structs from ${results.filter(Boolean).length}/${NSHARD} shards`)
return { proposals: all }
