(function attachAssetViewers(global) {
  "use strict";

  /*
   * Framework-free renderers for recovered firmware assets.
   *
   * Asset records are deliberately permissive. The renderer understands the
   * canonical fields used by the catalog (`name`, `address`, `kind`, `bytes`,
   * `values`, `fields`, `meaning`, `provenance`, `evidence`, `producers`,
   * `consumers`, `references`, `related_structs`) and tolerates aliases. A
   * GoToRef callback may be supplied as `options.onGoToRef(ref, asset)`. Without
   * one, the root dispatches a bubbling `asset-goto-ref` CustomEvent.
   */

  const VERSION = "1.0.0";
  const TYPE_ALIASES = new Map([
    ["string", "string"], ["format", "string"], ["format_string", "string"],
    ["constant", "constant"], ["enum", "constant"], ["bitfield", "constant"],
    ["table", "table"], ["pointer_table", "table"], ["string_pool", "table"], ["dispatch_table", "table"],
    ["numeric_table", "numeric"], ["algorithm_table", "numeric"], ["curve", "numeric"], ["chart", "numeric"],
    ["bitmap", "bitmap"], ["glyph", "bitmap"], ["image", "bitmap"], ["font", "bitmap"],
    ["frame_animation", "animation"], ["animation", "animation"],
    ["font_bank", "font"], ["external_font_bank", "font"],
    ["protocol", "protocol"], ["frame", "protocol"], ["packet", "protocol"], ["uuid", "protocol"],
    ["bytes", "hex"], ["blob", "hex"], ["hex", "hex"], ["unknown", "hex"],
  ]);

  const PRINTF_RE = /%[-+ #0']*(?:\d+|\*)?(?:\.(?:\d+|\*))?(?:hh|h|ll|l|j|z|t|L)?[diuoxXfFeEgGaAcspn%]/g;
  const FORMAT_TYPES = {
    d: "signed decimal", i: "signed decimal", u: "unsigned decimal", o: "octal",
    x: "hexadecimal", X: "hexadecimal", f: "floating point", F: "floating point",
    e: "scientific notation", E: "scientific notation", g: "compact floating point",
    G: "compact floating point", a: "hexadecimal float", A: "hexadecimal float",
    c: "character", s: "string", p: "pointer", n: "written byte count", "%": "literal percent",
  };

  const asArray = value => value == null ? [] : Array.isArray(value) ? value : [value];
  const text = value => value == null ? "" : String(value);
  const html = value => text(value).replace(/[&<>"']/g, char => ({"&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;"})[char]);
  const clamp = (value, low, high) => Math.max(low, Math.min(high, value));

  function bytesOf(value) {
    if (value == null) return [];
    if (value instanceof Uint8Array) return [...value];
    if (ArrayBuffer.isView(value)) return [...new Uint8Array(value.buffer, value.byteOffset, value.byteLength)];
    if (Array.isArray(value)) return value.map(item => Number(item) & 0xff);
    if (typeof value === "string") {
      const compact = value.trim();
      if (/^(?:0x)?[0-9a-f\s,:_-]+$/i.test(compact)) {
        return (compact.match(/[0-9a-f]{2}/gi) || []).map(pair => parseInt(pair, 16));
      }
      return [...new TextEncoder().encode(value)];
    }
    return [];
  }

  function numberOf(value) {
    if (value == null || value === "") return null;
    if (typeof value === "number") return value;
    if (typeof value === "bigint") return Number(value);
    const parsed = Number(text(value).replace(/_/g, ""));
    return Number.isFinite(parsed) ? parsed : null;
  }

  function hexNumber(value, width = 0) {
    const numeric = numberOf(value);
    if (numeric == null) return text(value) || "—";
    const negative = numeric < 0;
    const digits = Math.abs(Math.trunc(numeric)).toString(16).padStart(width, "0");
    return `${negative ? "-" : ""}0x${digits}`;
  }

  function titleCase(value) {
    return text(value).replace(/[_-]+/g, " ").replace(/\b\w/g, char => char.toUpperCase());
  }

  function normalizeRef(item, role = "reference") {
    if (typeof item === "string") return {label: item, token: item, role};
    const ref = item || {};
    const token = ref.token || ref.address || ref.symbol || ref.name || ref.id || ref.cid || "";
    return {
      ...ref,
      role: ref.role || role,
      token,
      label: ref.label || ref.display_name || ref.name || ref.symbol || ref.cid || ref.address || token || "Unknown reference",
      note: ref.meaning || ref.reason || ref.usage || ref.detail || ref.description || "",
    };
  }

  function normalizeAsset(input) {
    const asset = input || {};
    const evidence = typeof asset.evidence === "object" && asset.evidence !== null
      ? asset.evidence : {rationale: asset.evidence || asset.rationale || ""};
    const confidence = text(asset.confidence || evidence.confidence || "unknown").toLowerCase();
    return {
      ...asset,
      id: asset.id || asset.address || asset.name || asset.symbol || "asset",
      name: asset.display_name || asset.name || asset.symbol || asset.id || "Recovered asset",
      address: asset.address || asset.va || asset.location || "",
      meaning: asset.meaning || asset.purpose || asset.description || asset.summary || "",
      confidence,
      evidence: {...evidence, confidence},
      bytes: bytesOf(asset.bytes ?? asset.data ?? asset.raw_bytes ?? asset.payload),
      provenance: asArray(asset.provenance || asset.origins || asset.sources),
      producers: asArray(asset.producers || asset.writers || asset.generated_by).map(item => normalizeRef(item, "producer")),
      consumers: asArray(asset.consumers || asset.readers || asset.used_by || asset.usages).map(item => normalizeRef(item, "consumer")),
      references: asArray(asset.references || asset.refs || asset.related_symbols).map(item => normalizeRef(item, "reference")),
      related_structs: asArray(asset.related_structs || asset.structures || asset.structs).map(item => normalizeRef(item, "structure")),
      interpretations: asArray(asset.interpretations || asset.decoded_references || asset.semantic_notes),
    };
  }

  function detectKind(raw) {
    const asset = raw || {};
    const declared = text(asset.asset_type || asset.kind || asset.type || asset.viewer || asset.visualization).toLowerCase();
    if (TYPE_ALIASES.has(declared)) return TYPE_ALIASES.get(declared);
    if (declared.includes("font")) return "font";
    if (declared.includes("string_pool")) return "table";
    if (declared.includes("string") || typeof asset.text === "string" || typeof asset.string === "string") return "string";
    if (declared.includes("enum") || declared.includes("constant") || asset.enum_members || asset.flags || asset.bitfield) return "constant";
    if (asset.width && asset.height && (asset.pixels || asset.bytes || asset.data)) return "bitmap";
    if (asset.uuid || asset.protocol || asArray(asset.packet_fields).length || asArray(asset.frame_fields).length) return "protocol";
    if (asArray(asset.table_rows).length) {
      const tabularOnly = /pointer|dispatch|string.pool|schema|layout/.test(declared);
      return asArray(asset.values).length && !tabularOnly ? "numeric" : "table";
    }
    if (asArray(asset.values).length || asArray(asset.series).length || asArray(asset.rows).length) return "numeric";
    return "hex";
  }

  function contextCoverage(asset) {
    const checks = [
      Boolean(asset.meaning), asset.provenance.length > 0,
      Boolean(asset.evidence.rationale || asset.evidence.claims || asset.evidence.sources),
      asset.confidence !== "unknown", asset.producers.length > 0,
      asset.consumers.length > 0, asset.related_structs.length > 0,
      asset.interpretations.length > 0 || asset.references.some(ref => ref.note),
    ];
    return {score: checks.filter(Boolean).length, total: checks.length};
  }

  function badge(label, tone = "neutral") {
    return `<span class="av-badge av-${html(tone)}">${html(label)}</span>`;
  }

  function empty(message) {
    return `<div class="av-empty"><span aria-hidden="true">◇</span><p>${html(message)}</p></div>`;
  }

  function formatStringParts(value) {
    const input = text(value);
    const parts = [];
    let offset = 0;
    for (const match of input.matchAll(PRINTF_RE)) {
      if (match.index > offset) parts.push({kind: "text", value: input.slice(offset, match.index)});
      const specifier = match[0];
      parts.push({kind: "token", value: specifier, meaning: FORMAT_TYPES[specifier.at(-1)] || "format argument"});
      offset = match.index + specifier.length;
    }
    if (offset < input.length) parts.push({kind: "text", value: input.slice(offset)});
    return parts;
  }

  function renderString(asset) {
    let value = asset.text ?? asset.string ?? asset.decoded ?? (typeof asset.data === "string" ? asset.data : "");
    if (!value && asset.bytes.length) {
      const end = asset.bytes.indexOf(0);
      const raw = new Uint8Array(end < 0 ? asset.bytes : asset.bytes.slice(0, end));
      try { value = new TextDecoder(asset.encoding || "utf-8", {fatal: false}).decode(raw); }
      catch (_error) { value = new TextDecoder("utf-8", {fatal: false}).decode(raw); }
    }
    value = text(value);
    const parts = formatStringParts(value);
    const tokens = parts.filter(part => part.kind === "token");
    const rendered = parts.map(part => part.kind === "token"
      ? `<mark class="av-format-token" title="${html(part.meaning)}">${html(part.value)}</mark>`
      : html(part.value).replace(/\n/g, '<span class="av-control" title="newline">↵</span>\n').replace(/\t/g, '<span class="av-control" title="tab">⇥</span>'));
    return `<section class="av-visual av-string-view" aria-label="Decoded string">
      <div class="av-string-meta"><span>${html(asset.encoding || "UTF-8")}</span><span>${value.length.toLocaleString()} characters</span><span>${tokens.length} format argument${tokens.length === 1 ? "" : "s"}</span></div>
      <pre class="av-string-value" tabindex="0"><span class="av-quote">“</span>${rendered.join("")}<span class="av-quote">”</span></pre>
      ${tokens.length ? `<ol class="av-token-key">${tokens.map((token, index) => `<li><b>${index + 1}</b><code>${html(token.value)}</code><span>${html(token.meaning)}</span></li>`).join("")}</ol>` : ""}
    </section>`;
  }

  function constantMembers(asset) {
    const source = asset.enum_members || asset.members || asset.constants || [];
    if (Array.isArray(source)) return source.map((item, index) => typeof item === "object" ? item : {name: text(item), value: index});
    return Object.entries(source).map(([name, value]) => ({name, value}));
  }

  function flagMembers(asset, fallback) {
    const source = asset.flags || asset.bitfield;
    if (!source) return asset.kind === "bitfield" ? fallback : [];
    if (Array.isArray(source)) return source;
    return Object.entries(source).map(([name, value]) => ({name, value}));
  }

  function renderConstant(asset) {
    const value = numberOf(asset.value ?? asset.constant_value ?? 0);
    const members = constantMembers(asset);
    const flags = flagMembers(asset, members);
    const isBitfield = flags.length > 0;
    const listing = (isBitfield ? flags : members).map(item => {
      const member = typeof item === "object" ? item : {name: text(item)};
      const itemValue = numberOf(member.value ?? member.mask ?? 0);
      const active = value != null && itemValue != null && (isBitfield ? itemValue !== 0 && (value & itemValue) === itemValue : value === itemValue);
      return `<li class="${active ? "av-active" : ""}"><span class="av-bit-state" aria-label="${active ? "set" : "not set"}">${active ? "✓" : "·"}</span><code>${html(hexNumber(itemValue))}</code><strong>${html(member.name || member.label || "unnamed")}</strong><span>${html(member.meaning || member.description || "")}</span></li>`;
    }).join("");
    const bits = value == null ? "—" : (value >>> 0).toString(2).padStart(Math.max(8, Math.ceil((value.toString(2).length || 1) / 8) * 8), "0").replace(/(.{4})(?=.)/g, "$1 ");
    return `<section class="av-visual av-constant-view" aria-label="Decoded constant">
      <div class="av-number-hero"><div><span>Hexadecimal</span><strong>${html(hexNumber(value))}</strong></div><div><span>Decimal</span><strong>${value == null ? "—" : value.toLocaleString()}</strong></div><div class="av-binary"><span>Binary</span><strong>${html(bits)}</strong></div></div>
      ${listing ? `<div class="av-subheading"><span>${isBitfield ? "Decoded flags" : "Enumeration members"}</span><small>${members.length || flags.length} known</small></div><ol class="av-constant-list">${listing}</ol>` : empty("No enum members or bit definitions were recovered.")}
    </section>`;
  }

  function numericSeries(asset) {
    const raw = asset.values || asset.series || asset.rows || asset.data || [];
    if (Array.isArray(raw) && raw.every(value => typeof value === "number" || typeof value === "string")) {
      return [{name: asset.unit || "value", values: raw.map(numberOf).filter(value => value != null)}];
    }
    if (Array.isArray(raw) && raw.length && raw.every(row => Array.isArray(row))) {
      const width = raw.reduce((result, row) => Math.max(result, row.length), 0);
      return Array.from({length: width}, (_, column) => ({
        name: asArray(asset.columns)[column] || `column ${column + 1}`,
        values: raw.map(row => numberOf(row[column])).filter(value => value != null),
      })).filter(series => series.values.length);
    }
    if (Array.isArray(raw) && raw.length && raw.every(row => row && typeof row === "object" && !Array.isArray(row)) && !raw.some(row => row.values || row.data)) {
      const keys = [...new Set(raw.flatMap(row => Object.keys(row)))].filter(key => raw.some(row => numberOf(row[key]) != null));
      return keys.map(key => ({name: key, values: raw.map(row => numberOf(row[key])).filter(value => value != null)}));
    }
    if (Array.isArray(raw)) return raw.map((series, index) => ({
      name: series.name || series.label || `series ${index + 1}`,
      values: asArray(series.values || series.data || series).map(numberOf).filter(value => value != null),
    })).filter(series => series.values.length);
    return Object.entries(raw).map(([name, values]) => ({name, values: asArray(values).map(numberOf).filter(value => value != null)}));
  }

  function chartSvg(series) {
    const all = series.flatMap(item => item.values);
    if (!all.length) return empty("No numeric samples available.");
    const width = 720, height = 220, left = 48, top = 16, right = 16, bottom = 34;
    const min = all.reduce((result, value) => Math.min(result, value), Infinity);
    const max = all.reduce((result, value) => Math.max(result, value), -Infinity);
    const span = max - min || 1;
    const longest = Math.max(...series.map(item => item.values.length), 1);
    const palette = ["var(--accent)", "var(--violet)", "var(--orange)", "#68b8ff"];
    const lines = series.map((item, seriesIndex) => {
      const points = item.values.map((value, index) => {
        const x = left + (index / Math.max(longest - 1, 1)) * (width - left - right);
        const y = top + (1 - (value - min) / span) * (height - top - bottom);
        return `${x.toFixed(2)},${y.toFixed(2)}`;
      }).join(" ");
      return `<polyline points="${points}" vector-effect="non-scaling-stroke" style="--series:${palette[seriesIndex % palette.length]}"/>`;
    }).join("");
    const grid = [0, .25, .5, .75, 1].map(step => {
      const y = top + step * (height - top - bottom);
      const label = max - step * span;
      return `<line x1="${left}" y1="${y}" x2="${width - right}" y2="${y}"/><text x="${left - 8}" y="${y + 3}">${html(Number(label.toPrecision(4)))}</text>`;
    }).join("");
    return `<svg class="av-chart" viewBox="0 0 ${width} ${height}" role="img" aria-label="Numeric table chart"><g class="av-chart-grid">${grid}</g>${lines}</svg>`;
  }

  function renderNumeric(asset) {
    const series = numericSeries(asset);
    const length = Math.max(0, ...series.map(item => item.values.length));
    const tableLength = Math.min(length, 256);
    const tableRows = Array.from({length: tableLength}, (_, index) => `<tr><th scope="row">${index}</th>${series.map(item => `<td>${item.values[index] == null ? "—" : html(item.values[index])}</td>`).join("")}</tr>`).join("");
    return `<section class="av-visual av-numeric-view" aria-label="Numeric table visualization">
      <div class="av-chart-wrap">${chartSvg(series)}</div>
      <div class="av-legend">${series.map((item, index) => `<span style="--series-index:${index}"><i></i>${html(item.name)}</span>`).join("")}</div>
      <div class="av-table-wrap" tabindex="0"><table><thead><tr><th>Index</th>${series.map(item => `<th>${html(item.name)}</th>`).join("")}</tr></thead><tbody>${tableRows}</tbody></table></div>
      ${length > tableLength ? `<p class="av-truncation">Showing the first ${tableLength} of ${length.toLocaleString()} samples in the table. The chart uses the complete series.</p>` : ""}
    </section>`;
  }

  function cellValue(value) {
    if (value == null) return "—";
    if (typeof value === "object") return value.name || value.display_name || value.address || JSON.stringify(value);
    return String(value);
  }

  function renderTable(asset) {
    const rows = asArray(asset.table_rows || asset.rows || asset.entries);
    if (!rows.length) return `<section class="av-visual av-data-table">${empty("No decoded table rows are attached to this object.")}</section>`;
    const objects = rows.map((row, index) => row && typeof row === "object" && !Array.isArray(row) ? row : {index, value: row});
    const columns = [...new Set(objects.flatMap(row => Object.keys(row)))].filter(key => !["source", "evidence", "viewer_route"].includes(key)).slice(0, 9);
    const shown = objects.slice(0, 1024);
    return `<section class="av-visual av-data-table" aria-label="Decoded data table">
      <div class="av-subheading"><span>Decoded rows</span><small>${objects.length.toLocaleString()} total</small></div>
      <div class="av-table-wrap" tabindex="0"><table><thead><tr>${columns.map(column => `<th>${html(titleCase(column))}</th>`).join("")}</tr></thead><tbody>${shown.map(row => `<tr>${columns.map(column => `<td>${html(cellValue(row[column]))}</td>`).join("")}</tr>`).join("")}</tbody></table></div>
      ${objects.length > shown.length ? `<p class="av-truncation">Showing the first ${shown.length.toLocaleString()} of ${objects.length.toLocaleString()} rows.</p>` : ""}
    </section>`;
  }

  function bitmapPixels(asset) {
    const width = Math.max(1, Number(asset.width || asset.columns || 8));
    const height = Math.max(1, Number(asset.height || asset.rows_count || Math.ceil((asset.bytes.length * 8) / width) || 1));
    if (Array.isArray(asset.pixels) && asset.pixels.length) return {width, height, pixels: asset.pixels.flat().map(Number)};
    const bpp = Math.max(1, Number(asset.bits_per_pixel || asset.bpp || 1));
    const mask = (1 << Math.min(bpp, 8)) - 1;
    const pixels = [];
    const lowFirst = /low nibble (?:then|first)/i.test(text(asset.pixel_order || asset.pixelOrder));
    asset.bytes.forEach(byte => {
      if (bpp === 8) pixels.push(byte);
      else {
        const shifts = [];
        for (let shift = 8 - bpp; shift >= 0; shift -= bpp) shifts.push(shift);
        if (lowFirst) shifts.reverse();
        shifts.forEach(shift => pixels.push((byte >> shift) & mask));
      }
    });
    return {width, height, pixels};
  }

  function renderBitmap(asset) {
    const {width, height, pixels} = bitmapPixels(asset);
    const max = (1 << Math.min(Number(asset.bits_per_pixel || asset.bpp || 1), 8)) - 1;
    const shown = Math.min(width * height, pixels.length, 16384);
    const cells = Array.from({length: shown}, (_, index) => {
      const value = pixels[index] || 0;
      if (!value) return "";
      return `<rect x="${index % width}" y="${Math.floor(index / width)}" width="1" height="1" opacity="${clamp(value / max, 0, 1).toFixed(3)}"/>`;
    }).join("");
    return `<section class="av-visual av-bitmap-view" aria-label="Bitmap or glyph visualization">
      <div class="av-bitmap-stage"><svg viewBox="0 0 ${width} ${height}" role="img" aria-label="${width} by ${height} pixel recovered bitmap" shape-rendering="crispEdges"><rect class="av-pixel-bg" width="${width}" height="${height}"/>${cells}</svg></div>
      <div class="av-bitmap-stats"><span><b>${width} × ${height}</b> pixels</span><span><b>${html(asset.bits_per_pixel || asset.bpp || 1)}</b> bits/pixel</span><span><b>${asset.bytes.length.toLocaleString()}</b> render bytes</span>${asset.glyph || asset.character ? `<span>Glyph <b>${html(asset.glyph || asset.character)}</b></span>` : ""}</div>
      ${shown < width * height ? `<p class="av-truncation">Preview limited to ${shown.toLocaleString()} decoded pixels.</p>` : ""}
    </section>`;
  }

  function bitmapSvg(asset, bytes = asset.bytes, label = "Recovered bitmap") {
    const decoded = bitmapPixels({...asset, bytes});
    const {width, height, pixels} = decoded;
    const max = (1 << Math.min(Number(asset.bits_per_pixel || asset.bpp || 1), 8)) - 1;
    const cells = pixels.slice(0, Math.min(width * height, 16384)).map((value, index) => value
      ? `<rect x="${index % width}" y="${Math.floor(index / width)}" width="1" height="1" opacity="${clamp(value / max, 0, 1).toFixed(3)}"/>`
      : "").join("");
    return `<svg viewBox="0 0 ${width} ${height}" role="img" aria-label="${html(label)}" shape-rendering="crispEdges"><rect class="av-pixel-bg" width="${width}" height="${height}"/>${cells}</svg>`;
  }

  function renderAnimation(asset) {
    const width = Math.max(1, Number(asset.width || 1));
    const height = Math.max(1, Number(asset.height || 1));
    const stride = Math.max(1, Number(asset.frame_stride_bytes || Math.ceil(width * height * Number(asset.bits_per_pixel || 4) / 8)));
    const available = Math.floor(asset.bytes.length / stride);
    const count = Math.max(1, Math.min(Number(asset.frame_count || available || 1), available || 1));
    const frame = asset.bytes.slice(0, stride);
    return `<section class="av-visual av-bitmap-view av-animation-view" aria-label="Frame animation visualization" data-av-animation data-frame-stride="${stride}" data-frame-count="${count}">
      <div class="av-bitmap-stage" data-av-frame-stage>${bitmapSvg(asset, frame, `Animation frame 1 of ${count}`)}</div>
      <div class="av-animation-controls"><button type="button" data-av-frame-step="-1" aria-label="Previous frame">←</button><input type="range" min="0" max="${count - 1}" value="0" step="1" data-av-frame-slider aria-label="Animation frame"><button type="button" data-av-frame-step="1" aria-label="Next frame">→</button><output data-av-frame-label>Frame <b>1</b> / ${count}</output></div>
      <div class="av-bitmap-stats"><span><b>${width} × ${height}</b> pixels</span><span><b>${html(asset.bits_per_pixel || asset.bpp || 4)}</b> bits/pixel</span><span><b>${stride.toLocaleString()}</b> bytes/frame</span><span><b>${count}</b> frames</span></div>
    </section>`;
  }

  function glyphSvg(entry, payload, asset) {
    const width = Number(entry.width_pixels || entry.width || 1);
    const height = Number(entry.height_pixels || asset.height || 1);
    const offset = Number(entry.payload_offset || 0);
    const size = Number(entry.size_bytes || Math.ceil(width / 2) * height);
    const glyph = {...asset, width, height, bytes: payload.slice(offset, offset + size), bits_per_pixel: 4};
    const decoded = bitmapPixels(glyph);
    const max = 15;
    const cells = decoded.pixels.slice(0, width * height).map((value, index) => value ? `<rect x="${index % width}" y="${Math.floor(index / width)}" width="1" height="1" opacity="${clamp(value / max, 0, 1).toFixed(3)}"/>` : "").join("");
    return `<svg viewBox="0 0 ${width} ${height}" role="img" aria-label="Glyph ${html(entry.codepoint || entry.character || entry.index)}" shape-rendering="crispEdges"><rect class="av-pixel-bg" width="${width}" height="${height}"/>${cells}</svg>`;
  }

  function renderFont(asset) {
    const entries = asArray(asset.entries);
    const payload = bytesOf(asset.glyph_payload_hex || asset.glyph_payload);
    if (!entries.length || !payload.length) return `<section class="av-visual av-font-view">${empty("This font bank is external or its glyph payload is not embedded in the CPUAPP image.")}${entries.length ? renderTable({...asset, table_rows: entries}) : ""}</section>`;
    const shown = entries.slice(0, 450);
    return `<section class="av-visual av-font-view" aria-label="Recovered font glyph table">
      <div class="av-font-summary"><span><b>${entries.length.toLocaleString()}</b> glyphs</span><span><b>${payload.length.toLocaleString()} B</b> pixel payload</span><span><b>${html(asset.encoding || "packed 4-bit")}</b></span></div>
      <div class="av-glyph-grid">${shown.map(entry => `<article class="av-glyph-card" title="${html(entry.codepoint || "")}">${glyphSvg(entry, payload, asset)}<footer><strong>${html(entry.character || "·")}</strong><code>${html(entry.codepoint || `#${entry.index}`)}</code><small>${html(entry.width_pixels)}×${html(entry.height_pixels)}</small></footer></article>`).join("")}</div>
      ${entries.length > shown.length ? `<p class="av-truncation">Showing ${shown.length} of ${entries.length.toLocaleString()} glyphs.</p>` : ""}
    </section>`;
  }

  function frameFields(asset) {
    const source = asset.packet_fields || asset.frame_fields || asset.fields || [];
    const rows = Array.isArray(source) ? source : Object.entries(source).map(([name, field]) => ({name, ...(typeof field === "object" ? field : {length: field})}));
    return rows.map((field, index) => {
      const rawOffset = field.offset ?? field.start ?? 0;
      const rawLength = field.length ?? field.size ?? 1;
      const numericOffset = Number(rawOffset);
      const numericLength = Number(rawLength);
      return {
        ...field,
        name: field.name || field.label || `field_${index}`,
        offset: Number.isFinite(numericOffset) ? numericOffset : null,
        length: Number.isFinite(numericLength) ? numericLength : null,
        offsetLabel: text(rawOffset),
        lengthLabel: text(rawLength),
        meaning: field.meaning || field.description || field.decoded || "",
      };
    });
  }

  function renderProtocol(asset) {
    const fields = frameFields(asset);
    const uuid = text(asset.uuid || asset.service_uuid || asset.characteristic_uuid);
    const owner = index => fields.find(field => field.offset != null && field.length != null && index >= field.offset && index < field.offset + field.length);
    const byteStrip = asset.bytes.map((byte, index) => {
      const field = owner(index);
      return `<span class="av-frame-byte" style="--field:${field ? fields.indexOf(field) : -1}" title="byte ${index}${field ? ` · ${html(field.name)}` : ""}">${byte.toString(16).padStart(2, "0")}</span>`;
    }).join("");
    const fieldList = fields.map((field, index) => {
      const range = field.offset != null && field.length != null ? `${field.offset}..${field.offset + field.length - 1}` : `${field.offsetLabel} · ${field.lengthLabel} B`;
      return `<li style="--field:${index}"><i></i><code>${html(range)}</code><strong>${html(field.name)}</strong><span>${html(field.meaning)}</span></li>`;
    }).join("");
    return `<section class="av-visual av-protocol-view" aria-label="Protocol asset visualization">
      ${uuid ? `<div class="av-uuid"><span>UUID</span><strong>${html(uuid)}</strong><button class="av-copy" type="button" data-av-copy="${html(uuid)}" aria-label="Copy UUID">Copy</button></div>` : ""}
      ${asset.protocol ? `<div class="av-protocol-name"><span>Protocol</span><strong>${html(asset.protocol)}</strong>${asset.direction ? `<em>${html(asset.direction)}</em>` : ""}</div>` : ""}
      ${asset.bytes.length ? `<div class="av-frame-strip" role="img" aria-label="${asset.bytes.length} byte protocol frame">${byteStrip}</div>` : empty("No example frame bytes were recovered.")}
      ${fieldList ? `<ol class="av-frame-fields">${fieldList}</ol>` : ""}
    </section>`;
  }

  function renderHex(asset) {
    const bytes = asset.bytes;
    if (!bytes.length) return `<section class="av-visual av-hex-view">${empty("No raw bytes are attached to this asset.")}</section>`;
    const base = numberOf(asset.address) || 0;
    const rows = [];
    for (let offset = 0; offset < Math.min(bytes.length, 4096); offset += 16) {
      const slice = bytes.slice(offset, offset + 16);
      rows.push(`<div class="av-hex-row"><span class="av-hex-address">${hexNumber(base + offset, 8)}</span><code>${slice.map(byte => byte.toString(16).padStart(2, "0")).join(" ")}</code><span class="av-ascii">${slice.map(byte => byte >= 32 && byte < 127 ? html(String.fromCharCode(byte)) : "·").join("")}</span></div>`);
    }
    return `<section class="av-visual av-hex-view" aria-label="Hexadecimal data"><div class="av-hex-header"><span>Address</span><span>00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f</span><span>ASCII</span></div><div class="av-hex-scroll" tabindex="0">${rows.join("")}</div>${bytes.length > 4096 ? `<p class="av-truncation">Preview limited to 4,096 of ${bytes.length.toLocaleString()} bytes.</p>` : ""}</section>`;
  }

  function refGroup(title, items, icon) {
    if (!items.length) return "";
    return `<section class="av-ref-group"><header><span>${html(icon)}</span><h4>${html(title)}</h4><b>${items.length}</b></header><div>${items.map(ref => `<button class="av-ref" type="button" data-av-ref="${html(ref.token)}" data-av-role="${html(ref.role)}"><span><strong>${html(ref.label)}</strong>${ref.address && ref.address !== ref.label ? `<code>${html(ref.address)}</code>` : ""}</span>${ref.note ? `<small>${html(ref.note)}</small>` : ""}<i aria-hidden="true">→</i></button>`).join("")}</div></section>`;
  }

  function provenanceItem(item, index) {
    if (typeof item === "string") return `<li><i></i><div><strong>Evidence source ${index + 1}</strong><p>${html(item)}</p></div></li>`;
    const source = item || {};
    const name = source.name || source.source || source.method || source.kind || `Evidence source ${index + 1}`;
    const location = source.path || source.file || source.location || source.address || source.origin || "";
    const note = source.note || source.detail || source.description || source.evidence || "";
    return `<li><i></i><div><strong>${html(name)}</strong>${location ? `<code>${html(location)}</code>` : ""}${note ? `<p>${html(note)}</p>` : ""}</div></li>`;
  }

  function renderContext(asset) {
    const evidence = asset.evidence;
    const claims = asArray(evidence.claims || evidence.observations || asset.observations);
    const confidence = asset.confidence;
    const coverage = contextCoverage(asset);
    const confidenceTone = confidence === "high" || confidence === "verified" ? "good" : confidence === "medium" ? "warn" : confidence === "low" ? "bad" : "neutral";
    const interpretationRows = asset.interpretations.map(item => {
      if (typeof item === "string") return `<li><span>↳</span><p>${html(item)}</p></li>`;
      return `<li><span>↳</span><p><strong>${html(item.label || item.reference || item.name || "Interpretation")}</strong>${html(item.meaning || item.description || item.reason || "")}</p></li>`;
    }).join("");
    return `<div class="av-context-grid">
      <section class="av-context-card av-meaning"><span class="av-kicker">Recovered meaning</span><h3>What this data represents</h3>${asset.meaning ? `<p>${html(asset.meaning)}</p>` : `<p class="av-context-missing">Semantic description pending corroboration.</p>`}${interpretationRows ? `<ul class="av-interpretations">${interpretationRows}</ul>` : ""}</section>
      <section class="av-context-card av-evidence"><div class="av-evidence-head"><div><span class="av-kicker">Evidence quality</span><h3>${html(titleCase(confidence))} confidence</h3></div>${badge(`${coverage.score}/${coverage.total} context`, coverage.score >= 6 ? "good" : coverage.score >= 3 ? "warn" : "bad")}</div><div class="av-confidence av-${confidenceTone}"><i style="--confidence:${confidence === "high" || confidence === "verified" ? 100 : confidence === "medium" ? 66 : confidence === "low" ? 34 : 12}%"></i></div>${evidence.rationale || evidence.summary ? `<p>${html(evidence.rationale || evidence.summary)}</p>` : ""}${claims.length ? `<ul class="av-claims">${claims.map(claim => `<li>${html(typeof claim === "string" ? claim : claim.text || claim.claim || claim.description)}</li>`).join("")}</ul>` : ""}</section>
      <section class="av-context-card av-provenance"><span class="av-kicker">Provenance</span><h3>How it was recovered</h3>${asset.provenance.length ? `<ol>${asset.provenance.map(provenanceItem).join("")}</ol>` : `<p class="av-context-missing">No provenance chain attached.</p>`}</section>
      <section class="av-context-card av-relations"><span class="av-kicker">Data flow</span><h3>Connected code & types</h3>${refGroup("Produced by", asset.producers, "↗")}${refGroup("Consumed by", asset.consumers, "↘")}${refGroup("Decoded references", asset.references, "⌁")}${refGroup("Related structures", asset.related_structs, "{ }") || (!asset.producers.length && !asset.consumers.length && !asset.references.length && !asset.related_structs.length ? `<p class="av-context-missing">No relationships attached.</p>` : "")}</section>
    </div>`;
  }

  function renderHeader(asset, kind) {
    const tags = asArray(asset.tags || asset.labels);
    const confidenceTone = asset.confidence === "high" || asset.confidence === "verified" ? "good" : asset.confidence === "medium" ? "warn" : asset.confidence === "low" ? "bad" : "neutral";
    const sizeLabel = asset.bytes.length ? `${asset.bytes.length.toLocaleString()} B` : typeof asset.size === "number" ? `${asset.size.toLocaleString()} B` : asset.size || "—";
    return `<header class="av-header"><div class="av-title-block"><nav aria-label="Asset location"><span>${html((asset.core || "app").toUpperCase())}</span><b>›</b><span>DATA</span>${asset.address ? `<b>›</b><code>${html(asset.address)}</code>` : ""}</nav><div class="av-badges">${badge(titleCase(kind), "type")}${asset.confidence ? badge(`${titleCase(asset.confidence)} confidence`, confidenceTone) : ""}${tags.map(tag => badge(tag)).join("")}</div><h2>${html(asset.name)}</h2>${asset.symbol && asset.symbol !== asset.name ? `<p><code>${html(asset.symbol)}</code></p>` : ""}</div><div class="av-header-metrics"><div><span>Size</span><strong>${html(sizeLabel)}</strong></div><div><span>Identity</span><strong>${html(asset.id)}</strong></div></div></header>`;
  }

  function viewerFor(kind, asset) {
    if (kind === "string") return renderString(asset);
    if (kind === "constant") return renderConstant(asset);
    if (kind === "numeric") return renderNumeric(asset);
    if (kind === "table") return renderTable(asset);
    if (kind === "font") return renderFont(asset);
    if (kind === "bitmap") return renderBitmap(asset);
    if (kind === "animation") return renderAnimation(asset);
    if (kind === "protocol") return renderProtocol(asset);
    return renderHex(asset);
  }

  function bindInteractions(root, asset, options) {
    const animation = root.querySelector("[data-av-animation]");
    if (animation) {
      const slider = animation.querySelector("[data-av-frame-slider]");
      const stage = animation.querySelector("[data-av-frame-stage]");
      const label = animation.querySelector("[data-av-frame-label]");
      const stride = Number(animation.dataset.frameStride);
      const count = Number(animation.dataset.frameCount);
      const showFrame = value => {
        const index = clamp(Number(value) || 0, 0, count - 1);
        slider.value = index;
        stage.innerHTML = bitmapSvg(asset, asset.bytes.slice(index * stride, (index + 1) * stride), `Animation frame ${index + 1} of ${count}`);
        label.innerHTML = `Frame <b>${index + 1}</b> / ${count}`;
      };
      slider.addEventListener("input", () => showFrame(slider.value));
      animation.querySelectorAll("[data-av-frame-step]").forEach(button => button.addEventListener("click", () => showFrame(Number(slider.value) + Number(button.dataset.avFrameStep))));
    }
    root.addEventListener("click", event => {
      const copy = event.target.closest("[data-av-copy]");
      if (copy) {
        const copied = navigator.clipboard?.writeText(copy.dataset.avCopy);
        copied?.then(() => {
          const original = copy.textContent;
          copy.textContent = "Copied";
          setTimeout(() => { copy.textContent = original; }, 1200);
        });
        return;
      }
      const button = event.target.closest("[data-av-ref]");
      if (!button) return;
      const all = [...asset.producers, ...asset.consumers, ...asset.references, ...asset.related_structs];
      const ref = all.find(item => item.token === button.dataset.avRef && item.role === button.dataset.avRole) || normalizeRef(button.dataset.avRef);
      if (typeof options.onGoToRef === "function") options.onGoToRef(ref, asset);
      else root.dispatchEvent(new CustomEvent("asset-goto-ref", {bubbles: true, detail: {ref, asset}}));
    });
  }

  function create(rawAsset, options = {}) {
    const asset = normalizeAsset(rawAsset);
    const kind = detectKind(asset);
    const root = document.createElement("article");
    root.className = `av-root av-kind-${kind}`;
    root.dataset.assetId = asset.id;
    root.dataset.assetKind = kind;
    root.innerHTML = `${renderHeader(asset, kind)}<div class="av-viewer-shell">${viewerFor(kind, asset)}</div>${renderContext(asset)}`;
    bindInteractions(root, asset, options);
    return root;
  }

  function render(container, asset, options = {}) {
    if (!(container instanceof Element)) throw new TypeError("AssetViewers.render requires a DOM container");
    const rendered = create(asset, options);
    container.replaceChildren(rendered);
    return rendered;
  }

  function renderCollection(container, assets, options = {}) {
    if (!(container instanceof Element)) throw new TypeError("AssetViewers.renderCollection requires a DOM container");
    const grid = document.createElement("div");
    grid.className = "av-collection";
    asArray(assets).forEach(asset => grid.append(create(asset, options)));
    container.replaceChildren(grid);
    return grid;
  }

  global.AssetViewers = Object.freeze({VERSION, create, render, renderCollection, detectKind, normalizeAsset, contextCoverage});
})(window);
