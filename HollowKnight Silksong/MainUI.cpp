#include "PCH.h"
#include "MainUI.h"

MainUI::MainUI() : Player(nullptr), Stone_Appended(true), MukJu_Appended(true), dwTime{ GetTickCount(), GetTickCount() }, AnimEscape(true), Render_Enable(true),
		MukJuQuantity_ToAppend(0), StoneQuantity_ToAppend(0){ }
MainUI::~MainUI()	{ Release(); }
int* a = nullptr;
void MainUI::Initialize() {
	memset(HP_INFO, -1, sizeof(HP_INFO));
	memset(Silk_INFO, -1, sizeof(Silk_INFO));
	ZeroMemory(CoinText, sizeof(CoinText));
}
int MainUI::Update() {

	Update_RECT();
	if (Player == nullptr) { Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();}

	MukJu_Quantity	= dynamic_cast<PlayerObject*>(Player)->Get_MukJu();
	Stone_Quantity	= dynamic_cast<PlayerObject*>(Player)->Get_SilverStone();
	Silk_Quantity	= dynamic_cast<PlayerObject*>(Player)->Get_Silk();
	HP_Quantity		= dynamic_cast<PlayerObject*>(Player)->Get_HP();

	for (int i = 0; i < HP_Quantity; ++i) {
		HP_INFO[i] = 0;
	}
	for (int i = 0; i < Silk_Quantity; ++i) {
		Silk_INFO[i] = 0;
	}

	OBJINFO.CenterPosX = CameraManager::Get_Instance()->GetLookAt().X;
	OBJINFO.CenterPosY = CameraManager::Get_Instance()->GetLookAt().Y;

	return 0;
} 
void MainUI::Late_Update() {

}
void MainUI::Render(HDC DC) {
	if (Render_Enable) {
		FileManager::Get_Instance()->Append_Image(DC, L"HP_BackBar", { OBJINFO.CenterPosX - 370.f,	OBJINFO.CenterPosY - 290.f }, 0.5f, 0.5f);
		for (int i = 0; i < 10; ++i) {
			if (HP_INFO[i] == 0) { FileManager::Get_Instance()->Append_Image(DC, L"HP", { OBJINFO.CenterPosX - 481.f + 37.5f * i,	OBJINFO.CenterPosY - 286.f }, 0.41f, 0.41f); }
		}
		for (int i = 0; i < 10; ++i) {
			if (HP_INFO[i] == 1) {

				if (AnimEscape) {
					StartPixelFrame = 0;
					AnimEscape = false;
				}

				if (PlayAnimation_Once(DC, L"LoseHP", 165, 50, { OBJINFO.CenterPosX - 481.f + 37.5f * i, OBJINFO.CenterPosY - 287.f }, 0.41f, 0.41f)) {
					AnimEscape = true;
					for (int j = 0; j < 10; ++j) {
						if (HP_INFO[j] == 1) {
							HP_INFO[j] = -1;
						}
					}
				}
			}
		}


		FileManager::Get_Instance()->Append_Image(DC, L"Thread", { OBJINFO.CenterPosX - 520.f,	OBJINFO.CenterPosY - 220.f }, 0.5f, 0.5f);
		for (int i = 0; i < 15; ++i) {
			if (Silk_INFO[i] == 0) { FileManager::Get_Instance()->Append_Image(DC, L"Silk", { OBJINFO.CenterPosX - 562.f + 6.f * i,	OBJINFO.CenterPosY - 221.f }, 0.5f, 0.5f); }
		}
		FileManager::Get_Instance()->Append_Image(DC, L"MukJu", { OBJINFO.CenterPosX - 570.f,	OBJINFO.CenterPosY - 160.f }, 0.6f, 0.6f);

		Append_MukJu_Quantity(DC, &MukJuQuantity_ToAppend);

		FileManager::Get_Instance()->Append_Image(DC, L"Stone", { OBJINFO.CenterPosX - 570.f,	OBJINFO.CenterPosY - 110.f }, 0.6f, 0.6f);

		RECT MukJuText2 = { 120, 230 ,200 , 262 };

		wsprintf(CoinText, L"%d", Stone_Quantity);
		DrawText(DC, CoinText, 3, &MukJuText2, DT_LEFT | DT_VCENTER);
	}
}
void MainUI::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {

}
void MainUI::Release()		{	}

void MainUI::Append_MukJu_Quantity(HDC DC, INT* _EA) {

	RECT MukJuText1 = { 120, 178 ,250 , 210 };
	TCHAR MUKJU[16] = { 0 };
	if (MukJuQuantity_ToAppend == 0) {
		wsprintf(MUKJU, L"%d", MukJu_Quantity);
		dwTime[1] = GetTickCount();
	}
	
	if (MukJuQuantity_ToAppend > 0) {
		if (dwTime[1] + 500 >= GetTickCount()) {
			wsprintf(MUKJU, L"%d - %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu(), MukJuQuantity_ToAppend);
		}
		if (dwTime[1] + 500 < GetTickCount()) {
			dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Set_MukJu(
				dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu() - 1);
			MukJuQuantity_ToAppend -= 1;
			wsprintf(MUKJU, L"%d - %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu(), MukJuQuantity_ToAppend);
		}
	}

	DrawText(DC, MUKJU, 10, &MukJuText1, DT_LEFT | DT_VCENTER);
}

void MainUI::Append_Stone_Quantity(INT* _Stone, INT _EA)
{
	if (Stone_Appended) {
		if (dwTime[0] + 1000 < GetTickCount()) {
			Stone_Appended = false;
			dwTime[0] = GetTickCount();
		}
	}
}

void MainUI::Append_HP_Quantity(INT* _HP, INT _EA) {
	if (HP_Quantity >= 10) {
		HP_Quantity = 10;
		return;
	}

	for (int i = HP_Quantity; i < HP_Quantity + _EA; ++i) {
		if (HP_INFO[0] != 1) {
			HP_INFO[i] = 0;
		}
	}
	dynamic_cast<PlayerObject*>(Player)->Set_HP(HP_Quantity + _EA);
}

void MainUI::Append_Silk_Quantity(INT* _Silk, INT _EA) {
	if (Silk_Quantity >= 15) {
		Silk_Quantity = 15;
		return;
	}

	for (int i = Silk_Quantity; i < Silk_Quantity + _EA; ++i) {
		if (Silk_INFO[0] != 1) {
			Silk_INFO[i] = 0;
		}
	}
	dynamic_cast<PlayerObject*>(Player)->Set_Silk(Silk_Quantity + _EA);
}

void MainUI::Remove_MukJu_Quantity(INT* _MukJu, INT _EA)
{
}

void MainUI::Remove_Stone_Quantity(INT* _Stone, INT _EA)
{
}

void MainUI::Remove_HP_Quantity(INT* _HP, INT _EA) {
	if (HP_Quantity < _EA)		return;
	for (int i = HP_Quantity-1; i >= HP_Quantity - _EA; --i) {
		if (HP_INFO[0] != 1) {
			HP_INFO[i] = 1;
		}
	}
	dynamic_cast<PlayerObject*>(Player)->Set_HP(HP_Quantity - _EA);
}

void MainUI::Remove_Silk_Quantity(INT* _Silk, INT _EA) {
	if (Silk_Quantity < _EA) 	return;

	for (int i = Silk_Quantity-1; i >= Silk_Quantity - _EA; --i) {
		if (Silk_INFO[0] != 1) {
			Silk_INFO[i] = 1;
		}
	}
	dynamic_cast<PlayerObject*>(Player)->Set_Silk(Silk_Quantity - _EA);
}

BOOL MainUI::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X, StartTop - CameraManager::Get_Instance()->GetOffset().Y,
		Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		StartPixelFrame * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (StartPixelFrame >= _FrameEndIndex - 1) {
		return true;
	}

	if (_AnimSpeed + dwTime[0] < GetTickCount() && StartPixelFrame < _FrameEndIndex - 1) {
		StartPixelFrame++;
		dwTime[0] = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);

	return false;
}