# Analysis catalogs (Ghidra-derived) — backup

These are the function catalogs + call/data-ref graphs the tooling depends on
(`classified.json`, `app_funcs.json`, `net_funcs.json`, `refgraph_{app,net}.json`,
`ref_db.json`). They normally live in the ephemeral scratchpad and were LOST once
when temp storage was cleaned. Backed up here (gzipped) so they survive.

REGENERATE from the committed Ghidra project (`ghidra/EvenDecomp.rep`, programs
`app_update.bin` / `netcore_image.bin`) with JDK21:
  JAVA_HOME=/opt/homebrew/opt/openjdk@21/... \
  ~/ghidra_11.3.2_PUBLIC/support/analyzeHeadless ghidra EvenDecomp \
    -process app_update.bin -noanalysis -scriptPath tools \
    -postScript ghidra_export.py <SCR>/app_funcs.json
  (repeat for netcore_image.bin -> net_funcs.json; ghidra_refgraph.py -> refgraph_*.json)
  tools/ref_extract.py ~/ncs251/refapp/build/zephyr/zephyr.elf $(find ~/ncs251/refapp/build -name '*.obj')  -> ref_db.json
  tools/classify.py  -> classified.json
To USE: gunzip -k recon/catalogs/*.json.gz and copy into the scratchpad SCR path.
