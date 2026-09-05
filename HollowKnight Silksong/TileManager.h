#pragma once
class TileManager
{
	COMPONENT_SINGLETON(TileManager);
public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void		Picking_Tile(POINT ptMouse, int iDrawID, int iOption);
	void		Erase_Tile(POINT ptMouse);
	void		Save_Tile(const TCHAR* _FileAddress);
	void		Load_Tile(const TCHAR* _FileAddress);

	void		Set_DrawOption(INT I) { DrawOption = I; }

private:
	vector<GameObject*>	m_vecTile;
	INT		DrawOption;
};

