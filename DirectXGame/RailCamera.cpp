#include<RailCamera.h>
#include<Matrix.h>
#include<ImGuiManager.h>
void RailCamera::Initialize(ViewProjection camera) { 
	
	worldTransform_.translation_ = camera.translation_;
	worldTransform_.rotation_ = camera.rotation_;
	viewProjection_.farZ = camera.farZ;
	viewProjection_.Initialize();

}

void RailCamera::Update() { 
	
	//float movez = -1.0f;

	//float rotate = (1.0f / 360.0f);

	//worldTransform_.translation_.z += movez;
	//worldTransform_.rotation_.y += rotate;
	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1,1,1}, worldTransform_.rotation_, worldTransform_.translation_);

	//カメラオブジェクトのワールド行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	//ビュープロジェクションを転送
	viewProjection_.TransferMatrix();

#pragma region debug
	ImGui::Begin("Camera");
	ImGui::Text(
	    "translation %4.1f,%4.1f,%4.1f", worldTransform_.translation_.x,
	    worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text(
	    "rotate %4.1f,%4.1f,%4.1f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	    worldTransform_.rotation_.z);
	ImGui::End();
#pragma endregion
}

