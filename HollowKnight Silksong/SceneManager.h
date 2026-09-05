#pragma once
class SceneManager {
	COMPONENT_SINGLETON(SceneManager)
	
public:
	void	Initialize()		;
	void	Update()			;
	void	Late_Update()		;
	void	Render(HDC DC)		;
	void	Release()			;
	
public:
	void Scene_Transition(STAGE_TYPE _SceneType);
	
	STAGE_TYPE	Get_CurrentScene() { return CurrentScene; }

	void	PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	void Set_NextScene(STAGE_TYPE _TS) { TargetScene = _TS; }
	STAGE_TYPE Get_NextScene() { return  TargetScene; }
private:
	Scene*		SceneList[(LONG)STAGE_TYPE::STAGE_END];

	STAGE_TYPE	PreviousScene;
	STAGE_TYPE	CurrentScene;

	STAGE_TYPE	TargetScene;
	
};
