"use strict";

const $ = (selector, root = document) => root.querySelector(selector);
const $$ = (selector, root = document) => [...root.querySelectorAll(selector)];
const state = {
  core: "app",
  filter: "all",
  query: "",
  page: 1,
  limit: 60,
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
  symbolList: $("#symbol-list"),
  symbolCount: $("#symbol-count"),
  loadMore: $("#load-more"),
  catalogStatus: $("#catalog-status"),
  emptyState: $("#empty-state"),
  detailLayout: $("#detail-layout"),
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

function parseRoute() {
  const match = location.hash.match(/^#\/(app|net)\/([^?]+)(?:\?line=(\d+))?$/);
  return match ? {core: match[1], token: decodeURIComponent(match[2]), line: Number(match[3] || 0)} : null;
}

function navigate(core, token, line = 0) {
  const route = routeFor(core, token, line);
  if (location.hash === route) loadDetail(core, token, line);
  else location.hash = route;
}

function updateCoreUI() {
  $$(".core-switch button").forEach(button => button.classList.toggle("active", button.dataset.core === state.core));
  els.crumbCore.textContent = state.core === "app" ? "CPUAPP" : "CPUNET";
}

async function loadMeta() {
  try {
    state.meta = await api("/api/meta");
    const info = state.meta.cores[state.core];
    els.catalogStatus.textContent = state.meta.coordination_active
      ? `Live sweep · ${info.unnamed} unnamed`
      : `Catalogs live · ${info.unnamed} unnamed`;
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
  const params = new URLSearchParams({
    core: state.core,
    state: state.filter,
    q: state.query,
    page: String(state.page),
    limit: String(state.limit),
  });
  try {
    const result = await api(`/api/symbols?${params}`);
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
    const button = document.createElement("button");
    button.type = "button";
    button.className = "symbol-item";
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
    await loadDetail(state.core, token, 0, true);
  } catch (error) {
    toast(`Reference not found: ${token}`, true);
    els.gotoInput.select();
  }
}

async function loadDetail(core, token, line = 0, updateRoute = false) {
  const detail = await api(`/api/symbol/${core}/${encodeURIComponent(token)}`);
  state.core = core;
  state.current = detail;
  updateCoreUI();
  renderDetail(detail, line);
  renderSymbolList();
  if (updateRoute) history.pushState(null, "", routeFor(core, detail.address, line));
  document.title = `${detail.display_name} — Trace`;
  return detail;
}

function renderDetail(item, targetLine = 0) {
  els.emptyState.hidden = true;
  els.detailLayout.hidden = false;
  els.symbolTitle.textContent = item.display_name;
  els.rawName.textContent = item.raw_name;
  els.crumbAddress.textContent = item.goto_offset ? `${item.address} + 0x${item.goto_offset.toString(16)}` : item.address;
  els.sourcePath.textContent = item.source_path || (item.kind === "data" ? "Data reference" : "Ghidra fallback");
  els.sourceKind.textContent = item.source_kind.replaceAll("_", " ");
  els.renameButton.hidden = item.kind === "data";

  const badges = [];
  badges.push(item.kind === "data" ? ["Data", ""] : [item.human ? "Named" : "Unnamed", item.human ? "verified" : "unnamed"]);
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
    </section>`).join("");
  $$('[data-ref]', els.referenceGroups).forEach(button => button.addEventListener("click", () => navigate(state.core, button.dataset.ref)));
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
  els.loadMore.addEventListener("click", () => { state.page += 1; loadSymbols(true); });
  els.renameButton.addEventListener("click", openRename);
  els.renameForm.addEventListener("submit", saveRename);
  $("#close-rename").addEventListener("click", () => els.renameDialog.close());
  $("#cancel-rename").addEventListener("click", () => els.renameDialog.close());
  $("#copy-raw").addEventListener("click", () => { if (state.current) navigator.clipboard.writeText(state.current.raw_name).then(() => toast("Raw identity copied")); });
  $("#copy-source").addEventListener("click", () => { if (state.current?.source) navigator.clipboard.writeText(state.current.source).then(() => toast("Source copied")); });
  $("#shortcuts-button").addEventListener("click", () => els.shortcutDialog.showModal());

  $$(".core-switch button").forEach(button => button.addEventListener("click", async () => {
    state.core = button.dataset.core;
    state.current = null;
    updateCoreUI();
    await Promise.all([loadSymbols(), loadMeta()]);
    if (state.items[0]) navigate(state.core, state.items[0].address);
  }));
  $$(".filter-tabs button").forEach(button => button.addEventListener("click", () => {
    state.filter = button.dataset.state;
    $$(".filter-tabs button").forEach(tab => {
      const active = tab === button;
      tab.classList.toggle("active", active);
      tab.setAttribute("aria-selected", String(active));
    });
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
    try { await loadDetail(route.core, route.token, route.line); }
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
  if (route) state.core = route.core;
  updateCoreUI();
  await Promise.all([loadMeta(), loadSymbols()]);
  if (route) {
    try { await loadDetail(route.core, route.token, route.line); }
    catch (error) { toast(error.message, true); }
  } else if (state.items[0]) {
    navigate(state.core, state.items[0].address);
  }
  setInterval(loadMeta, 7000);
}

init();
