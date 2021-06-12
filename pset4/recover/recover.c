#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
 
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return (1);
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open card.\n");
        return (1);
    }

    int count = 0;
    uint8_t buffer[BLOCK_SIZE] = {};
    FILE *pic = NULL;
    char file_name[] = "000.jpg";
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
                && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            if (pic)
                fclose(pic);
            for (int i = 2, tmp = count; tmp > 0 || i >= 0; i--, tmp /= 10)
                file_name[i] = tmp % 10 + '0';
            pic = fopen(file_name, "w");
            count++;
        }
        if (pic)
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, pic);
    }
    if (pic)
        fclose(pic);
    fclose(card);
}
