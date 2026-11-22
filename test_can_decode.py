from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from can_decode import decode
assert decode(0x100,bytes.fromhex("09E6138818B82001"))["temperature_C"]==25.34
assert decode(0x101,bytes.fromhex("08000BB801010002"))["input_mV"]==3000
assert decode(0x110,bytes.fromhex("000003E801000003"))["uptime_ms"]==1000
print("PASS: CAN protocol decoder tests")
