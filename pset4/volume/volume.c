// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
const int INT16_T_MAX = 256 * 256 - 1;
const int INT16_T_MIN = -256 * 256;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);
    //printf("factor = %lf\n", factor);

    // TODO: Copy header from input file to output file
    size_t read_size, write_size;
    uint8_t header[HEADER_SIZE];
    
    read_size = fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    if (read_size != HEADER_SIZE)
    {
        printf("Could not read header normally.\n");
        fclose(input);
        fclose(output);
        return 1;
    }
    write_size = fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
    if (write_size != HEADER_SIZE)
    {
        printf("Could not write header normally.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    intmax_t volume;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        volume = buffer;
        volume = volume * factor;
        if (volume < INT16_T_MIN)
            volume = INT16_T_MIN;
        if (volume > INT16_T_MAX)
            volume = INT16_T_MAX;
        buffer = volume;
        write_size = fwrite(&buffer, sizeof(int16_t), 1, output);
        if (!write_size)
        {
            printf("Could not write output file normally");
            fclose(input);
            fclose(output);
            return 1;
        }
    }
    if (!feof(input))
    {
        printf("Could not read input file normally\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Close files
    fclose(input);
    fclose(output);
    return 0;
}
