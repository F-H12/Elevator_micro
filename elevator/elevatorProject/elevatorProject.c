/*
 * elevatorProject.c
 *
 * Created: 3/11/2019 11:10:23 PM
 * Author: Hejazi
 */

#include <io.h>
#include <mega16a.h>

int waitNo=0;
int MaxWait=10;

void main()
{
    bit f_1=0;
    bit upf_2=0;
    bit dwnf_2=0;
    bit f_3=0;

    DDRA=0xFF;
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00; 
    PORTA=0x00;
    PORTB=0b11111;
    PORTC=0b111;
    PORTD=0b111111;

    while(1)
    {   
        //buttons
        if (!(PIND & 0b000001)) 
            f_1 = 1;
        if (!(PIND & 0b000010)) 
            f_1 = 1;
        if (!(PIND & 0b000100)) 
            upf_2 = 1;
        if (!(PIND & 0b001000)) 
            dwnf_2 = 1;
        if (!(PIND & 0b010000)) 
            f_3 = 1;
        if (!(PIND & 0b100000)) 
            f_3 = 1;
            
                   
        if (!(PINC & 0b001))
            f_1 = 1;
        if (!(PINC & 0b010))
        {
            upf_2 = 1;
            dwnf_2 = 1;
        }
        if (!(PINC & 0b100))
            f_3 = 1;

        if (~PINC & 0b111 || ~PIND & 0b111111) waitNo = 0;
/*******************************************************************************************/
        //no moving
        if (f_1 && !(PINB & 0b00100) && !(PORTA & 0b01))
        {
            f_1 = 0;
            PORTA = 0;
        }
        else if (upf_2 && !(PINB & 0b01000) && !(PORTA & 0b10))
        {
            upf_2 = 0;
            dwnf_2 = 0;
            PORTA = 0;
        }
        else if (dwnf_2 && !(PINB & 0b01000) && !(PORTA & 0b01)) 
        {
            upf_2 = 0;
            dwnf_2 = 0;
            PORTA = 0;
        }
        else if (f_3 && !(PINB & 0b10000) && !(PORTA & 0b10)) 
        {
            f_3 = 0;
            PORTA = 0;
        }
/*******************************************************************************************/
        //checking weight and moving
        if ((PINB & 0b01)&& !(PINB & 0b10)&& !(PORTA))
        {
            if (!(PINB & 0b00100) && (upf_2 || dwnf_2 || f_3))
            {
                if (waitNo < MaxWait)
                    waitNo++;
                else 
                    PORTA = 0b01;
            }
            else if (!(PINB & 0b01000) && (f_3))
            {
                if (waitNo < MaxWait) 
                    waitNo++;
                else 
                    PORTA = 0b01;
            }
            else if (!(PINB & 0b01000) && (f_1))
            {
                if (waitNo < MaxWait) 
                    waitNo++;
                else 
                    PORTA = 0b10;
            }
            else if (!(PINB & 0b10000) && (f_1 || upf_2 || dwnf_2))
            {
                if (waitNo < MaxWait) 
                    waitNo++;
                else 
                    PORTA = 0b10;
            }
        }
        else waitNo = 0;
    }
}