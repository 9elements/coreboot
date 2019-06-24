# Apollolake

With Apollolake Intel invented another flash layout for x86 firmware called
IFWI (Intel FirmWare Image).

Usually on x86 platforms the bootblock is stored at the end of the bios region
and the Intel ME / TXE has its own IFD region. On Apollolake both have been
moved into the IFWI region, which is a subregion of "BIOS", since it allows to
store multiple firmware components.

The IFWI region can be manipulated by `ifwitool`.

## SPI flash layout

IFD regions:
* The "ME" region isn't used on production boards
* The "BIOS" region contains one or two logical boot partitions (LBP)
  * The IFD controls if one or two LBP are active
  * Each LBP has it's own IFWI and OBB
  * The last 256 KiB of the "BIOS" region are BIOS_UNUSABLE
* The "device extension" region is used by TXE as secure filesystem

### SPI layout with single LBP

When configured for single LBP mode, the LBP uses the whole "BIOS" region's
flash size.

![][apl_flash_layout]

### SPI layout with dual LBP

When configured for dual LBP mode, each LBP uses exactly half of the "BIOS"
region's flash size.

![][apl_flash_layout2]

### IFWI

The IFWI contains the bootblock, while the OBB contains the CBFS and other
regions as specified in the FMAP.
The OBB spans the whole size from IFWI till the end of the LBP.

**Note:** ifwitool doesn't care about LBP2!

### Logical boot partitions

Each LBP has their own IFWI and OBB. It allows failsafe firmware updates.

**Note:** If configured in dual partition mode, the TXE will enter recovery
mode if LBP2 is missing.

To disable dual partitioning mode, set bit3 in IFD at offset `0x1ff` to 1.

[apl_flash_layout]: flash_layout.svg
[apl_flash_layout2]: flash_layout2.svg

