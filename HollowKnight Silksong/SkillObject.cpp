#include "PCH.h"
#include "SkillObject.h"

SkillObject::SkillObject() : dwTime{ GetTickCount() }, GetGravity(true), Angle(180.f), ONGROUND(false), PlayerDirection(0){}
SkillObject::~SkillObject() { Release(); }

void SkillObject::Initialize(){
	OBJINFO = { 0.f, 0.f, 50.f, 50.f };

	Set_Tag(OBJECT_TAG::OBJ_PLAYER_HITBOX);
	ObjectJumpSpeed = 10.f;

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
}

int SkillObject::Update() {
	Update_RECT();
	GravitySetting();
	MoveDrill();
	return 0;
}

void SkillObject::Late_Update() {}

void SkillObject::Render(HDC DC) {

	if (PlayerDirection == 0) {
		if (dynamic_cast<PlayerObject*>(Player)->Get_PlayerDirection() < 0) {
			PlayerDirection = -1;
		}
		else { PlayerDirection = 1; }
	}

	if (ONGROUND && PlayerDirection == 1) {
		

		PlayAnimation_Loop(DC, L"Drill_R", &StartPixelFrame[0], 350, 20, &dwTime[0], 10, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.7f, 0.7f);
		if(StartPixelFrame[0] >= 10)
			PlayAnimation_Loop(DC, L"Drill_Effect_R", &StartPixelFrame[1], 300, 10, &dwTime[1], 0, { OBJINFO.CenterPosX - 80.f, OBJINFO.CenterPosY }, 0.8f, 0.8f);
	}
	else if (ONGROUND && PlayerDirection == -1) {

		PlayAnimation_Loop(DC, L"Drill_L", &StartPixelFrame[0], 350, 20, &dwTime[0], 10, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.7f, 0.7f);
		if (StartPixelFrame[0] >= 10)
			PlayAnimation_Loop(DC, L"Drill_Effect_L", &StartPixelFrame[1], 300, 10, &dwTime[1], 0, { OBJINFO.CenterPosX + 80.f, OBJINFO.CenterPosY }, 0.8f, 0.8f);
	}
	else if (!ONGROUND) {
		FileManager::Get_Instance()->Append_Image(DC, L"Drill_Image", { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (ONHIT) {
		if (PlayAnimation_Once(DC, L"OnHit_Effect", &StartPixelFrame[2], 200, 30, &dwTime[2], { MonsterPos.X - 70.f, MonsterPos.Y - 80.f })) {
			ONHIT = false;
		}
	}
}

void SkillObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_ENVIROMENT) {
		Set_PosY(_Value);
		ONGROUND = true;
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_MONSTER || pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS) {
		MonsterPos = pObj->Get_Pos();
		ONHIT = true;
	}
}

void SkillObject::Release()
{
}
void SkillObject::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + *Timer < GetTickCount()) {
		*_SPF += 1;
		*Timer = GetTickCount();

		if (*_SPF >= _FrameEndIndex) {
			*_SPF = LoopFrame;
		}
	}

	FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);

}
BOOL SkillObject::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
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
		*_SPF = _FrameEndIndex;
		return true;
	}

	if (_AnimSpeed + *Timer < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		*Timer = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);

	return false;
}
void SkillObject::GravitySetting() {
	FLOAT Gravity = 1.f;
	if (ObjectJumpSpeed >= -15.f) {
		ObjectJumpSpeed -= Gravity;
	}
	if (GetGravity) {
		OBJINFO.CenterPosY -= ObjectJumpSpeed;
	}
}

void SkillObject::MoveDrill() {
	if (PlayerDirection == 0) {
		if (dynamic_cast<PlayerObject*>(Player)->Get_PlayerDirection() < 0) {
			PlayerDirection = -1;
		}
		else { PlayerDirection = 1; }
	}
	if (!ONGROUND) {
		OBJINFO.CenterPosX += PlayerDirection * 10.f;
	}
	else if (ONGROUND) {

		if (Angle < 360) {
			Angle += 7.5f;
			OBJINFO.CenterPosX += 5 * PlayerDirection * sinf(Angle * PI / 180);
		}
		else {
			OBJINFO.CenterPosX += PlayerDirection * 20.f;
		}
	}
}
