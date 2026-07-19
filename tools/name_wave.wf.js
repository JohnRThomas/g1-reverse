export const meta = {
  name: 'g1-name-wave',
  description: 'Name 563 unnamed CPUAPP functions across 20 parallel agents',
  phases: [{ title: 'Name', detail: 'one agent per batch of ~28 functions' }],
}

const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NBATCH = 20

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
        required: ['address', 'name', 'confidence', 'evidence'],
        properties: {
          address: { type: 'string', description: 'function entry address, e.g. 0x0000c358' },
          name: { type: 'string', description: 'proposed unique valid C snake_case identifier' },
          confidence: { type: 'string', enum: ['high', 'medium', 'low'] },
          evidence: { type: 'string', description: 'one specific sentence tying the name to signals in the bundle' },
        },
      },
    },
  },
}

function prompt(i) {
  const bb = String(i).padStart(2, '0')
  return `You are a firmware reverse-engineering naming agent for the Even Realities G1 smart-glasses firmware (Nordic nRF5340 CPUAPP, ARM Cortex-M33).

Working dir: ${BASE}

1. Read recon/naming_bundles/GUIDE.md (naming rules) and recon/naming_bundles/existing_names.txt (names already taken — never collide with these).
2. Read recon/naming_bundles/batch_${bb}.json — a JSON array of function ids (e.g. "FUN_0000c358").
3. For EACH id, read recon/naming_bundles/<id>.md — readable reconstructed C source, callers, callees, referenced strings.
4. Propose a concise, unique, valid C snake_case name per the GUIDE for every function.

Base names on behavior, callers, callees, and strings. A bare C-identifier log string inside a function is almost certainly its real name — use it verbatim. Mark thin-evidence guesses confidence "low" but still propose a structural name. Never reuse an existing_names.txt name or one you already used in this batch.

Return your structured proposals (address = the @0x... entry value from each bundle header). Cover every function in the batch.`
}

phase('Name')
const results = await parallel(
  Array.from({ length: NBATCH }, (_, i) => () =>
    agent(prompt(i), { label: `name:batch_${String(i).padStart(2, '0')}`, phase: 'Name', schema: SCHEMA })
  )
)

const all = []
results.forEach((r, i) => {
  if (r && Array.isArray(r.proposals)) {
    for (const p of r.proposals) all.push({ ...p, batch: i })
  }
})
log(`collected ${all.length} proposals from ${results.filter(Boolean).length}/${NBATCH} batches`)
return { proposals: all }
