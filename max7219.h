
#ifndef _MAX7219_H
#define _MAX7219_H

#include "pico/types.h"

#define CS_PIN (5)
#define DIN_PIN (3)
#define CLK_PIN (2)

#define DECODE_MODE  0x09   //译码控制寄存器
#define INTENSITY    0x0A   //亮度控制寄存器
#define SCAN_LIMIT   0x0B   //扫描界限寄存器
#define SHUT_DOWN    0x0C   //关断模式寄存器
#define DISPLAY_TEST 0x0F   //测试控制寄存器

#define BCD_HYPHEN   (10)   //BDC '-'


extern void MAX7219_Write(unsigned char address,unsigned char dat);

extern void MAX7219_Initialize(void);

extern const uint LED_PIN;

extern void blink();
extern void init();

#endif // _MAX7219_H