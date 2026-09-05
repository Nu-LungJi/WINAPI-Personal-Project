#include "PCH.h"
#include "Scene_Boss.h"

Scene_Boss::Scene_Boss() : TalkPassing(0), StartPixelFrame{0}, dwTime(GetTickCount()), StartdwTime(GetTickCount()), CarrierPosY(0.f), degree(0.f),
		WalkAnimation(false){}
Scene_Boss::~Scene_Boss() { Release(); }

void Scene_Boss::Initialize() {
	if (ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->size() < 1) {
		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER, AbstractFactory<PlayerObject>::Create());
	}

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower01.bmp", L"Tile1");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower02.bmp", L"Tile2");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower13.bmp", L"Tile3");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower04.bmp", L"Tile4");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower05.bmp", L"Tile5");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower07.bmp", L"Tile6");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower10.bmp", L"Tile6");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower12.bmp", L"Tile7");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower08.bmp", L"Tile8");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower09.bmp", L"Tile9");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower01_Big.bmp", L"BigTile1");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower02_Big.bmp", L"BigTile2");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower03_Big.bmp", L"BigTile3");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower04_Big.bmp", L"BigTile4");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower05_Big.bmp", L"BigTile5");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower12_Big.bmp", L"BigTile6");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower13_Big.bmp", L"BigTile7");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Flower11.bmp", L"BigTile8");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Ref.bmp", L"Reference");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/BackGround.bmp", L"BackGround");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/BackGround_Front.bmp", L"BackGround_Front");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Floor_Right.bmp", L"FloorR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Floor_Left.bmp", L"FloorL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Walk/Walk11.bmp", L"WalkImage");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Walk/Walk_Anim.bmp", L"Walk");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_01.bmp", L"TalkAnim01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_02.bmp", L"TalkAnim02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_03.bmp", L"TalkAnim03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_04.bmp", L"TalkAnim04");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Carrier.bmp", L"Carrier");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/BossRoom/Chain.bmp", L"CarrierChain");

	//TileManager::Get_Instance()->Initialize();

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	Player->Set_Pos(DEFAULT_WINDOW_CX /2.f - 190.f, DEFAULT_WINDOW_CY / 2.f);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_BOSS, AbstractFactory<BossObject>::Create());
	Boss = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS)->front();
	Boss->Set_Pos(DEFAULT_WINDOW_CX / 2.f + 400.f, DEFAULT_WINDOW_CY / 2.f + 160.f);

	CameraManager::Get_Instance()->SetTarget(Player);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
	ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(DEFAULT_WINDOW_CX / 2, DEFAULT_WINDOW_CY / 2 + 220, DEFAULT_WINDOW_CX + 500, 30);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
	ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(-5, DEFAULT_WINDOW_CY / 2 , 10, 500);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
	ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(DEFAULT_WINDOW_CX + 205, DEFAULT_WINDOW_CY / 2, 10, 500);

	//TileManager::Get_Instance()->Load_Tile(L"../Data/BossTile.dat");

	// 연출
	dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(0.f);
	dynamic_cast<PlayerObject*>(Player)->Set_UIVisibility(false);
	dynamic_cast<PlayerObject*>(Player)->Set_PlayerRender(false);
}  //

void Scene_Boss::Update() {
	//TileManager::Get_Instance()->Update();
	
}

void Scene_Boss::Late_Update() {
	//TileManager::Get_Instance()->Late_Update();
}

void Scene_Boss::Render(HDC DC) {
	//Rectangle(DC, 0, 0, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY);
	//FileManager::Get_Instance()->Append_Image(DC, L"Reference", { DEFAULT_WINDOW_CX / 2.f-50.f, DEFAULT_WINDOW_CY / 2.f }, 0.44f, 0.44f);
	FileManager::Get_Instance()->Append_Image(DC, L"BackGround", { DEFAULT_WINDOW_CX / 2.f + 110.f, DEFAULT_WINDOW_CY / 2.f - 30.f });
	StartScene(DC);
	FileManager::Get_Instance()->Append_Image(DC, L"BackGround_Front", { DEFAULT_WINDOW_CX / 2.f + 110.f, DEFAULT_WINDOW_CY / 2.f - 30.f });
	After_BossDefeat(DC);
}
void Scene_Boss::Release()  {
	SAFE_DELETE_VEC(SPFList);
}

void Scene_Boss::StartScene(HDC DC) {
		FileManager::Get_Instance()->Append_Image(DC, L"Carrier", { 450.f, 1000.f - CarrierPosY }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"CarrierChain", { 450.f, 1000.f - CarrierPosY - 325.f }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"CarrierChain", { 450.f, 1000.f - CarrierPosY - 480.f }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"CarrierChain", { 450.f, 1000.f - CarrierPosY - 635.f }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"CarrierChain", { 450.f, 1000.f - CarrierPosY - 790.f }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"CarrierChain", { 450.f, 1000.f - CarrierPosY - 945.f }, 0.7f, 0.7f);
	if (StartdwTime + 2000.f < GetTickCount()) {
		
		if (degree < 180.f && degree >= 0.f) {
			Player->Set_Pos(DEFAULT_WINDOW_CX / 2.f - 190.f, 1000.f - CarrierPosY + 152.f);
			degree += 0.65f;
			CarrierPosY +=  2.34f * (cosf(degree * PI / 180) + 1);
	
			FileManager::Get_Instance()->Append_Image(DC, L"WalkImage", { Player->Get_Pos().X, 1000.f - CarrierPosY + 153.f }, 0.6f, 0.6f);
		}
		else if (degree >= 180.f) {
			WalkAnimation = true;
			degree = -100.f;
		}
	}
	if (WalkAnimation) {
		Player->Set_Pos(DEFAULT_WINDOW_CX / 2.f - 190.f, 1000.f - CarrierPosY + 152.f);
		if(StartPixelFrame[3] >= 0 && StartPixelFrame[3] < 41)
			PlayAnimation_Once(DC, L"Walk", &StartPixelFrame[3], 220, 50, { Player->Get_Pos().X, 1000.f - CarrierPosY + 152.f }, 0.6f, 0.6f);
		if (StartPixelFrame[3] >= 41) { 
			StartPixelFrame[3] = -1;
			WalkAnimation = false;
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BGM);
			SoundManager::Get_Instance()->PlayBGM(L"Boss_BGM.WAV", 0.6f);
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerPreviousMoveState(PLAYER_MOVE_STATE::PLAYER_IDLE_R);
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerMoveState(PLAYER_MOVE_STATE::PLAYER_IDLE_R);
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(10.f);
			dynamic_cast<PlayerObject*>(Player)->Set_UIVisibility(true);
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerRender(true);
		}
	}
}
void Scene_Boss::After_BossDefeat(HDC DC) {
	HPEN myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(DC, myPen);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);

	if (Boss->GET_DEAD() == true && KEY_COMMAND(KEY::T, KEY_STATE::DOWN)) {
		TalkPassing++;

		dynamic_cast<PlayerObject*>(Player)->Set_UIVisibility(false);
		//dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(0.f);
	}
	if (TalkPassing < 5 && TalkPassing > 0) {
		
		if(Player->Get_Pos().X < ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS)->front()->Get_Pos().X)
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerMoveState(PLAYER_MOVE_STATE::PLAYER_IDLE_R);
		else
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerMoveState(PLAYER_MOVE_STATE::PLAYER_IDLE_L);
	}
	if (TalkPassing == 1) {
		if (StartPixelFrame[0] > 3) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 100.f,
				DEFAULT_WINDOW_CX / 2.f + 300.f, 400.f);
			RECT MukJuText1 = { DEFAULT_WINDOW_CX / 2.f - 270.f, 160 ,DEFAULT_WINDOW_CX / 2.f + 270.f , 200 };

			DrawText(DC, L"실크송 7일 밤새서 야무지게 낋여왔다......        ", 25, &MukJuText1, DT_LEFT | DT_VCENTER);
		}
		
		PlayAnimation_Once(DC, L"TalkAnim01", &StartPixelFrame[0], 520, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 100.f }, 0.8f, 0.8f);
		PlayAnimation_Once(DC, L"TalkAnim02", &StartPixelFrame[1], 380, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 400.f }, 0.8f, 0.8f);
	}
	if (TalkPassing == 2) {
		if (StartPixelFrame[0] > 3) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 100.f,
				DEFAULT_WINDOW_CX / 2.f + 300.f, 400.f);
			RECT MukJuText1 = { DEFAULT_WINDOW_CX / 2.f - 270.f, 160 ,DEFAULT_WINDOW_CX / 2.f + 270.f , 200 };

			DrawText(DC, L"                                                    ", 20, &MukJuText1, DT_LEFT | DT_VCENTER);
		}
		PlayAnimation_Reverse(DC, L"TalkAnim01", &StartPixelFrame[0], 520, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X , 100.f }, 0.8f, 0.8f);
		PlayAnimation_Reverse(DC, L"TalkAnim02", &StartPixelFrame[1], 380, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 400.f }, 0.8f, 0.8f);
		if (StartPixelFrame[1] == -1) { TalkPassing++; StartPixelFrame[1] = 0; StartPixelFrame[0] = 0; }
	}
	if (TalkPassing == 3) {
		if (StartPixelFrame[0] > 3) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 100.f,
				DEFAULT_WINDOW_CX / 2.f + 300.f, 400.f);
			RECT MukJuText1 = { DEFAULT_WINDOW_CX / 2.f - 270.f, 160 ,DEFAULT_WINDOW_CX / 2.f + 270.f , 200 };

			DrawText(DC, L"봐줘서 고맙다.. 니넨 이런거 하지마라.......       ", 25, &MukJuText1, DT_LEFT | DT_VCENTER);
		}
		PlayAnimation_Once(DC, L"TalkAnim03", &StartPixelFrame[0], 570, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 100.f }, 0.8f, 0.8f);
		PlayAnimation_Once(DC, L"TalkAnim04", &StartPixelFrame[1], 420, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 400.f }, 0.8f, 0.8f);
	}
	if (TalkPassing == 4) {
		if (StartPixelFrame[0] > 3) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 100.f,
				DEFAULT_WINDOW_CX / 2.f + 300.f, 400.f);
			RECT MukJuText1 = { DEFAULT_WINDOW_CX / 2.f - 270.f, 160 ,DEFAULT_WINDOW_CX / 2.f + 270.f , 200 };

			DrawText(DC, L"         ", 5, &MukJuText1, DT_LEFT | DT_VCENTER);
		}
		PlayAnimation_Reverse(DC, L"TalkAnim03", &StartPixelFrame[0], 570, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 100.f }, 0.8f, 0.8f);
		PlayAnimation_Reverse(DC, L"TalkAnim04", &StartPixelFrame[1], 420, 70, 
					{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, 400.f }, 0.8f, 0.8f);
		if (StartPixelFrame[1] == -1) { TalkPassing++; StartPixelFrame[1] = 0; StartPixelFrame[0] = 0; }
	}
	if (TalkPassing == 5) {
		dynamic_cast<BossObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS)->front())->Boss_After_DefeatTalk();
		dynamic_cast<PlayerObject*>(Player)->Set_UIVisibility(true);
		dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(10.f);

		SelectObject(DC, oldBrush);
		DeleteObject(myBrush);

		SelectObject(DC, oldPen);
		DeleteObject(myPen);
	}
}
void Scene_Boss::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF , UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X, 
		StartTop - CameraManager::Get_Instance()->GetOffset().Y, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (*_SPF >= _FrameEndIndex - 1) {
		*_SPF = _FrameEndIndex - 1;
	}

	if (_AnimSpeed + dwTime < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		dwTime = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);
}
void Scene_Boss::PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X,
		StartTop - CameraManager::Get_Instance()->GetOffset().Y, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (*_SPF <= 0) {
		*_SPF = -1;
	}

	if (_AnimSpeed + dwTime < GetTickCount() && *_SPF <= _FrameEndIndex - 1) {
		*_SPF -= 1;
		dwTime = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);
}