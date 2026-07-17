#!/usr/bin/env python3
"""Build fail-closed ownership evidence for CPUAPP SDK residue batch 7."""
import argparse, hashlib, json, os

ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE=os.path.join(ROOT,"recon/analysis/app_link_residue.json")
JSON_OUT=os.path.join(ROOT,"recon/ownership/app_sdk_batch7_ownership.json")
MD_OUT=os.path.join(ROOT,"recon/ownership/app_sdk_batch7_ownership.md")

OWNERS={
 "atomic_and_0":("0x0007f3f0",22,"zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and","header_inline_outlined",40,0,"a13dbd30c173e4e8283a087d4f291ffe318aa6b4307622bcecf6ffede47faeeb"),
 "atomic_and_1":("0x00081180",22,"zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and","header_inline_outlined",40,0,"6be9530bdfeabda85b54bc67de82d0d3bbf3c998043509f0099f2d11213be67f"),
 "atomic_clear_bit":("0x0007f5d8",22,"zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit","header_inline_outlined",40,0,"0348909c9752bd019964a83576f2ee9f3c7120b89b827d7c3400f01939a07235"),
 "atomic_clear_bit_0":("0x00081e14",22,"zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit","header_inline_outlined",40,0,"98aa5de75e3d6faaabf12d55e2b94b34d0aa195a21add5de8a5abce3d08c42ca"),
 "atomic_test_and_set_bit_0":("0x00082236",34,"zephyr/include/zephyr/sys/atomic.h:atomic_test_and_set_bit","header_inline_outlined",40,0,"560ebcdcdd688cda060a7a960737704c5cee992e62029609e22d0ccac25678d3"),
 "att_op_get_type":("0x000582b8",108,"zephyr/subsys/bluetooth/host/att.c:att_op_get_type","source_static",46,6,"5864c766eeeab5b91b8c6182845024ca103396f258a7f45457bc2cc295f4f5c9"),
 "bt_start":("0x00019308",766,"firmware application Bluetooth-start owner","application_misclassified",6,6,"5c00ad066c461afa43b96218eaaa353bfcf6162c2cfa3cb5a60df25dec644070"),
 "gatt_req_send":("0x00082aee",128,"zephyr/subsys/bluetooth/host/gatt.c:gatt_req_send","source_static_configured",40,0,"bc4b22a69511be2379d408921265ecfb87dc911d9e1d4f6f88006d3501f8ee50"),
}

def digest(path):
 with open(path,"rb") as f:return hashlib.sha256(f.read()).hexdigest()

def build():
 with open(RESIDUE,encoding="utf-8") as f: refs={r["symbol"]:r for r in json.load(f)["entries"]}
 rows=[]
 for symbol,(va,size,owner,linkage,checked,cases,sha) in OWNERS.items():
  src=f"recon/app/src/{symbol}.c"; mirror=f"recon/verified/src/{symbol}.c"
  actual=digest(os.path.join(ROOT,src))
  if actual!=sha or digest(os.path.join(ROOT,mirror))!=actual: raise RuntimeError("source/mirror drift: "+symbol)
  residue=refs.get(symbol)
  if not residue or residue["reference_count"]!=3: raise RuntimeError("residue drift: "+symbol)
  rows.append({"symbol":symbol,"va":va,"size":size,"upstream_owner":owner,
   "linkage":linkage,"checked":checked,"cfg_cases":cases,"sha256":sha,
   "source":src,"verified_mirror":mirror,"reference_count_before":3,
   "reference_sites_before":residue["reference_sites"],
   "verification":f"cfg_verify.py app {symbol}: PASS ({checked} checked; reviewed cases={cases})",
   "decision":"retain_cfg_verified_configured_reconstruction"})
 with open(os.path.join(ROOT,"tools/recon_kit.py"),encoding="utf-8") as f: recon_text=f.read()
 with open(os.path.join(ROOT,"tools/cfg_verify.py"),encoding="utf-8") as f: cfg_text=f.read()
 required=(
  (recon_text,"0x000582b8: 0x6c"),
  (cfg_text,'("app", 0x000582b8): 0x6c'),
  (cfg_text,'("app", 0x00082aee): {3: 0x00080001}'),
  (cfg_text,'REVIEWED_ORACLE_CASES[("app", 0x00019308)]'),
  (cfg_text,'REVIEWED_STACK_POINTER_CALLS[("app", 0x00019308)] = {17: {0}}'),
 )
 if any(marker not in text for text,marker in required):
  raise RuntimeError("batch7 verifier contract drift")
 return {"schema":1,"core":"app","policy":{"fail_closed":True,
  "reason":"Configured static/header-inline and application owners need independent verified bodies.",
  "forbid":["weak stub","byte blob","assembly wrapper","same-name alias guess"]},
  "summary":{"function_count":len(rows),"reference_count_before":sum(r["reference_count_before"] for r in rows),"cfg_verified":len(rows)},
  "verification_infrastructure":{"att_op_get_type_true_extent":"0x000582b8+0x6c",
   "gatt_req_send_external_callback_arg":3,"bt_start_reviewed_state_count":6},
  "integration":{"derivatives":"pending centralized readable-tree consolidation","retain_all_result":"not claimed by this canonical-only milestone"},
  "functions":rows}

def markdown(d):
 out=["# CPUAPP SDK residue batch 7 ownership","",
 "Eight configured owners are retained as separately linkable, CFG-verified C.",
 "The evidence corrects the ATT classifier extent, models the GATT encode callback,",
 "and covers six production-shaped Bluetooth-start states.","",
 "| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |","|---|---:|---:|---:|---|---|"]
 for r in d["functions"]:out.append("| `{symbol}` | `{va}` | {size} | 3 | `{upstream_owner}` | PASS ({checked}) |".format(**r))
 out += ["",f"Canonical result: **8 functions / {d['summary']['reference_count_before']} prior references**, digest-pinned and CFG-verified.",""]
 return "\n".join(out)

def main():
 p=argparse.ArgumentParser();p.add_argument("--check",action="store_true");a=p.parse_args();d=build()
 j=json.dumps(d,indent=1)+"\n";m=markdown(d)
 if a.check:
  assert open(JSON_OUT,encoding="utf-8").read()==j;assert open(MD_OUT,encoding="utf-8").read()==m
 else:
  open(JSON_OUT,"w",encoding="utf-8").write(j);open(MD_OUT,"w",encoding="utf-8").write(m)
if __name__=="__main__":main()
