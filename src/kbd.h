#ifndef KBD_H
#define KBD_H

	#include "common.h"

/*scan codes*/



#define _kbd_escape        1
#define _kbd_f1            59
#define _kbd_f2            60
#define _kbd_f3            61
#define _kbd_f4            62
#define _kbd_f5            63
#define _kbd_f6            64
#define _kbd_f7            65
#define _kbd_f8            66
#define _kbd_f9            67
#define _kbd_f10           68
#define _kbd_f11	   87
#define _kbd_f12	   88		
#define _kbd_backspace     14
#define _kbd_tab           15
#define _kbd_enter         28
#define _kbd_up            72
#define _kbd_left          75
#define _kbd_right         77
#define _kbd_down          80
#define _kbd_delete        83
#define _kbd_insert        82
#define _kbd_home          71
#define _kbd_end           79
#define _kbd_pageup        73
#define _kbd_pagedown      81
#define _kbd_space         57
#define _kbd_colon	   27
#define _kbd_shift_l	   42
#define _kbd_shift_r	   54
#define _kbd_capslock	   58
#define _kbd_alt	   56
#define _kbd_cntrl	   29
#define _kbd_extended	   0xE0

#define scan_alt_f    0x21
#define scan_ctrl_f   0x21
#define scan_shift_f  0x21
#define scan_alt_d    0x20
#define scan_ctrl_d   0x20
#define scan_shift_d  0x20
#define scan_alt_e    0x12
#define scan_ctrl_e   0x12
#define scan_shift_e  0x12
#define scan_alt_s    0x1f
#define scan_alt_p    0x19
#define scan_alt_i    0x17
#define scan_alt_h    0x23



#define ascii_alt_f    0x00
#define ascii_ctrl_f   0x06
#define ascii_shift_f  0x46
#define ascii_alt_d    0x00
#define ascii_ctrl_d   0x04
#define ascii_shift_d  0x44
#define ascii_alt_e    0x00
#define ascii_ctrl_e   0x05
#define ascii_shift_e  0x45
#define ascii_alt_s    0x00
#define ascii_alt_p    0x00
#define ascii_alt_i    0x00
#define ascii_alt_h    0x00


	void init_kbd(void);
	void kbd_read(u8int *,u8int *);

#endif
