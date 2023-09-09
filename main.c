#include <stdio.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define DURATION 2  // 2 seconds
#define VOLUME 32760  // Almost max volume
#define TWO_PI (3.14159265 * 2)

// WAV header structure
typedef struct {
    char chunkID[4];
    int chunkSize;
    char format[4];
    char subchunk1ID[4];
    int subchunk1Size;
    short audioFormat;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
    char subchunk2ID[4];
    int subchunk2Size;
} WavHeader;

WavHeader makeWavHeader(int sampleRate, short numChannels, short bitsPerSample);

int main(int argc, char *argv[]) {
    // Get command line arguments
    if (argc != 3) {
        printf("Usage: %s <frequency> <output_filename>\n", argv[0]);
        return 1;
    }
    double FREQUENCY = atof(argv[1]);
    char *output_filename = argv[2];

    // Open file for writing
    FILE *file = fopen(output_filename, "wb");
    if (!file) {
        printf("Could not open file %s for writing\n", output_filename);
        return 1;
    }

    // Write WAV header
    WavHeader header = makeWavHeader(SAMPLE_RATE, 1, 16);
    fwrite(&header, sizeof(header), 1, file);

    // Write audio samples
    for (int i = 0; i < SAMPLE_RATE * DURATION; i++) {
        double time = (double)i / SAMPLE_RATE;
        short sample = (short)(VOLUME * sin(FREQUENCY * TWO_PI * time));
        fwrite(&sample, sizeof(sample), 1, file);
    }

    fclose(file);
    printf("File saved as %s\n", output_filename);
    return 0;
}

WavHeader makeWavHeader(int sampleRate, short numChannels, short bitsPerSample) {
    WavHeader header;
    header.chunkSize = 36 + 2 * SAMPLE_RATE * DURATION;
    header.subchunk2Size = 2 * SAMPLE_RATE * DURATION;
    header.sampleRate = sampleRate;
    header.numChannels = numChannels;
    header.bitsPerSample = bitsPerSample;
    header.byteRate = sampleRate * numChannels * bitsPerSample / 8;
    header.blockAlign = numChannels * bitsPerSample / 8;

    // "RIFF"
    header.chunkID[0] = 'R';
    header.chunkID[1] = 'I';
    header.chunkID[2] = 'F';
    header.chunkID[3] = 'F';

    // "WAVE"
    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';

    // "fmt"
    header.subchunk1ID[0] = 'f';
    header.subchunk1ID[1] = 'm';
    header.subchunk1ID[2] = 't';
    header.subchunk1ID[3] = ' ';
    header.subchunk1Size = 16;
    header.audioFormat = 1;

    // "data"
    header.subchunk2ID[0] = 'd';
    header.subchunk2ID[1] = 'a';
    header.subchunk2ID[2] = 't';
    header.subchunk2ID[3] = 'a';

    return header;
}

