#include "PCH.h"
#include "Enviroment.h"

Enviroment::Enviroment()  :dwTime(GetTickCount() + 1000){               }
Enviroment::~Enviroment()   { Release();    }

void Enviroment::Initialize() {
    OBJTAG = OBJECT_TAG::OBJ_ENVIROMENT;
    Enviroment_Type = ENV_TYPE::ENV_NORMAL;

    Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
}
int Enviroment::Update() {
    
    Update_RECT();
    return 0;

}
void Enviroment::Late_Update() {

}
void Enviroment::Render(HDC DC){
   FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
   FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;
   
   if (Enviroment_Type == ENV_TYPE::ENV_NORMAL) {
      // HPEN myPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
      // HGDIOBJ oldPen = SelectObject(DC, myPen);
      //
      // HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
      // HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
      //
      // Rectangle(DC, OBJRECT.left - OffsetX, OBJRECT.top - OffsetY, OBJRECT.right - OffsetX, OBJRECT.bottom - OffsetY);
      //
      // SelectObject(DC, oldBrush);
      // DeleteObject(myBrush);
      //
      // SelectObject(DC, oldPen);
      // DeleteObject(myPen);
   }
   if (Enviroment_Type == ENV_TYPE::ENV_OBSTACLE) {
      //HPEN myPen = CreatePen(PS_SOLID, 0, RGB(120, 120, 120));
      //HGDIOBJ oldPen = SelectObject(DC, myPen);
      //
      //HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
      //HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
      //
      //Rectangle(DC, OBJRECT.left - OffsetX, OBJRECT.top - OffsetY, OBJRECT.right - OffsetX, OBJRECT.bottom - OffsetY);
      //
      //SelectObject(DC, oldBrush);
      //DeleteObject(myBrush);
      //
      //SelectObject(DC, oldPen);
      //DeleteObject(myPen);
   }

}
void Enviroment::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
    if (Enviroment_Type == ENV_TYPE::ENV_NORMAL && (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER 
        || pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS || pObj->Get_Tag() == OBJECT_TAG::OBJ_MONSTER)) {
        if (_TYPE == COLLISION_TYPE::COL_TOP || _TYPE == COLLISION_TYPE::COL_BOTTOM)
            pObj->Set_PosY(_Value);
        if (_TYPE == COLLISION_TYPE::COL_LEFT || _TYPE == COLLISION_TYPE::COL_RIGHT)
            pObj->Set_PosX(_Value);
    }
    if (Enviroment_Type == ENV_TYPE::ENV_OBSTACLE && pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER) {
        Player->Set_Pos(3800, 4050);
        SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERSTATE);
        SoundManager::Get_Instance()->PlaySoundW(L"Hornet_DamageSound.WAV", CHANNELID::SOUND_PLAYERSTATE, 1.1f);

        if (1 == rand() % 2 + 1) {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
            SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Damage01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
        }
        else {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
            SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Damage02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
        }
    }
}
void Enviroment::Release() {

}
