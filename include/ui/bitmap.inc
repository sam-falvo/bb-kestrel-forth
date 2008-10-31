; Copyright (c) 2008 Samuel A. Falvo II
; See LICENSE for details
;
; Bitmap Render Driver (RD).  This module provides definitions relevant
; for monochrome bitmaps.
;
; Author: kc5tja@arrl.net (Samuel A. Falvo II)


; The Bitmap structure.
;
; A long pointer to the buffer's actual memory.
bm_bits             = 0

; The height of the buffer in pixels.
bm_height           = bm_bits+4

; The width of the bitmap in words.  Note that this field can be
; different than the pixel width; consider the case when you are defining a
; bitmap descriptor for a sub-bitmap of a larger bitmap (e.g., a window on
; the screen).
bm_widthInWords     = bm_height+2

; The width of the bitmap in pixels.  This field MUST satisfy the
; condition:
;
; 0 <= bm_widthInPixels <= (bm_widthInWords * 16)
;
; If this isn't the case, memory corruption will inevitably occur.
bm_widthInPixels    = bm_widthInWords+2

SIZEOF_Bitmap       = bm_widthInPixels+2

