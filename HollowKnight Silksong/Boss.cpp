#include "PCH.h"
#include "Boss.h"

ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;
Image* image[20];
int idx = 0;

BossObject::BossObject() : PlayerPos(0), dwTime{ GetTickCount() }, degree(0), PlayerDirection(-1), Pattern_Selector(0), StartPixelFrame{ 0 }, LoopTime(GetTickCount()),
NnockBacking_R(false), NnockBacking_L(false), NnockBack_Value(0), TimeDelay(false), PNGTime(GetTickCount()), Charging(false), EffectIndex(0),
LandStartPoint{ 0.f, 0.f }, StunPoint{0.f, 0.f}, ASLH_Count(0), ONHIT(false){
}

BossObject::~BossObject() { Release(); }

void BossObject::Initialize() {
	OBJINFO = {0.f, 0.f, 0.f, 0.f};
	OBJTAG = OBJECT_TAG::OBJ_BOSS;

	OBJHP = 1000;
	STATE_VALUE = 0;

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_BOSS_HITBOX, AbstractFactory<HitBoxObject>::Create());
	HitBox = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS_HITBOX)->back();
	HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	HitBox_Enable = 1;
	HitBox->Set_Tag(OBJECT_TAG::OBJ_BOSS_HITBOX);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_BOSS_HITBOX_CIRCLE, AbstractFactory<HitBoxObject>::Create());
	HitBox_Circle = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_BOSS_HITBOX_CIRCLE)->back();
	HitBox_Circle->Set_Info(0.f, 0.f, 0.f, 0.f);
	HitBox_Circle->Set_Tag(OBJECT_TAG::OBJ_BOSS_HITBOX_CIRCLE);

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();

	dwTime[9] = GetTickCount();

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Dash/BossDash_L_Anim.bmp", L"Boss_DashL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Dash/BossDash_R_Anim.bmp", L"Boss_DashR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P4/Pattern04_Anim_L.bmp", L"Pattern04L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P4/Pattern04_Anim_R.bmp", L"Pattern04R");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P2/Spinning_L_Anim.bmp", L"Pattern02L_Spinning");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P2/Spinning_R_Anim.bmp", L"Pattern02R_Spinning");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P2/Shot_L_Anim.bmp", L"Pattern02L_Landing");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P2/Shot_R_Anim.bmp", L"Pattern02R_Landing");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P1/Split_L_Anim.bmp", L"Pattern01L_Split");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P1/Split_R_Anim.bmp", L"Pattern01R_Split");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Idle/Idle_R_Anim.bmp", L"IdleR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Idle/Idle_L_Anim.bmp", L"IdleL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Start/Start_Anim.bmp", L"Start");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Start/Stage_Start.bmp", L"StartImage");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Stop_L_Anim.bmp", L"StopL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Stop_R_Anim.bmp", L"StopR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/NnockOut_L_Anim.bmp", L"NBK_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/NnockOut_R_Anim.bmp", L"NBK_R");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P3/Parring_R_Anim.bmp", L"Pattern03R_Parring");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P3/Parring_L_Anim.bmp", L"Pattern03L_Parring");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P3/Parring_R_Attack_Anim.bmp", L"Pattern03R_Parring_Attack");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/P3/Parring_L_Attack_Anim.bmp", L"Pattern03L_Parring_Attack");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Stun/Stun_R_Anim.bmp", L"StunR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Stun/Stun_L_Anim.bmp", L"StunL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Stun/Stun_PTC_Anim.bmp", L"PTC_Stun");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Fury/Fury_R_Anim.bmp", L"FuryR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Fury/Fury_L_Anim.bmp", L"FuryL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Stun/NnockOut_R_Anim.bmp", L"NnockOutR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Stun/NnockOut_L_Anim.bmp", L"NnockOutL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Down_R_Anim.bmp", L"DownR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Down_L_Anim.bmp", L"DownL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Dead_R_Anim.bmp", L"DeadR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/End/Dead_L_Anim.bmp", L"DeadL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/AirSlash/AirSlash_Anim.bmp", L"AirSlash");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/AirSlash/Slash_AF_Anim.bmp", L"AirSlash_AF");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/AirSlash/Slash_BF_Anim.bmp", L"AirSlash_BF");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/ASLH_Effect_Anim.bmp", L"ASLH_Effect");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/LAND_Effect_L_Anim.bmp", L"LAND_Effect_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/LAND_Effect_R_Anim.bmp", L"LAND_Effect_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/SpinJump_Effect_L_Anim.bmp", L"SJump_Effect_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/SpinJump_Effect_R_Anim.bmp", L"SJump_Effect_R"); 
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/ASLH_LAND_Effect_Anim.bmp", L"ASLH_LAND_Effect");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Stun_Effect.bmp", L"Stun_Effect");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Explosion_Effect.bmp", L"Exp_Effect");


	BossJumpSpeed = -3.f;
	Gravity = 1.f;
	GetGravity = false;
	OnUsingSkill = false;
	OnGround = true;
	BossMovable = 1;
	IsDead = false;
	Stage_StartTime = 9000;

	Previous_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
	Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;

	Previous_State = BOSS_STATE::BOSS_NONE;
	Current_State = BOSS_STATE::BOSS_START;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image[0] = Image::FromFile(L"Ring08.png");
	image[1] = Image::FromFile(L"Ring01.png");
	image[2] = Image::FromFile(L"Ring02.png");
	image[3] = Image::FromFile(L"Ring03.png");
	image[4] = Image::FromFile(L"Ring04.png");
	image[5] = Image::FromFile(L"Ring05.png");
	image[6] = Image::FromFile(L"Ring06.png");
	image[7] = Image::FromFile(L"Ring07.png");

	image[8] =	Image::FromFile(L"Dead01.png");
	image[9] =	Image::FromFile(L"Dead02.png");
	image[10] = Image::FromFile(L"Dead03.png");
	image[11] = Image::FromFile(L"Dead04.png");
	image[12] = Image::FromFile(L"Dead05.png");
	image[13] = Image::FromFile(L"Dead06.png");
	
}
int  BossObject::Update() {

	if (KEY_COMMAND(KEY::O, KEY_STATE::DOWN)) {
		OBJHP = 200;
		STATE_VALUE = 3;
	}
	Update_RECT();
	Boss_GravitySetting();
	Boss_StateMachine();
	Boss_State_Control();
	if (Current_State == BOSS_STATE::BOSS_NONE) {
		Boss_Skill_StateMachine();
		Boss_Skill_Control();
		Boss_Nnock_Back();
	}
	else{ 
		Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
		Previous_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
	}
	
	if (OBJINFO.CenterPosX < 50.f) {
		OBJINFO.CenterPosX = 50.f;
	}
	if (OBJINFO.CenterPosX > DEFAULT_WINDOW_CX + 200.f - 50.f) {
		OBJINFO.CenterPosX = DEFAULT_WINDOW_CX + 200.f - 50.f;
	}

	
	return OBJ_ALIVE;
}
void BossObject::Late_Update()	{ }
void BossObject::Render(HDC DC) {
	

	if (Charging && Current_State == BOSS_STATE::BOSS_NONE) {
		if (PNGTime + 20 < GetTickCount()) {
			idx++;
			PNGTime = GetTickCount();
		}
		::Graphics g(DC);
		g.DrawImage(image[idx % 8], (INT)PlayerPos - 200 - (INT)CameraManager::Get_Instance()->GetOffset().X, 150, 400, 400);
	}
	else if (Charging) { Charging = false; }
	
	if (Current_State == BOSS_STATE::BOSS_NONE) {
		if (dwTime[0] + 100 < GetTickCount() && TimeDelay) {
			FrameIntervalTimeB = 0;
		}
		if (dwTime[0] + 150 < GetTickCount() && TimeDelay) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_PATK;
			TimeDelay = false;
			dwTime[0] = GetTickCount();
		}

		//HPEN myPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 255));
		//HGDIOBJ oldPen = SelectObject(DC, myPen);
		//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
		//
		//Rectangle(DC, OBJRECT.left - CameraManager::Get_Instance()->GetOffset().X, OBJRECT.top,
		//	OBJRECT.right - CameraManager::Get_Instance()->GetOffset().X, OBJRECT.bottom);
		//
		//SelectObject(DC, oldBrush);
		//DeleteObject(myBrush);
		//
		//SelectObject(DC, oldPen);
		//DeleteObject(myPen);

		
		Boss_Animation_Dash(DC);
		Boss_Animation_Poke(DC);
		Boss_Animation_Spin(DC);
		Boss_Animation_Land(DC);
		Boss_Animation_Splt(DC);
		Boss_Animation_Idle(DC);
		Boss_Animation_Prng(DC);
		Boss_Animation_PATK(DC);
		Boss_Animation_ASLH(DC);
	}
	Boss_Animation_START(DC);
	Boss_Animation_FURY(DC);
	Boss_Animation_STUN(DC);
	Boss_Animation_DEAD(DC);

	Flower_Parade();
}

void BossObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_ENVIROMENT) {
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER_HITBOX) {
		
		
		if (Current_SkillState == BOSS_SKILL_STATE::BOSS_PRNG && !TimeDelay) {
			if (StartPixelFrame[0] >= 7 && StartPixelFrame[0] <= 24) {
				
				if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
				if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection =  1; }
   			
				dwTime[0] = GetTickCount();
				TimeDelay = true;
				FrameIntervalTimeB = 80;
				return;
			}
		}
		
		
	
		
		if (OBJINFO.CenterPosX > Catch_PlayerPosition() && !TimeDelay && Current_SkillState == BOSS_SKILL_STATE::BOSS_NONE) {
			NnockBacking_R = true;
		}
		else if (OBJINFO.CenterPosX <= Catch_PlayerPosition() && !TimeDelay && Current_SkillState == BOSS_SKILL_STATE::BOSS_NONE) {
			NnockBacking_L = true;
		}
	}
}

void BossObject::Release() {
	
}

void BossObject::Boss_GravitySetting() {
	if (BossJumpSpeed >= -30.f) {
		BossJumpSpeed -= Gravity;
	}

	if (GetGravity) {
		OBJINFO.CenterPosY -= BossJumpSpeed;
	}
}

void BossObject::Boss_Skill_StateMachine() {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_READY) {
     	if (Pattern_Selector <= 10) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_DASH;
			if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
			if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
		}
		else if (Pattern_Selector >= 11 && Pattern_Selector <= 25) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_POKE;
			if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
			if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
		}
		else if (Pattern_Selector >= 26 && Pattern_Selector <= 50) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_SPIN;
			if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
			if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
		}
		else if (Pattern_Selector >= 51 && Pattern_Selector <= 80) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_SPLIT;
			if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
			if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
		}
		else if (Pattern_Selector >= 81 && Pattern_Selector <= 90) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_PRNG;
			if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
			if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
		}
		else if (Pattern_Selector >= 91 && Pattern_Selector <= 100) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_ASLH_BF;
			PlayerPos = Player->Get_Pos().X;
		}
	}

	if(dwTime[0] + 1000.f < GetTickCount() && Current_SkillState == BOSS_SKILL_STATE::BOSS_NONE) {
		Current_SkillState = BOSS_SKILL_STATE::BOSS_READY;
		Previous_SkillState = BOSS_SKILL_STATE::BOSS_NONE;

		srand(time(NULL));
		Pattern_Selector = rand() % 100 + 1;
	}
	else if (dwTime[0] + 1000.f >= GetTickCount() ) {
		if (Pattern_Selector <= 10) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Ha.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
		else if (Pattern_Selector >= 11 && Pattern_Selector <= 25) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Heu01.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
		else if (Pattern_Selector >= 26 && Pattern_Selector <= 50) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Heu02.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
		else if (Pattern_Selector >= 51 && Pattern_Selector <= 80) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Heu03.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
		else if (Pattern_Selector >= 81 && Pattern_Selector <= 90) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Heu04.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
		else if (Pattern_Selector >= 91 && Pattern_Selector <= 100) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_WEAPON);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Heu05.WAV", CHANNELID::SOUND_WEAPON, 1.1f);
		}
	}
}

void BossObject::Boss_StateMachine() {
	if (OBJHP <= MAX_BOSS_HP / 5 * 4 && STATE_VALUE == 0) {
		Current_State = BOSS_STATE::BOSS_STUN;
		dwTime[0] = GetTickCount();

		if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
		if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }

		BossJumpSpeed = 12.f;
		GetGravity = true;
		FrameIntervalTimeB = 50;

		STATE_VALUE++;
	}
	if (OBJHP <= MAX_BOSS_HP / 5 * 3 && STATE_VALUE == 1) {
		Current_State = BOSS_STATE::BOSS_FURY;
		dwTime[0] = GetTickCount();
		CameraManager::Get_Instance()->CameraShake(4000, 5);
		STATE_VALUE++;
	}
	if (OBJHP <= MAX_BOSS_HP / 5 * 2 && STATE_VALUE == 2) {
		Current_State = BOSS_STATE::BOSS_STUN;
		dwTime[0] = GetTickCount();

		if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
		if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }

		BossJumpSpeed = 10.f;
		GetGravity = true;
		FrameIntervalTimeB = 50;

		STATE_VALUE++;
	}
	if (OBJHP <= MAX_BOSS_HP / 5 && STATE_VALUE == 3) {
		Current_State = BOSS_STATE::BOSS_FURY;
		CameraManager::Get_Instance()->CameraShake(4000, 5);
		dwTime[0] = GetTickCount();
		STATE_VALUE++;
	}
	if (OBJHP <= 0 && STATE_VALUE == 4) {
		Current_State = BOSS_STATE::BOSS_STOP;
		FrameIntervalTimeB = 50;

		

		HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
		DEAD = true;
		dwTime[0] = GetTickCount();
  		STATE_VALUE++;
	}
}

void BossObject::Boss_Skill_Control() {
	FLOAT	Dash_Speed = 30.f, Poke_Speed = 30.f, SpinMove_Speed = 30.f, 
		Land_Speed = 40.f, Split_Speed = 30.f, Parring_Speed = 30.f;

	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_DASH) {
		
		if ((StartPixelFrame[0] > 3 && StartPixelFrame[0] < 10) || (StartPixelFrame[0] > 17 && StartPixelFrame[0] < 23)) {
			if (PlayerDirection == 1) {
				if (degree < 360) {
					degree += 36;
					OBJINFO.CenterPosX += fabsf(sin((degree) * PI / 180)) * Dash_Speed;
				}
			}
			else if (PlayerDirection == -1) {
				if (degree < 360) {
					degree += 36;
					OBJINFO.CenterPosX -= fabsf(sin((degree ) * PI / 180)) * Dash_Speed;
				}
			}
		}
		if (StartPixelFrame[0] == 23 || StartPixelFrame[0] == 10) {
			degree = 0;
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_POKE) {
		if (StartPixelFrame[0] >= 15 && StartPixelFrame[0] <= 27) {

			if (PlayerDirection == 1) {
				if (degree <= 180) {
					OBJINFO.CenterPosX += sin((degree % 180) * PI / 180) * Poke_Speed;
					degree += 12;

					HitBox->Set_Info(OBJINFO.CenterPosX + 30.f, OBJINFO.CenterPosY + 20.f, 50, 40);
					dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
					dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
				}
			}
			else if (PlayerDirection == -1) {
				if (degree <= 180) {
					OBJINFO.CenterPosX -= sin((degree % 180) * PI / 180) * Poke_Speed;
					degree += 12;

					HitBox->Set_Info(OBJINFO.CenterPosX - 30.f, OBJINFO.CenterPosY + 20.f, 50, 40);
					dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
					dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
				}
			}
		}
		if (StartPixelFrame[0] > 27) {
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
			degree = 0;
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_SPIN) {
		if (LandStartPoint.X == 0.f && LandStartPoint.Y == 0.f) {
			LandStartPoint = { OBJINFO.CenterPosX, OBJINFO.CenterPosY };
		}
		if (StartPixelFrame[0] > 8) {
			OnGround = false;

			HitBox->Set_Info(OBJINFO.CenterPosX + 20.f, OBJINFO.CenterPosY , 100, 100);
			dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
			dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);

			Set_Info(OBJINFO.CenterPosX, OBJINFO.CenterPosY, 50.f, 50.f);

			if (PlayerDirection == 1) {
				OBJINFO.CenterPosX += (cosf(40 * (PI / 180))) * SpinMove_Speed;
				OBJINFO.CenterPosY -= (sinf(40 * (PI / 180))) * SpinMove_Speed;
			}
			else if (PlayerDirection == -1) {
				OBJINFO.CenterPosX -= (cosf(40 * (PI / 180))) * SpinMove_Speed;
				OBJINFO.CenterPosY -= (sinf(40 * (PI / 180))) * SpinMove_Speed;
			}
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_LAND) {
		if (LandStartPoint.X == 0.f && LandStartPoint.Y == 0.f) {
			LandStartPoint = {OBJINFO.CenterPosX, OBJINFO.CenterPosY};
		}
		if (StartPixelFrame[0] >= 9 && StartPixelFrame[0] <= 15) {
			BossJumpSpeed = -10.f;
			GetGravity = true;

			if (PlayerDirection == 1 && !OnGround) {
				OBJINFO.CenterPosX += cosf(40 * (PI / 180)) * Land_Speed;
				OBJINFO.CenterPosY += sinf(40 * (PI / 180)) * Land_Speed;
			}
			else if (PlayerDirection == -1 && !OnGround) {
				OBJINFO.CenterPosX -= cosf(40 * (PI / 180)) * Land_Speed;
				OBJINFO.CenterPosY += sinf(40 * (PI / 180)) * Land_Speed;
			}
		}
		if (StartPixelFrame[0] <= 15) {
			HitBox->Set_Info(OBJINFO.CenterPosX + 20.f, OBJINFO.CenterPosY, 100, 100);
			dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
			dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
		}
		if (StartPixelFrame[0] > 15) {
			Set_Info(OBJINFO.CenterPosX, OBJINFO.CenterPosY, 50.f, 100.f);
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
			GetGravity = false;
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_SPLIT) {
		if (StartPixelFrame[0] >= 6 && StartPixelFrame[0] <= 11) {
			HitBox->Set_Info(OBJINFO.CenterPosX + 20.f, OBJINFO.CenterPosY, 200, 100);
			dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
			dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
			if (PlayerDirection == 1) {
				if (degree < 180) {
					OBJINFO.CenterPosX += sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 30;
				}
				else { degree = 0; }
			}
			else if (PlayerDirection == -1) {
				if (degree < 180) {
					OBJINFO.CenterPosX -= sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 30;
				}
				else { degree = 0; }
			}
		}
		if (StartPixelFrame[0] == 13) {
			degree = 0; 
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
		}
		if (StartPixelFrame[0] >= 14 && StartPixelFrame[0] <= 19) {

			HitBox->Set_Info(OBJINFO.CenterPosX + 20.f, OBJINFO.CenterPosY, 200, 100);
			dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
			dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);

			if (PlayerDirection == 1) {
				if (degree < 180) {
					OBJINFO.CenterPosX += sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 18;
				}
				else { degree = 0; }
			}
			else if (PlayerDirection == -1) {
				if (degree < 180) {
					OBJINFO.CenterPosX -= sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 18;
				}
				else { degree = 0; }
			}
		}
		if (StartPixelFrame[0] == 21) {
			degree = 0; 
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
		}
		if (StartPixelFrame[0] >= 22 && StartPixelFrame[0] <= 27) {

			HitBox->Set_Info(OBJINFO.CenterPosX + 20.f, OBJINFO.CenterPosY, 200, 100);
			dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
			dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);

			if (PlayerDirection == 1) {
				if (degree < 180) {
					OBJINFO.CenterPosX += sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 18;
				}
				else { degree = 0; }
			}
			else if (PlayerDirection == -1) {
				if (degree < 180) {
					OBJINFO.CenterPosX -= sin((degree % 180) * PI / 180) * Split_Speed;
					degree += 18;
				}
				else { degree = 0; }
			}
		}
		if (StartPixelFrame[0] > 27) {
			degree = 0;
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_PATK) {
		if (StartPixelFrame[0] >= 0 && StartPixelFrame[0] <= 5) {

			if (PlayerDirection == 1 && degree <= 180) {
				OBJINFO.CenterPosX += (cosf(degree * (PI / 180)) + 1) * Parring_Speed;
				degree += 36;
			}
			if (PlayerDirection == -1 && degree <= 180) {
				OBJINFO.CenterPosX -= (cosf(degree * (PI / 180)) + 1) * Parring_Speed;
				degree += 36;

			}
		}
		if (StartPixelFrame[0] >= 6 && StartPixelFrame[0] <= 27) {
			if (PlayerDirection == 1) {
				HitBox->Set_Info(OBJINFO.CenterPosX + 100.f, OBJINFO.CenterPosY, 140, 100);
				dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
				dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
			}
			if (PlayerDirection == -1) {
				HitBox->Set_Info(OBJINFO.CenterPosX - 100.f, OBJINFO.CenterPosY, 140, 100);
				dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
				dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(2);
			}
		}
		else if(StartPixelFrame[0] > 27){
			degree = 0;
			HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH_BF) {
		Charging = true;
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH) {
		Charging = false;
		Set_Info(PlayerPos, 350.f, 50.f, 100.f);
		HitBox_Circle->Set_Info(PlayerPos - CameraManager::Get_Instance()->GetOffset().X, 350.f, 380.f, 380.f);
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH_AF) {
		CameraManager::Get_Instance()->CameraShake(200.f, 5);
		Set_Info(OBJINFO.CenterPosX, 520.f, 50.f, 100.f);
		HitBox_Circle->Set_Info(0.1f, 0.1f, 0.1f, 0.1f);
	}
} 
void BossObject::Boss_State_Control() {
	
	if (Current_State == BOSS_STATE::BOSS_STUN) {
		HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	}
	if (Current_State == BOSS_STATE::BOSS_FURY) {
		HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	}
	if (Current_State == BOSS_STATE::BOSS_DEAD) {
		//GetGravity = true;
		//if(!IsDead){
		//	BossJumpSpeed = 10.f;
		//	IsDead = true;
		//	dwTime = GetTickCount();
		//	FrameIntervalTimeB = 80;
		//}
		//if (dwTime + 100 < GetTickCount()) {
		//	FrameIntervalTimeB = 0;
		//}
	}if (Current_State == BOSS_STATE::BOSS_NUCKBACK) {
		GetGravity = true;
	}
}

void BossObject::Boss_Nnock_Back() {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_NONE 
		&& Current_State == BOSS_STATE::BOSS_NONE &&
		Previous_State == BOSS_STATE::BOSS_NONE) {
		if (NnockBacking_L) {
			
			OBJINFO.CenterPosX -= 30.f;
			NnockBack_Value += 80.f;
			if (NnockBack_Value > 200) {
				NnockBack_Value = 0.f;
				NnockBacking_L = false;
			}
			
		}
		if (NnockBacking_R) {
			OBJINFO.CenterPosX += 30.f;
			NnockBack_Value += 80.f;
			if (NnockBack_Value > 200) {
				NnockBack_Value = 0.f;
				NnockBacking_R = false;
			}
		}
	}
}

void BossObject::Boss_Animation_Dash(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_DASH) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_DASH) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_DASH;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"Boss_DashR", &StartPixelFrame[0], 210, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"Boss_DashL", &StartPixelFrame[0], 210, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_Poke(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_POKE) {
		
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_POKE) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_POKE;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Poke.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"Pattern04R", &StartPixelFrame[0], 270, 25, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"Pattern04L", &StartPixelFrame[0], 270, 25, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_Spin(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_SPIN) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_SPIN) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_SPIN;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
			StartPixelFrame[1] = 0;
			dwTime[1] = GetTickCount();
			if (1 == rand() % 3 + 1) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"Boss_SpinLand01.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			else if (2 == rand() % 3 + 1){
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"Boss_SpinLand02.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
			else {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"Boss_SpinLand03.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			}
		}
		if (PlayerDirection == 1) {
			if (StartPixelFrame[0] >= 10 && StartPixelFrame[0] <= 11)
				PlayAnimation_Once(DC, L"SJump_Effect_R", &StartPixelFrame[1], 400, 25, &dwTime[1], { LandStartPoint.X, LandStartPoint.Y }, 0.5f, 0.5f);
			if (PlayAnimation_Once(DC, L"Pattern02R_Spinning", &StartPixelFrame[0], 350, 25, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				dynamic_cast<HitBoxObject*>(HitBox)->DeActivate_HitBox();
				Current_SkillState = BOSS_SKILL_STATE::BOSS_LAND;
				if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
				if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
				dwTime[0] = GetTickCount();
				LandStartPoint = { 0.f, 0.f };
			}
		}
		else if (PlayerDirection == -1) {
			if(StartPixelFrame[0] >= 10 && StartPixelFrame[0] <= 11)
				PlayAnimation_Once(DC, L"SJump_Effect_L", &StartPixelFrame[1], 400, 12, &dwTime[1], { LandStartPoint.X, LandStartPoint.Y }, 0.5f, 0.5f);
			if (PlayAnimation_Once(DC, L"Pattern02L_Spinning", &StartPixelFrame[0], 350, 25, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_LAND;
				if (OBJINFO.CenterPosX > Catch_PlayerPosition()) { PlayerDirection = -1; }
				if (OBJINFO.CenterPosX < Catch_PlayerPosition()) { PlayerDirection = 1; }
				dwTime[0] = GetTickCount();
				LandStartPoint = { 0.f, 0.f };
			}
		}
		
	}
}
void BossObject::Boss_Animation_Land(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_LAND) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_LAND) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_LAND;
			dwTime[0] = GetTickCount();
			dwTime[1] = GetTickCount();
			StartPixelFrame[0] = 0;
			
		}
		if (PlayerDirection == 1) {
			if (StartPixelFrame[0] >= 8 && StartPixelFrame[0] <= 9) {
				PlayAnimation_Once(DC, L"LAND_Effect_R", &StartPixelFrame[1], 400, 15, &dwTime[1], { LandStartPoint.X - 40, LandStartPoint.Y - 40 }, 0.4f, 0.4f);
			}
			else {
				StartPixelFrame[1] = 0;
			}
			if (PlayAnimation_Once(DC, L"Pattern02R_Landing", &StartPixelFrame[0], 350, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
				LandStartPoint = { 0.f, 0.f };
			}
		}
		else if (PlayerDirection == -1) {
			if (StartPixelFrame[0] >= 8 && StartPixelFrame[0] <= 9) {
				PlayAnimation_Once(DC, L"LAND_Effect_L", &StartPixelFrame[1], 400, 15, &dwTime[1], { LandStartPoint.X + 40, LandStartPoint.Y - 40 }, 0.4f, 0.4f);
			}
			else {
				StartPixelFrame[1] = 0;
			}
			if (PlayAnimation_Once(DC, L"Pattern02L_Landing", &StartPixelFrame[0], 350, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
				LandStartPoint = { 0.f, 0.f };
			}
		}
	}
}
void BossObject::Boss_Animation_Splt(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_SPLIT) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_SPLIT) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_SPLIT;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
			if (1 == rand() % 2 + 1) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"Boss_Split01.WAV", CHANNELID::SOUND_EFFECT, 0.6f);
			}
			else {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
				SoundManager::Get_Instance()->PlaySoundW(L"Boss_Split02.WAV", CHANNELID::SOUND_EFFECT, 0.6f);
			}
			
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"Pattern01R_Split", &StartPixelFrame[0], 440, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();  
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"Pattern01L_Split", &StartPixelFrame[0], 440, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_Idle(HDC DC) {
	
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_NONE) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_NONE) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
		}
		if (OBJINFO.CenterPosX < Catch_PlayerPosition()) {
			PlayAnimation_Loop(DC, L"IdleR", &StartPixelFrame[0], 230, 50, dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0, 0.6f, 0.6f);
		}
		if (OBJINFO.CenterPosX > Catch_PlayerPosition()) {
			PlayAnimation_Loop(DC, L"IdleL", &StartPixelFrame[0], 230, 50, dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0, 0.6f, 0.6f);
		}
	}
}
void BossObject::Boss_Animation_Prng(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_PRNG) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_PRNG) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_PRNG;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_PRNG.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"Pattern03R_Parring", &StartPixelFrame[0], 300, 50, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"Pattern03L_Parring", &StartPixelFrame[0], 300, 50, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_PATK(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_PATK) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_PATK) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_PATK;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_PATK.WAV", CHANNELID::SOUND_EFFECT, 0.6f);
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"Pattern03R_Parring_Attack", &StartPixelFrame[0], 500, 60, &dwTime[0], { OBJINFO.CenterPosX + 60.f, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"Pattern03L_Parring_Attack", &StartPixelFrame[0], 500, 60, &dwTime[0], { OBJINFO.CenterPosX - 60.f, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_ASLH(HDC DC) {
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH_BF) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_ASLH_BF) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_ASLH_BF;
			dwTime[0] = GetTickCount();
			dwTime[1] = GetTickCount();
			StartPixelFrame[0] = 0;
			StartPixelFrame[1] = 0;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_ASLH.WAV", CHANNELID::SOUND_EFFECT, 0.6f);
		}
		PlayAnimation_Loop(DC, L"ASLH_Effect", &StartPixelFrame[1], 400, 20, dwTime[1], { OBJINFO.CenterPosX + 10, OBJINFO.CenterPosY + 20 }, 0, 1.f, 0.5f);
		if (PlayAnimation_Once(DC, L"AirSlash_BF", &StartPixelFrame[0], 225, 50, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_ASLH;
			dwTime[0] = GetTickCount();
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_ASLH) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_ASLH;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
		}
		if (PlayAnimation_Once(DC, L"AirSlash", &StartPixelFrame[0], 900, 15, &dwTime[0], { PlayerPos, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			Current_SkillState = BOSS_SKILL_STATE::BOSS_ASLH_AF;
			
			dwTime[0] = GetTickCount();
		}
	}
	if (Current_SkillState == BOSS_SKILL_STATE::BOSS_ASLH_AF) {
		if (Previous_SkillState != BOSS_SKILL_STATE::BOSS_ASLH_AF) {
			Previous_SkillState = BOSS_SKILL_STATE::BOSS_ASLH_AF;
			dwTime[0] = GetTickCount();
			dwTime[1] = GetTickCount();
			StartPixelFrame[0] = 0;
			StartPixelFrame[1] = 0;
			for (int i = 0; i < 30; ++i) {
				FlowerVec.push_back({ (FLOAT)(rand() % 1280 + 1), (FLOAT)(rand() % 50) });
			}
			int a = 0;
		}

		if (StartPixelFrame[0] >= 0 && StartPixelFrame[0] <= 2) {
			PlayAnimation_Once(DC, L"ASLH_LAND_Effect", &StartPixelFrame[1], 400, 20, &dwTime[1], { OBJINFO.CenterPosX + 40, OBJINFO.CenterPosY });
		}
		else {
			StartPixelFrame[1] = 0;
		}
		if (PlayAnimation_Once(DC, L"AirSlash_AF", &StartPixelFrame[0], 225, 40, &dwTime[0], { PlayerPos, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			if (ASLH_Count < 1) {
				ASLH_Count++;
				Current_SkillState = BOSS_SKILL_STATE::BOSS_ASLH_BF;
				PlayerPos = Player->Get_Pos().X;
			}
			else if (ASLH_Count >= 1) {
				ASLH_Count = 0;
				Current_SkillState = BOSS_SKILL_STATE::BOSS_NONE;
			}

			
			dwTime[0] = GetTickCount();
		}
	}
}
void BossObject::Boss_Animation_START(HDC DC) {
	if (Current_State == BOSS_STATE::BOSS_START) {
		if (Previous_State != BOSS_STATE::BOSS_START) {
			Previous_State = BOSS_STATE::BOSS_START;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
		}

		if (StartPixelFrame[0] == 10){
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_StartLaugh.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
		
		if (PNGTime + Stage_StartTime < GetTickCount()) {
			if (PlayAnimation_Once(DC, L"Start", &StartPixelFrame[0], 300, 60, &dwTime[0], { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NONE;
				PNGTime = GetTickCount();
				Set_Scale(50.f, 100.f);
			}
		}
		else {
			FileManager::Get_Instance()->Append_Image(DC, L"StartImage", { OBJINFO.CenterPosX , OBJINFO.CenterPosY + 20.f }, 0.6f, 0.6f);
		}
	}
}
void BossObject::Boss_Animation_FURY(HDC DC) {
	if (Current_State == BOSS_STATE::BOSS_FURY) {
		if (Previous_State != BOSS_STATE::BOSS_FURY) {
			Previous_State = BOSS_STATE::BOSS_FURY;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Fury.WAV", CHANNELID::SOUND_EFFECT, 0.6f);
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"FuryR", &StartPixelFrame[0], 200, 80, &dwTime[0], { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"FuryL", &StartPixelFrame[0], 200, 80, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
			}
		}
	}
}
void BossObject::Boss_Animation_STUN(HDC DC) {
	if (Current_State == BOSS_STATE::BOSS_STUN) {
		if (Previous_State != BOSS_STATE::BOSS_STUN) {
			Previous_State = BOSS_STATE::BOSS_STUN;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
		}
		if (StartPixelFrame[0] < 8) {
			OBJINFO.CenterPosX -= PlayerDirection * 3;
			
		}
		else {
			FrameIntervalTimeB = 0;
		}
		if (StunPoint.X == 0.f && StunPoint.Y == 0.f) {
			StunPoint.X = OBJINFO.CenterPosX;
			StunPoint.Y = OBJINFO.CenterPosY;
		}
		PlayAnimation_Once(DC, L"Stun_Effect", &StartPixelFrame[2], 320, 50, &dwTime[2], StunPoint, 0.8f, 0.8f);
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"StunR", &StartPixelFrame[0], 250,150, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
				GetGravity = false;
				StunPoint = { 0.f, 0.f };
				StartPixelFrame[2] = 0;
				dwTime[2] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"StunL", &StartPixelFrame[0], 250, 150, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NONE;
				dwTime[0] = GetTickCount();
				GetGravity = false;
				StunPoint = { 0.f, 0.f };
				StartPixelFrame[2] = 0;
				dwTime[2] = GetTickCount();
			}
		}
		//StartPixelFrame--;
		//PlayAnimation_Once(DC, L"PTC_Stun", 180, 150, { OBJINFO.CenterPosX, OBJINFO.CenterPosY - 20.f }, 0.6f, 0.6f);
	}
}
void BossObject::Boss_Animation_DEAD(HDC DC) {
	if (Current_State == BOSS_STATE::BOSS_STOP) {

		if (Previous_State != BOSS_STATE::BOSS_STOP) {
			Previous_State = BOSS_STATE::BOSS_STOP;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
			
			SoundManager::Get_Instance()->StopAll();
			SoundManager::Get_Instance()->PlaySoundW(L"Boss_Dead.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
			
		}
		if (StunPoint.X == 0.f && StunPoint.Y == 0.f) {
			StunPoint.X = OBJINFO.CenterPosX;
			StunPoint.Y = OBJINFO.CenterPosY;
		}

		if (PlayAnimation_Once(DC, L"Stun_Effect", &StartPixelFrame[2], 320, 100, &dwTime[2], StunPoint, 0.8f, 0.8f)) {
			CameraManager::Get_Instance()->CameraShake(1000, 10);
		}
		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"StopL", &StartPixelFrame[0], 250, 500, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NUCKBACK;
				BossJumpSpeed = 15.f;
				dwTime[0] = GetTickCount();
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"StopR", &StartPixelFrame[0], 250, 500, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_NUCKBACK;
				BossJumpSpeed = 15.f;
				dwTime[0] = GetTickCount();
			}
		}
	}
	if (Current_State == BOSS_STATE::BOSS_NUCKBACK) {

		if (Previous_State != BOSS_STATE::BOSS_NUCKBACK) {
			Previous_State = BOSS_STATE::BOSS_NUCKBACK;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
			StartPixelFrame[2] = 0;
		}
		if (StartPixelFrame[0] < 15) {
			OBJINFO.CenterPosX -= PlayerDirection * 3;
			PlayAnimation_Once(DC, L"Exp_Effect", &StartPixelFrame[2], 220, 40, &dwTime[2], StunPoint, 1.5f, 1.5f);
		}
		if (StartPixelFrame[0] < 5) {
			PlayAnimation_Once(DC, L"Exp_Effect", &StartPixelFrame[2], 220, 40, &dwTime[2], StunPoint, 1.5f, 1.5f);
		}

		if (PlayerDirection == 1) {
			if (PlayAnimation_Once(DC, L"NBK_L", &StartPixelFrame[0], 200, 100, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_DEAD;
				dwTime[0] = GetTickCount();
				//GetGravity = false;
			}
		}
		else if (PlayerDirection == -1) {
			if (PlayAnimation_Once(DC, L"NBK_R", &StartPixelFrame[0], 200, 100, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_State = BOSS_STATE::BOSS_DEAD;
				dwTime[0] = GetTickCount();
				//GetGravity = false;
			}
		}
	}
	if (Current_State == BOSS_STATE::BOSS_DEAD) {

		if (Previous_State != BOSS_STATE::BOSS_DEAD) {
			Previous_State = BOSS_STATE::BOSS_DEAD;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;
			FrameIntervalTimeB = 0;
			Set_Dead(true);
			
		}

		if (PlayerDirection == 1) {
			PlayAnimation_Once(DC, L"DeadL", &StartPixelFrame[0], 200, 100, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
		}
		else if (PlayerDirection == -1) {
			PlayAnimation_Once(DC, L"DeadR", &StartPixelFrame[0], 200, 100, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
		}
	}
	if (Current_State == BOSS_STATE::BOSS_DOWN) {
		if (Previous_State != BOSS_STATE::BOSS_DOWN) {
			Previous_State = BOSS_STATE::BOSS_DOWN;
			dwTime[0] = GetTickCount();
			StartPixelFrame[0] = 0;

		}
		if (PlayerDirection == 1) {
			PlayAnimation_Once_Stable(DC, L"DownL", &StartPixelFrame[0], 250, 80, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
		}
		else if (PlayerDirection == -1) {
			PlayAnimation_Once_Stable(DC, L"DownR", &StartPixelFrame[0], 250, 80, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
		}
	}
}



void BossObject::Flower_Parade() {
	for (auto i : FlowerVec) {
		i.Y += 3.f;
	}
}

BOOL BossObject::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
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

	if (*_SPF >= _FrameEndIndex - 1) {
		return true;
	}

	if (_AnimSpeed + *Timer < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		*Timer = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);

	return false;
}
void BossObject::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD Timer, 
	Vector2D _CenterPos, INT LoopFrame, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + Timer < GetTickCount()) {
		*_SPF += 1;
		Timer = GetTickCount();

		if (*_SPF >= _FrameEndIndex) {
			*_SPF = 0;
		}
	}

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X , StartTop - CameraManager::Get_Instance()->GetOffset().Y, 
		Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));
	ReleaseDC(hWnd, MemDC);

}
void BossObject::PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
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

	if (_AnimSpeed + *Timer < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		*Timer = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);
}
