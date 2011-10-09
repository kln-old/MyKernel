#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"

/*fore ground colors*/

#define fblack          0x00
#define fblue           0x01
#define fgreen          0x02
#define fcyan           0x03
#define fred            0x04
#define fmagenta        0x05
#define fbrown          0x06
#define flightgray      0x07
#define fdarkgray       0x08
#define flightblue      0x09
#define flightgreen     0x0a
#define flightcyan      0x0b
#define flightred       0x0c
#define flightmagenta   0x0d
#define fyellow         0x0e
#define fwhite          0x0f

/*back ground colors*/

#define bblack     0x00
#define bblue      0x10
#define bgreen     0x20
#define bcyan      0x30
#define bred       0x40
#define bmagenta   0x50
#define bbrown     0x60
#define blightgray 0x70

// blink character( 1000 000 )
#define blink 0x80

//TODO: put these into keyboard file
#define tabstop		0x04

#define _backspace	0X08
#define h_tab		0X09
#define v_tab		0X0B
#define bell		0X07
#define formfeed	0X0C
#define carriageret	0X0D
#define linefeed	0x0A

/*
struct Screen{
	
	u16int attr;
	u8int cursor_row;
	u8int cursor_col;

};

typedef struct Screen Screen;
*/
struct struct_win{
	
	u8int row1;u8int col1;
	u8int row2;u8int col2;
	char title[16];
	u16int w_attr;
	u16int b_attr;
	u8int cursor_row;
	u8int cursor_col;
};
typedef struct struct_win window;


//TODO: complete these functions 

//static void set_cursortype(void);
//static void set_videomode(void);
//static void scrollup(u8int x1, u8int y1, u8int x2, u8int y2);
//static void scrolldown(u8int x1, u8int y1, u8int x2, u8int y2);

void initscreen(void); //TODO; provide settings for screen back, fore etc...

void writechar(u8int row, u8int col, char c, u16int att);
void writestring(u8int row, u8int col, char *s, u16int att);
void set_screenbackground(u16int att);
void clearscreen(void);
void move_cursor(u8int row,u8int col);
void scroll_screen(void);
void h_doubleline(u8int row,u8int col1,u8int col2,u16int attr);

static void scroll_up(u8int row1,u8int col1,u8int row2,u8int col2,u16int attr);

static void create_window(u8int row1,u8int col1,u8int row2,u8int col2,char *title,u16int w_attr,u16int b_attr);

void monitor_write_hex(u32int);
void monitor_write_dec(u32int);

void win_init(window *,u8int ,u8int ,u8int ,u8int ,char *,u16int ,u16int );
void win_create(window *);
void win_scroll_up(window *);
void win_putchar(window *,char);
void win_putstring(window *,char *);
void win_clear(window *);
void win_clear_refresh(window *);
void win_printdec(window *,u32int);
void win_printhex(window *,u32int);
#endif
