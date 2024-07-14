#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// Source for code skeleton:  http://www.emulator101.com/chip-8-emulator.html

typedef struct Chip8State {    
    uint8_t     V[16];    
    uint16_t    I;    
    uint16_t    SP;    
    uint16_t    PC;    
    uint8_t     delay;    
    uint8_t     sound;    
    uint8_t     *memory;    
    uint8_t     *screen;  //this is memory[0xF00];    
} Chip8State;    


Chip8State* InitChip8(void)    
{    
Chip8State* s = calloc(sizeof(Chip8State), 1);    

s->memory = calloc(1024*4, 1);    
s->screen = &s->memory[0xf00];    
s->SP = 0xfa0;    
s->PC = 0x200;    

return s;    
}


void EmulateChip8Op(Chip8State *state)    
   {    
       uint8_t *op = &state->memory[state->PC];    

       int highnib = (*op & 0xf0) >> 4;    
       switch (highnib)    
       {    
        ﻿case 0x00: UnimplementedInstruction(state); break;    
        case 0x01:                      //JUMP $NNN    
            {    
                uint16_t target = ((code[0]&0xf)<<8) | code[1];    
                state->PC = target;    
            }    
            break;    
        case 0x02: UnimplementedInstruction(state); break;    
        case 0x03:                      //SKIP.EQ VX,#$NN    
            {    
                uint8_t reg = code[0] & 0xf;    
                if (state->V[reg] == code[1])    
                    state->PC+=2;    
                state->PC+=2;    
            }    
            break;    
        case 0x04: UnimplementedInstruction(state); break;    
        case 0x05: UnimplementedInstruction(state); break;    
        case 0x06:                      //MOV VX,#$NN    
            {    
                uint8_t reg = code[0] & 0xf;    
                state->V[reg] = code[1];    
                state->PC+=2;    
            }    
            break;    
        case 0x07: UnimplementedInstruction(state); break;    
        case 0x08: UnimplementedInstruction(state); break;    
        case 0x09: UnimplementedInstruction(state); break;    
        case 0x0a:                      //MOV I, #$NNN    
            {    
                state->I = ((code[0] & 0xf)<<8) | code[1];    
                state->PC+=2;    
            }    
            break;    
        case 0x0b: UnimplementedInstruction(state); break;    
        case 0x0c: UnimplementedInstruction(state); break;    
        case 0x0d: UnimplementedInstruction(state); break;    
        case 0x0e: UnimplementedInstruction(state); break;    
        case 0x0f: UnimplementedInstruction(state); break;    
       }    
   }    