#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:
	void Initialize(ViewProjection camera);

	void Update();

	ViewProjection GetViewProjection() { return viewProjection_; }

	const WorldTransform* GetWorldTransform() { return &worldTransform_; }

private:
	//ビュー
	ViewProjection viewProjection_;
	//ワールド
	WorldTransform worldTransform_;
};