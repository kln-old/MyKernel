#include "common.h"
#include "screen.h"

void isr_win(registers_t regs)
{

	window win_isr;
	char win_isr_title[15]="intr-hndlr";
	u8int row1,col1,row2,col2;
	row1=30;col1=6;
	row2=50;col2=18;

	win_init(&win_isr,row1,col1,row2,col2,win_isr_title,bblack|fred,bblack|fwhite);
	win_create(&win_isr);

	win_putstring(&win_isr,"recieved interrupt: ");
	win_printdec(&win_isr,regs.int_no);
	win_putchar(&win_isr,'\n');

	writestring(8,8,"called isr_win",bblue|fwhite);
}
void isr_handler(registers_t regs)
{
	writestring(0,0,"received interrupt:",bblue|fwhite);
}
