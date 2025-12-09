 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <xc.h>
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

// Morse timing in milliseconds per unit
#define UNIT_MS 100

typedef struct { char c; const char *code; } MorseEntry;

const MorseEntry MORSE_TABLE[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."},{'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."},{'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'0',"-----"}, {'1',".----"}, {'2',"..---"}, {'3',"...--"},
    {'4',"....-"}, {'5',"....."}, {'6',"-...."}, {'7',"--..."}, {'8',"---.."},
    {'9',"----."}
};

const char MSG[] = "HELLO WORLD";

// Morse functions
static void morse_delay(uint8_t units) { while (units--) __delay_ms(UNIT_MS); }

static const char *morse_lookup(char c) {
    if (c >= 'a' && c <= 'z') c -= 32;
    for (uint8_t i=0;i<sizeof(MORSE_TABLE)/sizeof(MorseEntry);i++)
        if (MORSE_TABLE[i].c==c) return MORSE_TABLE[i].code;
    return NULL;
}

static void send_morse_char(const char *pattern) {
    while (*pattern) {
        LED_LAT = 1;
        morse_delay(*pattern=='.'?1:3);
        LED_LAT = 0;
        morse_delay(1); // between symbols
        pattern++;
    }
}

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

// Send string once via UART
    const char *p = MSG;

    while(1) {
        // Morse loop
        p = MSG;
        printf("%s\n", p);
        while(*p) {
            if (*p == ' ') morse_delay(7); // word gap
            else {
                const char *mc = morse_lookup(*p);
                if(mc) { send_morse_char(mc); morse_delay(3); } // letter gap
            }
            p++;
        }
        morse_delay(7); // extra word gap before repeating
    }
}