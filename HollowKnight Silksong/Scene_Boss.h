#pragma once
class Scene_Boss : public Scene {
public:
	Scene_Boss();
	virtual ~Scene_Boss();

public:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC DC) override;
	void Release() override;

public:
	void StartScene(HDC DC);

	void After_BossDefeat(HDC DC);
	void PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1.f, FLOAT _MultipleHeight = 1.f);
	void PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1.f, FLOAT _MultipleHeight = 1.f);

private:
	GameObject* Player;
	GameObject* Boss;

	INT		TalkPassing;
	INT		StartPixelFrame[10];
	DWORD	dwTime;
	DWORD	StartdwTime;
	FLOAT	degree;
	BOOL	WalkAnimation;

	FLOAT	CarrierPosY;

	vector<int*>	SPFList;


};

