#include "screen.h"
#include "stdarg.h"

static short* scr_base=(short*)0xb8000;
static int scr_pos = 0;
static int scr_color = 0x0900;


void init_screen()
{
  scr_base = (short*)(0xb8000 + 0x640);
}


void putc(unsigned char ch)
{
  int i;
  if (ch == '\r')
    return;
  
  if (ch == '\n')
    scr_pos=(scr_pos+80)/80*80;
  else scr_base[scr_pos++]=ch + scr_color;

  if (scr_pos >= 80*25)
  {
    for (i=0; i<80*25; i++)
      scr_base[i]=scr_base[i+80];
    
    for (i=80*24; i<80; i++)
      scr_base[i]=' ' + scr_color;    

    scr_pos -= 80;
  }
}


void putstr(char* str)
{
  while (*str)
  {
    putc(*str);
    str++;
  }
}

void putdec(unsigned int num)
{
  int i=0;
  char buf[10];
  do
  {
    buf[i++]='0'+num%10;
    num /= 10;
  }  while (num);
  do
  {
    putc(buf[--i]);
  } while (i);
}

void puthex(unsigned int num)
{
  int i;
  char buf[10];
  for (i=0; i<8; i++)
  {
    if ( (buf[i]=num&0x0f)>9 )
      buf[i]+=7;
    buf[i]+='0';
    num>>=4;
  }
  i=8;
  do putc(buf[--i]);
  while(i);
}

void putf(const char* str, ...)
{
  va_list ap;
  int arg_int;
  va_start(ap, str);
  while (*str)
  {
    if (*str == '%')
    {
      str++;
      if (*str =='%')
      {
        putc(*str);
      }
      else
      {
        arg_int = va_arg(ap, int);
        switch(*str)
        {
          case 'c': putc(arg_int);
                    break;
          case 's': putstr((char*)arg_int);
                    break;
          case 'u': putdec(arg_int);
                    break;
          case 'x': puthex(arg_int);
                    break;
          default: putc('?');  
        }
      }
    }
    else
    {
      putc(*str);
    }
    str++;
  }
  va_end(ap);
}



