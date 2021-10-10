/*
 * bonfire.c
 *
 * Created: 27.07.2021 9:35:37
 * Author : piro.tex
 */ 


///--- defines
#define F_CPU 1000000UL

#define flame_1 OCR0A
#define flame_2 OCR0B
#define flame_3 OCR1A
#define flame_4 OCR1B
#define flame_5 OCR2A
#define flame_6 OCR2B


///--- includes
#include <avr/io.h>
#include <util/delay.h>


///--- enums
enum flames
{
    // PWM pins
    flame_1_pin     = 6,
    flame_2_pin     = 5,
    flame_3_pin     = 1,
    flame_4_pin     = 2,
    flame_5_pin     = 3,
    flame_6_pin     = 3,
    
    // flames in mass
    flame_1_pos     = 0,
    flame_2_pos     = 1,
    flame_3_pos     = 2,
    flame_4_pos     = 3,
    flame_5_pos     = 4,
    flame_6_pos     = 5,
};


///--- init
void init_PWM(void);
void init_LED(void);


///--- functionts
void flame_pwm(uint8_t flame); // kindle a fire


///--- consts
//const uint8_t flame_max[6] = { 35, 30, 25, 20, 15, 10 };
const uint8_t flame_max[6] = { 50, 40, 30, 20, 10, 8 };


///--- variables
uint8_t flame_val[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // pwm value


///-----------------------------------------------------------------------------
int main(void)
{
    init_PWM();
    init_LED();
    
    uint8_t timer = 0;
    
    while(1)
    {       
        if(timer % 25 == 0)
            flame_pwm(flame_6_pos);
        if(timer % 20 == 0)
            flame_pwm(flame_5_pos);
        if(timer % 17 == 0)
            flame_pwm(flame_4_pos);
        if(timer % 9 == 0)
            flame_pwm(flame_3_pos);
        if(timer % 4 == 0)
            flame_pwm(flame_2_pos);
        if(timer % 20 == 0)
            flame_pwm(flame_1_pos);
        
        
        timer++;
        _delay_ms(1);
    } // while (1)
} // int main(void)
///-----------------------------------------------------------------------------


///--- init
void init_PWM(void)
{
    ///--- TIM0 - fast pwm
    TCCR0A = ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01));
    TCCR0B |= (1 << CS10);
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    TIMSK0 |= 0x00;
    
    ///--- TIM1 - fast pwm
    TCCR1A = ((1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM12));
    TCCR1B |= (1 << CS10);
    TCNT1 = 0x00;
    OCR1A = 0x00;
    OCR1B = 0x00;
    TIMSK1 |= 0x00;
    
    ///--- TIM2 - fast pwm
    TCCR2A = ((1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21));
    TCCR2B |= (1 << CS10);
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    TIMSK2 |= 0x00;
    
    return;
} // void init_PWM(void)

void init_LED(void)
{
    // Ports as out
    DDRD |= ((1 << flame_1_pin) | (1 << flame_2_pin) | (1 << flame_6_pin));
    DDRB |= ((1 << flame_3_pin) | (1 << flame_4_pin) | (1 << flame_5_pin));
    
    // Init ports value
    PORTD &= ~((1 << flame_1_pin) | (1 << flame_2_pin) | (1 << flame_6_pin));
    PORTB &= ~((1 << flame_3_pin) | (1 << flame_4_pin) | (1 << flame_5_pin));
    
    return;
} // void init_LED(void)


///-----------------------------------------------------------------------------
///--- functionts
void flame_pwm(uint8_t flame) // kindle a fire
{
    flame_val[flame]++; // set next pwm value
    if(flame_val[flame] >= flame_max[flame]) // if max pwm
        flame_val[flame] = 0; // set pwm 0
        
    switch(flame)
    {
        case flame_1_pos:
            flame_1 = flame_val[flame]; // set pwm
            break;
        case flame_2_pos:
            flame_2 = flame_val[flame]; // set pwm
            break;
        case flame_3_pos:
            flame_3 = flame_val[flame]; // set pwm
            break;
        case flame_4_pos:
            flame_4 = flame_val[flame]; // set pwm
            break;
        case flame_5_pos:
            flame_5 = flame_val[flame]; // set pwm
            break;
        case flame_6_pos:
            flame_6 = flame_val[flame]; // set pwm
            break;
    } // switch(flame)
    
    return;
} // flame_pwm