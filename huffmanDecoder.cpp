#include <stdio.h>
#include <math.h>
#define HUFFMAN_MAX 64
#define IMAGE_MAX 1000

struct huffman{
    unsigned char key[HUFFMAN_MAX];
    unsigned char value;
    unsigned char digit;
};

struct jpeg{
    unsigned char image;
};

int main(void){
    struct huffman huffmancode[256];
    struct jpeg image[IMAGE_MAX];
    FILE *fp_huf;
    FILE *fp_img;
    FILE *fp_len;
    FILE *fp_out;
    int HUFFMAN_LENGTH=0;
    int IMAGE_LENGTH=0;

    // length data load ------------------------------------
    fp_len=fopen("./length.bin","rb");
    fread(&HUFFMAN_LENGTH,1,4,fp_len);
    fread(&IMAGE_LENGTH,1,4,fp_len);
    fclose(fp_len);
    HUFFMAN_LENGTH++;   // ############# AC + DC(=1) #################

    // huffman table load ----------------------------------
    fp_huf=fopen("./huffmanTable.bin","rb");
    //-- initialize
    for(int i=0;i<HUFFMAN_LENGTH;i++){
      huffmancode[i].digit=0;
      for(int j=0;j<16;j++){
        huffmancode[i].key[j]=0;
      }
      huffmancode[i].value=0;
    }
    //-- data load
    for(int i=0;i<HUFFMAN_LENGTH;i++){
        fread(&huffmancode[i].digit,1,1,fp_huf);
        for(int j=0;j<16;j++){
            fread(&huffmancode[i].key[j],1,1,fp_huf);
        }
        fread(&huffmancode[i].value,1,1,fp_huf);
    }
    fclose(fp_huf);

    // image data load ----------------------------------
    fp_img=fopen("./image.bin","rb");
    //-- initialize
    for(int i=0;i<IMAGE_MAX;i++){
        image[i].image=0;
    }
    for(int i=0;i<IMAGE_LENGTH;i++){
        fread(&image[i],1,1,fp_img);
    }
    fclose(fp_img);

    int match=0;
    unsigned char imageTemp[256*256*8];

    // output file open
    fp_out=fopen("./image.txt","w");

    // image file read
    for(int j=0;j<IMAGE_LENGTH;j++){
        for(int i=0;i<8;i++){
            imageTemp[j*8+(7-i)]=(image[j].image >>i) & 0b1;
        }
    }

    int imgStart=0; // image start position
    int dcFlag=0;   // 0:DC data has not been decoded, 1: DC data has already decoded. 
    int i=0;

    while(1){
        for(i=imgStart;i<IMAGE_LENGTH*8;i++){
            for(int j=dcFlag;j<HUFFMAN_LENGTH;j++){
                int match=0;
                for(int k=0;k<huffmancode[j].digit;k++){
                    if(imageTemp[i+k]==huffmancode[j].key[16-huffmancode[j].digit+k]){
                        match++;
                    }
                }
                if(match==huffmancode[j].digit){
                    printf("Matched: ");
                    printf("Huffman value=%2X\t",huffmancode[j].value);
                    int takeBit = (huffmancode[j].value & 0b00001111)
                                  +huffmancode[j].digit;
                    int skipBit = (huffmancode[j].value & 0b11110000);
                    int vdigit = huffmancode[j].value & 0b00001111;
                    int cdigit = huffmancode[j].digit;
                    int v=0;
                    for(int vi=vdigit+cdigit-1; vi>=cdigit ;vi--){
                        v += imageTemp[i+vi] << (vdigit+cdigit-1-vi);
                    }
                    skipBit = skipBit >> 4;
                    i += takeBit-1;
                    printf("take %1X (%1X+%1X) digit,\t",
                                takeBit,(huffmancode[j].value & 0b00001111),
                                huffmancode[j].digit);
                    printf("skip %2d cells,\t",skipBit);
                    printf("value %d,\t", v);
                    if(imageTemp[i-vdigit+1]==0){//*******************ここだけ*************************
                        v = v-pow(2,(double)vdigit)+1;
                    }
                    printf("value2 %d\n", v);

                    // output file write -------------------------
                    if(skipBit !=0){
                        for(int skip=0;skip<skipBit;skip++){
                            fprintf(fp_out, "0\n");
                        }
                    }
                    fprintf(fp_out,"%d\n",v);
                    // output file complete -----------------------

                    if(!dcFlag) dcFlag=1;
                    match=0;
                    break;
                }
            }
        }
        if(i>IMAGE_LENGTH*8){
            break;
        }
    }
    fclose(fp_out);
    return 0;

}