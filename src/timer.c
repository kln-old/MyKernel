#include "screen.h"
#include "isr.h"
#include "timer.h"

u32int tick = 0;
int timer_sec=0;
extern window win_boot;

static void timer_callback(registers_t regs)
{
//	win_putstring(&win_boot,"\ntimercallback\n");
	tick++;
	
	if( tick % 18 ==0 ){
	timer_sec++;
//	win_putstring(&win_boot,"tick:");
//	win_printdec(&win_boot,tick);
//	win_putstring(&win_boot,"\t sec:");
//	win_printdec(&win_boot,timer_sec);
//	win_putchar(&win_boot,'\n');
	}
	
}

void init_timer(u32int freq)
{
	register_interrupt_handler(IRQ0, &timer_callback);

/*
//	win_putstring(&win_boot,"\ncalled init_timer\n");
//	win_printdec(&win_boot,(int)freq);
	u32int divisor = 1193180 / freq;
//	win_putchar(&win_boot,'\n');
//	win_printdec(&win_boot,divisor);
		
	outb(0x43, 0x36);//roll back and contiue after completion
	
	u8int l=(u8int )(divisor & 0xff);
	u8int h=(u8int )( (divisor>>8) & 0xff);

	outb(0x40,l);
	outb(0x40,h);
*/

//	timer_callback();
}

void wait(u32int sec)
{
	u32int t;
	
	t=timer_sec + sec;
	while(timer_sec < t);
	
}
