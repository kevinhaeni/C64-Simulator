#include "SDL.h"
#include "SDL_audio.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

SDL_AudioSpec desiredDeviceSpec;
SDL_AudioSpec spec;
SDL_AudioDeviceID dev;

struct SDLVoice{
	int frequency;				// the frequency of the voice
	int amp;					// the amplitude of the voice

	int samplesLeft;			// number of samples to be played, eg: 1.2 seconds * 44100 samples per second
	int audioPosition = 0;		// counter

	void playForNMicroSeconds(int n){		 // calculates the number of samples and delays the program
		samplesLeft = 44100 * n / 1000;
		audioPosition = 0;					 // reset the counter
		SDL_PauseAudioDevice(dev, 0);		 // play
		SDL_Delay(n);						 // delay the program to prevent the voice to be overridden before it has been played to the end
		SDL_PauseAudioDevice(dev, 1);		 // pause
	}

	enum WaveForm{
		SINE, RECT, SAWTOOTH, TRIANGLE
	} waveForm;

	uint8_t getSample(){

		int time = (audioPosition * frequency) / 44100;
        uint8_t rect_value = 0x00;
        
       // std::cout << audioPosition << " - ";
		switch (waveForm){
		case SINE:
		{
			float sineStep = 2 * M_PI * audioPosition * frequency / 44100;
			return amp * sin(sineStep);
			break;
		}			
		case RECT:
            if(fmod((double)audioPosition, (double)frequency) >= 0.5 * frequency){
                rect_value = 0xFF;
            }
            return amp * rect_value;
			break;

		case SAWTOOTH:
			return amp * fmod((double)audioPosition, (double)frequency);
			break;

		case TRIANGLE:
            return amp * abs(fmod((double)audioPosition, (double)frequency) - 0.5 * (double)frequency) ;
			break;

		default:
			return 0;
        }
	}
} voice;


// SDL calls this function whenever it wants its buffer to be filled with samples
void SDLAudioCallback(void *data, Uint8 *buffer, int length){
	uint8_t *stream = (uint8_t*)buffer;
	
	for (int i = 0; i <= length; i++){

		if (voice.samplesLeft-- <= 0)
			stream[i] = 0;
		else
		{
			stream[i] = voice.getSample();
			voice.audioPosition++;
		}		


	}
}

void initSDL(){
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
	SDL_zero(desiredDeviceSpec);

	desiredDeviceSpec.freq = 44100;			// Sample Rate
	desiredDeviceSpec.format = AUDIO_U8;	// Unsigned 8-Bit Samples
	desiredDeviceSpec.channels = 1;			// Mono
	desiredDeviceSpec.samples = 2048;		// The size of the Audio Buffer (in number of samples, eg: 2048 * 1 Byte (AUDIO_U8)
	desiredDeviceSpec.callback = SDLAudioCallback;

	dev = SDL_OpenAudioDevice(NULL, 0, &desiredDeviceSpec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
	if (dev == 0) {
		printf("\nFailed to open audio: %s\n", SDL_GetError());
	}
	else {
		SDL_PauseAudioDevice(dev, 1); /* pause! */
		SDL_PauseAudio(1);
	}
}

int main(int argc, char* argv[]){
	initSDL();

    voice.waveForm = SDLVoice::WaveForm::TRIANGLE;
    voice.amp = 1;

    voice.frequency = 440;
    voice.playForNMicroSeconds(2000);
    
    
	voice.frequency = 500;
	voice.playForNMicroSeconds(300);
	voice.frequency = 750;
	voice.playForNMicroSeconds(300);
	voice.frequency = 1000;
	voice.playForNMicroSeconds(300);
	voice.frequency = 300;
	voice.playForNMicroSeconds(1000);

	int i;
	std::cin >> i;

	return 0;
}