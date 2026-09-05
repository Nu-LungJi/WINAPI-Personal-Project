#include "PCH.h"
#include "Monster.h"

MonsterObject::MonsterObject() : dwTime{ GetTickCount() }, AnimationTime(GetTickCount()), Action_Transition_Time(0.f), Player_CatchRange(0.f),
                                    Gravity_Enable(true), Catch_Player(false), StartPixelFrame{0}, Angle(0.f), ONHIT(false), Death_Sound(false){}
MonsterObject::~MonsterObject() { Release(); }

void MonsterObject::Initialize() {
    OBJINFO = { 0.f, 0.f, 50.f, 70.f };
    OBJHP = 200;
    OBJDMG = 1;
    OBJTAG = OBJECT_TAG::OBJ_MONSTER;

    Monster_Type = MONSTER_TYPE::MONSTER_CHAMBER;

    dwTime[9] = GetTickCount();
    dwTime[8] = GetTickCount();

    MonsterSpeed = 1.f;
    MonsterJumpSpeed = -3.f;
    MonsterDirection = 1;

    ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER_HITBOX, AbstractFactory<HitBoxObject>::Create());
    MonsterHitBox = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER_HITBOX)->back();
    MonsterHitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
    MonsterHitBox->Set_Tag(OBJECT_TAG::OBJ_MONSTER_HITBOX);

    Action_Transition_Time = 10000.f;
    Player_CatchRange = 300.f;

    Previous_State = MONSTER_STATE::MONSTER_NONE;
    Current_State = MONSTER_STATE::MONSTER_NONE;

    Previous_HitState = false;
    Current_HitState = false;

    Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Walk_L_Anim.bmp", L"Envoy_Walk_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Walk_R_Anim.bmp", L"Envoy_Walk_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Attack_L_Anim.bmp", L"Envoy_Attack_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Attack_R_Anim.bmp", L"Envoy_Attack_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Dead_L_Anim.bmp", L"Envoy_Dead_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Dead_R_Anim.bmp", L"Envoy_Dead_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Idle_L_Anim.bmp", L"Envoy_Idle_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Envoy/Idle_R_Anim.bmp", L"Envoy_Idle_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Idle_Anim.bmp", L"Chamber_Idle");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Walk_L_Anim.bmp", L"Chamber_Walk_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Walk_R_Anim.bmp", L"Chamber_Walk_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Attack_L_Anim.bmp", L"Chamber_Attack_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Attack_R_Anim.bmp", L"Chamber_Attack_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Dead_L_Anim.bmp", L"Chamber_Dead_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Monster/Chamber/Dead_R_Anim.bmp", L"Chamber_Dead_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Splash/Splash_L_Effect.bmp", L"Splash_L");
    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Splash/Splash_R_Effect.bmp", L"Splash_R");

    FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Slash/Slash_Effect_B_Anim.bmp", L"Slash_Effect_R");
}
int MonsterObject::Update() {
    Update_RECT();

    Monster_GravitySetting();
    Monster_StateMachine();
    Monster_Control();

    for (auto& i : *ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)) {
        if (CollisionManager::Check_Collision(this, i)) {
            ONGROUND = true;
            break;
        }
        if (i == ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()) {
            ONGROUND = false;
        }
    }
    // TRUE 0 FALSE
    if (OBJHP <= 0 && DEAD) {
        MonsterJumpSpeed += 15.f;
        if (Player->Get_Pos().X > OBJINFO.CenterPosX) { Current_State = MONSTER_STATE::MONSTER_DEAD_R;  }
        else if (Player->Get_Pos().X <= OBJINFO.CenterPosX) {   Current_State = MONSTER_STATE::MONSTER_DEAD_L; }
       
        OBJHP = 999;
        Death_Sound = true;
        StartPixelFrame[3] = 0;
    }

    if (dynamic_cast<PlayerObject*>(Player)->Get_PlayerAttackState() != PLAYER_ATTACK_STATE::PLAYER_ATTACK_R
        && dynamic_cast<PlayerObject*>(Player)->Get_PlayerAttackState() != PLAYER_ATTACK_STATE::PLAYER_ATTACK_L) {
        PlayerPrevious_AttackState = false;
    }
    if (ONHIT && !DEAD) {
        if (Angle < 270.f) {
            if (Player->Get_Pos().X > OBJINFO.CenterPosX) {
                OBJINFO.CenterPosX -= 15 * (sinf(Angle * PI / 180) + 1);
            }
            if (Player->Get_Pos().X <= OBJINFO.CenterPosX) {
                OBJINFO.CenterPosX += 15 * (sinf(Angle * PI / 180) + 1);
            }
        }
        else { ONHIT = false; }
        Angle += 48.f;
    } // KnockBack

    if (ONHIT == false) {
        StartPixelFrame[3] = 0;
        StartPixelFrame[4] = 0;
    }

   //if (Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
   //    SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
   //    SoundManager::Get_Instance()->PlaySoundW(L"Chamber_Sound.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 1.1f);
   //}
   //if (Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
   //    SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
   //    SoundManager::Get_Instance()->PlaySoundW(L"Convoy_Sound.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 1.1f);
   //}

    return 0;
}
void MonsterObject::Late_Update()  { 
    if (Check_Distance_Player().X < 300.f && Check_Distance_Player().Y < 300.f) {
        Catch_Player = true; 
        MonsterDirection = (Player->Get_Pos().X - OBJINFO.CenterPosX) / fabsf(Player->Get_Pos().X - OBJINFO.CenterPosX);
    }

    if (Check_Distance_Player().X >= 300.f || Check_Distance_Player().Y >= 300.f) { 
        Catch_Player = false; }

    if (DEAD && !ONGROUND) {
        if (Angle < 270.f && Player->Get_Pos().X > OBJINFO.CenterPosX) {
            OBJINFO.CenterPosX -= 5 * (sinf(Angle++ * PI / 180) + 1);
        }
        else if (Angle < 270.f && Player->Get_Pos().X <= OBJINFO.CenterPosX) {
            OBJINFO.CenterPosX += 5 * (sinf(Angle++ * PI / 180) + 1);
        }
    }
}
void MonsterObject::Render(HDC DC) {
    FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
    FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;
    //
    // (DC, OBJRECT.left - OffsetX, OBJRECT.top - OffsetY, OBJRECT.right - OffsetX, OBJRECT.bottom - OffsetY);

    Monster_Animation_IDLE(DC);
    Monster_Animation_WALK(DC);
    Monster_Animation_ATTK(DC);
    Monster_Animation_DEAD(DC);

    if (ONHIT && !DEAD) {
        if (dynamic_cast<PlayerObject*>(Player)->Get_PlayerDirection() >= 0) {
            if (PlayAnimation_Once(DC, L"Splash_R", &StartPixelFrame[4], 400, 12, { OBJINFO.CenterPosX + 140, OBJINFO.CenterPosY }, 0.5f, 0.5f)) {
                StartPixelFrame[4] = 0;
            }
        }
        else if (dynamic_cast<PlayerObject*>(Player)->Get_PlayerDirection() < 0) {
            if (PlayAnimation_Once(DC, L"Splash_L", &StartPixelFrame[4], 400, 12, { OBJINFO.CenterPosX - 140, OBJINFO.CenterPosY }, 0.5f, 0.5f)) {
                StartPixelFrame[4] = 0;
            }
        }

        if (PlayAnimation_Once(DC, L"Slash_Effect_R", &StartPixelFrame[3], 1000, 20, { OBJINFO.CenterPosX + 70, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
            StartPixelFrame[4] = 0;
        }
   }
       
   
}
void MonsterObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
    if (pObj->Get_Tag() == OBJECT_TAG::OBJ_ENVIROMENT) {
        if(_TYPE == COLLISION_TYPE::COL_TOP)        Set_PosY(_Value);
        if (_TYPE == COLLISION_TYPE::COL_RIGHT)     Set_PosX(_Value);
        if (_TYPE == COLLISION_TYPE::COL_LEFT)      Set_PosX(_Value);

        ONGROUND = true;

        if (OBJRECT.left < pObj->Get_Rect()->left) { 
            MonsterDirection = 1; }
        if (OBJRECT.right > pObj->Get_Rect()->right) {
            MonsterDirection = -1; }
    }
    if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER) {
        if (dynamic_cast<PlayerObject*>(Player)->Get_Infinity() == false && !DEAD) {
            MonsterJumpSpeed = 10.f;
            OBJINFO.CenterPosX += MonsterDirection * 10.f;
        }
    }
    if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER_HITBOX) {
        
        if((dynamic_cast<PlayerObject*>(Player)->Get_PlayerAttackState() == PLAYER_ATTACK_STATE::PLAYER_ATTACK_R
            || dynamic_cast<PlayerObject*>(Player)->Get_PlayerAttackState() == PLAYER_ATTACK_STATE::PLAYER_ATTACK_L) 
            && PlayerPrevious_AttackState == false){

            if (Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
                SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
                SoundManager::Get_Instance()->PlaySoundW(L"Monster_Damage.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 0.6f);
            }
            if (Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
                SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
                SoundManager::Get_Instance()->PlaySoundW(L"Monster_Damage.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 0.6f);
            }
          
            OBJHP -= Player->Get_Damage();
            MonsterJumpSpeed = 8.f;
            ONHIT = true;
            Angle = 0.f;
            PlayerPrevious_AttackState = true;

        }
        else if(PlayerPrevious_AttackState == false && !ONHIT) {

            if (Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
                SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
                SoundManager::Get_Instance()->PlaySoundW(L"Monster_Damage.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 0.6f);
            }
            if (Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
                SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
                SoundManager::Get_Instance()->PlaySoundW(L"Monster_Damage.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 0.6f);
            }

            OBJHP -= Player->Get_Damage();
            MonsterJumpSpeed = 8.f;
            ONHIT = true;
            Angle = 0.f;
            PlayerPrevious_AttackState = true;
        }
        if (OBJHP <= 0) { 
             MonsterJumpSpeed = 8.f; Angle = 0.f; Set_Dead(true); }
    }

}
void MonsterObject::Release() { }

void MonsterObject::Monster_GravitySetting() {
    FLOAT   Gravity = 1.f;
    if (MonsterJumpSpeed >= -30.f) MonsterJumpSpeed -= Gravity;
    if (Gravity_Enable) {
        OBJINFO.CenterPosY -= MonsterJumpSpeed;
    }
}
void MonsterObject::Monster_StateMachine() {
    INT Action_Index = 0;
    if (Current_State != MONSTER_STATE::MONSTER_DEAD_L 
        && Current_State != MONSTER_STATE::MONSTER_DEAD_R) {
        if (dwTime[0] + Action_Transition_Time < GetTickCount() && Catch_Player == false) {
            Action_Index = 1;
            dwTime[0] = GetTickCount();
        }
        if (dwTime[0] + Action_Transition_Time / 5 < GetTickCount() && Catch_Player == true) {
            if (Check_Distance_Player().X < 250.f && Check_Distance_Player().Y < 250.f)        { Action_Index = 3; }
            else if (Check_Distance_Player().X >= 250.f || Check_Distance_Player().Y >= 250.f)  { Action_Index = 2; }
            dwTime[0] = GetTickCount();
        }
        if (Action_Index == 1) {
            if (MonsterDirection ==  1) { Current_State = MONSTER_STATE::MONSTER_IDLE_R; }
            if (MonsterDirection == -1) { Current_State = MONSTER_STATE::MONSTER_IDLE_L; }
        }
        if (Action_Index == 2) {
            if (MonsterDirection ==  1) { Current_State = MONSTER_STATE::MONSTER_WALK_R; }
            if (MonsterDirection == -1) { Current_State = MONSTER_STATE::MONSTER_WALK_L; }
        }
        if (Action_Index == 3) {
            if (MonsterDirection ==  1) { Current_State = MONSTER_STATE::MONSTER_ATTACK_R; }
            if (MonsterDirection == -1) { Current_State = MONSTER_STATE::MONSTER_ATTACK_L; }
        }
    }
}
void MonsterObject::Monster_Control() {
    if (Current_State != MONSTER_STATE::MONSTER_DEAD_L && Current_State != MONSTER_STATE::MONSTER_DEAD_R) {
        
        if (Current_State == MONSTER_STATE::MONSTER_IDLE_R 
            || Current_State == MONSTER_STATE::MONSTER_IDLE_L) {
            MonsterSpeed = 0.f;
        }
        if (Current_State == MONSTER_STATE::MONSTER_WALK_R) {
            MonsterDirection = 1;
            MonsterSpeed = 1.f;
        }
        if (Current_State == MONSTER_STATE::MONSTER_WALK_L) {
            MonsterDirection = -1;
            MonsterSpeed = 1.f;
        }
        if (Current_State == MONSTER_STATE::MONSTER_ATTACK_R) {
            MonsterSpeed = 0.f;
            if (StartPixelFrame[0] >= 8 && StartPixelFrame[0] <= 14 && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
                MonsterHitBox->Set_Info(OBJINFO.CenterPosX + 75.f, OBJINFO.CenterPosY - 60.f, 140.f, 120.f);
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Activate_HitBox();
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Set_HitBoxDamage(1);
            }
            if (StartPixelFrame[1] >= 13 && StartPixelFrame[1] <= 17 && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
                MonsterHitBox->Set_Info(OBJINFO.CenterPosX + 50.f, OBJINFO.CenterPosY - 30.f, 80.f, 30.f);
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Activate_HitBox();
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Set_HitBoxDamage(1);
            }
        }
        else { MonsterHitBox->Set_Info(0.f, 0.f, 0.f, 0.f); }
        if (Current_State == MONSTER_STATE::MONSTER_ATTACK_L) {
            MonsterSpeed = 0.f;
            if (StartPixelFrame[0] >= 8 && StartPixelFrame[0] <= 14 && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
                MonsterHitBox->Set_Info(OBJINFO.CenterPosX - 75.f, OBJINFO.CenterPosY - 60.f, 140.f, 120.f);
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Activate_HitBox();
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Set_HitBoxDamage(1);
            }
            else if (StartPixelFrame[1] >= 13 && StartPixelFrame[1] <= 17 && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
                MonsterHitBox->Set_Info(OBJINFO.CenterPosX - 50.f, OBJINFO.CenterPosY - 30.f, 80.f, 30.f);
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Activate_HitBox();
                dynamic_cast<HitBoxObject*>(MonsterHitBox)->Set_HitBoxDamage(1);
            }
        }
        else { MonsterHitBox->Set_Info(0.f, 0.f, 0.f, 0.f); }
        OBJINFO.CenterPosX += MonsterSpeed * MonsterDirection;
    }
}

void MonsterObject::Monster_Animation_IDLE(HDC DC) {
    if (Previous_State != Current_State ) {
        Previous_State = Current_State;
        StartPixelFrame[0] = 0;
        StartPixelFrame[1] = 0;
        AnimationTime = GetTickCount();
    }
    if (Current_State == MONSTER_STATE::MONSTER_IDLE_R && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        PlayAnimation_Loop(DC, L"Envoy_Idle_R", &StartPixelFrame[0], 200, 60, { OBJINFO.CenterPosX + 14.f, OBJINFO.CenterPosY - 38.f }, 0.5f, 0.5f);
    }
    else if (Current_State == MONSTER_STATE::MONSTER_IDLE_L && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        PlayAnimation_Loop(DC, L"Envoy_Idle_L", &StartPixelFrame[0], 200, 60, { OBJINFO.CenterPosX - 14.f, OBJINFO.CenterPosY - 38.f }, 0.5f, 0.5f);
    }
    if ((Current_State == MONSTER_STATE::MONSTER_IDLE_R || Current_State == MONSTER_STATE::MONSTER_IDLE_L) && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        PlayAnimation_Loop(DC, L"Chamber_Idle", &StartPixelFrame[1], 150, 60, { OBJINFO.CenterPosX + 14.f, OBJINFO.CenterPosY }, 0.5f, 0.5f);
    }
}
void MonsterObject::Monster_Animation_WALK(HDC DC) {
    if (Previous_State != Current_State) {
        Previous_State = Current_State;
        StartPixelFrame[0] = 0;
        StartPixelFrame[1] = 0;
        AnimationTime = GetTickCount();
    }

    if (StartPixelFrame[0] == 2 && (Current_State == MONSTER_STATE::MONSTER_WALK_R || Current_State == MONSTER_STATE::MONSTER_WALK_L)) {
        if (Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
            SoundManager::Get_Instance()->PlaySoundW(L"Convoy_Sound.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 1.1f);
        }
    }
    if (StartPixelFrame[1] == 2 && (Current_State == MONSTER_STATE::MONSTER_WALK_R || Current_State == MONSTER_STATE::MONSTER_WALK_L)) {
        if (Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
            SoundManager::Get_Instance()->PlaySoundW(L"Chamber_Sound.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 1.1f);
        }
    }
    if (Current_State == MONSTER_STATE::MONSTER_WALK_R && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        PlayAnimation_Loop(DC, L"Envoy_Walk_R", &StartPixelFrame[0], 150, 30, { OBJINFO.CenterPosX + 10.f, OBJINFO.CenterPosY - 38.f}, 0.5f, 0.5f);
    }
    else if(Current_State == MONSTER_STATE::MONSTER_WALK_L && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY){
        PlayAnimation_Loop(DC, L"Envoy_Walk_L", &StartPixelFrame[0], 150, 30, { OBJINFO.CenterPosX - 10.f, OBJINFO.CenterPosY - 38.f }, 0.5f, 0.5f);
    }
    if (Current_State == MONSTER_STATE::MONSTER_WALK_R && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        PlayAnimation_Loop(DC, L"Chamber_Walk_R", &StartPixelFrame[1], 250, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 12.f}, 0.5f, 0.5f);
    }
    else if (Current_State == MONSTER_STATE::MONSTER_WALK_L && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        PlayAnimation_Loop(DC, L"Chamber_Walk_L", &StartPixelFrame[1], 250, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 12.f }, 0.5f, 0.5f);
    }
}
void MonsterObject::Monster_Animation_ATTK(HDC DC) {
    if (Previous_State != Current_State) {
        Previous_State = Current_State;
        StartPixelFrame[0] = 0;
        StartPixelFrame[1] = 0;
        AnimationTime = GetTickCount();

    }
        
    if ((Current_State == MONSTER_STATE::MONSTER_ATTACK_R || Current_State == MONSTER_STATE::MONSTER_ATTACK_L) && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY && StartPixelFrame[0] == 2) {
        SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
        SoundManager::Get_Instance()->PlaySoundW(L"Convoy_Attack.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 1.1f);
    }
    if ((Current_State == MONSTER_STATE::MONSTER_ATTACK_R || Current_State == MONSTER_STATE::MONSTER_ATTACK_L) && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER && StartPixelFrame[1] == 2) {
        SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
        SoundManager::Get_Instance()->PlaySoundW(L"Chamber_Attack.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 1.1f);
    }
    if (Current_State == MONSTER_STATE::MONSTER_ATTACK_R && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        if (PlayAnimation_Once(DC, L"Envoy_Attack_R", &StartPixelFrame[0], 600, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 20.f }, 0.5f, 0.5f)) {
            Previous_State = MONSTER_STATE::MONSTER_NONE;
            Current_State = MONSTER_STATE::MONSTER_IDLE_R;
           
            StartPixelFrame[0] = 0;
        }
    }
    else if (Current_State == MONSTER_STATE::MONSTER_ATTACK_L && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        if (PlayAnimation_Once(DC, L"Envoy_Attack_L", &StartPixelFrame[0], 600, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 20.f }, 0.5f, 0.5f)) {
            Previous_State = MONSTER_STATE::MONSTER_NONE;
            Current_State = MONSTER_STATE::MONSTER_IDLE_L;
            
            StartPixelFrame[0] = 0;
        }
    }
    if (Current_State == MONSTER_STATE::MONSTER_ATTACK_R && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        if (PlayAnimation_Once(DC, L"Chamber_Attack_R", &StartPixelFrame[1], 430, 30, { OBJINFO.CenterPosX + 50.f, OBJINFO.CenterPosY - 17.f }, 0.5f, 0.5f)) {
            Previous_State = MONSTER_STATE::MONSTER_NONE;
            Current_State = MONSTER_STATE::MONSTER_WALK_R;
            
            StartPixelFrame[1] = 0;
        }
    }
    else if (Current_State == MONSTER_STATE::MONSTER_ATTACK_L && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        if (PlayAnimation_Once(DC, L"Chamber_Attack_L", &StartPixelFrame[1], 430, 30, { OBJINFO.CenterPosX - 50.f, OBJINFO.CenterPosY - 17.f }, 0.5f, 0.5f)) {
            Previous_State = MONSTER_STATE::MONSTER_NONE;
            Current_State = MONSTER_STATE::MONSTER_WALK_L;
            StartPixelFrame[1] = 0;
        }
    }
}
void MonsterObject::Monster_Animation_DEAD(HDC DC) {
    if (Previous_State != Current_State) {
        Previous_State = Current_State;
        StartPixelFrame[0] = 0;
        AnimationTime = GetTickCount();
    }

    if ((Current_State == MONSTER_STATE::MONSTER_DEAD_R || Current_State == MONSTER_STATE::MONSTER_DEAD_L) && Death_Sound) {
        if (Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CONVOY);
            SoundManager::Get_Instance()->PlaySoundW(L"Convoy_Death.WAV", CHANNELID::SOUND_MONSTER_CONVOY, 1.1f);
        }
    }
    if ((Current_State == MONSTER_STATE::MONSTER_DEAD_R || Current_State == MONSTER_STATE::MONSTER_DEAD_L) && Death_Sound) {
        if (Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
            SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_MONSTER_CHAMBER);
            SoundManager::Get_Instance()->PlaySoundW(L"Chamber_Death.WAV", CHANNELID::SOUND_MONSTER_CHAMBER, 1.1f);
        }
    }
    Death_Sound = false;
    if (Current_State == MONSTER_STATE::MONSTER_DEAD_R && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        PlayAnimation_Once(DC, L"Envoy_Dead_R", &StartPixelFrame[0], 200, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 13.f }, 0.5f, 0.5f);
    }
    else if (Current_State == MONSTER_STATE::MONSTER_DEAD_L && Monster_Type == MONSTER_TYPE::MONSTER_ENVOY) {
        PlayAnimation_Once(DC, L"Envoy_Dead_L", &StartPixelFrame[0], 200, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 13.f }, 0.5f, 0.5f);
    }
    if (Current_State == MONSTER_STATE::MONSTER_DEAD_R && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        PlayAnimation_Once(DC, L"Chamber_Dead_R", &StartPixelFrame[1], 250, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 13.f }, 0.5f, 0.5f);
    }
    else if (Current_State == MONSTER_STATE::MONSTER_DEAD_L && Monster_Type == MONSTER_TYPE::MONSTER_CHAMBER) {
        PlayAnimation_Once(DC, L"Chamber_Dead_L", &StartPixelFrame[1], 250, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 13.f }, 0.5f, 0.5f);
    }
}

BOOL MonsterObject::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
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
        return true;
    }

    if (_AnimSpeed + AnimationTime < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
        *_SPF += 1;
        AnimationTime = GetTickCount();
    }

    ReleaseDC(hWnd, MemDC);

    return false;
}

void MonsterObject::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
    Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
    HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

    UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
    UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

    UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

    FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
    FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

    if (_AnimSpeed + AnimationTime < GetTickCount()) {
        *_SPF += 1;
        AnimationTime = GetTickCount();

        if (*_SPF >= _FrameEndIndex-1) {  *_SPF = 0;  }
    }

    GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X, StartTop - CameraManager::Get_Instance()->GetOffset().Y,
        Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
        *_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));
    ReleaseDC(hWnd, MemDC);

}