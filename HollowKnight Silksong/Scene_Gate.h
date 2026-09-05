#pragma once
class Scene_Gate : public Scene {
public:
	Scene_Gate();
	virtual ~Scene_Gate();

public:
	void	Initialize()	override;
	void	Update()		override;
	void	Late_Update()	override;
	void	Render(HDC DC)	override;
	void	Release()		override;

	void PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1.f, FLOAT _MultipleHeight = 1.f);
	void PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1.f, FLOAT _MultipleHeight = 1.f);
	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

private:
	GameObject* Player;
	FLOAT		LiftValue;
	GameObject* Gate;

	BOOL		CarryOn;

	INT StartPixelFrame[10];
	DWORD	dwTime[10];
};

