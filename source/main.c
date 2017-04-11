#include "gpio.h"
#include "system_timer.h"
#include "uart.h"
#include "debug.h"

#define checkBit(bit, loopWXYZ) ((loopWXYZ & (1 << bit)) == 0 )

void blink_once()
{
    // Turn on GPIO 24
    gpio[GPSET0] |= 1 << 24;

    timer_delay_ms(500);

    // Turn off GPIO 24
    gpio[GPCLR0] |= 1 << 24;

    timer_delay_ms(500);
}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        blink_once();
    }

    // Only delay 4 seconds, since we delay for 1 additional
    // second in blink_once().
    timer_delay_ms(4500);
}

void part_1(){

    put_string("w  x  y  z | f | g\r\n------------------\r\n");

    for(uint32_t loopWXYZ = 0; loopWXYZ <= 15; loopWXYZ++){

        uint32_t w = checkBit(3, loopWXYZ);
        uint32_t x = checkBit(2, loopWXYZ);
        uint32_t y = checkBit(1, loopWXYZ);
        uint32_t z = checkBit(0, loopWXYZ);

        uint32_t f = ( (!w && !x && !y && !z) || 
                (!w && !x && y && !z) || 
                (!w && x && !y && !z) || 
                (!w && x && y && z) || 
                (!w && x && y && !z) || 
                (w && x && !y && z) || 
                (w && x && y && z) || 
                (w && x && y && !z) || 
                (w && !x && !y && z) );

        uint32_t g = ( (w && !y && z) || (x && y) || (!w && !z) );

        char wbuf;
        char xbuf;
        char ybuf;
        char zbuf;
        char fbuf;
        char gbuf;

        char* wchar = to_decimal_str(w, &wbuf);
        char* xchar = to_decimal_str(x, &xbuf);
        char* ychar = to_decimal_str(y, &ybuf);
        char* zchar = to_decimal_str(z, &zbuf);
        char* fchar = to_decimal_str(f, &fbuf);
        char* gchar = to_decimal_str(g, &gbuf);


        put_char(*wchar);
        put_string("  ");
        put_char(*xchar);
        put_string("  ");
        put_char(*ychar);
        put_string("  ");
        put_char(*zchar);
        put_string(" | ");
        put_char(*fchar);
        put_string(" | ");
        put_char(*gchar);
        put_string("\r\n\n");
        
    }
}

void part_2(){

    put_string("a  b  c  d | R1 | R2\r\n--------------------\r\n");

    for(uint32_t loopWXYZ = 0; loopWXYZ <= 15; loopWXYZ++){

        uint32_t w = checkBit(3, loopWXYZ);
        uint32_t x = checkBit(2, loopWXYZ);
        uint32_t y = checkBit(1, loopWXYZ);
        uint32_t z = checkBit(0, loopWXYZ);

        uint32_t f = ( (!x && !z) || (!w && y && !z) || (x && y) );

        uint32_t g = ( !z );

        char wbuf;
        char xbuf;
        char ybuf;
        char zbuf;
        char fbuf;
        char gbuf;

        char* wchar = to_decimal_str(w, &wbuf);
        char* xchar = to_decimal_str(x, &xbuf);
        char* ychar = to_decimal_str(y, &ybuf);
        char* zchar = to_decimal_str(z, &zbuf);
        char* fchar = to_decimal_str(f, &fbuf);
        char* gchar = to_decimal_str(g, &gbuf);


        put_char(*wchar);
        put_string("  ");
        put_char(*xchar);
        put_string("  ");
        put_char(*ychar);
        put_string("  ");
        put_char(*zchar);
        put_string(" | ");
        put_char(*fchar);
        put_string(" | ");
        put_char(*gchar);
        put_string("\r\n\n");
        
    }
}

void part_3(){

    put_string("a  b  c  d | R3 | R4\r\n--------------------\r\n");

    for(uint32_t loopWXYZ = 0; loopWXYZ <= 15; loopWXYZ++){

        uint32_t w = checkBit(3, loopWXYZ);
        uint32_t x = checkBit(2, loopWXYZ);
        uint32_t y = checkBit(1, loopWXYZ);
        uint32_t z = checkBit(0, loopWXYZ);

        uint32_t f = ( (!x && !z) || (!w && y) );

        uint32_t g = ( (!x && !z) || (!w && y && !z) || (w && !y && z));

        char wbuf;
        char xbuf;
        char ybuf;
        char zbuf;
        char fbuf;
        char gbuf;

        char* wchar = to_decimal_str(w, &wbuf);
        char* xchar = to_decimal_str(x, &xbuf);
        char* ychar = to_decimal_str(y, &ybuf);
        char* zchar = to_decimal_str(z, &zbuf);
        char* fchar = to_decimal_str(f, &fbuf);
        char* gchar = to_decimal_str(g, &gbuf);


        put_char(*wchar);
        put_string("  ");
        put_char(*xchar);
        put_string("  ");
        put_char(*ychar);
        put_string("  ");
        put_char(*zchar);
        put_string(" | ");
        put_char(*fchar);
        put_string(" | ");
        put_char(*gchar);
        put_string("\r\n\n");
        
    }
}

char request_input(){
    put_string("Input 1 to view Pre-Lab Kmap.\r\nInput 2 to view SoP1 and SoP2\r\n\n");

    char buf;

    size_t inputSize = get_string(&buf, 80);
    return buf;
}

void welcome(){
    put_string("Welcome to SoP Kmap analyzer.\r\n");
}

void invalid_entry(){
    put_string("Invalid input.\r\n");
}

int main()
{
    // Implement Lab 4 as described in the lab manual

    init_uart();

    welcome();

    char inputChar;

    while(1){
        inputChar = request_input();
        put_string("\n-------------------\r\n");

        if( inputChar == '1'){

            part_1();
        
        } else if( inputChar == '2'){

            part_2();
            put_string("--------------------\r\n\n\n");
            part_3();
        
        } else {
            invalid_entry();
        }

    }
    
    return 0;
}
