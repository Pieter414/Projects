#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER *headers = malloc(sizeof(WAVHEADER));

    fread(headers, 1, sizeof(WAVHEADER), input);

    // Use check_format to ensure WAV format
    // TODO #4
    int check = check_format(*headers);
    if (check != 0)
    {
        printf("Input is not a WAV file\n");
        return 0;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        free(headers);
        fclose(input);
        printf("Could not open file\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(headers, 1, sizeof(WAVHEADER), output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(*headers);
    // printf("%i\n", block_size);

    // Write reversed audio to file
    // TODO #8
    BYTE *audio_data = malloc(block_size * sizeof(BYTE));
    bool hit_header = false;

    // Define the start of audio data (after the header)
    long start_of_audio = ftell(input);

    // seek end of the file and get the input size
    fseek(input, 0, SEEK_END);
    long input_size = ftell(input);

    while (!hit_header)
    {
        // Minus the input size, to get the data
        input_size -= block_size;

        // Go to the file pointer for reading
        fseek(input, input_size, SEEK_SET);

        // Read and write the block_size BYTE chuck
        fread(audio_data, sizeof(BYTE), block_size, input);

        fwrite(audio_data, sizeof(BYTE), block_size, output);

        // Check if the input size, already hit the end of header
        if (input_size <= start_of_audio)
        {
            hit_header = true;
        }
    }

    // Close and free all the file
    free(audio_data);
    free(headers);
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] != 87 && header.format[1] != 65 && header.format[2] != 86 && header.format[3] != 69)
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    return block_size;
}