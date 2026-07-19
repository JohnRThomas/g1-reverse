"use strict";

const $ = (selector, root = document) => root.querySelector(selector);
const $$ = (selector, root = document) => [...root.querySelectorAll(selector)];
const state = {
  view: "functions",
  core: "app",
  filter: "all",
  structScope: "all",
  structFeature: "all",
  assetFamily: "all",
  query: "",
  page: 1,
  limit: 60,
  applicationOnly: true,
  total: 0,
  items: [],
  current: null,
  meta: null,
  request: 0,
};

const els = {
  gotoForm: $("#goto-form"),
  gotoInput: $("#goto-input"),
  symbolSearch: $("#symbol-search"),
  applicationOnly: $("#application-only"),
  ownershipToggle: $("#ownership-toggle"),
  functionFilters: $("#function-filters"),
  structFilters: $("#struct-filters"),
  assetFilters: $("#asset-filters"),
  inventoryTitle: $("#inventory-title"),
  symbolList: $("#symbol-list"),
  symbolCount: $("#symbol-count"),
  loadMore: $("#load-more"),
  catalogStatus: $("#catalog-status"),
  emptyState: $("#empty-state"),
  detailLayout: $("#detail-layout"),
  structLayout: $("#struct-layout"),
  assetLayout: $("#asset-layout"),
  assetViewer: $("#asset-viewer"),
  structCid: $("#struct-cid"),
  structBadges: $("#struct-badges"),
  structTitle: $("#struct-title"),
  structPurpose: $("#struct-purpose"),
  structMetrics: $("#struct-metrics"),
  fieldList: $("#field-list"),
  structMembers: $("#struct-members"),
  structInfo: $("#struct-info"),
  layoutProof: $("#layout-proof"),
  symbolTitle: $("#symbol-title"),
  rawName: $("#raw-name"),
  titleBadges: $("#title-badges"),
  metricStrip: $("#metric-strip"),
  crumbCore: $("#crumb-core"),
  crumbAddress: $("#crumb-address"),
  sourcePath: $("#source-path"),
  sourceKind: $("#source-kind"),
  codeLines: $("#code-lines"),
  codeScroll: $("#code-scroll"),
  noSource: $("#no-source"),
  referenceGroups: $("#reference-groups"),
  usageList: $("#usage-list"),
  infoList: $("#info-list"),
  renameButton: $("#rename-button"),
  renameDialog: $("#rename-dialog"),
  renameForm: $("#rename-form"),
  renameIdentity: $("#rename-identity"),
  renameName: $("#rename-name"),
  renameEvidence: $("#rename-evidence"),
  renameError: $("#rename-error"),
  coordinationNote: $("#coordination-note"),
  shortcutDialog: $("#shortcut-dialog"),
  toastRegion: $("#toast-region"),
};

function escapeHtml(value) {
  return String(value ?? "").replace(/[&<>"']/g, char => ({"&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;"})[char]);
}

function debounce(fn, delay = 180) {
  let timer;
  return (...args) => {
    clearTimeout(timer);
    timer = setTimeout(() => fn(...args), delay);
  };
}

async function api(path, options = {}) {
  const response = await fetch(path, {
    ...options,
    headers: {"Content-Type": "application/json", ...(options.headers || {})},
  });
  const payload = await response.json().catch(() => ({}));
  if (!response.ok) throw new Error(payload.error || `${response.status} ${response.statusText}`);
  return payload;
}

function toast(message, error = false) {
  const item = document.createElement("div");
  item.className = `toast${error ? " error" : ""}`;
  item.textContent = message;
  els.toastRegion.append(item);
  setTimeout(() => {
    item.classList.add("out");
    setTimeout(() => item.remove(), 240);
  }, 2600);
}

function formatBytes(size) {
  if (size == null) return "—";
  return size >= 1024 ? `${(size / 1024).toFixed(size >= 10240 ? 0 : 1)} KB` : `${size} B`;
}

function routeFor(core, token, line = 0) {
  return `#/${core}/${encodeURIComponent(token)}${line ? `?line=${line}` : ""}`;
}

function structRouteFor(token) {
  return `#/struct/${encodeURIComponent(token)}`;
}

function assetRouteFor(token) {
  return `#/asset/${encodeURIComponent(token)}`;
}

function parseRoute() {
  const structMatch = location.hash.match(/^#\/struct\/([^?]+)$/);
  if (structMatch) return {view: "structs", token: decodeURIComponent(structMatch[1])};
  const assetMatch = location.hash.match(/^#\/asset\/([^?]+)$/);
  if (assetMatch) return {view: "assets", token: decodeURIComponent(assetMatch[1])};
  const match = location.hash.match(/^#\/(app|net)\/([^?]+)(?:\?line=(\d+))?$/);
  return match ? {view: "functions", core: match[1], token: decodeURIComponent(match[2]), line: Number(match[3] || 0)} : null;
}

function navigateAsset(token) {
  const route = assetRouteFor(token);
  if (location.hash === route) loadAssetDetail(token);
  else location.hash = route;
}

function navigateStruct(token) {
  const route = structRouteFor(token);
  if (location.hash === route) loadStructDetail(token);
  else location.hash = route;
}

function navigate(core, token, line = 0) {
  const route = routeFor(core, token, line);
  if (location.hash === route) loadDetail(core, token, line);
  else location.hash = route;
}

function navigateFirst() {
  if (!state.items[0]) return;
  if (state.view === "structs") navigateStruct(state.items[0].cid);
  else if (state.view === "assets") navigateAsset(state.items[0].id);
  else navigate(state.core, state.items[0].address);
}

function updateCoreUI() {
  $$(".core-switch button").forEach(button => button.classList.toggle("active", button.dataset.core === state.core));
  $$('.core-switch button[data-core="net"]').forEach(button => button.disabled = state.view !== "functions");
  $$(".view-switch button").forEach(button => button.classList.toggle("active", button.dataset.view === state.view));
  els.crumbCore.textContent = state.core === "app" ? "CPUAPP" : "CPUNET";
}

function updateViewUI() {
  const structures = state.view === "structs";
  const assets = state.view === "assets";
  els.inventoryTitle.textContent = structures ? "Structures" : assets ? "Built-in data" : "Symbols";
  els.symbolSearch.placeholder = structures ? "Filter structures" : assets ? "Filter data and assets" : "Filter symbols";
  els.symbolList.setAttribute("aria-label", structures ? "Structures" : assets ? "Data assets" : "Functions");
  els.gotoInput.placeholder = structures ? "Go to struct, CID, symbol, or address…" : assets ? "Go to asset, symbol, or 0x address…" : "Go to symbol, FUN_*, or 0x address…";
  els.ownershipToggle.hidden = structures || assets;
  els.functionFilters.hidden = structures || assets;
  els.structFilters.hidden = !structures;
  els.assetFilters.hidden = !assets;
  els.detailLayout.hidden = structures || assets || !state.current;
  els.structLayout.hidden = !structures || !state.current;
  els.assetLayout.hidden = !assets || !state.current;
  updateCoreUI();
}

async function loadMeta() {
  try {
    state.meta = await api("/api/meta");
    if (state.view === "structs") {
      const info = state.meta.structs;
      els.catalogStatus.textContent = `${info.total.toLocaleString()} verified layouts · ${info.clusters_covered}/${info.clusters_target} clusters`;
      return;
    }
    if (state.view === "assets") {
      const info = state.meta.assets || {};
      els.catalogStatus.textContent = `${(info.assets || 0).toLocaleString()} evidence-gated assets · ${(info.reference_semantics || 0).toLocaleString()} decoded references`;
      return;
    }
    const info = state.meta.cores[state.core];
    const ownershipStatus = state.applicationOnly
      ? `${info.application.toLocaleString()} G1 · ${info.library.toLocaleString()} libraries hidden`
      : `${info.total.toLocaleString()} functions · libraries visible`;
    els.catalogStatus.textContent = state.meta.coordination_active ? `Live sweep · ${ownershipStatus}` : ownershipStatus;
    els.coordinationNote.hidden = !state.meta.coordination_active;
  } catch (error) {
    els.catalogStatus.textContent = "Catalog read delayed";
  }
}

async function loadSymbols(append = false) {
  const request = ++state.request;
  if (!append) {
    state.page = 1;
    state.items = [];
    els.symbolList.setAttribute("aria-busy", "true");
  }
  const structures = state.view === "structs";
  const assets = state.view === "assets";
  const params = new URLSearchParams(structures ? {
    scope: state.structScope, feature: state.structFeature, q: state.query,
    page: String(state.page), limit: String(state.limit),
  } : assets ? {
    family: state.assetFamily, q: state.query,
    page: String(state.page), limit: String(state.limit),
  } : {
    core: state.core, state: state.filter, q: state.query,
    page: String(state.page), limit: String(state.limit),
    application_only: state.applicationOnly ? "1" : "0",
  });
  try {
    const result = await api(`${structures ? "/api/structs" : assets ? "/api/assets" : "/api/symbols"}?${params}`);
    if (request !== state.request) return;
    state.total = result.total;
    state.items = append ? [...state.items, ...result.items] : result.items;
    renderSymbolList();
  } catch (error) {
    if (request === state.request) toast(`Could not read symbols: ${error.message}`, true);
  } finally {
    els.symbolList.removeAttribute("aria-busy");
  }
}

function renderSymbolList() {
  els.symbolCount.textContent = state.total.toLocaleString();
  els.symbolList.innerHTML = "";
  const fragment = document.createDocumentFragment();
  state.items.forEach((item, index) => {
    if (state.view === "structs") {
      const button = document.createElement("button");
      button.type = "button";
      button.className = `symbol-item struct-item${item.is_library ? " library" : ""}`;
      button.style.setProperty("--i", index % state.limit);
      button.setAttribute("role", "option");
      const active = state.current?.cid === item.cid;
      button.classList.toggle("active", active);
      button.setAttribute("aria-selected", String(active));
      button.innerHTML = `<span class="symbol-glyph">{ }</span><span class="symbol-copy"><strong>${escapeHtml(item.struct_name)}</strong><span>${escapeHtml(item.cid)} · ${item.n_members} use${item.n_members === 1 ? "" : "s"}</span></span><span class="symbol-size">${item.is_union ? "union" : formatBytes(item.size_lower_bound)}</span>`;
      button.addEventListener("click", () => navigateStruct(item.cid));
      fragment.append(button);
      return;
    }
    if (state.view === "assets") {
      const button = document.createElement("button");
      button.type = "button";
      button.className = `symbol-item asset-item family-${escapeHtml(item.family)}`;
      button.style.setProperty("--i", index % state.limit);
      button.setAttribute("role", "option");
      const active = state.current?.id === item.id;
      button.classList.toggle("active", active);
      button.setAttribute("aria-selected", String(active));
      const glyphs = {visual: "◫", fonts: "Ag", strings: "Aa", constants: "#", tables: "⌁", protocols: "⇄", data: "◇"};
      button.innerHTML = `<span class="symbol-glyph">${glyphs[item.family] || "◇"}</span><span class="symbol-copy"><strong>${escapeHtml(item.name)}</strong><span>${escapeHtml(item.address)} · ${escapeHtml(item.subsystem)}</span></span><span class="asset-confidence ${escapeHtml(item.confidence)}">${escapeHtml(item.confidence)}</span>`;
      button.addEventListener("click", () => navigateAsset(item.id));
      fragment.append(button);
      return;
    }
    const button = document.createElement("button");
    button.type = "button";
    button.className = "symbol-item";
    button.classList.toggle("library", item.ownership === "library");
    button.style.setProperty("--i", index % state.limit);
    button.dataset.address = item.address;
    button.setAttribute("role", "option");
    const active = state.current?.address === item.address;
    button.classList.toggle("active", active);
    button.setAttribute("aria-selected", String(active));
    button.innerHTML = `
      <span class="symbol-glyph">ƒ</span>
      <span class="symbol-copy"><strong>${item.edited ? '<i class="edit-dot"></i>' : ""}${escapeHtml(item.display_name)}</strong><span>${escapeHtml(item.address)}</span></span>
      <span class="symbol-size">${escapeHtml(formatBytes(item.size))}</span>`;
    button.addEventListener("click", () => navigate(state.core, item.address));
    fragment.append(button);
  });
  els.symbolList.append(fragment);
  els.loadMore.hidden = state.items.length >= state.total;
}

async function goToReference(token) {
  token = token.trim();
  if (!token) return;
  try {
    if (state.view === "assets") {
      try { await loadAssetDetail(token, true); return; }
      catch (_) { /* Fall through to symbols and structures. */ }
      try { await loadDetail("app", token, 0, true); return; }
      catch (_) { await loadStructDetail(token, true); }
    } else if (state.view === "structs") {
      try { await loadStructDetail(token, true); return; }
      catch (_) { /* Fall through so GoToRef still reaches a function. */ }
      await loadDetail(state.core, token, 0, true);
    } else {
      try { await loadDetail(state.core, token, 0, true); return; }
      catch (_) { /* Struct names and CIDs share the global GoToRef surface. */ }
      await loadStructDetail(token, true);
    }
  } catch (error) {
    toast(`Reference not found: ${token}`, true);
    els.gotoInput.select();
  }
}

async function loadAssetDetail(token, updateRoute = false) {
  const detail = await api(`/api/asset/${encodeURIComponent(token)}`);
  const changedView = state.view !== "assets";
  state.core = "app";
  state.view = "assets";
  state.current = detail;
  if (changedView) {
    state.query = "";
    els.symbolSearch.value = "";
  }
  els.emptyState.hidden = true;
  updateViewUI();
  AssetViewers.render(els.assetViewer, detail, {onGoToRef: ref => {
    if (ref.cid || ref.role === "structure") navigateStruct(ref.cid || ref.token);
    else if (ref.role === "asset" || ref.id || String(ref.token).startsWith("data:") || String(ref.token).startsWith("app:string:")) navigateAsset(ref.id || ref.token);
    else navigate("app", ref.address || ref.token);
  }});
  if (changedView) await loadSymbols();
  renderSymbolList();
  if (updateRoute) history.pushState(null, "", assetRouteFor(detail.id));
  document.title = `${detail.name} — Trace`;
  return detail;
}

async function loadDetail(core, token, line = 0, updateRoute = false) {
  const detail = await api(`/api/symbol/${core}/${encodeURIComponent(token)}`);
  const changedView = state.view !== "functions";
  state.core = core;
  state.view = "functions";
  state.current = detail;
  if (changedView) {
    state.query = "";
    els.symbolSearch.value = "";
  }
  updateCoreUI();
  updateViewUI();
  renderDetail(detail, line);
  if (changedView) await loadSymbols();
  renderSymbolList();
  if (updateRoute) history.pushState(null, "", routeFor(core, detail.address, line));
  document.title = `${detail.display_name} — Trace`;
  return detail;
}

async function loadStructDetail(token, updateRoute = false) {
  const detail = await api(`/api/struct/${encodeURIComponent(token)}`);
  const changedView = state.view !== "structs";
  state.core = "app";
  state.view = "structs";
  state.current = detail;
  if (changedView) {
    state.query = "";
    els.symbolSearch.value = "";
  }
  updateViewUI();
  renderStructDetail(detail);
  if (changedView) await loadSymbols();
  renderSymbolList();
  if (updateRoute) history.pushState(null, "", structRouteFor(detail.cid));
  document.title = `${detail.struct_name} — Trace`;
  return detail;
}

function renderStructDetail(item) {
  els.emptyState.hidden = true;
  els.detailLayout.hidden = true;
  els.structLayout.hidden = false;
  els.assetLayout.hidden = true;
  els.structCid.textContent = item.cid;
  els.structTitle.textContent = item.struct_name;
  els.structPurpose.textContent = item.purpose || "Recovered memory object";
  const badges = [
    [item.is_library ? "Library" : "G1 original", item.is_library ? "library" : "verified"],
    [item.verified ? "D1 + D2 verified" : "Review", item.verified ? "verified" : "unnamed"],
    [item.confidence || "unknown", item.confidence === "high" ? "verified" : item.confidence === "low" ? "unnamed" : "candidate"],
  ];
  if (item.library_verified) badges.push(["SDK header match", "verified"]);
  if (item.is_union) badges.push(["Union / overlap", "edited"]);
  if (item.is_array) badges.push(["Array", "candidate"]);
  els.structBadges.innerHTML = badges.map(([label, cls]) => `<span class="badge ${cls}">${escapeHtml(label)}</span>`).join("");
  const metrics = [[formatBytes(item.size_lower_bound), "Lower bound"], [item.fields.length, "Fields"], [item.members.length, "Usages"], [item.merged_cids?.length || 1, "Clusters"]];
  els.structMetrics.innerHTML = metrics.map(([value, label]) => `<span class="metric"><strong>${escapeHtml(value)}</strong><span>${label}</span></span>`).join("");
  els.layoutProof.textContent = item.verified ? "D1 access proof · D2 offsetof proof" : "Requires review";
  els.fieldList.innerHTML = item.fields.map((field, index) => `<article class="field-row" style="--i:${index}"><span class="field-offset">${escapeHtml(field.offset)}</span><span class="field-rail"><i></i></span><span class="field-type">${escapeHtml(field.type)}</span><strong>${escapeHtml(field.name)}</strong>${field.library_member ? `<small>SDK: ${escapeHtml(field.library_member)}</small>` : ""}${field.note ? `<p>${escapeHtml(field.note)}</p>` : ""}</article>`).join("") || '<p class="empty-group">No fields recorded</p>';
  els.structMembers.innerHTML = item.members.map(member => `<button class="member-card" type="button" data-member="${escapeHtml(member.address || member.entry)}" ${member.resolvable ? "" : "disabled"}><span><strong>${escapeHtml(member.display_name || member.func)}</strong><small>${escapeHtml(member.address || member.entry)}</small></span><span><code>${escapeHtml(member.base)}</code> →</span></button>`).join("") || '<p class="empty-group">No member functions recorded</p>';
  $$('[data-member]', els.structMembers).forEach(button => button.addEventListener("click", () => navigate("app", button.dataset.member)));
  const values = [
    ["Cluster identity", item.cid], ["Kind", item.kind], ["Ownership", item.is_library ? `Library · ${item.library_name || item.struct_name}` : "G1-original"],
    ["Library header", item.library_header || "Not a library layout"], ["Merged clusters", item.merged_cids?.join(", ") || item.cid],
    ["Verification", item.verified ? "Passed D1 field access + D2 compile-time offsets" : "Not verified"],
    ["Review note", item.review_note || "No review caveat"], ["Warnings", item.verify_warnings?.join("; ") || "None"], ["Errors", item.verify_errors?.join("; ") || "None"],
  ];
  els.structInfo.innerHTML = values.map(([key, value]) => `<div><dt>${escapeHtml(key)}</dt><dd>${escapeHtml(value)}</dd></div>`).join("");
}

function renderDetail(item, targetLine = 0) {
  els.emptyState.hidden = true;
  els.detailLayout.hidden = false;
  els.assetLayout.hidden = true;
  els.symbolTitle.textContent = item.display_name;
  els.rawName.textContent = item.raw_name;
  els.crumbAddress.textContent = item.goto_offset ? `${item.address} + 0x${item.goto_offset.toString(16)}` : item.address;
  els.sourcePath.textContent = item.source_path || (item.kind === "data" ? "Data reference" : "Ghidra fallback");
  els.sourceKind.textContent = item.source_kind.replaceAll("_", " ");
  els.renameButton.hidden = item.kind === "data";

  const badges = [];
  badges.push(item.kind === "data" ? ["Data", ""] : [item.human ? "Named" : "Unnamed", item.human ? "verified" : "unnamed"]);
  if (item.ownership === "library") badges.push(["Library", "library"]);
  else if (item.ownership === "g1_application_candidate") badges.push(["G1 candidate", "candidate"]);
  if (item.edited) badges.push(["User edit", "edited"]);
  if (item.is_thunk) badges.push(["Thunk", ""]);
  els.titleBadges.innerHTML = badges.map(([text, cls]) => `<span class="badge ${cls}">${text}</span>`).join("");

  const metrics = [
    [formatBytes(item.size), "Size"],
    [item.callers.length, "Callers"],
    [item.calls.length, "Callees"],
    [item.data_refs.length, "Data refs"],
  ];
  els.metricStrip.innerHTML = metrics.map(([value, label]) => `<span class="metric"><strong>${escapeHtml(value)}</strong><span>${label}</span></span>`).join("");

  renderSource(item, targetLine);
  renderReferences(item);
  renderUsages(item);
  renderInfo(item);
}

const KEYWORDS = new Set("auto break case char const continue default do double else enum extern float for goto if inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while bool true false NULL".split(" "));

function referenceLookup(item) {
  const map = new Map();
  const references = [...item.calls, ...item.data_refs];
  references.forEach(ref => {
    if (!ref.resolvable) return;
    [ref.address, ref.address.replace(/^0x0*/, "0x"), ref.display_name, ref.raw_name].filter(Boolean).forEach(token => map.set(String(token).toLowerCase(), ref.owner_address || ref.address));
  });
  return map;
}

function highlightLine(line, lookup) {
  const tokenPattern = /(\/\/.*$|\/\*.*?\*\/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|0x[0-9a-fA-F]+|FUN_[0-9a-fA-F]+|[A-Za-z_][A-Za-z0-9_]*|\b\d+(?:\.\d+)?\b)/g;
  let html = "";
  let cursor = 0;
  for (const match of line.matchAll(tokenPattern)) {
    html += escapeHtml(line.slice(cursor, match.index));
    const token = match[0];
    const target = lookup.get(token.toLowerCase());
    if (target) {
      html += `<button class="code-ref" data-goto="${escapeHtml(target)}">${escapeHtml(token)}</button>`;
    } else if (token.startsWith("//") || token.startsWith("/*")) {
      html += `<span class="tok-comment">${escapeHtml(token)}</span>`;
    } else if (token.startsWith('"') || token.startsWith("'")) {
      html += `<span class="tok-string">${escapeHtml(token)}</span>`;
    } else if (KEYWORDS.has(token)) {
      html += `<span class="tok-keyword">${escapeHtml(token)}</span>`;
    } else if (/^(0x|\d)/.test(token)) {
      html += `<span class="tok-number">${escapeHtml(token)}</span>`;
    } else {
      html += escapeHtml(token);
    }
    cursor = match.index + token.length;
  }
  return html + escapeHtml(line.slice(cursor));
}

function renderSource(item, targetLine) {
  els.codeLines.innerHTML = "";
  const source = item.source || "";
  els.noSource.hidden = Boolean(source);
  els.codeLines.hidden = !source;
  if (!source) return;
  const lookup = referenceLookup(item);
  const fragment = document.createDocumentFragment();
  source.split("\n").forEach((line, index) => {
    const li = document.createElement("li");
    li.dataset.line = String(index + 1);
    const code = document.createElement("code");
    code.innerHTML = highlightLine(line, lookup);
    li.append(code);
    fragment.append(li);
  });
  els.codeLines.append(fragment);
  $$('[data-goto]', els.codeLines).forEach(button => button.addEventListener("click", () => navigate(state.core, button.dataset.goto)));
  requestAnimationFrame(() => {
    const line = targetLine ? $(`li[data-line="${targetLine}"]`, els.codeLines) : null;
    if (line) {
      line.classList.add("target-line");
      line.scrollIntoView({block: "center", behavior: matchMedia("(prefers-reduced-motion: reduce)").matches ? "auto" : "smooth"});
    } else if (item.goto_offset) {
      els.codeScroll.scrollTop = Math.min(els.codeScroll.scrollHeight, item.goto_offset * 2);
    } else {
      els.codeScroll.scrollTop = 0;
    }
  });
}

function renderReferences(item) {
  const groups = [
    ["Callers", item.callers, "↑"],
    ["Callees", item.calls, "↘"],
    ["Data references", item.data_refs, "◇"],
  ];
  els.referenceGroups.innerHTML = groups.map(([title, refs, icon]) => `
    <section class="ref-group">
      <div class="ref-heading"><h3>${title}</h3><span>${refs.length}</span></div>
      ${refs.length ? refs.map(ref => `
        <button class="ref-item" type="button" data-ref="${escapeHtml(ref.owner_address || ref.address)}" ${ref.resolvable ? "" : "disabled"}>
          <span class="ref-kind ${ref.kind === "data" ? "data" : ""}">${icon}</span>
          <span class="ref-copy"><strong>${escapeHtml(ref.display_name)}</strong><small>${escapeHtml(ref.address)}${ref.offset ? ` + 0x${ref.offset.toString(16)}` : ""}</small></span>
          <span class="ref-arrow">→</span>
        </button>`).join("") : '<p class="empty-group">No references in the current graph</p>'}
    </section>`).join("") + (item.structs?.length ? `
    <section class="ref-group"><div class="ref-heading"><h3>Recovered structures</h3><span>${item.structs.length}</span></div>
      ${item.structs.map(row => `<button class="ref-item" type="button" data-struct-ref="${escapeHtml(row.cid)}"><span class="ref-kind data">{ }</span><span class="ref-copy"><strong>${escapeHtml(row.struct_name)}</strong><small>${escapeHtml(row.cid)} · ${row.n_members} usage${row.n_members === 1 ? "" : "s"}</small></span><span class="ref-arrow">→</span></button>`).join("")}
    </section>` : "") + (item.semantic_references?.length ? `
    <section class="ref-group semantic-group"><div class="ref-heading"><h3>Decoded meaning</h3><span>${item.semantic_references.length}</span></div>
      ${item.semantic_references.slice(0, 160).map(ref => `<button class="ref-item semantic-ref" type="button" data-semantic-ref="${escapeHtml(ref.asset?.id || ref.target?.address || "")}" data-semantic-kind="${ref.asset ? "asset" : "symbol"}"><span class="ref-kind data">⌁</span><span class="ref-copy"><strong>${escapeHtml(ref.target?.human_name || ref.target?.raw_name || ref.target?.address || ref.role)}</strong><small>${escapeHtml(ref.access_mode || "reference")} · ${escapeHtml(ref.meaning)}</small></span><span class="confidence-dot ${escapeHtml(ref.confidence)}"></span></button>`).join("")}
    </section>` : "");
  $$('[data-ref]', els.referenceGroups).forEach(button => button.addEventListener("click", () => navigate(state.core, button.dataset.ref)));
  $$('[data-struct-ref]', els.referenceGroups).forEach(button => button.addEventListener("click", () => navigateStruct(button.dataset.structRef)));
  $$('[data-semantic-ref]', els.referenceGroups).forEach(button => button.addEventListener("click", () => button.dataset.semanticKind === "asset" ? navigateAsset(button.dataset.semanticRef) : navigate(state.core, button.dataset.semanticRef)));
}

function renderUsages(item) {
  if (!item.usages.length) {
    els.usageList.innerHTML = '<p class="usage-none">No incoming source usages were found. Address-taken or table-based references may still appear under References.</p>';
    return;
  }
  els.usageList.innerHTML = item.usages.map(usage => `
    <article class="usage-item">
      <button class="usage-head" type="button" data-usage="${escapeHtml(usage.address)}"><strong>${escapeHtml(usage.display_name)}</strong><span>${escapeHtml(usage.address)} →</span></button>
      ${usage.hits.length ? usage.hits.map(hit => `<button class="usage-hit" type="button" data-usage="${escapeHtml(usage.address)}" data-line="${hit.line}"><b>${hit.line}</b><code>${escapeHtml(hit.preview)}</code></button>`).join("") : '<p class="empty-group">Graph edge found; textual call may be indirect or renamed.</p>'}
    </article>`).join("");
  $$('[data-usage]', els.usageList).forEach(button => button.addEventListener("click", () => navigate(state.core, button.dataset.usage, Number(button.dataset.line || 0))));
}

function renderInfo(item) {
  const values = [
    ["Core", item.core === "app" ? "CPUAPP · Cortex-M33" : "CPUNET · Cortex-M33"],
    ["Entry address", item.address],
    ["Raw identity", item.raw_name],
    ["Canonical name", item.canonical_name],
    ["Ownership", item.kind === "data" ? "Data reference" : item.ownership === "library" ? "Library / SDK" : item.ownership === "g1_application" ? "G1 application" : "G1 application candidate"],
    ["Ownership evidence", item.ownership_evidence?.join(", ") || item.ownership_status || "Not classified as library"],
    ["Signature", item.signature || "Unknown / data"],
    ["Calling convention", item.calling_convention || "Unknown"],
    ["Name evidence", item.name_source || "Not yet recorded"],
    ["Aliases", item.aliases?.join(", ") || "None"],
    ["Source", item.source_path || item.source_kind],
    ["Stack references", item.stack_refs?.join(", ") || "None recorded"],
    ["Override evidence", item.override?.evidence || "No interactive override"],
  ];
  els.infoList.innerHTML = values.map(([key, value]) => `<div><dt>${escapeHtml(key)}</dt><dd>${escapeHtml(value)}</dd></div>`).join("");
}

function openRename() {
  const item = state.current;
  if (!item || item.kind === "data") return;
  els.renameIdentity.textContent = `${item.raw_name} · ${item.address}`;
  els.renameName.value = item.display_name.startsWith("FUN_") ? "" : item.display_name;
  els.renameEvidence.value = item.override?.evidence?.replace(/^\[symbol-browser[^\]]*\]\s*/, "") || "";
  els.renameError.textContent = "";
  els.renameDialog.showModal();
  requestAnimationFrame(() => els.renameName.select());
}

async function saveRename(event) {
  event.preventDefault();
  if (!state.current) return;
  if (!els.renameName.checkValidity()) {
    els.renameError.textContent = "Use a valid C identifier: letters, digits, and underscores; no leading digit.";
    els.renameName.focus();
    return;
  }
  const button = $("#save-rename");
  button.disabled = true;
  button.textContent = "Saving…";
  try {
    await api("/api/rename", {
      method: "POST",
      body: JSON.stringify({core: state.core, address: state.current.address, name: els.renameName.value, evidence: els.renameEvidence.value}),
    });
    els.renameDialog.close();
    toast(`Canonical rename applied: ${els.renameName.value}`);
    await Promise.all([loadSymbols(), loadMeta()]);
    await loadDetail(state.core, state.current.address, 0, true);
  } catch (error) {
    els.renameError.textContent = error.message;
  } finally {
    button.disabled = false;
    button.innerHTML = '<span aria-hidden="true">✓</span> Apply rename';
  }
}

function bindEvents() {
  els.gotoForm.addEventListener("submit", event => { event.preventDefault(); goToReference(els.gotoInput.value); });
  els.symbolSearch.addEventListener("input", debounce(() => { state.query = els.symbolSearch.value; loadSymbols(); }));
  els.applicationOnly.addEventListener("change", async () => {
    state.applicationOnly = els.applicationOnly.checked;
    await Promise.all([loadSymbols(), loadMeta()]);
    if (state.applicationOnly && state.current?.ownership === "library" && state.items[0]) {
      navigate(state.core, state.items[0].address);
    }
  });
  els.loadMore.addEventListener("click", () => { state.page += 1; loadSymbols(true); });
  els.renameButton.addEventListener("click", openRename);
  els.renameForm.addEventListener("submit", saveRename);
  $("#close-rename").addEventListener("click", () => els.renameDialog.close());
  $("#cancel-rename").addEventListener("click", () => els.renameDialog.close());
  $("#copy-raw").addEventListener("click", () => { if (state.current) navigator.clipboard.writeText(state.current.raw_name).then(() => toast("Raw identity copied")); });
  $("#copy-source").addEventListener("click", () => { if (state.current?.source) navigator.clipboard.writeText(state.current.source).then(() => toast("Source copied")); });
  $("#shortcuts-button").addEventListener("click", () => els.shortcutDialog.showModal());

  $$(".view-switch button").forEach(button => button.addEventListener("click", async () => {
    if (state.view === button.dataset.view) return;
    state.view = button.dataset.view;
    if (state.view !== "functions") state.core = "app";
    state.current = null;
    state.query = "";
    els.symbolSearch.value = "";
    updateViewUI();
    await Promise.all([loadSymbols(), loadMeta()]);
    navigateFirst();
  }));

  $$(".core-switch button").forEach(button => button.addEventListener("click", async () => {
    state.core = button.dataset.core;
    state.current = null;
    updateCoreUI();
    await Promise.all([loadSymbols(), loadMeta()]);
    if (state.items[0]) navigate(state.core, state.items[0].address);
  }));
  $$("#function-filters button").forEach(button => button.addEventListener("click", () => {
    state.filter = button.dataset.state;
    $$("#function-filters button").forEach(tab => {
      const active = tab === button;
      tab.classList.toggle("active", active);
      tab.setAttribute("aria-selected", String(active));
    });
    loadSymbols();
  }));
  $$(".struct-scope button").forEach(button => button.addEventListener("click", () => {
    state.structScope = button.dataset.scope;
    $$(".struct-scope button").forEach(tab => { const active = tab === button; tab.classList.toggle("active", active); tab.setAttribute("aria-selected", String(active)); });
    loadSymbols();
  }));
  $$("#struct-filters [data-feature]").forEach(button => button.addEventListener("click", () => {
    state.structFeature = button.dataset.feature;
    $$("#struct-filters [data-feature]").forEach(chip => chip.classList.toggle("active", chip === button));
    loadSymbols();
  }));
  $$("#asset-filters [data-family]").forEach(button => button.addEventListener("click", () => {
    state.assetFamily = button.dataset.family;
    $$("#asset-filters [data-family]").forEach(chip => chip.classList.toggle("active", chip === button));
    loadSymbols();
  }));
  $$(".inspector-tabs button").forEach(button => button.addEventListener("click", () => {
    $$(".inspector-tabs button").forEach(tab => {
      const active = tab === button;
      tab.classList.toggle("active", active);
      tab.setAttribute("aria-selected", String(active));
    });
    $$(".inspector-panel").forEach(panel => panel.classList.toggle("active", panel.id === `panel-${button.dataset.panel}`));
  }));

  window.addEventListener("hashchange", async () => {
    const route = parseRoute();
    if (!route) return;
    try {
      if (route.view === "structs") await loadStructDetail(route.token);
      else if (route.view === "assets") await loadAssetDetail(route.token);
      else await loadDetail(route.core, route.token, route.line);
    }
    catch (error) { toast(error.message, true); }
  });

  document.addEventListener("keydown", event => {
    if (event.metaKey || event.ctrlKey || event.altKey) return;
    const typing = /INPUT|TEXTAREA/.test(document.activeElement?.tagName);
    if (event.key === "g" && !typing) { event.preventDefault(); els.gotoInput.focus(); els.gotoInput.select(); }
    if (event.key === "/" && !typing) { event.preventDefault(); els.symbolSearch.focus(); }
    if (event.key === "r" && !typing && state.current) { event.preventDefault(); openRename(); }
  });
}

async function init() {
  bindEvents();
  const route = parseRoute();
  if (route) {
    state.view = route.view;
    state.core = route.core || "app";
  }
  updateViewUI();
  await Promise.all([loadMeta(), loadSymbols()]);
  if (route) {
    try {
      if (route.view === "structs") await loadStructDetail(route.token);
      else if (route.view === "assets") await loadAssetDetail(route.token);
      else await loadDetail(route.core, route.token, route.line);
    }
    catch (error) { toast(error.message, true); }
  } else if (state.items[0]) {
    navigateFirst();
  }
  setInterval(loadMeta, 7000);
}

init();
