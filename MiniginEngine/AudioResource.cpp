#include "MiniginPCH.h"
#include "AudioResource.h"

// SDL
/*#include "SDL_mixer.h"

int proxy::AudioService::m_iChannelCount = 1;

proxy::AudioService::AudioService()
	: m_iChannel(m_iChannelCount)
	, m_pChunk(nullptr)
	, m_pMusic(nullptr)
{
	m_iChannelCount++;
}

void proxy::AudioService::Initialize()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void proxy::AudioService::Delete()
{
	for (auto sound : m_vSounds)
	{
		Mix_FreeChunk(sound);
	}
	for (auto music : m_vMusics)
	{
		Mix_FreeMusic(music);
	}
}

void proxy::AudioService::SaveSound(std::string& filePath)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

	if (chunk == nullptr)
	{
		std::string exception{ Mix_GetError() };
		throw std::exception(exception.c_str());
	}

	m_vSounds.push_back(chunk);
}

void proxy::AudioService::SaveMusic(std::string& filePath)
{
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());

	if (music == nullptr)
	{
		std::string exception{ Mix_GetError() };
		throw std::exception(exception.c_str());
	}

	m_vMusics.push_back(music);
}

Mix_Chunk& proxy::AudioService::GetChunk() const
{
	return *m_pChunk;
}

_Mix_Music& proxy::AudioService::GetMusic() const
{
	return *m_pMusic;
}

void proxy::AudioService::SetChunk(Mix_Chunk* chunk)
{
	m_pChunk = chunk;
}

void proxy::AudioService::SetMusic(_Mix_Music* music)
{
	m_pMusic = music;
}

void proxy::AudioService::PlaySoundFromVect(int atIdx, int loop)
{
	Mix_PlayChannel(-1, m_vSounds[atIdx], loop);
}

void proxy::AudioService::PlayMusicFromVect(int atIdx, int loop)
{
	Mix_PlayMusic(m_vMusics[atIdx], loop);
}

void proxy::AudioService::PlaySound(int loop)
{
	Mix_PlayChannel(m_iChannel, m_pChunk, loop);
}

void proxy::AudioService::PlayMusic(int loop)
{
	Mix_PlayMusic(m_pMusic, loop);
}

void proxy::AudioService::Pause()
{
	Mix_Pause(m_iChannel);
}

bool proxy::AudioService::IsPlaying()
{
	return Mix_Playing(m_iChannel);
}

bool proxy::AudioService::IsPaused()
{
	return Mix_Paused(m_iChannel);
}

void proxy::AudioService::StopSounds()
{
	Mix_HaltChannel(-1);
}

void proxy::AudioService::StopMusic()
{
	Mix_HaltMusic();
}*/


