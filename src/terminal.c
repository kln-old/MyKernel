#include "common.h"
#include "screen.h"
#include "string.h"
#include "timer.h"
#include "kbd.h"

u8int row1=0,col1=0,row2=24,col2=79;

char win_terminal_title[16]="terminal";
u16int win_terminal_wattr=bblack|fwhite;
u16int win_terminal_battr=bblack|flightgray;
window win_terminal;

char prompt[]=":>>";
char buff[256];
u8int cntr=0;

static void terminal_init(void)
{
	win_init(&win_terminal,row1,col1,row2,col2,win_terminal_title,win_terminal_wattr,win_terminal_battr);
	win_create(&win_terminal);
	return;
}


static void clearbuff(void)
{
	u8int i;
	memset(buff,'\0',255);
	cntr=0;
	return;
}
static void analyze(char *cmd)
{
	if( strcmp(cmd,"man")== 0)
		win_putstring(&win_terminal,"\nnow that would be a waste of space, wouldn't it!");

	else if(strcmp(cmd,"clear")==0)
		win_clear_refresh(&win_terminal);
	else if(strcmp(cmd,"strcpy")==0)
		{
			char* source="helloworld";
			char dest[20];
		
			strcpy(dest,source);
			win_putstring(&win_terminal,dest);
			
		}
	else if(strcmp(cmd,"genint")==0){

		asm volatile("int $0x3");
	}
	else
		win_putstring(&win_terminal,"\nto be implemented...");

	clearbuff();

	return; 
}
void display_prompt(void)
{
	win_putchar(&win_terminal,'\n');
	win_putstring(&win_terminal,prompt);
	
}
int terminal(void)
{
	u8int s,a;

	terminal_init();
	display_prompt();

	while(1)
	{

		kbd_read(&s,&a);

		switch(s)
		{
			case _kbd_enter:
					if( (buff[0]!='\0') && (buff!=0) )
					{
						buff[cntr++]='\0';
						analyze(buff);
					}
					display_prompt();
					break;
			case _kbd_space:
					buff[cntr++]='\0';
					break;

			case _kbd_backspace:
					if(cntr>0)
					{
						buff[--cntr]='\0';
						win_putchar(&win_terminal,a);
					}
					break;
			default:
				win_putchar(&win_terminal,a);
				buff[cntr++]=a;		
		}	
	
	}
	
}

