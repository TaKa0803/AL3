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

#pragma region debug
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#pragma endregion

	//float movez = 1.0f;

	//float rotate = (1.0f / 360.0f);

	//worldTransform_.translation_.z += movez;
	//worldTransform_.rotation_.y += rotate;
	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1,1,1}, worldTransform_.rotation_, worldTransform_.translation_);

	//カメラオブジェクトのワールド行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	//ビュープロジェクションを転送
	viewProjection_.TransferMatrix();


}

