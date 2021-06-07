
/*未実装なので使用していません*/

#include "Sound.h"

Sound::Sound()
    :mChunk(nullptr)
    , mChannel(-1)
{
}

bool Sound::LoadSound(const std::string& fileName)
{
    mChunk = Mix_LoadWAV(fileName.c_str());
    return mChunk != nullptr;
}

bool Sound::IsPlaying()
{
    return mChannel >= 0 && Mix_Playing(mChannel);
}


Sound::~Sound()
{
    Mix_FreeChunk(mChunk);//読み取ったサウンドの開放
}

void Sound::Play()
{
    mChannel = Mix_PlayChannel(-1, mChunk, 0);
}

void Sound::Stop()
{
    if (mChannel == -1)
    {
        return;
    }

    if (Mix_Playing(mChannel))
    {
        Mix_HaltChannel(mChannel);
    }
    mChannel = -1;
}
