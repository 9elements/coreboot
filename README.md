coreboot README
===============

CTF - Malfunctioning UART

## Problem

There's no serial output on UART0.

## Payload

-

## Target

UP²

## Task

Fix the mainboard code in `src/mainboard/up/squared` by using the 'flash console':

* Enable flash console in Kconfig
* Build
* Flash and run the generated coreboot.rom
* Read back the coreboot.rom
** For example
** `$ flashrom -pdediprog:voltage=1.8V --fmap -i CONSOLE -r /tmp/console.log`
* Extract the CONSOLE region
* Read the log in CONSOLE region
* Fix the non-working serial console
