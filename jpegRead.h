#define IMAGE_MAX 10000
#define HUFFMAN_MAX 16384   // 16*256
#include <stdio.h>

void printb(unsigned short x, unsigned char digit){
    
    char c[16] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};

    switch (x & 0b1111000000000000){
        case 0x0000: c[0]=0; c[1]=0; c[2]=0; c[3]=0; break;
        case 0x1000: c[0]=0; c[1]=0; c[2]=0; c[3]=1; break;
        case 0x2000: c[0]=0; c[1]=0; c[2]=1; c[3]=0; break;
        case 0x3000: c[0]=0; c[1]=0; c[2]=1; c[3]=1; break;
        case 0x4000: c[0]=0; c[1]=1; c[2]=0; c[3]=0; break;
        case 0x5000: c[0]=0; c[1]=1; c[2]=0; c[3]=1; break;
        case 0x6000: c[0]=0; c[1]=1; c[2]=1; c[3]=0; break;
        case 0x7000: c[0]=0; c[1]=1; c[2]=1; c[3]=1; break;
        case 0x8000: c[0]=1; c[1]=0; c[2]=0; c[3]=0; break;
        case 0x9000: c[0]=1; c[1]=0; c[2]=0; c[3]=1; break;
        case 0xA000: c[0]=1; c[1]=0; c[2]=1; c[3]=0; break;
        case 0xB000: c[0]=1; c[1]=0; c[2]=1; c[3]=1; break;
        case 0xC000: c[0]=1; c[1]=1; c[2]=0; c[3]=0; break;
        case 0xD000: c[0]=1; c[1]=1; c[2]=0; c[3]=1; break;
        case 0xE000: c[0]=1; c[1]=1; c[2]=1; c[3]=0; break;
        case 0xF000: c[0]=1; c[1]=1; c[2]=1; c[3]=1; break;
    }
    switch (x & 0b0000111100000000){
        case 0x000: c[4]=0; c[5]=0; c[6]=0; c[7]=0; break;
        case 0x100: c[4]=0; c[5]=0; c[6]=0; c[7]=1; break;
        case 0x200: c[4]=0; c[5]=0; c[6]=1; c[7]=0; break;
        case 0x300: c[4]=0; c[5]=0; c[6]=1; c[7]=1; break;
        case 0x400: c[4]=0; c[5]=1; c[6]=0; c[7]=0; break;
        case 0x500: c[4]=0; c[5]=1; c[6]=0; c[7]=1; break;
        case 0x600: c[4]=0; c[5]=1; c[6]=1; c[7]=0; break;
        case 0x700: c[4]=0; c[5]=1; c[6]=1; c[7]=1; break;
        case 0x800: c[4]=1; c[5]=0; c[6]=0; c[7]=0; break;
        case 0x900: c[4]=1; c[5]=0; c[6]=0; c[7]=1; break;
        case 0xA00: c[4]=1; c[5]=0; c[6]=1; c[7]=0; break;
        case 0xB00: c[4]=1; c[5]=0; c[6]=1; c[7]=1; break;
        case 0xC00: c[4]=1; c[5]=1; c[6]=0; c[7]=0; break;
        case 0xD00: c[4]=1; c[5]=1; c[6]=0; c[7]=1; break;
        case 0xE00: c[4]=1; c[5]=1; c[6]=1; c[7]=0; break;
        case 0xF00: c[4]=1; c[5]=1; c[6]=1; c[7]=1; break;
    }
    switch (x & 0b0000000011110000){
        case 0x00: c[8]=0; c[9]=0; c[10]=0; c[11]=0; break;
        case 0x10: c[8]=0; c[9]=0; c[10]=0; c[11]=1; break;
        case 0x20: c[8]=0; c[9]=0; c[10]=1; c[11]=0; break;
        case 0x30: c[8]=0; c[9]=0; c[10]=1; c[11]=1; break;
        case 0x40: c[8]=0; c[9]=1; c[10]=0; c[11]=0; break;
        case 0x50: c[8]=0; c[9]=1; c[10]=0; c[11]=1; break;
        case 0x60: c[8]=0; c[9]=1; c[10]=1; c[11]=0; break;
        case 0x70: c[8]=0; c[9]=1; c[10]=1; c[11]=1; break;
        case 0x80: c[8]=1; c[9]=0; c[10]=0; c[11]=0; break;
        case 0x90: c[8]=1; c[9]=0; c[10]=0; c[11]=1; break;
        case 0xA0: c[8]=1; c[9]=0; c[10]=1; c[11]=0; break;
        case 0xB0: c[8]=1; c[9]=0; c[10]=1; c[11]=1; break;
        case 0xC0: c[8]=1; c[9]=1; c[10]=0; c[11]=0; break;
        case 0xD0: c[8]=1; c[9]=1; c[10]=0; c[11]=1; break;
        case 0xE0: c[8]=1; c[9]=1; c[10]=1; c[11]=0; break;
        case 0xF0: c[8]=1; c[9]=1; c[10]=1; c[11]=1; break;
    }
    switch (x & 0b0000000000001111){
        case 0x0: c[12]=0; c[13]=0; c[14]=0; c[15]=0; break;
        case 0x1: c[12]=0; c[13]=0; c[14]=0; c[15]=1; break;
        case 0x2: c[12]=0; c[13]=0; c[14]=1; c[15]=0; break;
        case 0x3: c[12]=0; c[13]=0; c[14]=1; c[15]=1; break;
        case 0x4: c[12]=0; c[13]=1; c[14]=0; c[15]=0; break;
        case 0x5: c[12]=0; c[13]=1; c[14]=0; c[15]=1; break;
        case 0x6: c[12]=0; c[13]=1; c[14]=1; c[15]=0; break;
        case 0x7: c[12]=0; c[13]=1; c[14]=1; c[15]=1; break;
        case 0x8: c[12]=1; c[13]=0; c[14]=0; c[15]=0; break;
        case 0x9: c[12]=1; c[13]=0; c[14]=0; c[15]=1; break;
        case 0xA: c[12]=1; c[13]=0; c[14]=1; c[15]=0; break;
        case 0xB: c[12]=1; c[13]=0; c[14]=1; c[15]=1; break;
        case 0xC: c[12]=1; c[13]=1; c[14]=0; c[15]=0; break;
        case 0xD: c[12]=1; c[13]=1; c[14]=0; c[15]=1; break;
        case 0xE: c[12]=1; c[13]=1; c[14]=1; c[15]=0; break;
        case 0xF: c[12]=1; c[13]=1; c[14]=1; c[15]=1; break;
    }

    for (int i=0;i<16-digit;i++){
        c[i]=15;
    }
    printf("digit=%2d ",digit);

    for(int i=0;i<16;i++) 
        if(c[i]<2) printf("%1X",c[i]);
        else printf(".");

    printf("\t");
}