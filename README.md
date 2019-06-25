coreboot README
===============

CTF - DRAM training result store

## Problem

The FSP-M takes about 10 seconds to init DRAM.

Usually DRAM training results are stored in flash to reduce boot time on
the second power on, which takes less than a second.

For some reason it doesn't work in this branch.

## Payload

-

## Target

UP²

## Task

Find and fix the problem why FSP-M takes so long on the second power on.

* Build coreboot for UP² with serial enabled
* Flash coreboot and run it on the UP²
* Search the coreboot log for errors
* Fix the errors in `src/mainboard/up/squared`
