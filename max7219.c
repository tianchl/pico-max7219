#include "max7219.h"
#include "pico/stdlib.h"
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

//发送地址、数据
void MAX7219_Write(unsigned char address,unsigned char dat)
{
    unsigned char i;
    gpio_put(CS_PIN, 0); //拉低片选线，选中器件
    sleep_ms(1);
    //发送地址
    for (i=0;i<8;i++)        //移位循环8次             
    {
       gpio_put(CLK_PIN, 0);        //清零时钟总线
       sleep_ms(1);
       gpio_put(DIN_PIN, (bool)(address&0x80)); //每次取高字节  
       sleep_ms(1);   
       address<<=1;             //左移一位
       sleep_ms(1);
       gpio_put(CLK_PIN, 1);        //时钟上升沿，发送地址
       sleep_ms(1);
    }
    
    //发送数据
    for (i=0;i<8;i++)              
    {
       gpio_put(CLK_PIN, 0);
       sleep_ms(1);
       gpio_put(DIN_PIN, (bool)(dat&0x80)); 
       sleep_ms(1);   
       dat<<=1; 
       sleep_ms(1);
       gpio_put(CLK_PIN, 1);        //时钟上升沿，发送数据
       sleep_ms(1);
    }
    gpio_put(CS_PIN, 1);    //发送结束，上升沿锁存数据 
    sleep_ms(1);                     
}

void MAX7219_Initialize(void)
{
    gpio_init(CS_PIN);
    gpio_set_dir(CS_PIN, GPIO_OUT);

    gpio_init(CLK_PIN);
    gpio_set_dir(CLK_PIN, GPIO_OUT);

    gpio_init(DIN_PIN);
    gpio_set_dir(DIN_PIN, GPIO_OUT);
    
    sleep_ms(10);

    MAX7219_Write(SHUT_DOWN,0x01);         //开启正常工作模式（0xX1）    
    MAX7219_Write(DISPLAY_TEST,0x00);      //选择工作模式（0xX0）
    MAX7219_Write(DECODE_MODE,0xff);       //选用全译码模式
    MAX7219_Write(SCAN_LIMIT,0x07);        //8只LED全用
    MAX7219_Write(INTENSITY,0x02);         //设置初始亮度

    sleep_ms(10);
}

void init()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void blink()
{
    gpio_put(LED_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_PIN, 0);
    sleep_ms(100);
}