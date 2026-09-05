#pragma once
class Scene_Select :  public Scene {
public:
	Scene_Select();
	virtual ~Scene_Select();

public:
	void	Initialize()		override;
	void	Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Release()			override;

	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
		Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight);

private:
	vector<GameObject*>		ButtonList;
	DWORD					dwTime[10];
	INT						StartPixelIndex[10];

	INT						AnimationIndex;
};

