#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // 1. Check if the one command line argument given
    if (argc != 2)
    {
        printf("Invalid input. ./recover image.raw\n");
        return 1;
    }

    // 2. Open the file that want to be recovered
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // 3. Create a num for filename naming
    int num = 0;
    // 4. Create space by malloc for buffer and filename
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);
    char *filename = malloc(sizeof(char) * 8);
    // 5. Declare output file outside for freeing, and found_jpg
    FILE *output = NULL;
    bool found_jpg = false;

    // 6. Repeat the card until the end, also reading the input file
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // 7. If start of new JPEG, by checking the first 4 byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // 8. Assign the found_jpg to true
            found_jpg = true;
            // 9. If the first JPEG readed, write the new data, new filename with sprintf, check output file opening
            if (num == 0)
            {
                sprintf(filename, "%03i.jpg", num);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    fclose(input);
                    printf("Could not open file\n");
                    free(filename);
                    free(buffer);
                    return 1;
                }
                // 10. Write the buffer into the output, add 1 to num
                fwrite(buffer, 1, BLOCK_SIZE, output);
                num++;
            }
            // 11. If this not the first JPEG, close the previous JPEG and start again
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", num);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    fclose(input);
                    free(filename);
                    free(buffer);
                    printf("Could not open file\n");
                    return 1;
                }
                fwrite(buffer, 1, BLOCK_SIZE, output);
                num++;
            }
        }
        // 12. If already found JPEG, based on found_jpg already true. Continue writing
        else if (found_jpg)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }

        // 13. To prevent overwrite file like last time and need to delete all the file
        if (num > 55)
        {
            free(buffer);
            free(filename);
            fclose(input);
            fclose(output);
            return 2;
        }
        // printf("check num = %i\n", num);
    }

    // 14. Close and free remaining file
    free(filename);
    free(buffer);

    fclose(input);
    fclose(output);
}