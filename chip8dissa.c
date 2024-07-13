#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


void DisassembleChip8Op(uint8_t *codebuffer, int pc)    
{    
    // # is an indicator of a literal number
    //uint8_t are unsigned integers of 8 bits
    uint8_t *code = &codebuffer[pc];    
    uint8_t firstnib = (code[0] >> 4);    

    printf("%04x %02x %02x ", pc, code[0], code[1]);    
    switch (firstnib)    
    {    
        case 0x00:
            {
                // get last four bits of first byte
                uint8_t secondnib = code[0] & 0x0f;
                // get second nibble of 2nd byte
                uint8_t firstnibofsecond = (code[1] >> 4);
                if (secondnib == 0x00 && firstnibofsecond == 0x0e){
                    
                    uint8_t lastnib = code[1] & 0x0f;

                    if (lastnib == 0x00){
                    printf("This is a display clear instruction");
                    } else {
                    printf("This is a return instruction");
                    }
                    
                } else {
                    printf("We will not handle a 0NNN Call instruction");
                }
            }
            break;    
        case 0x01:
            {
                uint8_t firstnib = code[0] & 0x0f;
                // this instruction is goto NNN or jumps to address NNN
                printf("JUMP #$%01x%02x", firstnib, code[1]);
            }
            break;
      
        case 0x02:
            {
                uint8_t firstnib = code[0] & 0x0f;
                printf("CALL #$%01x%02x", firstnib, code[1]);
            }
            break;  
        case 0x03: printf("3 not handled yet"); break;    
        case 0x04: printf("4 not handled yet"); break;    
        case 0x05: printf("5 not handled yet"); break;    
        case 0x06:    
            {    
                // this sets Vx = NN, so #$ signifies a constant
                uint8_t reg = code[0] & 0x0f;    
                printf("%-10s V%01X,#$%02x", "MVI", reg, code[1]);    
            }    
            break;    
        case 0x07: printf("7 not handled yet"); break;    
        case 0x08: printf("8 not handled yet"); break;    
        case 0x09: printf("9 not handled yet"); break;    
        case 0x0a:    
            {   
                // Sets I to the address NNN, which is in ANNN, a is the first nibble 
                uint8_t addresshi = code[0] & 0x0f;    
                printf("%-10s I,#$%01x%02x", "MVI", addresshi, code[1]);    
            }    
            break;    
        case 0x0b: printf("b not handled yet"); break;    
        case 0x0c: printf("c not handled yet"); break;    
        case 0x0d: printf("d not handled yet"); break;    
        case 0x0e: printf("e not handled yet"); break;    
        case 0x0f: printf("f not handled yet"); break;    
    }    
}    

int main (int argc, char**argv)    
{    
    FILE *f= fopen(argv[1], "rb");    
    if (f==NULL)    
    {    
        printf("error: Couldn't open %s\n", argv[1]);    
        exit(1);    
    }    

    //Get the file size    
    fseek(f, 0L, SEEK_END);    
    int fsize = ftell(f);    
    fseek(f, 0L, SEEK_SET);    

    //CHIP-8 convention puts programs in memory at 0x200    
    // They will all have hardcoded addresses expecting that    
    //    
    //Read the file into memory at 0x200 and close it.    
    unsigned char *buffer=malloc(fsize+0x200);    
    fread(buffer+0x200, fsize, 1, f);    
    fclose(f);    

    int pc = 0x200;    
    while (pc < (fsize+0x200))    
    {    
        DisassembleChip8Op(buffer, pc);    
        pc += 2;    
        printf ("\n");    
    }    
    return 0;    
} 




// http://www.emulator101.com/chip-8-disassembler.html


// https://www.geeksforgeeks.org/cc-command-in-linux-with-examples/

//ways to compile, and/or add -g to enable debugging
// cc chip8dissa.c -o diss

// this will chck for all errors and warnings in the program
// cc example.c -Wall -o examp_out