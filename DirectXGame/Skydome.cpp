#include<Skydome.h>


void Skydome::Initialize(Model* model) { 
	skydomeScalar = 500;
	model_ = model;

	//設定
	worldTransform_.translation_={0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {skydomeScalar, skydomeScalar, skydomeScalar};
	
	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw(ViewProjection view){model_->Draw(worldTransform_, view);}