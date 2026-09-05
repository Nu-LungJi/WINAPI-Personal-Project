#include "PCH.h"
#include "NPC.h"

NPC::NPC()	: dwTime(GetTickCount())	{				}
NPC::NPC(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, NPC_TAG _Tag)
	: dwTime(GetTickCount()), StartPixelFrame{ 0 }, SignFlag(false), TalkWithNPC(false), TalkingPass(-1)
{
	OBJINFO = { _X, _Y, _WTH, _HGT };
	Tag = _Tag;
}
NPC::~NPC() {	Release();	}

void NPC::Initialize()
{
	//FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/BigBug/NPC_BigBug_Anim_R.bmp", L"NPC_BigBug");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Ghoul/NPC_Ghoul_Anim.bmp", L"NPC_Ghoul");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Flea/NPC_Flea_Anim.bmp", L"NPC_Flea");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Pulp/NPC_Pulp_Anim.bmp", L"NPC_Pulp");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Big_Pulp/NPC_Big_Pulp_Anim.bmp", L"NPC_Big_Pulp");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/PulpFamily/NPC_PulpFamily_Anim.bmp", L"NPC_PulpFamily");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Sherma/NPC_Sherma_Anim.bmp", L"NPC_Sherma");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/NPC/Sherma/NPC_SpecialSherma_Anim.bmp", L"NPC_SpecialSherma");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Fleur/NPC_Talk_Anim.bmp", L"TalkSign");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Fleur/NPC_Sale_Anim.bmp", L"SaleSign");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_01.bmp", L"TalkFleurAnim01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_02.bmp", L"TalkFleurAnim02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_03.bmp", L"TalkFleurAnim03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Talk/TalkFleur_Anim_04.bmp", L"TalkFleurAnim04");

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
}

int NPC::Update() {
	Update_RECT();
	return OBJ_ALIVE;
}

void NPC::Late_Update()	{ }

void NPC::Render(HDC DC) {

	
	RECT	RT = { DEFAULT_WINDOW_CX / 2 + 100, DEFAULT_WINDOW_CY / 2 - 250, DEFAULT_WINDOW_CX / 2 + 400, DEFAULT_WINDOW_CY / 2 - 200 };
	if (fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX) < 50.f && Tag != NPC_TAG::NPC_BIGPULP) {
		if (Tag == NPC_TAG::NPC_FLEA) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[19], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
		if (Tag == NPC_TAG::NPC_GHOUL) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[18], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
		if (Tag == NPC_TAG::NPC_PULP) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[18], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
		if (Tag == NPC_TAG::NPC_PULP_FAMILY) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[17], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
		if (Tag == NPC_TAG::NPC_SHERMA) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[16], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
		if (Tag == NPC_TAG::NPC_SPECIALSHERMA) {
			PlayAnimation_Once_Stable(DC, L"TalkSign", &StartPixelFrame[15], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
		}
	}
	else if (fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX) < 50.f && Tag == NPC_TAG::NPC_BIGPULP) {
		PlayAnimation_Once_Stable(DC, L"SaleSign", &StartPixelFrame[0], 160, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 100.f }, 0.5f, 0.5f);
	}
	else if (fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX) >= 50.f && fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX) < 100.f) {
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
	}
	else {
	
	}
	
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {
		if (Tag == NPC_TAG::NPC_BIGPULP && Player->Get_Pos().X < 2485.f && Player->Get_Pos().X > 970.f)
		{	PlayAnimation_Loop(DC, L"NPC_Big_Pulp", &StartPixelFrame[1], NPC_BIGPULP_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.75f, 0.75f);	}
		if (Tag == NPC_TAG::NPC_FLEA && Player->Get_Pos().X > 2550.f)
		{	PlayAnimation_Loop(DC, L"NPC_Flea", &StartPixelFrame[3], NPC_FLEA_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);				}
		if (Tag == NPC_TAG::NPC_GHOUL && Player->Get_Pos().X > 2800.f)
		{	PlayAnimation_Loop(DC, L"NPC_Ghoul", &StartPixelFrame[4], NPC_GHOUL_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);		}
		if (Tag == NPC_TAG::NPC_PULP)		
		{	PlayAnimation_Loop(DC, L"NPC_Pulp", &StartPixelFrame[5], NPC_PULP_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);			}
		if (Tag == NPC_TAG::NPC_PULP_FAMILY)
		{	PlayAnimation_Loop(DC, L"NPC_PulpFamily", &StartPixelFrame[6], NPC_PULP_FAMILY_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);}
		if (Tag == NPC_TAG::NPC_SHERMA && Player->Get_Pos().X > 2100.f && Player->Get_Pos().X < 3500.f)
		{	PlayAnimation_Loop(DC, L"NPC_Sherma", &StartPixelFrame[7], NPC_SHERMA_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);		}
		if (Tag == NPC_TAG::NPC_SPECIALSHERMA && Player->Get_Pos().X < 3100.f && Player->Get_Pos().X > 1720.f)
		{	PlayAnimation_Loop(DC, L"NPC_SpecialSherma", &StartPixelFrame[8], NPC_SPECIAL_SHERMA_PIXELFRAME, 100, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f); }
	}
	TalkNPC(DC);
}
void NPC::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER) {
		SignFlag = true;
	}
}
void NPC::Release() {}

void NPC::TalkNPC(HDC DC) {

	if (KEY_COMMAND(KEY::T, KEY_STATE::DOWN) && fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX) < 50.f) {
		
		if (TalkingPass == -1){
			if (Tag == NPC_TAG::NPC_GHOUL) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_Ghoul_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_FLEA) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_Flea_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_SHERMA) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_Sherma_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_SHERMA) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_Sherma_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_PULP) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_Pulp_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_PULP_FAMILY) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_PulpFamily_Sound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			if (Tag == NPC_TAG::NPC_BIGPULP) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"NPC_BigPulp_Sound01.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
		}
		TalkingPass++;
		TalkWithNPC = TRUE;
	}

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
		
	if (TalkWithNPC && TalkingPass == 0) {
		Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 68.f, DEFAULT_WINDOW_CX / 2.f + 300.f, 360.f);
		PlayAnimation_Once_Stable(DC, L"TalkFleurAnim01", &StartPixelFrame[10], 520, 35, 
			{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y - 300.f }, 0.8f, 0.8f);
		PlayAnimation_Once_Stable(DC, L"TalkFleurAnim02", &StartPixelFrame[11], 380, 35,
			{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y - 3.f }, 0.8f, 0.8f);
	}
	if (TalkWithNPC && TalkingPass == 1) {
		if (StartPixelFrame[10] >= 0 || StartPixelFrame[11] >= 0) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 68.f, DEFAULT_WINDOW_CX / 2.f + 300.f, 360.f);
			PlayAnimation_Reverse(DC, L"TalkFleurAnim01", &StartPixelFrame[10], 520, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y - 300.f }, 0.8f, 0.8f);
			PlayAnimation_Reverse(DC, L"TalkFleurAnim02", &StartPixelFrame[11], 380, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y  - 3.f}, 0.8f, 0.8f);
		}
		if (StartPixelFrame[10] < 0 && StartPixelFrame[11] < 0) {
			if (StartPixelFrame[13] == 1) {
				srand(time(NULL));
				INT Randomx = rand() % 3 + 1;
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				if (Randomx == 1) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Talk01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}if (Randomx == 2) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Talk02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}if (Randomx == 3) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Talk03.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}
			}

			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 68.f, DEFAULT_WINDOW_CX / 2.f + 300.f, 360.f);
			PlayAnimation_Once_Stable(DC, L"TalkFleurAnim03", &StartPixelFrame[12], 570, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y - 290.f }, 0.8f, 0.8f);
			PlayAnimation_Once_Stable(DC, L"TalkFleurAnim04", &StartPixelFrame[13], 420, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y }, 0.8f, 0.8f);
		}
	}
	if (TalkWithNPC && TalkingPass == 2) {

		if (StartPixelFrame[12] >= 0 || StartPixelFrame[13] >= 0) {
			Rectangle(DC, DEFAULT_WINDOW_CX / 2.f - 300.f, 68.f, DEFAULT_WINDOW_CX / 2.f + 300.f, 360.f);
			PlayAnimation_Reverse(DC, L"TalkFleurAnim03", &StartPixelFrame[12], 570, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y - 290.f }, 0.8f, 0.8f);
			PlayAnimation_Reverse(DC, L"TalkFleurAnim04", &StartPixelFrame[13], 420, 35,
				{ DEFAULT_WINDOW_CX / 2.f + CameraManager::Get_Instance()->GetOffset().X, DEFAULT_WINDOW_CY / 2.f + CameraManager::Get_Instance()->GetOffset().Y}, 0.8f, 0.8f);
		}
		if (StartPixelFrame[12] < 0 && StartPixelFrame[13] < 0) {
			TalkWithNPC = false;
			TalkingPass = -1;
			StartPixelFrame[10] = 0; StartPixelFrame[11] = 0; StartPixelFrame[12] = 0; StartPixelFrame[13] = 0;
		}
	}
	

	SelectObject(DC, myBrush);
	DeleteObject(oldBrush);
}

void NPC::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + dwTime < GetTickCount()) {
		*_SPF += 1;
		dwTime = GetTickCount();

		if (*_SPF >= _FrameEndIndex) {
			*_SPF = 0;
		}
	}

	FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);

}
void NPC::PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	INT _FrameEndIndex = (INT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X, StartTop - CameraManager::Get_Instance()->GetOffset().Y,
		Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (_AnimSpeed + dwTime < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		dwTime = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);
}
void NPC::PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
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