#pragma once
class Scene_Load : public Scene {
public:
	Scene_Load();
	virtual ~Scene_Load();

public:
	void Initialize()		override;
	void Update()			override;
	void Late_Update()		override;
	void Render(HDC DC)		override;
	void Release()			override;

public:
	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	

private:
	DWORD		dwTime;
	DWORD		SceneTransitionTime;

	INT			StartPixelFrame;

	
};

