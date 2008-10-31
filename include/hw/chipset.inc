;
; Standard hardware mnemonics
;
; CC - CRTC
; CK - Clock
; DA - Data
; EA - Enable
; EN - End
; HZ - Horizontal
; IQ - IRQ/Interrupt
; KB - Keyboard
; LI - Line
; MO - Mouse
; PH - Phase
; PL - Polarity
; PN - Pending
; PT - Pointer
; RX - Receive
; SB - SerBus
; SL - Select
; ST - Start/Status
; SY - Sync
; TL - Total
; TM - Time(r)
; TX - Transmit
; VR - Vertical
; WD - Width
; 


IOBASE = $FF0000


;
; Monochrome Graphics Interface Adapter
;

CCHZTL  = IOBASE + $0000    ; CRTC Horizontal Total
CCVRTL  = IOBASE + $0002    ; CRTC Vertical Total
CCSYWD  = IOBASE + $0004    ; CRTC Sync Widths
  HZSYWD = CCSYWD           ; byte sized half-registers!
  VRSYWD = CCSYWD+1
CCVRLI  = IOBASE + $0006    ; CRTC Current Line/Raster Compare
VIHZST  = IOBASE + $0008    ; Video Horizontal Start
VIHZEN  = IOBASE + $000A    ; Video Horizontal End
VIVRST  = IOBASE + $000C    ; Video Vertical Start
VIVREN  = IOBASE + $000E    ; Video Vertical End
VIDAPT  = IOBASE + $0010    ; Video Data Pointer
  VIDAPTL = VIDAPT
  VIDAPTH = VIDAPT+2


;
; IRQ Controller
;

IQEA    = IOBASE + $0100    ; IRQ Enable Register
IQPN    = IOBASE + $0102    ; IRQ Pending Register

IQVRLI  = $0001             ; Video (Raster Compare) Interrupt
IQKBMO  = $0002             ; Keyboard/Mouse Controller Interrupt


;
; Keyboard Input and Mouse Adapter
;

KBDA    = IOBASE + $0200    ; Keyboard scancode
;       = IOBASE + $0202    ; unused
;       = IOBASE + $0204    ; unused
KBMOST  = IOBASE + $0206    ; Keyboard/Mouse Status


;
; Timers
;

TMSB    = IOBASE + $0300    ; SerBus baudrate generator (write-only)


;
; SerBus
;

SBDATX  = IOBASE + $0400    ; transmit register (bits 8-15 ignored)
SBDARX  = IOBASE + $0402    ; receive register (bits 8-15 undefined)
SBSL    = IOBASE + $0404    ; device select + SPI mode bits
SBST    = IOBASE + $0406    ; status register

SBCKPH  = $8000             ; SPI clock phase control
SBCKPL  = $4000             ; SPI clock polarity control
SBDSAM  = $0007             ; Device Select AND-Mask

SBDONE  = $8000             ; SerBus status: is done transceiving

