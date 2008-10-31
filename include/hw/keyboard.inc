;
; kestrel/keyboard.inc
; Copyright (c) 2006-2008 Samuel A. Falvo II
; See LICENSE for further details.
; 

KF_PRESSED      = $8000
KF_RELEASED     = $0000

;
; Keyboard Pseudo-Mode Flags -- a semi-cooked and convenient way
; of probing current keyboard modifier flags.  The name, pseudomode,
; is from Jef Raskin's use of the term in his book The Humane Interface.
;

KMF_RMENU       = $0200
KMF_RLOGO       = $0080
KMF_LLOGO       = $0040
KMF_RALT        = $0020
KMF_LALT        = $0010
KMF_RCTRL       = $0008
KMF_LCTRL       = $0004
KMF_RSHIFT      = $0002
KMF_LSHIFT      = $0001

;
; Raw keycodes returned by the KIMO chip when interfaced to the SDL
; environment.
;

K_ESC           = $0009
K_F1            = $0043
K_F2            = $0044
K_F3            = $0045
K_F4            = $0046
K_F5            = $0047
F_F6            = $0048
K_F7            = $0049
K_F8            = $004A
K_F9            = $004B
K_F10           = $004C
K_F11           = $005F
K_F12           = $0060
K_PRTSCR        = $006F
K_SCRLOCK       = $004E
K_BREAK         = $006E
K_RTICK         = $0031
K_1             = $000A
K_2             = $000B
K_3             = $000C
K_4             = $000D
K_5             = $000E
F_6             = $000F
K_7             = $0010
K_8             = $0011
K_9             = $0012
K_0             = $0013
K_DASH          = $0014
K_EQUALS        = $0015
K_BACKSPACE     = $0016
K_TAB           = $0017
K_Q             = $0018
K_W             = $0019
K_E             = $001A
K_R             = $001B
K_T             = $001C
K_Y             = $001D
K_U             = $001E
K_I             = $001F
K_O             = $0020
K_P             = $0021
K_LBRACKET      = $0022
K_RBRACKET      = $0023
K_BACKSLASH     = $0033
K_CAPSLOCK      = $0042
K_A             = $0026
K_S             = $0027
K_D             = $0028
K_F             = $0029
K_G             = $002A
K_H             = $002B
K_J             = $002C
K_K             = $002D
K_L             = $002E
K_SEMICOLON     = $002F
K_TICK          = $0030
K_ENTER         = $0024
K_LSHIFT        = $0032
K_Z             = $0034
K_X             = $0035
K_C             = $0036
K_V             = $0037
K_B             = $0038
K_N             = $0039
K_M             = $003A
K_COMMA         = $003B
K_DOT           = $003C
K_SLASH         = $003D
K_RSHIFT        = $003E
K_LCTRL         = $0025
K_LLOGO         = $0073
K_LALT          = $0040
K_SPACE         = $0041
K_RALT          = $0071
K_RLOGO         = $0074
K_RMENU         = $0075
K_RCTRL         = $006D
K_HOME          = $0061
K_END           = $0067
K_DELETE        = $006B
K_PGUP          = $0063
K_PGDOWN        = $0069
K_INSERT        = $006A
K_UP            = $0062
K_LEFT          = $0064
K_RIGHT         = $0066
K_DOWN          = $0068
K_NUMLOCK       = $004D
K_N_SLASH       = $0070
K_N_STAR        = $003F
K_N_DASH        = $0052
K_N_7           = $004F
K_N_8           = $0050
K_N_9           = $0051
K_N_PLUS        = $0056
K_N_4           = $0053
K_N_5           = $0054
K_N_6           = $0055
K_N_1           = $0057
K_N_2           = $0058
K_N_3           = $0059
K_N_0           = $005A
K_N_DOT         = $005B
K_N_ENTER       = $006C

