#ifndef __SCREEN_H
#define __SCREEN_H


void init_screen(void);
void putc(unsigned char ch);
void putstr(char* str);
void putdec(unsigned int num);
void puthex(unsigned int num);
void putf(const char* str, ...);

#endif
