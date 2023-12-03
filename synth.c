#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <al.h>
#include <alc.h>
#include <GL/glut.h>

ALCdevice *device;
ALCcontext *context;
ALshort waveData[48000];
ALuint buffer;
ALuint source;
int SamplingFrequency;
double baseFrequency = 440.0;
double frequency;

void GetKey(unsigned char key, int x, int y)
{
    frequency = baseFrequency * pow(2.0, ((key - 49.0) / 12.0));

    alSourceStop(source);

    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    for (int i = 0; i < 48000; i++)
    {
        waveData[i] = 32767.0 * sin(2 * M_PI * frequency * i / SamplingFrequency);
    }
    alBufferData(buffer, AL_FORMAT_MONO16, waveData, sizeof(waveData), SamplingFrequency);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcePlay(source);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[])
{
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    alcGetIntegerv(device, ALC_FREQUENCY, 1, &SamplingFrequency);

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("synth");
    glutDisplayFunc(Display);
    glutKeyboardUpFunc(GetKey);
    glutMainLoop();

    return 0;
}