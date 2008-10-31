; Copyright (c) 2008 Samuel A. Falvo II
; See LICENSE for more information.
;
; Definitions for the softblit module.
;
; Author: Samuel A. Falvo II <kc5tja@arrl.net>

; The softblit code forms the core inner loop of many graphics operations.
; As a result, the need for speed trumps the normal Kestrel coding
; conventions: no unnecessary register preservation, no stack frame
; creation, etc.  Realizing the best possible speed requires submission of
; all blitter parameters in a single, fixed-sized Software Blitter Control
; Block, or SBCB.  In a sense, one might think of the SBCB as a mirror or
; shadow of some hypothetical hardware blitter.
; 
; The fields of the SBCB follow:
;
; The first of two sources of pixel data, specified as a long-address.
; CPU register Y indexes into the data pointed to by this field.
sbcb_source1        = 0

; The second of two sources of pixel data, specified as a long-address.
; CPU register Y indexes into the data pointed to by this field.
sbcb_source2        = sbcb_source1+4

; The long-address of where to put the blit results.  CPU register Y
; indexes into the data pointed to by this field.
sbcb_dest           = sbcb_source2+4

; When blitting only a single word of binary data, this field contains a mask
; declaring which bits of the destination word to update.  Note that while the
; bitmap data exists in big-endian format, the mask data is little-endian.
; emulateBlitterCycleUsing_withMasking uses this field, while
; emulateBlitterCycleUsing_ ignores it by assuming a mask of $FFFF for
; slightly better performance.
sbcb_destMask       = sbcb_dest+4

; A near-pointer of a procedure that uses the data in the sbcb_s?data* fields
; to compute some logical operation between the fetched data.  The field's
; name derives from the phrase, "draw mode."
sbcb_mode           = sbcb_destMask+2

; The offset into a look-up table of procedures, each shifting the data
; fetched from source 1 by a set amount.  Procedures appear in the table such
; that one may compute the offset based on how many bits to shift.  The
; equation to determine the offset is:
;  
; offset = 2*(16+d)
; 
; where d = the number of bits to shift to the right.  If shifting to the
; left, use a negative number (e.g., d = -3 means shift _left_ 3 bits, while
; d = 3 means shift _right_ 3 bits).  Think of the number-line, where
; negative numbers appear to the left of zero, and positives to the right.
sbcb_shift1         = sbcb_mode+2

; When blitting across multiple words in a single row of pixel data, bits
; shifted out from the previous word need to roll over into the current word
; being processed.  Likewise, bits shifted out from the current word must
; carry over into the next word, and so on.  This field serves as a temporary
; holding variable to support multi-word blits.
; 
; Prior to blitting a new row of pixels, reset this field to zero to prevent
; garbage from appearing in the first column of the blit.
sbcb_previous       = sbcb_shift1+2

; First and last word masks apply when blitting a whole row of pixels only.
; See the blitRowLeftToRight and blitRowRightToLeft procedures.  The first
; word mask applies to the _left_ edge of the destination bitmap, while the
; last word mask applies to the _right_ edge.
sbcb_fwmask         = sbcb_previous+2
sbcb_lwmask         = sbcb_fwmask+2

; To facilitate when the blitter has completed a row of pixels, initialize
; this field with the _byte offset_ of the last addressed word in the row.
; Blits will continue until the CPU register Y equals or exceeds the limit
; set in this field.
; 
; Note that two blit directions exist; blitting from right to left supports
; graphics operations involving a left-shift.  In this case, initialize this
; field with the byte offset of the left column, and the CPU register Y with
; the byte offset of the right column.  Reverse these settings for left to
; right blits, involving right shifts.
sbcb_lastColumn     = sbcb_lwmask+2

; When blitting over a rectangular area, we need to know the width of the
; various bitmaps in bytes (in other APIs, we use words; but since we are
; in a tight loop, we use bytes here to save the 6 cycles per row that it'd
; take to multiply these values by two).  These are used to adjust, in place,
; the sbcb_source1, sbcb_source2, and sbcb_dest pointers.
;
; Bitmap data MAY cross bank boundaries, thus permitting bitmaps that are
; either exceptionally large, or are densely packed in memory.
sbcb_s1span         = sbcb_lastColumn+2
sbcb_s2span         = sbcb_s1span+2
sbcb_destSpan       = sbcb_s2span+2

; These four fields need no pre-initialization, as they are populated as a
; blit proceeds.  The sbcb_s1data and sbcb_s1data_ fields contains the word
; fetched from the address contained in sbcb_source1, the latter field being
; inverted from the former.  Likewise, sbcb_s2data and sbcb_s2data_ serve the
; same purposes with respect to the sbcb_source2 pointer.
;
; The procedure referenced in the sbcb_mode field uses these fields to
; perform the desired logic operation.  For example, to logically-NOR sources
; 1 and 2, you'd use a procedure like the following:
;
; lda sbcb_s1data_+1
; and sbcb_s2data_+1
; rts
;
; The file softblit.a discusses the need for the +1 offset.
sbcb_s1data         = sbcb_destSpan+2
sbcb_s2data         = sbcb_s1data+2
sbcb_s1data_        = sbcb_s2data+2
sbcb_s2data_        = sbcb_s1data_+2

; This field needs no pre-initialization, as it serves only as a temporary
; holding location for spilled bits during the shifting process.  This
; location's value has no defined value upon completion of a blit operation.
sbcb_spill          = sbcb_s2data_+2

; Depending on future needs, additional fields may appear in upcoming
; releases of the Kestrel firmware.  For this reason, NEVER call the softblit
; functions yourself; rely instead on the higher-level blitting operations
; provided by the firmware.
sbcb_SIZEOF         = sbcb_spill+2

; Specifying a hard-coded shift of "zero bits" appears so frequently that
; we've defined a symbol to make this easier and more readable.
noShift             = 32

; The sbcb_mode field receives a near pointer to a procedure implementing
; the desired "draw mode" logic.  Because the blitter implemented by the
; softblit core includes only two operands, only four "minterms" exist.
; 
; Minterm 0: not A and not B
; Minterm 1: not A and     B
; Minterm 2:     A and not B
; Minterm 3:     A and     B
;
; Each minterm generates a '1' bit only if the corresponding source bits
; satisfy the enabled criteria.  A '1' bit in a mask enables the
; corresponding minterm.  If we map minterm 0 to bit 0, minterm 1 to bit 1,
; etc., we end up with the following core mask values:
modeNotAandNotB     = 1
modeNotAandB        = 2
modeAandNotB        = 4
modeAandB           = 8

; By logically-ORing these minterms in various combinations, you get the
; following additional functions.
modeAllZeros        = 0
modeNotA            = modeNotAandNotB + modeNotAandB
modeNotB            = modeAandNotB + modeNotAandNotB
modeAxorB           = modeAandNotB + modeNotAandB
modeAnandB          = modeAandNotB + modeNotAandB + modeNotAandNotB
modeAxnorB          = modeAandB + modeNotAandNotB
modeB               = modeAandB + modeNotAandB
modeBorAnorB        = modeAandB + modeNotAandB + modeNotAandNotB
modeA               = modeAandB + modeAandNotB
modeAorB            = modeAandB + modeAandNotB + modeNotAandB
modeAllOnes         = modeAandB + modeAandNotB + modeNotAandB + modeNotAandNotB

; A more recognizable form of the first minterm, ~A & ~B, is the NOR
; operation (~(A|B)).
modeAnorB           = modeNotAandNotB

