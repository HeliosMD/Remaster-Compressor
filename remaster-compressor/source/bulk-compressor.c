#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Usage: bulk-compressor directory\n");
		return 1;
	}
	char invocation[512];
	sprintf(invocation, "ls %s/*.wav > ls.txt", argv[1]);
	int error = system(invocation);
	FILE *files = fopen("ls.txt", "r");
	char file[255][255];
	uint8_t byte;
	int nfiles = 0;
	int c = 0;
	while (fread(&byte, sizeof(uint8_t), 1, files))
	{
		if(byte=='\n')
		{
			file[nfiles][c] = '\0';
			nfiles++;
			c = 0;
		}
		else
		{
			file[nfiles][c] = (char) byte;
			c++;
		}
	}
	fclose(files);
	sprintf(invocation, "rm ls.txt");
	error = system(invocation);
	for(int i = 0; i < nfiles; i++)
	{
		printf("%i: %s\n", i + 1, file[i]);
		sprintf(invocation, "./remaster-compressor.sh %s\n", file[i]);
		error = system(invocation);
		printf("\n");
		printf("------------------------------------------------------------\n");
		printf("\n");
	}
	return 0;
}
