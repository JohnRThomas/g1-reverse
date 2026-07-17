#!/usr/bin/env python3
import os,sys,unittest
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch7_ownership as o

class TestBatch7(unittest.TestCase):
 @classmethod
 def setUpClass(c):c.d=o.build();c.r={x["symbol"]:x for x in c.d["functions"]}
 def test_scope(self):
  self.assertEqual(set(o.OWNERS),set(self.r));self.assertEqual(8,self.d["summary"]["function_count"]);self.assertEqual(24,self.d["summary"]["reference_count_before"])
 def test_fail_closed(self):
  self.assertTrue(self.d["policy"]["fail_closed"]);self.assertTrue(all(x["decision"]=="retain_cfg_verified_configured_reconstruction" for x in self.r.values()))
 def test_backmaps_and_mirrors(self):
  for n,x in self.r.items():
   with open(os.path.join(o.ROOT,x["source"]),encoding="utf-8") as f:s=f.read()
   self.assertIn(x["va"],s);self.assertIn("FUN_%08x"%int(x["va"],16),s)
 def test_verifier_contracts(self):
  v=self.d["verification_infrastructure"]
  self.assertEqual("0x000582b8+0x6c",v["att_op_get_type_true_extent"]);self.assertEqual(3,v["gatt_req_send_external_callback_arg"]);self.assertEqual(6,v["bt_start_reviewed_state_count"])
  self.assertEqual(46,self.r["att_op_get_type"]["checked"]);self.assertEqual(6,self.r["bt_start"]["checked"])
if __name__=="__main__":unittest.main()
