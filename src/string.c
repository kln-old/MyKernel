#include "string.h"

int strlen(char *s)
{
	int i=0;
	while( s[i++] );
	return i-1;
}

int strcpy(char *d,char *s)
{
	int i=0;
	int j=strlen(s);
//	if( strlen(d) >= j )
	{
		while(i<=j)
		{
			d[i]=s[i];
			i++;
		}
		d[i]='\0';
	}
	return i;
}

int strcmp(char *str1, char *str2)
{
      int i = 0;
      int failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0')
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;

      return failed;
}


// Copy len bytes from src to dest.
void memcpy(u8int *dest, const u8int *src, u32int len)
{
    // TODO: implement this yourself!

   const u8int *sp = (const u8int *)src;
    u8int *dp = (u8int *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(u8int *dest, u8int val, u32int len)
{
    // TODO: implement this yourself!

        u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

char * strsplit(const char *src,const char dl)
{
	char *d;

	
	
}













	
