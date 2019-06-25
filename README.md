coreboot README
===============

CTF - GDB on qemu

## Problem

The ramstage hangs at the very start.

## Payload

-

## Target

qemu-i440fx

## Task

Find and fix the problem which causes the ramstage to hang.

* Build coreboot for qemu-i440fx with serial enabled
* Run in qemu:
`qemu-system-i386 -M pc -m 2048 -bios build/coreboot.rom -serial stdio`
* Boot and write down the ramstage load address:

If the serial log show this line:
```
Loading module at 3ffa8000 with entry 3ffa8000. filesize: 0x168b0 memsize: 0x21668
```

the load address is *0x3ffa8000*.

* Now start qemu with GDB server
`qemu-system-i386 -M pc -m 2048 -bios build/coreboot.rom -serial stdio -s -S`
* Attach with GDB

`$ gdb`

```
(gdb) add-symbol-file build/cbfs/fallback/ramstage.debug 0x3ffa8000
(gdb) b main
(gdb) target remote localhost:1234
(gdb) c
```
