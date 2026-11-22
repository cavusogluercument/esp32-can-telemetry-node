# KiCad Hardware Sources
- `telemetry_node.sch`: editable legacy KiCad schematic/design-note source.
- `NETLIST.csv`: Rev-A connectivity authority for schematic capture/review.
- `telemetry_node.kicad_pcb`: editable KiCad PCB Rev-A placement/reference outline.

The PCB intentionally does **not** pretend to be fabrication-ready: final footprints, copper routing, planes, antenna keep-out implementation, ERC/DRC and manufacturer-specific checks must be completed in KiCad before Gerber export. This is preferable to publishing an unverified board as if it had been fabricated.
