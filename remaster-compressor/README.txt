REMASTER COMPRESSOR - V.0.2
By: Helios Martinez Dominguez
Estudio Siddhi - Copyleft 2021.

Remaster Compressor is a single pass audio remastering tool designed to accomplish with audio mastering industry requirements.
As for now, it processes 16bit audio files using SIN-COMP curve compressor. Binaries for Linux are distributed.
Sometimes, binaries distributed may fail to execute, in such case you need to compile the application from source.
This is due to differences between distributions (x86/x64, etc).

How to compile from source:

For the compilation process you would need GCC (GNU C compiler) installed (most Linux distributions have it by default).
First, after decompressing the files into the master-compander/ directory, you have to provide the "compile.sh" with execution priviledges:

	$ sudo chmod 775 compile.sh

Then, just invoque:

	$ ./compile.sh

All binaries will compile. Once compiled, the files need to be in the same directory as the "master-compander.sh" file (this is done automatically).
In case compilation fails, each source file can also be compiled separatedly by invocating the compiler and specifing it's output.
Sometimes linking math.h is also necessary. "compiles.sh" script also provides priviledges of execution to the "master-compander.sh" file.

Example:

	$ gcc -o rms rms.c -std=c99 -lm
	$ gcc -o peak peak.c -std=c99 -lm
	$ gcc -o wav_header wav_header.c -std=c99 -lm
	$ gcc -o sin-comp sin-comp.c -std=c99 -lm
	$ sudo chmod 775 remaster-compressor.sh

How to use it:

Open the Terminal Emulator or Shell (bash, zsh, etc).
Get into the remaster-compressor/ folder or directory.
Then execute:

$ ./remaster-compressor.sh path/audiofile.wav

Where "path/audiofile.wav" is the audio file to be remastered. That is pretty much it!.
The Remaster Compressor will check on the audiofile's RMS and Peak values and provide for RMS and Peak values for the output audio file.
After the remastering process, there will be a new audio file named with "-remastered.wav" as a suffix. That is you remastered audio file.

This is a typical screen:

	helios@helios-CQ1115LA:~$ ./remaster-compressor.sh vacio.wav
	REMASTER COMPRESSOR - V.0.1
	By: Helios Martinez Dominguez
	Estudio Siddhi - Copyleft 2021.

	Remastering:
	vacio.wav

	Standard WAV Header
	Channels: 2
	Bits per Sample: 16
	Sample Rate: 44100
	44 bytes header

	Input RMS:
	-17.026594 dB
	Input Peak:
	-0.000263 dB

	SIN-COMP: Processing 64 floating-point

	Output RMS:
	-13.400059 dB
	Output Peak:
	-0.000263 dB

	Remastered:
	vacio.wav-remastered.wav
	helios@helios-CQ1115LA:~$ 

How it works:

Remaster Compressor works making use of four main processes, each provided as a separate executable and joined together through a script shell.
First, the script file provides for a Title, Author and Copyleft information.
At this point, Master Compander shows WAV header file information.
Then, RMS of the input is calculated by scanning the whole audiofile.
After that, Peak value is also calculated scannig the whole audio file.
Up to this point there is no process being done to the audio file.
Then, SIN-COMP is exectued on the audio file.
SIN-COMP process it through a compressing curve, compressing the dynamic range.
SIN-COMP is not a linear compressor, it is based on a mathematical curve (sinusoidal curve).
After this process is done, the output file is named after the original audio file with the "-remastered.wav" suffix.
Output audio file is then measured again for it's RMS and Peak values.

About the author:

Helios Martinez Dominguez is a musician and audio engineer. Is the recording, mix and master engineer of Estudio Siddhi.
There are more than thirty records recorded, mixed and mastered in his experience. Some can be listened (and downloaded) at:

https://helios70.bandcamp.com
https://heliosmartinezdominguez.bandcamp.com
https://avrvm-music.bandcamp.com
https://bounces.bandcamp.com
https://judaslion.bandcamp.com

Bugs fixed:
- Non Standard WAV Headers failed to be properly processed requiring RAW import into DAW.

Known bugs:
- Incomplete handling when input file is inexisting or filename contain spaces.

TODO:
- Percentage increase and progress bar while processing audio file.
- Migrate remaster-compressor.sh to C language.
- 24bit precission handling.
- AIFF support.
