;
; kestrel/cpu.inc
; Kestrel 1p4 CPU-related definitions
; Release 1p1
;
; Copyright (c) 2006 Samuel A. Falvo II
; See LICENSE for details.
;



; 
; 65816 P register field definitions.  Note that some bits are
; overloaded depending on operating mode.  CPUP_M is undefined in
; M6502() mode, while CPUP_X is really CPUP_B, for example.
; 

CPUP_N = $80
CPUP_V = $40
CPUP_M = $20
CPUP_X = $10
CPUP_D = $08
CPUP_I = $04
CPUP_Z = $02
CPUP_C = $01

;  M6502 mode synonyms; 

CPUP_B = CPUP_X

; 
; Mode change macros.  M65816 forces the CPU into native mode, but
; doesn't adjust register settings.  M6502 forces the CPU into 6502-
; emulation mode, which *is* register setting destructive!
; 

.macro M65816
    clc
    xce
.endmacro

.macro M6502
    sec
    xce
.endmacro

; 
; Register size coercion.  Note that these both adjust the P
; register AND affect assembler state.  To affect only assembler
; state, use .a(s|l) and .x(s|l) pseudo-operations manually.
; 

.macro AX8
    sep #(CPUP_M+CPUP_X)
    .a8
    .i8
.endmacro

.macro A8X16
    sep #CPUP_M
    rep #CPUP_X
    .a8
    .i16
.endmacro

.macro A16X8
    rep #CPUP_M
    sep #CPUP_X
    .a16
    .i8
.endmacro

.macro AX16
    rep #(CPUP_M+CPUP_X)
    .a16
    .i16
.endmacro

; 
; Support for the WDM opcode, which is used by the development emulator
; to invoke emulator-specific functionality.
;
; Examples:
;       WDM WdmReq::TraceOn
;       ... instructions here ...
;       WDM WdmReq::TraceOff
; 

.macro WDM v
    .byte $42,(v)
.endmacro

.enum WdmReq
    ExitEmulator
    TraceOff
    TraceOn
    StackDump
.endenum

