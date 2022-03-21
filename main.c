/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "max7219.h"
#include "hardware/rtc.h"

int main() {
    stdio_init_all(); 
    // Start on Friday 5th of June 2020 15:45:00
    datetime_t t = {
            .year  = 2022,
            .month = 03,
            .day   = 13,
            .dotw  = 0, // 0 is Sunday, so 5 is Friday
            .hour  = 14,
            .min   = 54,
            .sec   = 00
    };

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);

    init();
    MAX7219_Initialize(); 
    while (true) {
        //blink();
        datetime_t tmp;
        rtc_get_datetime(&tmp);

        if( tmp.year != t.year ||
            tmp.month != t.month ||
            tmp.hour != t.hour ||
            tmp.min != t.min ||
            tmp.sec != t.sec ||
            tmp.day != t.day
            )
        {
            t.year = tmp.year;
            t.month = tmp.month;
            t.hour = tmp.hour;
            t.min = tmp.min;
            t.sec = tmp.sec;
            t.dotw = tmp.dotw;
            t.day = tmp.day;

            MAX7219_Write(1, t.sec%10);
            MAX7219_Write(2, t.sec/10);
            MAX7219_Write(3, BCD_HYPHEN);
            MAX7219_Write(4, t.min%10);
            MAX7219_Write(5, t.min/10);
            MAX7219_Write(6, BCD_HYPHEN);
            MAX7219_Write(7, t.hour%10);
            MAX7219_Write(8, t.hour/10);
        }
        else
        {
            blink();
        }
    }
}
