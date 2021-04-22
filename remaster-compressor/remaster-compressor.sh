echo REMASTER COMPRESSOR - V.0.2
echo By: Helios Martinez Dominguez
echo Estudio Siddhi - Copyleft 2021.
echo
echo Remastering:
echo $1
echo
./wav_header $1
echo
echo Input RMS:
./rms $1
echo Input Peak:
./peak $1
echo
./sin-comp $1 $1-remastered.wav
echo
echo Output RMS:
./rms $1-remastered.wav
echo Output Peak:
./peak $1-remastered.wav
echo
echo Remastered:
echo $1-remastered.wav
