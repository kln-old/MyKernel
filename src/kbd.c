#include "screen.h"
#include "isr.h"
#include "kbd.h"

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */


u8int scancode,ascii;
u8int received;
u8int shift,capslock,alt,cntrl;

extern window win_boot;

unsigned char kbdus[256] =
{
    0,  27, /*escape*/
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', /* row1 */
  '\t',	'q', 'w', 'e', 'r','t', 'y', 'u', 'i', 'o', 'p', '[', ']', 	/* row2 */ 
  '\n',		/* Enter key */
    0,		/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',			/* row3 */
  '`',   0,		/* Left shift */
  '\\', 
  'z', 'x', 'c', 'v', 'b', 'n','m', ',', '.', '/', 0,/* Right shift *//* row4 */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdus_shift[256] =
{
    0,  27, /*escape*/
  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', /* row1 */
  '\t',	'Q', 'W', 'E', 'R','T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 	/* row2 */ 
  '\n',		/* Enter key */
    0,		/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"',			/* row3 */
  '~',   0,		/* Left shift */
  '|', 
  'Z', 'X', 'C', 'V', 'B', 'N','M', '<', '>', '?', 0,/* Right shift *//* row4 */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
/* Handles the keyboard interrupt */
void keyboard_handler(registers_t regs)
{
    unsigned char _scancode;

    /* Read from the keyboard's data buffer */
    _scancode = inb(0x60);

	scancode=_scancode;
//	received=1;	

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (_scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
//	win_putstring(&win_boot,"\nkey released: ");
//	win_putchar(&win_boot,kbdus[_scancode]);
//	win_putchar(&win_boot,' ');
//	win_printdec(&win_boot,_scancode);
//	win_putchar(&win_boot,'\n');

		switch( _scancode )
		{
//			case 186://capslock
//					capslock=0;
//					break;
			case 170://shift-L
//				win_putstring(&win_boot,"\nreleased shiftL\n");
				shift=0;
				break;
			case 182://shift-R
//				win_putstring(&win_boot,"\nreleased shiftR\n");
				shift=0;
				break;
			case 157://cntrl
//				win_putstring(&win_boot,"\nreleased cntrl\n");
				cntrl=0;
				break;			
			case 185://alt
//				win_putstring(&win_boot,"\nreleased alt\n");
				alt=0;
				break;
		}

    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        
	received = 1;
	switch( _scancode )
	{
		case _kbd_capslock:
				capslock=1-capslock;
				break;

		case _kbd_shift_l:
		/*		win_putstring(&win_boot,"\npressed shift\n");
				win_putstring(&win_boot,"shift=");
				win_printdec(&win_boot,shift);
				win_putchar(&win_boot,'\n');
		*/		shift=1;
				break;
		
		case _kbd_shift_r:
				shift=1;
				break;
		case _kbd_cntrl:
				cntrl=1;
				break;

		case _kbd_alt:
				alt=1;
				break;
	}
/*
	win_putstring(&win_boot,"\nstatus:\n");

	win_putstring(&win_boot,"caps=");
	win_printdec(&win_boot,capslock);
	win_putchar(&win_boot,'\n');
	win_putstring(&win_boot,"shift=");
	win_printdec(&win_boot,shift);
	win_putchar(&win_boot,'\n');
	win_putstring(&win_boot,"cntrl=");
	win_printdec(&win_boot,cntrl);
	win_putchar(&win_boot,'\n');
	win_putstring(&win_boot,"alt=");
	win_printdec(&win_boot,alt);
	win_putchar(&win_boot,'\n');
*/
	if ( shift )
	{
		ascii=kbdus_shift[_scancode];
	}
	else
	{
		ascii=kbdus[_scancode];
	}
	if( capslock )
	{
		if( (ascii >= 'a') && (ascii <= 'z') )
				ascii=ascii-('a'-'A');
//		if( ascii >= 'A' && ascii <= 'Z' )
//				ascii=ascii+('a'-'A');
	}

				
//	win_putstring(&win_boot,"\nkey pressed: ");
//	win_putchar(&win_boot,kbdus[_scancode]);
//	win_putchar(&win_boot,' ');
//	win_printdec(&win_boot,scancode);
//	win_putchar(&win_boot,'\n');

    }

	outb(0x20,0x20);
//	win_putstring(&win_boot,"--------------\n");
}

/* Installs the keyboard handler into IRQ1 */
void init_kbd()
{
    register_interrupt_handler(IRQ1,&keyboard_handler);
}

void kbd_read(u8int *s,u8int *a)
{
	received=0;

	while(received ==0 );

	*s=scancode;
	*a=ascii;

}
