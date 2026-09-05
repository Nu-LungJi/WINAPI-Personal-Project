#include "PCH.h"
#include "HitBox.h"

void	HitBoxObject::Initialize() {
	HITBOX_PREVIOUS = false;
	HITBOX_CURRENT = false;

	memset(&StartPixelFrame, 0, sizeof(StartPixelFrame));
	dwTime = GetTickCount();

	BossPos = { 0.f, 0.f };
	Boss = nullptr;
	ONHIT = FALSE;

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Slash/Slash_Effect_B_Anim.bmp", L"Slash_Effect_R");
	Player = nullptr;
}
int		HitBoxObject::Update() {
	Update_RECT();
	if (Player == nullptr) {
		Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	}
	if (Boss == nullptr && SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_BOSS) {
		Boss = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS)->front();
	}
	return 0;
}
void HitBoxObject::Late_Update()
{
}

void HitBoxObject::Render(HDC DC) {

	MainDC = DC;
	if (BossPos.X != 0.f) {
		if (dynamic_cast<PlayerObject*>(Player)->PlayAnimation_Once(DC, L"Slash_Effect_R", &StartPixelFrame[0], 1000, 10, &dwTime, BossPos, 0.5f, 0.5f)) {
			BossPos = { 0.f, 0.f };
			dwTime = GetTickCount();
		}
	}
	
	if (HITBOX_CURRENT) {
		Vector2D Offset = CameraManager::Get_Instance()->GetOffset();

		//HPEN myPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
		//HGDIOBJ oldPen = SelectObject(DC, myPen);
		//
		//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
		//
		//Rectangle(DC, OBJRECT.left - Offset.X, OBJRECT.top - Offset.Y, OBJRECT.right - Offset.X, OBJRECT.bottom - Offset.Y);
		//
		//SelectObject(DC, oldBrush);
		//DeleteObject(myBrush);
		//
		//SelectObject(DC, oldPen);
		//DeleteObject(myPen);

		if (ONHIT && dynamic_cast<BossObject*>(Boss)->PlayAnimation_Once(MainDC, L"Slash_Effect_R", 
			&StartPixelFrame[6], 1000, 20, &dwTime, { OBJINFO.CenterPosX + 70, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			StartPixelFrame[6] = 0;
			ONHIT = FALSE;
		}
	}
}

void HitBoxObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (HITBOX_CURRENT && !HITBOX_PREVIOUS) {
		if (this->Get_Tag() == OBJECT_TAG::OBJ_PLAYER_HITBOX) {
  			if (pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS &&
				!dynamic_cast<BossObject*>(pObj)->Boss_Shield()) {
				
				if(BossPos.X == 0.f && BossPos.Y == 0.f){
					BossPos = pObj->Get_Pos();
				}
				ONHIT = TRUE;

				int randomv = rand() % 3 + 1;
				if (randomv == 1) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BOSS);
					SoundManager::Get_Instance()->PlaySoundW(L"Boss_Wound01.WAV", CHANNELID::SOUND_BOSS, 1.1f);
				}
				else if (randomv == 2) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BOSS);
					SoundManager::Get_Instance()->PlaySoundW(L"Boss_Wound02.WAV", CHANNELID::SOUND_BOSS, 1.1f);
				}
				else if (randomv == 3) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BOSS);
					SoundManager::Get_Instance()->PlaySoundW(L"Boss_Wound03.WAV", CHANNELID::SOUND_BOSS, 1.1f);
				}

				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
				SoundManager::Get_Instance()->PlaySoundW(L"Monster_Damage.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 0.6f);

				pObj->Set_HP(pObj->Get_HP() - HITBOX_DAMAGE);
				HITBOX_PREVIOUS = true;
				
			}
			if (dynamic_cast<PlayerObject*>(Player)->Get_Silk() <= 14) {
				dynamic_cast<PlayerObject*>(Player)->Set_Silk(dynamic_cast<PlayerObject*>(Player)->Get_Silk() + 1);
			}
		}
	}
}

void HitBoxObject::Release()
{
}
