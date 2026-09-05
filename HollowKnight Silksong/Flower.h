#pragma once
class Flower : public GameObject {
	// GameObject을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC DC) override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void Release() override;

private:
	INT		index;
};

