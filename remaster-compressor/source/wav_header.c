// Reads and identifies the header of WAV file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        printf("Usage: ./wav_header audiofile.wav\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declare variables
    int header_type = 0;
    wave_header buffer;

    // Determine which kind of WAV Header corresponds
    if (fread(&buffer, sizeof(wave_header), 1, input))
    {
	if (buffer.fmt_id == 0x20746D66 && buffer.data_id == 0x61746164)
	{
		header_type = 1;
		printf("Standard WAV Header\n");
		printf("Channels: %i\n", buffer.channels);
		printf("Bits per Sample: %i\n", buffer.bits_per_sample);
		printf("Sample Rate: %i\n", buffer.sample_rate);
		printf("44 bytes header\n");
	}
	else if (buffer.fmt_id == 0x74786562)
	{
		header_type = 2;
		printf("Non Standard WAV Header\n");
		printf("Pro Tools generated\n");
		printf("Presumably 1024 bytes\n");
		printf("Asuming 16 bits per sample\n");
	}
	else
	{
		header_type = 3;
		printf("Non Standard WAV Header\n");
		printf("Unkown\n");
		printf("Presumably 88 bytes\n");
		printf("Asuming 16 bits per sample\n");
	}
    }
    else
    {
        printf("Could not read input.\n");
        return 1;
    }

    // Close file
    fclose(input);
}
