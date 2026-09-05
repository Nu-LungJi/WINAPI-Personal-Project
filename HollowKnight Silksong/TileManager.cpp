#include "PCH.h"
#include "TileManager.h"

TileManager* TileManager::Instance = nullptr;

TileManager::TileManager(){ 
	m_vecTile.reserve(TILEX * TILEY);
	DrawOption = 1;
}
TileManager::~TileManager() { Release(); }

void TileManager::Initialize(){

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float		fX = (TILECX * j) + (TILECX >> 1);
			float		fY = (TILECY * i) + (TILECY >> 1);

			GameObject* pTile = AbstractFactory<Tile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}
}
int	 TileManager::Update(){
	for (auto& pTile : m_vecTile)
		pTile->Update();

	if (KEY_COMMAND(KEY::NUM_1, KEY_STATE::DOWN)) Set_DrawOption(1);
	if (KEY_COMMAND(KEY::NUM_2, KEY_STATE::DOWN)) Set_DrawOption(2);
	if (KEY_COMMAND(KEY::NUM_3, KEY_STATE::DOWN)) Set_DrawOption(3);
	if (KEY_COMMAND(KEY::NUM_4, KEY_STATE::DOWN)) Set_DrawOption(4);
	if (KEY_COMMAND(KEY::NUM_5, KEY_STATE::DOWN)) Set_DrawOption(5);
	if (KEY_COMMAND(KEY::NUM_6, KEY_STATE::DOWN)) Set_DrawOption(6);
	if (KEY_COMMAND(KEY::NUM_7, KEY_STATE::DOWN)) Set_DrawOption(7);
	if (KEY_COMMAND(KEY::NUM_8, KEY_STATE::DOWN)) Set_DrawOption(8);
	if (KEY_COMMAND(KEY::NUM_9, KEY_STATE::DOWN)) Set_DrawOption(9);

	if (KEY_COMMAND(KEY::F1, KEY_STATE::DOWN)) Set_DrawOption(11);
	if (KEY_COMMAND(KEY::F2, KEY_STATE::DOWN)) Set_DrawOption(12);
	if (KEY_COMMAND(KEY::F3, KEY_STATE::DOWN)) Set_DrawOption(13);
	if (KEY_COMMAND(KEY::F4, KEY_STATE::DOWN)) Set_DrawOption(14);
	if (KEY_COMMAND(KEY::F5, KEY_STATE::DOWN)) Set_DrawOption(15);
	if (KEY_COMMAND(KEY::F6, KEY_STATE::DOWN)) Set_DrawOption(16);
	if (KEY_COMMAND(KEY::F7, KEY_STATE::DOWN)) Set_DrawOption(17);
	if (KEY_COMMAND(KEY::F8, KEY_STATE::DOWN)) Set_DrawOption(18);
	if (KEY_COMMAND(KEY::F9, KEY_STATE::DOWN)) Set_DrawOption(19);

	return OBJ_ALIVE;
}
void TileManager::Late_Update(){
	for (auto& pTile : m_vecTile)
		pTile->Late_Update();
}
void TileManager::Render(HDC hDC){
	int	iCullX = abs((int)CameraManager::Get_Instance()->GetOffset().X / TILECX);
	int	iCullY = abs((int)CameraManager::Get_Instance()->GetOffset().Y / TILECY);

	int iMaxX = iCullX + (DEFAULT_WINDOW_CX ) / TILECX + 5;
	int iMaxY = iCullY + DEFAULT_WINDOW_CY / TILECY + 5;

	for (int i = iCullY - 5; i < iMaxY; ++i)
	{
		for (int j = iCullX - 5; j < iMaxX; ++j)
		{
			int iIndex = i * TILEX + j;
			
			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;
			m_vecTile[iIndex]->Render(hDC);
		}
	}
}
void TileManager::Release() {
	for_each(m_vecTile.begin(), m_vecTile.end(), SAFE_DELETE<GameObject*>);
	m_vecTile.clear();
}

void TileManager::Picking_Tile(POINT ptMouse, int iDrawID, int iOption) {
	int	x = ptMouse.x / TILECX;
	int	y = ptMouse.y / TILECY;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size() ||
		dynamic_cast<Tile*>(m_vecTile[iIndex])->Get_EnableTiling() == true)
		return;

	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_Option(iOption);
	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_EnableTiling(true);
	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_DrawOption(DrawOption);
}

void TileManager::Erase_Tile(POINT ptMouse) {
	int	x = ptMouse.x / TILECX;
	int	y = ptMouse.y / TILECY;

	int iIndex = y * TILEX + x;
	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size() ||
		dynamic_cast<Tile*>(m_vecTile[iIndex])->Get_EnableTiling() == false)
		return;
	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_EnableTiling(false);
	dynamic_cast<Tile*>(m_vecTile[iIndex])->Set_DrawOption(0);
}

void TileManager::Save_Tile(const TCHAR* _FileAddress)
{
	HANDLE	hFile = CreateFile(_FileAddress, // 파일 이름이 포함된 경로
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		CREATE_ALWAYS,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(hWnd, _T("Tile File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD		dwByte(0);
	int			iDrawID(0), iOption(0), iDO(0);
	BOOL		Enable(false);

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<Tile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<Tile*>(pTile)->Get_Option();
		Enable = dynamic_cast<Tile*>(pTile)->Get_EnableTiling();
		iDO = dynamic_cast<Tile*>(pTile)->Get_DrawOption();

		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &Enable, sizeof(BOOL), &dwByte, NULL);
		WriteFile(hFile, &iDO,	sizeof(INT), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(hWnd, _T("Tile 저장 완료"), L"Success", MB_OK);
}

void TileManager::Load_Tile(const TCHAR* _FileAddress)
{
	HANDLE	hFile = CreateFile(_FileAddress, // 파일 이름이 포함된 경로
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(hWnd, _T("Load Tile File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD	dwByte(0);		// eof 역할

	Release();

	INFO		tInfo{};
	int			iDrawID(0), iOption(0), iDO(0);
	BOOL		Enable(false);
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &Enable, sizeof(BOOL), &dwByte, NULL);
		ReadFile(hFile, &iDO, sizeof(INT), &dwByte, NULL);
		if (0 == dwByte)
			break;

		GameObject* pTile = AbstractFactory<Tile>::Create(tInfo.CenterPosX, tInfo.CenterPosY);
		dynamic_cast<Tile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<Tile*>(pTile)->Set_Option(iOption);
		dynamic_cast<Tile*>(pTile)->Set_EnableTiling(Enable);
		dynamic_cast<Tile*>(pTile)->Set_DrawOption(iDO);

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}
