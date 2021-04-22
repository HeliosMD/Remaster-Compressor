gcc -o rms source/rms.c -std=c99 -lm
gcc -o peak source/peak.c -std=c99 -lm
gcc -o sin-comp source/sin-comp.c -std=c99 -lm
gcc -o wav_header source/wav_header.c -std=c99 -lm
chmod 775 remaster-compressor.sh
