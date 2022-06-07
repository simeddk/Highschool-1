#include "stdafx.h"
#include "CSound.h"

CSound::CSound()
{
	FMOD::System_Create(&system);
	FMOD_RESULT result = system->init(maxChannelCount, FMOD_INIT_NORMAL, nullptr);
	assert(result == FMOD_RESULT::FMOD_OK);

	channels = new FMOD::Channel*[maxChannelCount];
	sounds = new FMOD::Sound*[maxChannelCount];

	ZeroMemory(channels, sizeof(FMOD::Channel*) * maxChannelCount);
	ZeroMemory(sounds, sizeof(FMOD::Sound*) * maxChannelCount);
}

CSound::~CSound()
{
	for (int i = 0; i < maxChannelCount; i++)
	{
		if (channels[i] != nullptr)
			channels[i]->stop();

		if (sounds[i] != nullptr)
			sounds[i]->release();
	}

	SafeDeleteArray(channels);
	SafeDeleteArray(sounds);

	system->release();
	system->close();

	soundMap.clear();
}

void CSound::Update()
{
	system->update();
}

void CSound::AddSound(wstring name, wstring soundFile, bool bLoop)
{
	soundFile = L"../../_Sounds/" + soundFile;
	string path = String::ToString(soundFile);

	bLoop
	? system->createStream(path.c_str(), FMOD_LOOP_NORMAL, nullptr, &sounds[soundMap.size()])
	: system->createStream(path.c_str(), FMOD_DEFAULT, nullptr, &sounds[soundMap.size()]);
	
	soundMap[name] = sounds[soundMap.size()];
}

void CSound::Play(wstring name, float volume)
{
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			system->playSound(FMOD_CHANNEL_FREE, it->second, false, &channels[count]);
			channels[count]->setVolume(volume);
		}
	}
}

void CSound::Stop(wstring name)
{
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->stop();
			break;
		}
	}
}

void CSound::Pause(wstring name)
{
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->setPaused(true);
			break;
		}
	}
}

void CSound::Resume(wstring name)
{
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->setPaused(false);
			break;
		}
	}
}

bool CSound::IsPlaying(wstring name)
{
	bool bPlay = false;
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->isPlaying(&bPlay);
			break;
		}
	}

	return bPlay;
}

bool CSound::IsPaused(wstring name)
{
	bool bPause = false;
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->getPaused(&bPause);
			break;
		}
	}

	return bPause;
}

void CSound::Volume(wstring name, float volume)
{
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->setVolume(volume);
			break;
		}
	}
}

float CSound::Volume(wstring name)
{
	float volume = 0;
	int count = 0;
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it, count++)
	{
		if (name == it->first)
		{
			channels[count]->getVolume(&volume);
			break;
		}
	}

	return volume;
}

void CSound::GetAllNames(vector<wstring>& outNames)
{
	it = soundMap.begin();
	for (it; it != soundMap.end(); ++it)
		outNames.push_back(it->first);
}
