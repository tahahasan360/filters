#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <string.h>

typedef uint8_t BYTE;

const int block = 512;

int main(int argc, char *argv[])
{
    //ensures proper input
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    //open file for reading
    char *infile = argv[1];
    FILE *file = fopen(infile, "r");

    if (file == NULL)
    {
        printf("Error while opening file");
        return 1;
    }
    //initializing
    BYTE buffer1[block - 4];
    memset(buffer1, 0x00, block - 4);
    BYTE buffer[block];
    memset(buffer, 0x00, block);
    BYTE x = 0;
    memset(&x, 0x00, 1);
    BYTE JPEG[3] = {0xff, 0xd8, 0xff};
    char filename[8];
    int imagecount = 0;

    //open file output for writing
    FILE *output = NULL;
    output = fopen("000.jpg", "w");
    
    //iterate until JPEG signature bytes found
    while (1)
    {
        fread(&x, sizeof(BYTE), 1, file);
        if (x == JPEG[0])
        {
            fread(&x, sizeof(BYTE), 1, file);
            if (x == JPEG[1])
            {
                fread(&x, sizeof(BYTE), 1, file);
                if (x == JPEG[2])
                {
                    fread(&x, sizeof(BYTE), 1, file);
                    int y = (int) x;
                    if ((y >= 224) && (y <= 239))
                    {
                        break;
                    }
                }
            }
        }
    }
    
    //write first block of first JPEG into output 
    fwrite(JPEG, sizeof(BYTE), 3, output);
    fwrite(&x, sizeof(BYTE), 1, output);
    fread(buffer1, sizeof(BYTE), block - 4, file);
    fwrite(buffer1, sizeof(BYTE), block - 4, output);
    
    //copy file into output, block by block
    while (1)
    {
        int n = fread(&buffer, sizeof(BYTE), block, file);
        if (n == 0)
        {
            break;
        }
        //if JPEG signature found, close output file and open a new output file
        if (buffer[0] == JPEG[0] && buffer[1] == JPEG[1] && buffer[2] == JPEG[2])
        {
            fclose(output);
            imagecount++;
            sprintf(filename, "%03i.jpg", imagecount);
            output = fopen(filename, "w");
        }
        fwrite(buffer, sizeof(BYTE), block, output);
    }
}
