#include "PCH.h"
#include "Tile.h"

Tile::Tile()
	: m_iDrawID(0), m_EnableTiling(false), m_DrawOption(11)
{
}

Tile::~Tile() { Release(); }

void Tile::Initialize()
{
	m_TileScale = 0.8f;
}

int Tile::Update() {
	Update_RECT();
	return 0;
}

void Tile::Late_Update()
{
}

void Tile::Render(HDC DC) {
	
	
	if (m_EnableTiling) {
		TCHAR		KeyName[32];

		if (m_DrawOption == 1) { lstrcpyW(KeyName, L"Tile1"); }
		else if (m_DrawOption == 2) { lstrcpyW(KeyName, L"Tile2"); }
		else if (m_DrawOption == 3) { lstrcpyW(KeyName, L"Tile3"); }
		else if (m_DrawOption == 4) { lstrcpyW(KeyName, L"Tile4"); }
		else if (m_DrawOption == 5) { lstrcpyW(KeyName, L"Tile5"); }
		else if (m_DrawOption == 6) { lstrcpyW(KeyName, L"Tile6"); }
		else if (m_DrawOption == 7) { lstrcpyW(KeyName, L"Tile7"); }
		else if (m_DrawOption == 8) { lstrcpyW(KeyName, L"Tile8"); }
		else if (m_DrawOption == 9) { lstrcpyW(KeyName, L"Tile9"); }

		else if (m_DrawOption == 11) { lstrcpyW(KeyName, L"BigTile1"); }
		else if (m_DrawOption == 12) { lstrcpyW(KeyName, L"BigTile2"); }
		else if (m_DrawOption == 13) { lstrcpyW(KeyName, L"BigTile3"); }
		else if (m_DrawOption == 14) { lstrcpyW(KeyName, L"BigTile4"); }
		else if (m_DrawOption == 15) { lstrcpyW(KeyName, L"BigTile5"); }
		else if (m_DrawOption == 16) { lstrcpyW(KeyName, L"BigTile6"); }
		else if (m_DrawOption == 17) { lstrcpyW(KeyName, L"BigTile7"); }
		else if (m_DrawOption == 18) { lstrcpyW(KeyName, L"BigTile8"); }
		
		else {
			lstrcpyW(KeyName, L"");
		}


		HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(KeyName)->Get_SubDC();

		UINT Width = FileManager::Get_Instance()->Find_BMPFile(KeyName)->Get_BMPWidth();
		UINT Height = FileManager::Get_Instance()->Find_BMPFile(KeyName)->Get_BMPHeight();

		OBJINFO.Width = Width * m_TileScale;
		OBJINFO.Height = Height * m_TileScale;

		int		iScrollX = (int)CameraManager::Get_Instance()->GetOffset().X;
		int		iScrollY = (int)CameraManager::Get_Instance()->GetOffset().Y;

		
		GdiTransparentBlt(DC, OBJRECT.left - iScrollX, OBJRECT.top - iScrollY, Width * m_TileScale, Height * m_TileScale, MemDC, 0, 0, Width, Height, RGB(255, 0, 255));
	}
}

void Tile::Release()
{
}

void Tile::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {

}
