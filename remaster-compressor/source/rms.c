// Measures the RMS of an audio file

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE_1 = 44;
const int HEADER_SIZE_2 = 1024;
const int HEADER_SIZE_3 = 88;
const int NBITS = 16;

// Define WAV Header struct
typedef struct
{
	uint32_t riff_id;
	uint32_t file_size;
	uint32_t wave_id;
	uint32_t fmt_id;
	uint32_t fmt_size;
	int16_t audio_format;
	int16_t channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	int16_t block_align;
	int16_t bits_per_sample;
	uint32_t data_id;
	uint32_t data_size;
}
wave_header;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./rms input.wav\n");
        return 1;
    }

    // Open file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declare variables
    int channels = 0;
    int header_type = 0;
    int bytes_per_sample = 0;
    wave_header buffer;

    // Determine which kind of WAV Header corresponds
    if (fread(&buffer, sizeof(wave_header), 1, input))
    {

	if (buffer.fmt_id == 0x20746D66 && buffer.data_id == 0x61746164)
	{
		header_type = 1;
	}
	else if (buffer.fmt_id == 0x74786562)
	{
		header_type = 2;
	}
	else
	{
		header_type = 3;
	}
	channels = buffer.channels;
	bytes_per_sample = buffer.block_align;
    }
    else
    {
        printf("Could not read input.\n");
        return 1;
    }

    // Close file
    fclose(input);

    // Open file
    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declare data chuck size
    uint32_t data_size = 0;
    
    // Calculate data chuck size according to header type
    if (header_type == 1)
    {
    	// Read header type 1 from input file
   	uint8_t buffer[HEADER_SIZE_1];

    	if (!fread(&buffer, sizeof(uint8_t), HEADER_SIZE_1, input))
        {
            printf("Could not read input.\n");
            return 1;
        }

   	// Validate data chunk and get size
	if (buffer[0x24] == 0x64 && buffer[0x25] == 0x61 && buffer[0x26] == 0x74 && buffer[0x27] == 0x61)
	{
	    data_size = buffer[0x28] + buffer[0x29] * pow(2, 8) + buffer[0x2A]  * pow(2, 16) + buffer[0x2B] * pow(2, 24);
	}

    }
    else if (header_type == 2)
    {
    	// Read header type 2 from input file
   	uint8_t buffer[HEADER_SIZE_2];

    	if (!fread(&buffer, sizeof(uint8_t), HEADER_SIZE_2, input))
        {
            printf("Could not read input.\n");
            return 1;
        }

   	// Validate data chunk and get size
	if (buffer[0x3F8] == 0x64 && buffer[0x3F9] == 0x61 && buffer[0x3FA] == 0x74 && buffer[0x3FB] == 0x61)
	{
	    data_size = buffer[0x3FC] + buffer[0x3FD] * pow(2, 8) + buffer[0x3FE]  * pow(2, 16) + buffer[0x3FF] * pow(2, 24);
	}
    }
    else if (header_type == 3)
    {
    	// Read header type 2 from input file
   	uint8_t buffer[HEADER_SIZE_3];

    	if (!fread(&buffer, sizeof(uint8_t), HEADER_SIZE_3, input))
        {
            printf("Could not read input.\n");
            return 1;
        }

   	// Validate data chunk and get size
	if (buffer[0x50] == 0x64 && buffer[0x51] == 0x61 && buffer[0x52] == 0x74 && buffer[0x53] == 0x61)
	{
	    data_size = buffer[0x54] + buffer[0x55] * pow(2, 8) + buffer[0x56]  * pow(2, 16) + buffer[0x57] * pow(2, 24);
	}
    }


    // Read samples from input file
    int n_samples = 0;
    int16_t audio_buffer = 0;
    float sum_s = 0;
    float dB = 0;
    float i = 0;
    int t = data_size / 2;
    for (int n = 0; n < t; n++)
    {
	if (!fread(&audio_buffer, sizeof(int16_t), 1, input))
	{
		printf("Could not read file\n");
		return 1;
	}
	n_samples++;
        sum_s += pow(audio_buffer, 2.0);
        i = sqrt(sum_s / n_samples);
	dB = log2(i) + 1;
	dB = 6.0 * (dB-NBITS);
    }

    // Close files
    fclose(input);

    // Show RMS in dB
    printf("%f dB\n", dB);
}
