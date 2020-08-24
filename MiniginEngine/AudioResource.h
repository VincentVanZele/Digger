#pragma once
// Includes
#include <vector>
#include "SDL_mixer.h"
 

// Class-Struct Forward declarations
struct Mix_Chunk;
struct _Mix_Music;

namespace engine
{
	class AudioResource
	{
	public:
		AudioResource() = default;
		virtual ~AudioResource() = default;

		AudioResource(const AudioResource&) = delete;
		AudioResource(AudioResource&&) = delete;
		AudioResource& operator= (const AudioResource&) = delete;
		AudioResource& operator= (const AudioResource&&) = delete;

		// Functions
		virtual void Initialize() = 0;
		virtual void Delete() = 0;

		virtual void SaveSound(std::string& filePath) = 0; // push to m_vSounds
		virtual void SaveMusic(std::string& filePath) = 0; // push to m_vMusics

		virtual void PlaySoundFromVect(int atIdx, int loop) = 0; // Play Chunks
		virtual void PlayMusicFromVect(int atIdx, int loop) = 0;

		virtual void PlaySound(int loop) = 0;
		virtual void PlayMusic(int loop) = 0;

		virtual void Pause() = 0;

		virtual bool IsPlaying() = 0;
		virtual bool IsPaused() = 0;

		virtual void StopSounds() = 0;
		virtual void StopMusic() = 0;

	protected:
		std::vector<Mix_Chunk*> m_vSounds; // Store Chunks
		std::vector<_Mix_Music*> m_vMusics; // Store Musics
	private:

	};

	class AudioService final : public AudioResource
	{
	public:
		AudioService();
		virtual ~AudioService() = default;

		// Functions
		virtual void Initialize() override;
		virtual void Delete() override;

		virtual void SaveSound(std::string& filePath) override; // push to m_vSounds
		virtual void SaveMusic(std::string& filePath) override; // push to m_vMusics

		Mix_Chunk& GetChunk() const;
		void SetChunk(Mix_Chunk* chunk);

		_Mix_Music& GetMusic() const;
		void SetMusic(_Mix_Music* music);

		virtual void PlaySoundFromVect(int atIdx, int loop) override; // Play Chunks
		virtual void PlayMusicFromVect(int atIdx, int loop) override;

		virtual void PlaySound(int loop) override;
		virtual void PlayMusic(int loop) override;

		virtual void Pause() override;

		virtual bool IsPlaying() override;
		virtual bool IsPaused() override;

		virtual void StopSounds() override;
		virtual void StopMusic() override;

	protected:
	private:
		Mix_Chunk* m_pChunk;
		_Mix_Music* m_pMusic;

		int m_iChannel;
		static int m_iChannelCount;
	};
}

