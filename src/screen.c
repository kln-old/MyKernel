#include "screen.h"
#include "string.h"

u16int *video_memory = (u16int *)0xb8000;

/*
u8int cursor_row=0;
u8int cursor_col=0;*/
u16int screen_attr= bblack|fwhite;


void writechar(u8int row, u8int col, char c, u16int attr)
{
	u16int *location;

	location = video_memory + (row * 80 + col);
	*location= ( attr << 8 ) | c;

	return;
}

void writestring(u8int row, u8int col, char *s, u16int attr)
{
	u16int i=0;
	u16int *location;

	while( s[i] )
	{
		location = video_memory + ( row * 80 + col );
		*location = ( attr << 8 ) | s[i++];

		col++;
		if(col >= 80)break;		
	}	
}

void set_screenbackground(u16int attr)
{
	u8int row,col;
	char c=' ';

	for( row=0; row < 25 ;row++ )
		for( col=0; col < 80 ; col++ )
			writechar(row,col,c,attr);

	return;
}

void clearscreen(void)
{
	set_screenbackground(bblack|fblack);

	return;
}

void move_cursor(u8int row, u8int col)
{
	u16int cursorloc=row*80+col;
	outb(0x3d4,14);
	outb(0x3d5,cursorloc>>8);
	outb(0x3d4,15);
	outb(0x3d5,cursorloc);	

//	cursor_row=row;
//	cursor_col=col;
}
	
/*
void scroll_screen(void)
{
	if( cursor_row >= 25)
	{
		u8int x,y;
		//move everty thing one line up
		for(y=1;y<25;y++)
		{
			for(x=0;x<80;x++)
			{
				*(video_memory+ ( (y-1)*80 + x ) ) = *(video_memory + (y*80 + x));  
			}
		}

		//rite a blank line
		for(x=0,y=24;x<80;x++)
		{
			writechar(y,x,' ',screen_attr);
		}
	
		cursor_col=0;
		cursor_row=24;
	}
}
*/
void h_doubleline(u8int row,u8int col1,u8int col2,u16int attr)
{
	if(col2>col1 && col2<80 && row<25)
	{
		u16int *loc;
		u8int i;

		loc=video_memory +( (row * 80)+col1 );
	
		for(i=0;i<(col2-col1);i++)
		{
			*loc=(attr << 8) | (0xcd);
			loc++;
		}
	}
}



static void scroll_up(u8int row1,u8int col1,u8int row2,u8int col2,u16int attr)
{
	if( row2>row1 && col2>col1 && row1>=0 && row2<25 && col1>=0 && col2<80)
//	if( row2>row1 && col2>col1)
	{
		u8int row,col;
		u16int *loc;

		//move everty thing one line up
		for(row=row1;row<row2;row++)
		{
			for(col=col1;col<=col2;col++)
			{
				loc= video_memory+ (row*80 + col);
				*loc=*(video_memory + ( (row+1)*80 + col) );
			}
		}

		//write a blank line
		loc=video_memory+(row2*80 + col1);
		for(col=0;col<=col2-col1;col++)
		{
			*loc=(attr << 8)|' ';
			loc++;
		}
	
	}
		
}

static void create_window(u8int row1,u8int col1,u8int row2,u8int col2,char *title,u16int w_attr,u16int b_attr)
{
	u8int row,col;
	u16int *loc;

	//draw layer
	for(row=row1;row<=row2;row++)
	{
		for(col=col1;col<=col2;col++)
		{
			loc=video_memory+(row*80 + col);
			*loc=(w_attr << 8)| ' ';
		}
	}

	//left 
	loc=video_memory+(row1*80 + col1);
	for(row=0;row<=row2-row1;row++)
	{
		*loc=(b_attr << 8)| (0xb3);
		loc=loc+80;
	}

	//bottom 
	loc=video_memory +( (row2 * 80)+col1 );
	for(col=0;col<=(col2-col1);col++)
    {
    	*loc=(b_attr << 8) | (0xc4);
        loc++;
    }	

	//right		
	loc=video_memory+(row1*80 + col2);
	for(row=0;row<=row2-row1;row++)
	{
		*loc=(b_attr << 8)| (0xb3);
		loc=loc+80;
	}
	
	//top
	loc=video_memory +( (row1 * 80)+col1 );
    	for(col=0;col<=(col2-col1);col++)
    	{
        	*loc=(b_attr << 8) | (0xc4);
        	loc++;
    	}

	if( title )
	{
		col=( ((col2+col1)/2) - (strlen(title)/2) -1 );
	
		loc=video_memory+(row1*80 + col);
		*loc=(b_attr << 8)|(0xb3);

		u16int attr;
		u8int i=0;
		attr=((w_attr & 0x0f)|(b_attr & 0xf0)); 
	
		loc++;

		while(title[i])
		{
			*loc=(attr << 8)|title[i++];
			loc++;
		}

		*loc=(b_attr << 8)|(0xb3);

		loc=video_memory+(row1*80 + col1);
		*loc=(b_attr << 8 )|(0xda);
		loc=loc+(col2-col1);
		*loc=(b_attr << 8)|(0xbf);
		loc=loc+((row2-row1)*80);
		*loc=(b_attr << 8)|(0xd9);
		loc=loc-(col2-col1);
		*loc=(b_attr << 8)|(0xc0);
	}

}

void win_init(window *win,u8int row1,u8int col1,u8int row2,u8int col2,char *s,u16int w,u16int b)
{
	win->row1=row1;win->col1=col1;
	win->row2=row2;win->col2=col2;
	strcpy(win->title,s);
	win->w_attr=(u16int)(w & 0x00ff);
	win->b_attr=(u16int)(b & 0x00ff);

	win->cursor_row=row1+1;
	win->cursor_col=col1+1;
}

void win_create(window *win)
{
	if( (win->row2 > win->row1) && (win->col2 > win->col1) )
	{
		create_window(	win->row1,win->col1,
				win->row2,win->col2,
				win->title,
				win->w_attr,win->b_attr
			     );
	}
	move_cursor(win->cursor_row,win->cursor_col);	
}

void win_scroll_up(window *win)
{
	if(win->cursor_row >= win->row2)
	{
		scroll_up(win->row1+1,win->col1+1,win->row2-1,win->col2-1,win->w_attr);
		win->cursor_row=win->row2 - 1;
		win->cursor_col=win->col1+1;
	}
}

void win_clear(window *win)
{
	u8int row,col;
	u16int *loc;

	for(row=win->row1+1; row < win->row2 ; row++)
	for(col=win->col1+1; col < win->col2 ; col++)
	{
		loc=video_memory + (row*80 + col);
		*loc=(win->w_attr << 8)|' ';
	}

}

void win_clear_refresh(window *win)
{
	win_clear(win);
	win->cursor_row=win->row1+1;
	win->cursor_col=win->col1+1;	
	move_cursor(win->cursor_row,win->cursor_col);
}

void win_putchar(window *win,char c)
{
	u16int *loc;

	if ( c == _backspace && win->cursor_col > (win->col1 + 1) )
	{
		win->cursor_col--;	
		loc = video_memory + ( (win->cursor_row *80)+ win->cursor_col);
		*loc= (win->w_attr << 8) | ' ';
	}
	else if( c==h_tab )
		win->cursor_col=(win->cursor_col + tabstop) & ~(tabstop-1);
	else if(c==carriageret)
		win->cursor_col=win->col1+1;
	else if(c==linefeed)
		{ win->cursor_col=win->col1+1;(win->cursor_row)++; }
	else if (c >= ' ')
	{
		loc = video_memory + ( (win->cursor_row *80)+ win->cursor_col);
		*loc= (win->w_attr << 8) | c;

		win->cursor_col=win->cursor_col + 1;
	}
	
	if( win->cursor_col >= win->col2 )
	{
		win->cursor_col = win->col1 + 1;
		win->cursor_row = win->cursor_row + 1;
	}
		
	win_scroll_up(win);
	move_cursor(win->cursor_row,win->cursor_col);
		
}

void win_putstring(window *win,char *s)
{
	u8int i=0;

	while( s[i] )
	{
		win_putchar(win,s[i++]);
	}
}

void win_printhex(window *win,u32int n)
{
    s32int tmp;

    win_putstring(win,"0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            win_putchar(win,tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            win_putchar(win, tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
       	win_putchar (win,tmp-0xA+'a');
    }
    else
    {
        win_putchar (win,tmp+'0');
    }

}

void win_printdec(window *win,u32int n)
{

    if (n == 0)
    {
        win_putchar(win,'0');
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    win_putstring(win,c2);
}



