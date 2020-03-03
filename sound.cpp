#include<windows.h>

#pragma comment(lib,"Winmm.lib")

int main()
{
    PlaySound("music.wav",NULL,SND_SYNC);
    return 0;
}