#pragma once

class CSound
{
public:
	CSound();
	~CSound();

	void Update();

public:
	void AddSound(wstring name, wstring soundFile, bool bLoop = false);
	void Play(wstring name, float volume = 1.0f);
	void Stop(wstring name);
	void Pause(wstring name);
	void Resume(wstring name);

	bool IsPlaying(wstring name);
	bool IsPaused(wstring name);

	void Volume(wstring name, float volume);
	float Volume(wstring name);

	void GetAllNames(vector<wstring>& outNames);

private:
	FMOD::System* system = nullptr;
	FMOD::Sound** sounds;
	FMOD::Channel** channels;

	UINT maxChannelCount = 15;
	map<wstring, FMOD::Sound*> soundMap;
	map<wstring, FMOD::Sound*>::iterator it;
};