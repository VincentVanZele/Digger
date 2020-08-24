#pragma once
#include "Scene.h"
#include "GameStructs.h"
#include <memory>

namespace engine
{
	class PlayerCharacter;
	class EnemyCharacter;
	class Texture2D;

	class TextComponent;
	class WorldGridComponent;

	class GameScenes final : public Scene
	{
	public:
		//GameScenes() = default;
		//~GameScenes() = default;

		GameScenes(GameMode mode = GameMode::Soloplayer); // default = solo

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Draw() const override;

		void SetUpWorld();

		// ---
		void SetGameMode(GameMode gMode);
		GameMode GetGameMode() const;

		int GetClosestPlayerByTile(int index);

		// --- players
		std::shared_ptr<PlayerCharacter> GetPlayer1;
		std::shared_ptr<PlayerCharacter> GetPlayer2; // need if check
		
		void RespawnPlayer(); // solo
		void RespawnPlayer(int player); // coop

		void AddScore(float score); // solo
		void AddScore(float score, int player); // coop

	protected:
	private:
		float m_Scale = 2.0f;
		GameMode m_GameMode;

		std::shared_ptr<WorldGridComponent> m_spWorld;

		std::shared_ptr<PlayerCharacter> m_spPlayer1;
		std::shared_ptr<PlayerCharacter> m_spPlayer2;

		std::vector<std::shared_ptr<EnemyCharacter>> m_vspEnemies{};

		// text
		std::shared_ptr<TextComponent> m_spScoreText;


		std::shared_ptr<Texture2D> m_spLife;
		std::shared_ptr<Texture2D> m_spLife2;

		// Game stats
		int m_player1Pos = 0, m_player2Pos = 0,
			m_Player1Lives = 3, m_Player2Lives = 3;

		float m_player1Score = 0.0f, m_player2Score = 0.0f,
			m_player1RespawnDeltaT = 0.0f, m_player2RespawnDeltaT = 0.0f,
			m_lifeDeltaT = 0.0f;

		bool m_respawnPlayer1 = false, m_respawnPlayer2;

		// Game info
		// char

	};
}