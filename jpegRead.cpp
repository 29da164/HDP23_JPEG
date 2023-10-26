#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpegRead.h" // printb and CONSTANTS

struct huffman{

    unsigned char key[16];
    unsigned char value;
    unsigned char digit;
    
};


void jfif(FILE *fp){

    unsigned char buf1,dummy,cnt;
    int icnt;

    printf("JFIF\n");
    fread(&dummy,sizeof(dummy),1,fp);
    fread(&cnt,sizeof(cnt),1,fp);
    icnt = (int)cnt;

    for(int i=0;i<icnt-2;i++){
        fread(&buf1,sizeof(buf1),1,fp);
    }

}

void dqt(FILE *fp){ // define quantum table

    unsigned char buf1,dummy,cnt;
    int icnt;
    FILE *fp_out;

    fp_out=fopen("./quantum.txt","w");

    printf("DQT\n");
    fread(&dummy,sizeof(dummy),1,fp);
    fread(&cnt,sizeof(cnt),1,fp);
    icnt = (int)cnt;
    fread(&dummy,sizeof(dummy),1,fp);
    printf("%02x\n",dummy);

    for(int i=0;i<icnt-3;i++){
        fread(&buf1,sizeof(buf1),1,fp);
        printf("%02d ",(int)buf1);
        fprintf(fp_out,"%d\n",(int)buf1);
        if(i%8==7){printf("\n");}
    }

    fclose(fp_out);

}

int dht(FILE *fp, long huffmanLength, huffman huffmanTable[]){

    unsigned char buf1,dummy,cnt;
    unsigned char huffmanDigit[HUFFMAN_MAX];
    int icnt, inc=0;

    printf("Define Huffman Table\n");
    fread(&dummy,sizeof(dummy),1,fp);
    fread(&cnt,sizeof(cnt),1,fp);

    // DC or AC
    fread(&dummy,sizeof(dummy),1,fp);
    printf("%d\n",dummy);
    if(dummy==0x00 || dummy==0x01){
        printf("DC\n");
    }
    if(dummy==0x10 || dummy==0x11){
        printf("AC\n");
    }

    icnt = (int)cnt;
    for(int i=0;i<16;i++){
        fread(&buf1,sizeof(buf1),1,fp);
        huffmanDigit[i]=(int)buf1;
    }

    int key=0;

    for(int i=0;i<16;i++){
        for(int j=0;j<huffmanDigit[i];j++){
            for(int k=0;k<16;k++){
                huffmanTable[inc].key[k] = 15;// Initialize
                // huffmanTable[].key[]="FFFF_FFFF_FFFF_FFFF"
            }
            fread(&buf1,sizeof(buf1),1,fp);
            for(int k=i;k>=0;k--){
                huffmanTable[inc].key[15-k] = (key>>k) & 0b1;
            }
            huffmanTable[inc].value = buf1;
            huffmanTable[inc].digit = i+1;
            key++;
            inc++;
        }
        key = key <<1;
    }
    printf("\n");

    return inc;

}

int scanHeader(FILE *fp, unsigned char image[], long *imageLength){

    unsigned char buf1,buf2,dummy,cnt;
    int icnt;

    printf("\nScan header\n");

    fread(&dummy,sizeof(dummy),1,fp);
    fread(&cnt,sizeof(cnt),1,fp);
    icnt = (int)cnt;

    for(int i=0;i<icnt-2;i++){
        fread(&buf1,sizeof(buf1),1,fp);
    }

    printf("----- Image data start -----\n");
    buf1=' ';
    int i=0;
    while(1){
        fread(&buf2,sizeof(buf2),1,fp);
        image[i]=buf2;
        // printf("%02X ",image[i]);
        for(int b=0;b<8;b++){
            // printf("%1X",(image[i]>>(7-b))&0b1);
        }
        // printf("\n");
        i++;

        if(buf1==0xFF && buf2==0xD9){
            break;
        }
        buf1=buf2;
    }
    (*imageLength) = i;
    printf("\n----- Image data end -----\n");

    return 0;

}

long acDecoder(long imageCounter, long huffmanLength, huffman huffmanTable, unsigned char imageSeriese_0[], unsigned char imageSeriese_1[]){
    
    printf("imageCounter1=%d\n",imageCounter);
    for(int i=0;i<160;i+=2){
        printf("%X",huffmanTable.key[i]);
        for(int j=0;j<huffmanLength-1;j++){
            if((huffmanTable.key[j]==imageSeriese_0[i+9])
                &&(huffmanTable.key[j+1]==imageSeriese_1[i+9])){
                printf("OK");
                break;
            }
            if(i%16==15){
                printf("\n");
            }
        }
    }
    printf("huffmanValue[1]=%X\n",huffmanTable.value);
    printf("huffmanDigit[1]=%X\n",huffmanTable.digit);
    imageCounter++;
    return imageCounter;

}

void imageDecode(long imageLength, unsigned char image[], long huffmanLength, huffman huffmanTable){

    FILE *fp;
    fp=fopen("./image_temp.txt","w");
    unsigned char imageSeriese[2][100];

    for(int i=0;i<imageLength;i++){
        imageSeriese[0][i]=image[i]%16;
        imageSeriese[1][i]=image[i]/16;
        switch (imageSeriese[1][i]){
            case 0x0: fprintf(fp,"0000");break;
            case 0x1: fprintf(fp,"0001");break;
            case 0x2: fprintf(fp,"0010");break;
            case 0x3: fprintf(fp,"0011");break;
            case 0x4: fprintf(fp,"0100");break;
            case 0x5: fprintf(fp,"0101");break;
            case 0x6: fprintf(fp,"0110");break;
            case 0x7: fprintf(fp,"0111");break;
            case 0x8: fprintf(fp,"1000");break;
            case 0x9: fprintf(fp,"1001");break;
            case 0xA: fprintf(fp,"1010");break;
            case 0xB: fprintf(fp,"1011");break;
            case 0xC: fprintf(fp,"1100");break;
            case 0xD: fprintf(fp,"1101");break;
            case 0xE: fprintf(fp,"1110");break;
            case 0xF: fprintf(fp,"1111");break;
        }
        switch (imageSeriese[0][i]){
            case 0x0: fprintf(fp,"0000");break;
            case 0x1: fprintf(fp,"0001");break;
            case 0x2: fprintf(fp,"0010");break;
            case 0x3: fprintf(fp,"0011");break;
            case 0x4: fprintf(fp,"0100");break;
            case 0x5: fprintf(fp,"0101");break;
            case 0x6: fprintf(fp,"0110");break;
            case 0x7: fprintf(fp,"0111");break;
            case 0x8: fprintf(fp,"1000");break;
            case 0x9: fprintf(fp,"1001");break;
            case 0xA: fprintf(fp,"1010");break;
            case 0xB: fprintf(fp,"1011");break;
            case 0xC: fprintf(fp,"1100");break;
            case 0xD: fprintf(fp,"1101");break;
            case 0xE: fprintf(fp,"1110");break;
            case 0xF: fprintf(fp,"1111");break;
        }
    }
    fclose(fp);

    //========= DECODER ===================
    int imageCounter = 0;
    // fp=fopen("./image.txt","r");
    imageCounter = acDecoder(imageCounter, huffmanLength, huffmanTable, imageSeriese[0], imageSeriese[1]);
    printf("ImageCounter2=%d\n",imageCounter);

}

int main(int argc, char **argv){

    unsigned char buf1,buf2,dummy;
    unsigned char buf_huffman;  
    unsigned char buf_image;
    unsigned char image[IMAGE_MAX];
    huffman huffmanTable[HUFFMAN_MAX];

    int icnt, huffmanLength=0;
    int run=1;
    long imageLength=0;

    // initialize image data
    for(int i=0;i<IMAGE_MAX;i++){image[i]=0;}

    FILE *fp;
    FILE *fp_huf;
    FILE *fp_img;
    FILE *fp_len;

    // for debugging only
    // fp = fopen("./8x8_org.jpg","rb");
    // fp = fopen("./profile.jpg","rb");

    fp = fopen(argv[1],"rb");
    fp_huf = fopen("./huffmanTable.bin","wb");
    fp_img = fopen("./image.bin","wb");
    fp_len = fopen("./length.bin","wb");

    buf1=' ';

    while(1){
        fread(&buf2,sizeof(buf2),1,fp);
        if(buf1==0xFF && buf2==0xE0) jfif(fp);
        if(buf1==0xFF && buf2==0xDB) dqt(fp);
        if(buf1==0xFF && buf2==0xC4) {
            huffmanLength = dht(fp, huffmanLength, huffmanTable);
            for(int j=0;j<huffmanLength;j++){
                buf_huffman = huffmanTable[j].digit;
                fwrite(&buf_huffman,1,1,fp_huf);
                for(int i=0;i<16;i++){
                    printf("%X",huffmanTable[j].key[i]);
                    buf_huffman = huffmanTable[j].key[i];
                    fwrite(&buf_huffman,1,1,fp_huf);
                }
                printf("\t%02X %d\n",huffmanTable[j].value,huffmanTable[j].digit);
                buf_huffman = huffmanTable[j].value;
                fwrite(&buf_huffman,1,1,fp_huf);
            }
        }
        if(buf1==0xFF && buf2==0xDA){
            run = scanHeader(fp,image,&imageLength);
            for(int i=0;i<imageLength;i++){
                printf("%02X ",image[i]);
                buf_image = image[i];
                fwrite(&buf_image,1,1,fp_img);
                if(i%16==15) printf("\n");
            }
        }
        if(!run) break;
        buf1=buf2;
    }
    printf("\n");
    fwrite(&huffmanLength,1,4,fp_len);
    fwrite(&imageLength,1,4,fp_len);

    // imageDecode(imageLength, image, huffmanLength, *huffmanTable);

    fclose(fp);
    fclose(fp_huf);
    fclose(fp_img);
    fclose(fp_len);

    return 0;

}