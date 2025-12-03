#include <xc.h>
#include <stdlib.h>
#include <time.h>

#define led0 LATAbits.LATA0
#define led1 LATAbits.LATA1
#define led2 LATAbits.LATA2
#define led3 LATAbits.LATA3
#define led4 LATAbits.LATA4
#define led5 LATAbits.LATA5
#define led6 LATAbits.LATA6
#define led7 LATAbits.LATA7

#define switch0 PORTFbits.RF3
#define switch1 PORTFbits.RF5
#define switch2 PORTFbits.RF4
#define switch3 PORTDbits.RD15
#define switch4 PORTDbits.RD14
#define switch5 PORTBbits.RB11
#define switch6 PORTBbits.RB10
#define switch7 PORTBbits.RB9

#define BTNUP PORTBbits.RB1
#define BTNDWN PORTAbits.RA15
#define BTNCTR PORTFbits.RF0
#define BTNLFT PORTBbits.RB0
#define BTNRGT PORTBbits.RB8

#define AN0 LATBbits.LATB12 
#define AN1 LATBbits.LATB13
#define AN2 LATAbits.LATA9
#define AN3 LATAbits.LATA10

#define CA LATGbits.LATG12
#define CB LATAbits.LATA14
#define CC LATDbits.LATD6
#define CD LATGbits.LATG13
#define CE LATGbits.LATG15
#define CF LATDbits.LATD7
#define CG LATDbits.LATD13
#define DP LATGbits.LATG14

#define RGB_R LATDbits.LATD2
#define RGB_G LATDbits.LATD12
#define RGB_B LATDbits.LATD3
#define DELAY4 700 //perfect amount of delay for displaying 4 digits

#define ldata LATE
#define rs PORTBbits.RB15
#define rw PORTDbits.RD5
#define en PORTDbits.RD4

void delay(unsigned int ms) { //delay function from online forum
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1400; j++) { 
              
        }
    }
}

void display_number(int digit, int anode) {
    AN3 = 1;
    AN2 = 1;
    AN1 = 1;
    AN0 = 1;
    switch (anode) { //select anode
        case 0:
            AN3 = 1;
            AN2 = 1;
            AN1 = 1;
            AN0 = 0;
            break;
        case 1:
            AN3 = 1;
            AN2 = 1;
            AN1 = 0;
            AN0 = 1;
            break;
        case 2:
            AN3 = 1;
            AN2 = 0;
            AN1 = 1;
            AN0 = 1;
            break;
        case 3:
            AN3 = 0;
            AN2 = 1;
            AN1 = 1;
            AN0 = 1;
            break;   
    }
    
    switch (digit) { //select digit
        case 0:
            CA = 0; 
            CB = 0;
            CC = 0;
            CD = 0;
            CE = 0;
            CF = 0;
            CG = 1;
            DP = 1;
            return;
        case 1:
            CA = 1;
            CB = 0;
            CC = 0;
            CD = 1;
            CE = 1;
            CF = 1;
            CG = 1;
            DP = 1;
            return;
        case 2:
            CA = 0;
            CB = 0;
            CC = 1;
            CD = 0;
            CE = 0;
            CF = 1;
            CG = 0;
            DP = 1;
            return;
        case 3:
            CA = 0;
            CB = 0;
            CC = 0;
            CD = 0;
            CE = 1;
            CF = 1;
            CG = 0;
            DP = 1;
            return;
        case 4:
            CA = 1;
            CB = 0;
            CC = 0;
            CD = 1;
            CE = 1;
            CF = 0;
            CG = 0;
            DP = 1;
            return;
        case 5:
            CA = 0;
            CB = 1;
            CC = 0;
            CD = 0;
            CE = 1;
            CF = 0;
            CG = 0;
            DP = 1;
            return;
        case 6:
            CA = 0;
            CB = 1;
            CC = 0;
            CD = 0;
            CE = 0;
            CF = 0;
            CG = 0;
            DP = 1;
            return;
        case 7:
            CA = 0;
            CB = 0;
            CC = 0;
            CD = 1;
            CE = 1;
            CF = 1;
            CG = 1;
            DP = 1;
            return;
        case 8:
            CA = 0;
            CB = 0;
            CC = 0;
            CD = 0;
            CE = 0;
            CF = 0;
            CG = 0;
            DP = 1;
            return;
        case 9:
            CA = 0;
            CB = 0;
            CC = 0;
            CD = 0;
            CE = 1;
            CF = 0;
            CG = 0;
            DP = 1;
            return;
        default:
            CA = 1;
            CB = 1;
            CC = 1;
            CD = 1;
            CE = 1;
            CF = 1;
            CG = 1;
            DP = 1;
    }   
        
}

void display_complex(int number) { //display function that always displays 4 numbers
    if (number > 9999) { //9999 is max number on 7 seg with 4 anodes
        number = 9999;
    }
    if (number < 0) { //border case
        number = 0;
    }
    int numberOG = number; //save for later
    int digits[4];
    int divisor = 1000;
    for (int i = 0; i < 4; i++) { //break number down into digits and put in array
        digits[i] = number / divisor;
        number = number % divisor;
        divisor = divisor / 10;
    }
    if (numberOG < 1000) { //if number is less than certain number, make it 99 which activates the default case in display_number()
        digits[0] = 99;
    } 
    if (numberOG < 100) {
        digits[1] = 99;
    }
    if (numberOG < 10) {
        digits[2] = 99;
    }
    for (int i = 0; i < DELAY4; i++) { //display each number and clear it with display_number(99) afterwards
        display_number(digits[0], 3);
        display_number(99, 3);
        display_number(digits[1], 2);
        display_number(99, 2);
        display_number(digits[2], 1);
        display_number(99, 1);
        display_number(digits[3], 0); 
        display_number(99, 0);
    }   
}

void pwm(int duty_r, int duty_g, int duty_b) {
    if (duty_r != 0) { //if duty isnt 0, RGB LED turns on
        RGB_R = 1;
    }
    if (duty_g != 0) {
        RGB_G = 1;
    }
    if (duty_b != 0) {
        RGB_B = 1;
    }
    int cycle = 100; //using 100 as the cycle means you dont have to modify the given duty
    for (int i = 0; i <= cycle; i++) {
        if (i >= duty_r) { //turn off after duty is completed
            RGB_R = 0;
        }
        if (i >= duty_g){
            RGB_G = 0;
        }
        if (i >= duty_b) {
            RGB_B = 0;
        }
    }
}

void MSDelay(unsigned int itime) { //delay function from professor for LCD
    unsigned int i, j;
    for (i = 0; i < itime; i++) {
        for (j = 0; j < 135; j++) {
            
        }
    }
}
void lcdcmd(int value) { //give a command to the LCD
    ldata = value;
    rs = 0;
    rw = 0;
    en = 1;
    MSDelay(1);
    en = 0;
}

void lcddata(unsigned char value) { //write data to the LCD
    ldata = value;
    rs = 1;
    rw = 0;
    en = 1;
    MSDelay(1);
    en = 0;
}

void write_lcd(unsigned char input[16], int line, int start) { //write the given array to a line
    int line_hex;
    int start_hex;
    int start_position;

    if (line == 2) { //line 2 starts at 0x40 in memory
        line_hex = 0x40;
    } else {
        line_hex = 0x00; //default to line 1
    }
    if (start < 1 || start > 16) { //border cases
        start = 1;
    }
    start_hex = start - 1; //start positions begin at 1
    start_position = line_hex + start_hex + 0x80; //0x80 is the bit needed for the position command
    lcdcmd(start_position); //set start
    MSDelay(15);
    int i = 0;
    while (input[i] >= 0x20 && input[i] <= 0x7E && i < 16) { //input between '!' and '~' and not out of the array bounds
        lcddata(input[i]);
        MSDelay(15);
        i++;
    }
}

void clear_lcd(void) { //simple clear LCD function
    lcdcmd(0x1);
    MSDelay(15);
}

int randomize_key() { //rand parameters make sure the key has 4 digits
    return (rand() % (9999-1111 + 1)) + 1111;
}

int randomize_n() { //n value not known to the user
    return (rand() % (8-0 + 1)) + 0;
}

void xor(int input[8], int modifier[8]) {
    for (int i = 0; i < 8; i++) {
        input[i] ^= modifier[i];
    }

}

void mix_bits(int input[8]) {
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i];
    }
    input[0] = temp[3];
    input[1] = temp[6];
    input[2] = temp[4];
    input[3] = temp[0];
    input[4] = temp[7];
    input[5] = temp[1];
    input[6] = temp[5];
    input[7] = temp[2];
}

void swap(int input[8]) { //swap left 4 bits with right 4 bits
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i];
    }
    for (int i = 0; i < 4; i++) {
        input[i + 4] = temp[i];
        input[i] = temp[i + 4];
    }
}

void rotate_right(int input[8], int n) { //round rotation with n value not known to user 
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i];
    }
    for (int i = 0; i < 8; i++) {
        input[i] = temp[(i - n + 8) % 8];
    }
}

void rotate_left(int input[8], int n) { //same as rotate right but opposite
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i];
    }
    for (int i = 0; i < 8; i++) {
        input[i] = temp[(i + n) % 8];
    }
}

void inv_mix_bits(int input[8]) { //reverses mix_bits()
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i];
    }
    input[0] = temp[3];
    input[1] = temp[5];
    input[2] = temp[7];
    input[3] = temp[0];
    input[4] = temp[2];
    input[5] = temp[6];
    input[6] = temp[1];
    input[7] = temp[4];
}

void key_format(int key, int key_left[8], int key_right[8]) { //formats the 16-bit (4 decimal digit) key into 2 8-bit arrays
    int temp_key = key;
    int divisor = 1000;
    int key_digits[4];
    for (int i = 0; i < 4; i++) {
        key_digits[i] = temp_key / divisor;
        temp_key %= divisor;
        divisor /= 10;
    }

    for (int i = 0; i < 2; i++) {
        divisor = 8;
        for (int j = 0; j < 4; j++) {
            key_left[j + (4 * i)] = key_digits[i] / divisor;
            key_digits[i] %= divisor;
            key_right[j + (4 * i)] = key_digits[i + 2] / divisor;
            key_digits[i + 2] %= divisor;
            divisor /= 2;
        }
    }
}

void encrypt(int input[8], int key, int n) {
    int key_right[8];
    int key_left[8];
    int constant_xor[8] = {1, 0, 1, 0, 1, 0, 1, 0};
    key_format(key, key_left, key_right);
    swap(input);
    xor(input, key_right);
    rotate_right(input, n);         
    xor(input, key_left);
    mix_bits(input); 
    xor(input, constant_xor);
}

void decrypt(int input[8], int key, int n) {
    int key_right[8];
    int key_left[8];
    int constant_xor[8] = {1, 0, 1, 0, 1, 0, 1, 0};
    key_format(key, key_left, key_right);
    xor(input, constant_xor);
    inv_mix_bits(input); 
    xor(input, key_left);           
    rotate_left(input, n);
    xor(input, key_right);
    swap(input);
}

void display_result(int input[8]) {
    led0 = input[7];
    led1 = input[6];
    led2 = input[5];
    led3 = input[4];
    led4 = input[3];
    led5 = input[2];
    led6 = input[1];
    led7 = input[0];
}

void set_input(int input[8]) {
    input[0] = switch7;
    input[1] = switch6;
    input[2] = switch5;
    input[3] = switch4;
    input[4] = switch3;
    input[5] = switch2;
    input[6] = switch1;
    input[7] = switch0;
}

void display_welcome() { //simple idle display message
    unsigned char welcome[16] = {'R', 'O', 'W', 'A', 'N', 0x27, 'S', ' ', 'A', 'W', 'E', 'S', 'O', 'M', 'E'};
    unsigned char welcome2[16] = {'E', 'N', 'C', 'R', 'Y', 'P', 'T', 'E', 'R'};
    clear_lcd();
    write_lcd(welcome, 1, 1);
    write_lcd(welcome2, 2, 4);
}

void setup() { //all input and output configurations
    DDPCONbits.JTAGEN = 0;
    
    TRISAbits.TRISA0 = 0; //LED as output
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;

    TRISFbits.TRISF3 = 1; //Switch 0-7 as input (minus 3 and 4)
    TRISFbits.TRISF5 = 1; 
    TRISFbits.TRISF4 = 1; 
    TRISBbits.TRISB11 = 1; 
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB9 = 1;

    ANSELBbits.ANSB11 = 0; //Switch 5-7 analog disable
    ANSELBbits.ANSB10 = 0;
    ANSELBbits.ANSB9 = 0;

    TRISBbits.TRISB12 = 0; //Seven-segment as output
    TRISBbits.TRISB13 = 0;
    TRISAbits.TRISA9 = 0;
    TRISAbits.TRISA10 = 0;
    TRISGbits.TRISG12 = 0; 
    TRISAbits.TRISA14 = 0; 
    TRISDbits.TRISD6 = 0; 
    TRISGbits.TRISG13 = 0; 
    TRISGbits.TRISG15 = 0; 
    TRISDbits.TRISD7 = 0; 
    TRISDbits.TRISD13 = 0; 
    TRISGbits.TRISG14 = 0;        

    ANSELBbits.ANSB12 = 0; //Seven-segment analog disable     
    ANSELBbits.ANSB13 = 0;

    TRISDbits.TRISD2 = 0; //RGB LEDs as output;                
    TRISDbits.TRISD12 = 0;
    TRISDbits.TRISD3 = 0;

    TRISBbits.TRISB1 = 1; //Buttons as input
    TRISBbits.TRISB0 = 1;
    TRISFbits.TRISF4 = 1;
    TRISBbits.TRISB8 = 1;
    TRISAbits.TRISA15 = 1;

    ANSELBbits.ANSB1 = 0; //Buttons Up, Left, and Right disabled analog        
    ANSELBbits.ANSB0 = 0;               
    ANSELBbits.ANSB8 = 0;

    ANSELBbits.ANSB15 = 0;
    TRISBbits.TRISB15 = 0;
    ANSELBbits.ANSB15 = 0;

    AN0 = 1; //seven-segment set off
    AN1 = 1;
    AN2 = 1;
    AN3 = 1;
    
    led0 = 0; //all LEDs set off
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;
    led7 = 0;
    
    TRISD = 0;  //LCD configuration
    TRISE = 0;
    en = 0;
    MSDelay(250);
    
    lcdcmd(0x3C); //set display type
    MSDelay(250);
    
    lcdcmd(0x0E); //set display mode
    MSDelay(15);
    
    lcdcmd(0x1); //clear display
    MSDelay(15);
    
    lcdcmd(0x06); //cursor movement
    MSDelay(15);
    
    TRISDbits.TRISD15 = 1; //switch 3 and 4 as input
    TRISDbits.TRISD14 = 1; 
}

void main(void) {
    setup(); //setup inputs and outputs and LCD configuration
    int mode = 0; //initialize variables
    int key = 0;
    int n = 0;
    int input[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char key_random[16] = {'K', 'E', 'Y', ' ', 'R', 'A', 'N', 'D', 'O', 'M', 'I', 'Z', 'E', 'D', '!'}; // user message definitions
    unsigned char encr[16] = {'E', 'N', 'C', 'R', 'Y', 'P', 'T', 'I', 'O', 'N'};
    unsigned char decr[16] = {'D', 'E', 'C', 'R', 'Y', 'P', 'T', 'I', 'O', 'N'};
    unsigned char comp[16] = {'C', 'O', 'M', 'P', 'L', 'E', 'T', 'E', 'D', '!'};
    unsigned char mode_change[16] = {'C', 'H', 'A', 'N', 'G', 'I', 'N', 'G', ' ', 'M', 'O', 'D', 'E', '.', '.', '.'};
    unsigned char key_show[16] = {'S', 'H', 'O', 'W', 'I', 'N', 'G', ' ', 'K', 'E', 'Y', '.', '.', '.'};
    unsigned char input_set[16] = {'S', 'E', 'T', 'T', 'I', 'N', 'G', ' ', 'I', 'N', 'P', 'U', 'T', '.', '.', '.'};
    unsigned char changed[16] = {'M', 'O', 'D', 'E', ' ', 'C', 'H', 'A', 'N', 'G', 'E', 'D', '!'};
    unsigned char mode_e[16] = {'M', 'O', 'D', 'E', ':', 'E', 'N', 'C', 'R', 'Y', 'P', 'T', 'I', 'O', 'N'};
    unsigned char mode_d[16] = {'M', 'O', 'D', 'E', ':', 'D', 'E', 'C', 'R', 'Y', 'P', 'T', 'I', 'O', 'N'};
    unsigned char encr_progress[16] = {'E', 'N', 'C', 'R', 'Y', 'P', 'T', 'I', 'N', 'G', '.', '.', '.'};
    unsigned char decr_progress[16] = {'D', 'E', 'C', 'R', 'Y', 'P', 'T', 'I', 'N', 'G', '.', '.', '.'};
    display_welcome();
    srand(time(NULL)); //seed the randomizer with the time 
    for (int i = 0; i < 10; i++) {
        key = randomize_key(); //randomize the key and the secret "n" for extra protection against psuedo-randomness
        n = randomize_n();
    }

    while (1) {            
        if (BTNDWN == 1) { //pressing button down displays the mode with the RGB and the encryption key for a short time
            clear_lcd();
            if (mode == 0) { //encrypt is red and decrypt is blue
                write_lcd(mode_e, 1, 1);
                for (int i = 0; i < 200; i++) {
                    pwm(i / 2, 0, 0);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(i / 2, 0, 0);
                }
            } else {
                write_lcd(mode_d, 1, 1);
                for (int i = 0; i < 200; i++) {
                    pwm(0, 0, i / 2);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(0, 0, i / 2);
                }
            }
            
            write_lcd(key_show, 2, 1);
            delay(35);
            display_complex(key); 
            set_input(input); //Button down also sets the input
            delay(25);
            write_lcd(input_set, 2, 1);
            delay(10);
            display_result(input); //display given input
            delay(70);
            display_welcome();
        }

        if (BTNUP == 1) { //pressing the up button displays the current key, randomizes it, then displays the new key
            display_complex(key);
            key = randomize_key(); //randomize key and secret "n"
            n = randomize_n();
            display_complex(key);   
            clear_lcd();
            write_lcd(key_random, 1, 1);
            delay(70);
            display_welcome();
        }

        if (BTNLFT == 1 || BTNRGT == 1) { //pressing the left or right button changes the mode
            mode = (mode + 1) % 2; //round mode selection
            clear_lcd();
            write_lcd(mode_change, 1, 1);
            delay(10);
            if (mode == 0) { //encryption
                for (int i = 0; i < 200; i++) {
                    pwm(i / 2, 0, 0);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(i / 2, 0, 0);
                }
            } else { //decryption
                for (int i = 0; i < 200; i++) {
                    pwm(0, 0, i / 2);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(0, 0, i / 2);
                }
            }
            clear_lcd();
            write_lcd(changed, 1, 2);
            if (mode == 0) {
                write_lcd(mode_e, 2, 1);
            } else {
                write_lcd(mode_d, 2, 1);
            }
            delay(70);
            display_welcome();
        }

        if (BTNCTR == 1) { // pressing the center button shows the mode with RGB, carries out the mode, then displays the result with the LEDs
            clear_lcd();
            if (mode == 0) { //encryption
                write_lcd(encr_progress, 1, 2);
                delay(15);
                for (int i = 0; i < 200; i++) {
                    pwm(i / 2, 0, 0);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(i / 2, 0, 0);
                }
                encrypt(input, key, n);
                display_result(input);
                clear_lcd();
                write_lcd(encr, 1, 4);
                write_lcd(comp, 2, 4);
                delay(70);
                display_welcome();
            } else { //decryption
                write_lcd(decr_progress, 1, 2);
                delay(15);
                for (int i = 0; i < 200; i++) {
                    pwm(0, 0, i / 2);
                }
                for (int i = 200; i > 0; i--) {
                    pwm(0, 0, i / 2);
                }
                decrypt(input, key, n);
                display_result(input);
                clear_lcd();
                write_lcd(decr, 1, 4);
                write_lcd(comp, 2, 4);
                delay(70);
                display_welcome();
            }
        }
    }
    
    return;
}
