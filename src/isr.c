//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "isr.h"
#include "screen.h"
#include "timer.h"

isr_t interrupt_handlers[256];	//array of int handlers, for each of 256 intrs

extern window win_boot;

static void die(registers_t regs)
{

	window win_isr;
	char win_isr_title[15]="intr-hndlr";
	u8int row1,col1,row2,col2;
	row1=4;col1=10;
	row2=20;col2=70;

	win_init(&win_isr,row1,col1,row2,col2,win_isr_title,bblack|fred,bblack|fwhite);
	win_create(&win_isr);

	win_putstring(&win_isr,"interrupt:\t");
	win_printhex(&win_isr,regs.int_no);
	win_putstring(&win_isr,"\nerror code:\t");
	win_printhex(&win_isr,regs.err_code);
	win_putstring(&win_isr,"\nds:\t");
	win_printhex(&win_isr,regs.ds);
	win_putstring(&win_isr,"\nedi:\t");
	win_printhex(&win_isr,regs.edi);
	win_putstring(&win_isr,"\nesi:\t");
	win_printhex(&win_isr,regs.esi);
	win_putstring(&win_isr,"\nebp:\t");
	win_printhex(&win_isr,regs.ebp);
	win_putstring(&win_isr,"\nesp:\t");
	win_printhex(&win_isr,regs.esp);
	win_putstring(&win_isr,"\necx:\t");
	win_printhex(&win_isr,regs.ecx);
	win_putstring(&win_isr,"\nedx:\t");
	win_printhex(&win_isr,regs.edx);
	win_putstring(&win_isr,"\nebx:\t");
	win_printhex(&win_isr,regs.ebx);
	win_putstring(&win_isr,"\neax:\t");
	win_printhex(&win_isr,regs.eax);
	
	win_putstring(&win_isr,"\n");
}

void register_interrupt_handler(u8int intr, isr_t handler)
{
	win_putstring(&win_boot,"\nregisteting ");
	win_printdec(&win_boot,(int )intr);
	interrupt_handlers[intr]=handler;
}

void register_intrhandler(void)
{
	u8int i=0;

	//temporarily set all the handler to die
	for(i=0;i<0x20;i++)
		register_interrupt_handler(i,&die);
	
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
	if( interrupt_handlers[regs.int_no] != 0)//if a handler is defined
	{
		isr_t handler=interrupt_handlers[regs.int_no];
		handler(regs);//call it
	}
	else
	{
		win_putstring(&win_boot,"\nintr unhandled\n");
	}
}

void irq_handler(registers_t regs)
{
	//send eoi(end of interrupt) signal to pic
	
	if(regs.int_no >= 40 )		//if interrupt invloves slave
	{
		outb(0xA0, 0x20);	//send reset signal to slave
//		win_putstring(&win_boot,"\nsent eoi to slave\n");
	}
	outb(0x20, 0x20);
//	win_putstring(&win_boot,"\nsent eoi to master\n");

	if(interrupt_handlers[regs.int_no]!=0)	//if and handler is definde
	{			
		isr_t handler=interrupt_handlers[regs.int_no];
		handler(regs);//call it
	}
	else
	{
		win_putstring(&win_boot,"\nirq unhandled\n");
	}
}

