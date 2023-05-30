#pragma once
#include "Model.h"
#include "WorldTransform.h"


///

class Skydome {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection view);

	float GetScalar() { return skydomeScalar; }
	private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

	float skydomeScalar = 0;
	
};