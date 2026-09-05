#pragma once
#include "Scene.h"
class Scene_Loading : public Scene {
	// Scene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC DC) override;
	void Release() override;
};

