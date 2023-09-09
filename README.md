# Sound Generator

Generate sounds and generate .wav files.

## Compile

Compile the program with the `lm` flag to link the math library.

```
gcc main.c -o sounds.exe -lm
```

## Usage

- Frequency: The frequency of the note
- Output-File: The output filename (.wav)

```
sounds.exe <frequency> <output-file.wav>
```

## Example

Generate a C4 (Middle C) note:

```
sounds.exe 261.63 c4.wav 
```

### Some Example Notes

| Note      | Frequency (Hz) |
|-----------|----------------|
| B3        | 246.94         |
| C4 (Middle C) | 261.63    |
| C#4/Db4   | 277.18         |
| D4        | 293.66         |
| D#4/Eb4   | 311.13         |
| E4        | 329.63         |
| F4        | 349.23         |
| F#4/Gb4   | 369.99         |
| G4        | 392.00         |
| G#4/Ab4   | 415.30         |
| A4        | 440.00         |
| A#4/Bb4   | 466.16         |
| B4        | 493.88         |


## More Information

### Structure of a WAV File:

1. **RIFF Header**:
   - Begins with the characters "RIFF".
   - Specifies the size of the entire file.
   - Contains the "WAVE" identifier to denote that the file is a WAV format.

2. **Format Sub-chunk (fmt)**:
   - Begins with the characters "fmt ".
   - Describes the format of the audio data, including:
     - Audio format (e.g., PCM for uncompressed audio).
     - Number of channels (mono, stereo).
     - Sample rate (e.g., 44100 Hz).
     - Byte rate and block align.
     - Bits per sample (e.g., 16 bits).

3. **Data Sub-chunk**:
   - Begins with the word "data".
   - Contains the actual audio samples.
   - The size of this chunk corresponds to the length of the audio.

### How the WAV file is generated:

1. **WAV Header Creation**: The program starts by creating the RIFF header and the fmt sub-chunk based on the desired audio properties.

2. **Audio Data Generation**: Using the sine function and the provided frequency, the program generates a waveform representing the desired musical note. This waveform data is then written to the data sub-chunk.

3. **File Writing**: The constructed headers and audio data are written sequentially to a `.wav` file, producing a playable audio file.

### Importance of `TWO_PI` in the Program

The constant `TWO_PI` (represented mathematically as \(2\pi\)) is crucial for generating the sine wave audio signal. 
The sine function, used to produce the waveform, oscillates between its peak values over a \(2\pi\) interval, representing a full cycle. 
By multiplying the desired frequency with `TWO_PI`, we ensure that the generated waveform oscillates at the correct rate, producing the desired musical note. 

