// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "screen.h"
#include "string.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "kbd.h"

//extern Screen screen;

window win_boot;

void welcome(void)
{

char name[6][35]={
			" _  __         _   _      _ ",
			"| |/ /        | \\ | |    | |",
			"| ' / ___ _ __|  \\| | ___| |",
			"|  < / _ \\ '__| . ` |/ _ \\ |",
			"| . \\  __/ |  | |\\  |  __/ |____ ",
			"|_|\\_\\___|_|  |_| \\_|\\___|______|"		
		};

char msg1[]="version 0.1";
char msg2[]="(c) copyright '6 bytes more',2010";
char msg3[]="witten by nitheeh k l";
char warning[7][38]={"Warning: this is the first release",
		"of the kenel and is under testing.",
		"nothing found here has necessarily",
		"been reviewed by professionals with ",
		"the expertise requierd to provide",
		"you with complete, accurate or",
		"reliable information."
		};

u16int screenattr	= blightgray|fred;
u16int name_attr	= screenattr;
u16int msg_attr		= blightgray|fdarkgray;
u16int warning_attr	= blightgray|fwhite;

	clearscreen();
	set_screenbackground(screenattr);
	
	u8int row,col;
	u8int i;	
	row=2;col=25;

	for(i=0;i<6;i++,row++)
	{
		writestring(row,col,name[i],name_attr);
	}
	
	h_doubleline(row,24,59,warning_attr);

	writestring(11,2,msg1,msg_attr);
	writestring(12,2,msg2,msg_attr);
	writestring(13,2,msg3,msg_attr);
	
	row=16;
	for(i=0;i<7;i++,row++)
		writestring(row,2,warning[i],warning_attr);

	u8int row1,col1,row2,col2;

	row1=11;col1=40;
	row2=23;col2=78;

//	window win_boot;
	char win_boot_title[16]="booting....";
	u16int win_boot_wattr=bblack|fwhite;
	u16int win_boot_battr=bblack|flightgray;
	
	win_init(&win_boot,row1,col1,row2,col2,win_boot_title,win_boot_wattr,win_boot_battr);
	win_create(&win_boot);

}	

/*
void test(void)
{
	window win;
	char name[10]="window";
	clearscreen();
	win_init(&win,1,1,10,40,name,blightgray|fwhite,blightgray|fblack);
	win_create(&win);

	win_putchar(&win,'n');
	win_putchar(&win,'\n');

	int i;
	for(i=0;i<7;i++)
	win_putstring(&win,"testing win_putstring\n");/
	for(i=0;i<4;i++)//
	win_putstring(&win,"new line\n");

}
*/
int main(struct multiboot *mboot_ptr)
{
	welcome();		

	init_descriptor_tables();

	asm volatile("sti");
	
	init_timer(1);

	wait(1);
	win_clear(&win_boot);

	win_putstring(&win_boot,"\ninitializing timer...\t");
	wait(1);
	win_putstring(&win_boot," done");

	win_putstring(&win_boot,"\ninitializing keyboard...\t");
	init_kbd();
	wait(1);
	win_putstring(&win_boot," done");

	win_putstring(&win_boot,"\npress any key to continue...\n");

	u8int s,a;

	kbd_read(&s,&a);

	clearscreen();
	terminal();	
	
	while(1);	
    return 0;

}
