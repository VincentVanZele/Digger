#include "MiniginPCH.h"
#include "AudioResource.h"

// SDL
/*#include "SDL_mixer.h"

int engine::AudioService::m_iChannelCount = 1;

engine::AudioService::AudioService()
	: m_iChannel(m_iChannelCount)
	, m_pChunk(nullptr)
	, m_pMusic(nullptr)
{
	m_iChannelCount++;
}

void engine::AudioService::Initialize()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void engine::AudioService::Delete()
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

void engine::AudioService::SaveSound(std::string& filePath)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

	if (chunk == nullptr)
	{
		std::string exception{ Mix_GetError() };
		throw std::exception(exception.c_str());
	}

	m_vSounds.push_back(chunk);
}

void engine::AudioService::SaveMusic(std::string& filePath)
{
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());

	if (music == nullptr)
	{
		std::string exception{ Mix_GetError() };
		throw std::exception(exception.c_str());
	}

	m_vMusics.push_back(music);
}

Mix_Chunk& engine::AudioService::GetChunk() const
{
	return *m_pChunk;
}

_Mix_Music& engine::AudioService::GetMusic() const
{
	return *m_pMusic;
}

void proxy::AudioService::SetChunk(Mix_Chunk* chunk)
{
	m_pChunk = chunk;
}

void engine::AudioService::SetMusic(_Mix_Music* music)
{
	m_pMusic = music;
}

void engine::AudioService::PlaySoundFromVect(int atIdx, int loop)
{
	Mix_PlayChannel(-1, m_vSounds[atIdx], loop);
}

void engine::AudioService::PlayMusicFromVect(int atIdx, int loop)
{
	Mix_PlayMusic(m_vMusics[atIdx], loop);
}

void engine::AudioService::PlaySound(int loop)
{
	Mix_PlayChannel(m_iChannel, m_pChunk, loop);
}

void engine::AudioService::PlayMusic(int loop)
{
	Mix_PlayMusic(m_pMusic, loop);
}

void engine::AudioService::Pause()
{
	Mix_Pause(m_iChannel);
}

bool engine::AudioService::IsPlaying()
{
	return Mix_Playing(m_iChannel);
}

bool engine::AudioService::IsPaused()
{
	return Mix_Paused(m_iChannel);
}

void engine::AudioService::StopSounds()
{
	Mix_HaltChannel(-1);
}

void engine::AudioService::StopMusic()
{
	Mix_HaltMusic();
}*/


