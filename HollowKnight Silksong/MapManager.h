#pragma once
class MapManager {
	COMPONENT_SINGLETON(MapManager)

	void Initialize();
	void Update();
	void Late_Update();
	void Render_Backward(HDC DC);
	void Render_Forward(HDC DC);
	void Release();
	
public:
	void MapGenerator_Village_Initialize();
	void MapGenerator_Dungeon_Initialize();

	void MapGenerator_Village_Back(HDC DC);
	void MapGenerator_Village_Front(HDC DC);

	void MapGenerator_Dungeon_Back(HDC DC);
	void MapGenerator_Dungeon_Front(HDC DC);
	void UI_Initialize();
	void Player_Initialize();

	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

private:
	GameObject* Player;
	FLOAT		XVALUE, YVALUE;
};

