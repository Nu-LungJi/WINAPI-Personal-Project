#pragma once
enum class PTAG { VILLAGE_TO_DUNGEON, DUNGEON_TO_VILLAGE, DUNGEON_TO_GATE};

class Portal : public GameObject {
public:
	Portal() {}
	Portal(PTAG _pt) : PortalTag(_pt) {}
	~Portal() { Release(); }

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC DC) override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void Release() override;

public:
	void Set_PortalTag(PTAG _PT) { PortalTag = _PT; }

private:
	PTAG	PortalTag;
};

