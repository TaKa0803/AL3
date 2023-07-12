#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <Input.h>
#include<sound.h>

#include "x3daudio.h"
#include <assert.h>
#include <xaudio2.h>
#pragma comment(lib, "xaudio2.lib")
#include <fstream>

struct ChunkHeader {
	char id[4];   // チャンク用のID
	int32_t size; // チャンクサイズ
};
struct RiffHeader {
	ChunkHeader chunk; // RIFF
	char type[4];      // WAVE
};
struct FormatChunk {
	ChunkHeader chunk; // ｆｍｔ
	WAVEFORMATEX fmt;  // 波形フォーマット
};

// 音声データ
struct SoundData {
	// 波形フォーマット
	WAVEFORMATEX wfex;
	// バッファの先頭アドレス
	BYTE* pBuffer;
	// バッファのサイズ
	unsigned int bufferSize;
};
class Player;

class GameScene;

class Enemy {
public:
	//syoki
	void Initialize(Model* model, uint32_t textureHandle, Vector3 translation);

	void Update();

	void Draw(ViewProjection view);

	void Fire();
	//
	void ApproachFazeInitialize();

	bool Approach();
	bool Leave();

	void SetPlayer(Player* player) { player_ = player; }
	
	Vector3 GetWorldPosition();


	void OnCollision();

	//const std::list<EnemyBullet*>& GetBullets() { return bullets_; }

	float Getsize() { return size; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDraw() { return isdraw; }

private:
	//位置
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};
	//攻撃モード
	Phase phase_=Phase::Approach;

	bool isdraw = true;


	//発射感覚
	static const int kFireIntervaal = 60;
	//発射タイマー
	int32_t timer = 0;
	//
	Input* input_ = nullptr;

	//自キャラ
	Player* player_=nullptr;

	float size;

	//ゲームシーン
	GameScene* gameScene_ = nullptr;

	Sound* music_=nullptr;
};