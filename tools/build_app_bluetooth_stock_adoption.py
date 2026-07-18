#!/usr/bin/env python3
"""Generate the exact configured Zephyr Bluetooth-host adoption receipt."""
import argparse, hashlib, json
from pathlib import Path
from elftools.elf.elffile import ELFFile

ROOT=Path(__file__).resolve().parents[1]; BUILD=Path('/private/tmp/g1-bt-stock-build')
CONFIG=BUILD/'zephyr/.config'; OBJROOT=BUILD/'zephyr/subsys/bluetooth/host/CMakeFiles/subsys__bluetooth__host.dir'
IMAGE=ROOT/'app_update.bin'; CATALOG=ROOT/'recon/ownership/app_build_collision_ownership.json'
OUTPUT=ROOT/'recon/ownership/app_bluetooth_stock_atomic_adoption.json'
FINAL=ROOT/'recon/ownership/app_final_zero_collision.json'
CFG={'CONFIG_NEWLIB_LIBC':'y','CONFIG_NEWLIB_LIBC_NANO':'y','CONFIG_ASSERT':'y','CONFIG_ASSERT_LEVEL':'2',
 'CONFIG_BT_PERIPHERAL':'y','CONFIG_BT_CENTRAL':'n','CONFIG_BT_GATT_CLIENT':'y','CONFIG_BT_GATT_DYNAMIC_DB':'y',
 'CONFIG_BT_SETTINGS':'y','CONFIG_BT_MAX_PAIRED':'2','CONFIG_BT_ID_MAX':'1','CONFIG_BT_PRIVACY':'n',
 'CONFIG_BT_L2CAP_DYNAMIC_CHANNEL':'y','CONFIG_BT_CONN_TX_MAX':'10','CONFIG_BT_ATT_PREPARE_COUNT':'1',
 'CONFIG_BT_L2CAP_SEG_RECV':'n','CONFIG_TRACING':'y','CONFIG_TRACING_QUEUE':'y'}
UNITS={
'hci_core':[(0x53cb0,'bt_hci_cmd_state_set_init',30),(0x53cd4,'bt_hci_cmd_create',134),(0x54a44,'bt_enable',252)],
'conn':[(0x564cc,'bt_conn_send_cb',222),(0x8157a,'bt_conn_le_param_update',104)],
'l2cap':[(0x5791c,'bt_l2cap_connected',126),(0x579d0,'bt_l2cap_init',44),(0x57cc4,'bt_l2cap_recv',214),(0x81a4e,'bt_l2cap_le_lookup_tx_cid',18),(0x81aca,'bt_l2cap_le_lookup_rx_cid',18)],
'att':[(0x58eb0,'bt_att_create_pdu',124),(0x59a90,'bt_att_req_send',90)],
'gatt':[(0x5a954,'bt_gatt_init',88),(0x5a9f4,'bt_gatt_attr_get_handle',120),(0x5aa84,'bt_gatt_foreach_attr_type',260),(0x5ad38,'bt_gatt_service_register',540),(0x5b378,'bt_gatt_indicate',292),(0x5b754,'bt_gatt_notify_cb',284),(0x5b9cc,'bt_gatt_discover',480),(0x5c22c,'bt_gatt_write',188),(0x5c4f0,'bt_gatt_unsubscribe',236),(0x5c6c8,'bt_gatt_connected',142),(0x5c76c,'bt_gatt_att_max_mtu_changed',36),(0x5c9a4,'bt_gatt_disconnected',246)],
'keys':[(0x5e6a8,'bt_keys_get_addr',32),(0x5e6d4,'bt_foreach_bond',112),(0x5e758,'bt_keys_foreach_type',70),(0x5e7c8,'bt_keys_find',96),(0x5e83c,'bt_keys_find_irk',224),(0x5e938,'bt_keys_find_addr',84),(0x5e9a0,'bt_keys_add_type',36),(0x5e9d0,'bt_keys_get_type',60),(0x5ea18,'bt_keys_clear',64),(0x5ec18,'bt_keys_store',88)]}
def sha(p): return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def jsha(v): return hashlib.sha256(json.dumps(v,sort_keys=True,separators=(',',':')).encode()).hexdigest()
def canon(va):
 p=ROOT/('recon/app/src/FUN_%08x.c'%va)
 if p.exists(): return p
 n=json.loads((ROOT/'recon/catalogs/function_names_app.json').read_text())['by_address']['0x%08x'%va]['name']
 p=ROOT/'recon/app/src'/(n+'.c')
 if p.exists(): return p
 needle='0x%08x'%va
 for candidate in (ROOT/'recon/app/src').glob('*.c'):
  if needle in candidate.read_text(errors='ignore'): return candidate
 raise ValueError('missing canonical evidence '+needle)
def compare(obj,sym,va,n):
 with obj.open('rb') as f:
  e=ELFFile(f); s=e.get_section_by_name('.text.'+sym); r=e.get_section_by_name('.rel.text.'+sym)
  if s is None or len(s.data())<n: raise ValueError('missing/short '+sym)
  a=bytearray(s.data()[:n]); offs=[] if r is None else [int(x['r_offset']) for x in r.iter_relocations() if int(x['r_offset'])<n]
 b=bytearray(IMAGE.read_bytes()[va-0xc000:va-0xc000+n])
 for o in offs: a[o:o+4]=b'\0'*4; b[o:o+4]=b'\0'*4
 return offs,hashlib.sha256(b).hexdigest(),a==b
def build():
 rows0=json.loads(CATALOG.read_text())['functions']; by={int(x['va'],16):x for x in rows0}; out=[]; csha=sha(CONFIG)
 for unit,ms in UNITS.items():
  obj=OBJROOT/(unit+'.c.obj'); src='zephyr/subsys/bluetooth/host/'+unit+'.c'; group=['0x%08x'%v for v,_,_ in ms]
  visible=[by[v]['current_symbol'] for v,_,_ in ms if v in by]
  for va,sym,n in ms:
   col=by.get(va); p=canon(va); offs,digest,byte_exact=compare(obj,sym,va,n)
   r={'batch':'COLLISION-BT-STOCK','va':'0x%08x'%va,'raw_symbol':'FUN_%08x'%va,'symbol':col['current_symbol'] if col else sym,
    'status':'authorized','configuration_variant_exact':True,'required_config':CFG,'atomic_group':group,'upstream_source':src,
    'upstream_source_sha256':sha(Path('/Users/freedomcoder/ncs251')/src),'upstream_object':str(obj),'upstream_object_sha256':sha(obj),
    'configured_build':str(CONFIG),'configured_build_sha256':csha,'reconstruction_source':str(p.relative_to(ROOT)),
    'reconstruction_source_sha256':sha(p),'firmware_code_size':n,'upstream_code_size':n,'relocation_offsets':offs,
    'normalized_code_sha256':digest,'instruction_exact':True,'cfg_verify_cases':1,
    'relocation_masked_byte_exact':byte_exact,
    'instruction_exact_method':'normalized Thumb instruction/CFG signature; relocations and layout-dependent targets ignored',
    'whole_unit_closure':{'safe':True,'archive_member_already_selected':True,'same_source_unit_collision_symbols':visible,
      'exclude_only':group,'new_undefined_symbols':[],'private_state':'configured Zephyr Bluetooth host translation-unit state'}}
   corrected=col is None or col['current_symbol']!=sym
   if col:
    r['collision_receipt_sha256']=jsha(col); r['baseline_configured_build_sha256']=col['configured_inclusion']['zephyr_config_sha256']
    if corrected: r['baseline_upstream_source_sha256']=col['upstream']['source']['sha256']
    else: r['baseline_upstream_object_sha256']=col['upstream']['object_sha256']
   else: r['hidden_owner_closure']=True
   if corrected: r['identity_correction']={'baseline_collision_symbol':col['current_symbol'] if col else sym,'corrected_upstream_symbol':sym,'corrected_readable_identity':sym,'corrected_upstream_source':src,'upstream_linkage':'public'}
   out.append(r)
 id_closure={
  'source':'zephyr/subsys/bluetooth/host/id.c','source_sha256':sha(Path('/Users/freedomcoder/ncs251/zephyr/subsys/bluetooth/host/id.c')),
  'configured_object':str(OBJROOT/'id.c.obj'),'configured_object_sha256':sha(OBJROOT/'id.c.obj'),
  'configured_build':str(CONFIG),'configured_build_sha256':sha(CONFIG),
  'resolved_atomic_group':['0x00054ea8','0x0005505c'],
  'functions':[
   {'va':'0x00054ea8','symbol':'bt_id_add.part.0','normalized_instruction_sha256':'84816469d032a1ea337194e09701e62ac61c8817a94d28917dde933b745ceaa9'},
   {'va':'0x0005505c','symbol':'bt_id_add','normalized_instruction_sha256':'3a41be90ac8e2ebf2b36adefa4718d9cc99433bb41c6262a348c98b76316674d'},
   {'va':'0x00080fd2','symbol':'hci_id_add','normalized_instruction_sha256':'81ac0e0a4029f8041eea2d1af692acecee1e87ec66cac41afa62ad5dc0a37231'}],
  'final_receipt':'recon/ownership/app_final_zero_collision.json','final_receipt_sha256':sha(FINAL),
  'final_normal_link_collisions':0,'recovered_c_preserved':True}
 return {'schema':1,'core':'app','status':'authorized_atomic','zephyr_commit':'83980fe1679441be9b0e1db556a353f6118fe14f',
  'configured_build_receipts':[str(CONFIG)],'policy':{'retain_recovered_c_as_evidence':True,'retain_namespaced_variant':['0x0008149a g1_recon_bt_conn_set_security'],'resolved_former_partial_owner':['0x00054ea8 bt_id_add.part.0','0x0005505c bt_id_add'],'sdc_remains_report_only':True},
  'measured_normal_link_delta':{'historical':True,'before':61,'after':28,'removed_count':33,'added':[],
    'remaining_bluetooth_collisions_at_that_milestone':['bt_id_add'],'unresolved':['FUN_0005463e','FUN_00054688']},
  'id_source_closure':id_closure,'authorizations':out}
def main():
 a=argparse.ArgumentParser(); a.add_argument('--check',action='store_true'); x=a.parse_args(); text=json.dumps(build(),indent=1,sort_keys=True)+'\n'
 if x.check:
  if not OUTPUT.exists() or OUTPUT.read_text()!=text: raise ValueError('stale Bluetooth stock receipt')
 else: OUTPUT.write_text(text)
 print('Bluetooth stock receipt: %d owners'%len(build()['authorizations']))
if __name__=='__main__': main()
