#include "PCH.h"
#include "Player.h"


PlayerObject::PlayerObject() : Inventory(nullptr), PlayerJumpSpeed(0.f), dwTime{ GetTickCount() }, InfinityTime(GetTickCount()), MainUI_Enable(true)
, GetGravity(false), Player_Damaged(false), Player_Infinity_Enable(false), Player_Render(true), OnGround(true), StartPixelIndex{0}, SkillRoutine(0), effectIndex(5),
	PlayerEffectPos{0.f, 0.f} {
}
PlayerObject::~PlayerObject()	{ Release(); }

void PlayerObject::Initialize() {
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_UI, AbstractFactory<InventoryObject>::Create());
	Inventory = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_UI)->back();
	
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_UI, AbstractFactory<MainUI>::Create());
	PlayerMainUI =  ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_UI)->back();
	
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER_HITBOX, AbstractFactory<HitBoxObject>::Create());
	HitBox = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER_HITBOX)->back();

	HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	HitBox_Enable = 1;
	HitBox->Set_Tag(OBJECT_TAG::OBJ_PLAYER_HITBOX);

	OBJINFO = { DEFAULT_WINDOW_CX / 2.f, 4700.f, 40.f, 120.f };

	PlayerSpeed = 10.f;
	PlayerDirection = 0.f;
	PlayerMovable = 1;
	PlayerJumpSpeed = -3.f;
	PlayerJumpCount = 0;

	OBJTAG = OBJECT_TAG::OBJ_PLAYER;
	OBJDMG = 20;

	Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;
	Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;

	Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
	Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;

	Previous_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
	Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;

	Previous_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
	Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;

	Previous_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
	Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
	
	MukJu = 242;
	SilverStone = 107;
	OBJHP = 10;
	SILK = 8;
	Gravity = 1.0f;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image[0] = Image::FromFile(L"HLight01.png");
	image[1] = Image::FromFile(L"HLight02.png");
	image[2] = Image::FromFile(L"HLight03.png");
	image[3] = Image::FromFile(L"HLight04.png");
	image[4] = Image::FromFile(L"HLight05.png");

	image[5] = Image::FromFile(L"Para01.png");
	image[6] = Image::FromFile(L"Para02.png");
	image[7] = Image::FromFile(L"Para03.png");
	image[8] = Image::FromFile(L"Para04.png");
	image[9] = Image::FromFile(L"Para05.png");
}

int PlayerObject::Update() {
	Update_RECT();
	Player_StateMachine();
	Player_Control();
	Player_JumpDirection_Transition();

	Player_GravitySetting();
	//if (KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::HOLD)) { OBJINFO.CenterPosY -= 30.f; }
	//if (KEY_COMMAND(KEY::ARROW_DOWN, KEY_STATE::HOLD)) { OBJINFO.CenterPosY += 30.f; }
	
	if (KEY_COMMAND(KEY::I, KEY_STATE::DOWN)) {
		if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() == false) {
			dynamic_cast<InventoryObject*>(Inventory)->Set_Render_Enable(true);
			dynamic_cast<MainUI*>(PlayerMainUI)->Set_Render_Enable(false);
			PlayerMovable = -1;
		}
		else if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() == true) {
			dynamic_cast<InventoryObject*>(Inventory)->Set_Render_Enable(false);
			dynamic_cast<MainUI*>(PlayerMainUI)->Set_Render_Enable(true);
			PlayerMovable = 1;
		}
	}

	if((!CollisionManager::Check_Collision(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER),
		*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)) && Current_SkillState == PLAYER_SKILL_STATE::PLAYER_NONE)){
		GetGravity = true;
	}

	if (OBJHP <= 0) {
		PlayerJumpSpeed = 0.f;
		PlayerSpeed = 0.f;
		GetGravity = false;
		Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;
	}
	if (InfinityTime + 160 < GetTickCount()) {
		FrameIntervalTimeA = 10;		
	}
	if (InfinityTime + 3000 < GetTickCount()) {
		Player_Infinity_Enable = false;
		InfinityTime = GetTickCount();
	}

	Player_NormalAttack();
	Player_SkillAttack();
		
	return OBJ_ALIVE;
}
void PlayerObject::Late_Update()	{	}
void PlayerObject::Render(HDC DC)	{
	if (Player_Render) 
		Player_Animation(DC);
}
void PlayerObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_ENVIROMENT) {
		if ((Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R
			|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R) 
			&& _TYPE == COLLISION_TYPE::COL_BOTTOM) {
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
			PlayerJumpCount = 0;
			PlayerSpeed = 10.f;
			FileManager::Get_Instance()->Animation_Escape();
			GetGravity = false;
			OnGround = true;
		}
	}
	else {	OnGround = false;	}
	if(pObj->Get_Tag() == OBJECT_TAG::OBJ_ENVIROMENT && dynamic_cast<Enviroment*>(pObj)->Get_EnvTag() == ENV_TYPE::ENV_OBSTACLE) {
		
		dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 1);
		FrameIntervalTimeA = 200;
		InfinityTime = GetTickCount();
		PlayerJumpSpeed = 15.f;
		GetGravity = false;
		PlayerSpeed = 0.f;
		CameraManager::Get_Instance()->CameraShake(400.f, 5.f);
		Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS && OBJHP > 0) {
		
		if (!Player_Infinity_Enable && !pObj->GET_DEAD()) {
			dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 1);
			Player_Infinity_Enable = true;
			if (OBJHP <= 0) {
				PlayerSpeed = 0.f;
				PlayerJumpSpeed = 15.f;
				CameraManager::Get_Instance()->CameraShake(5000.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;

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
			else {
				FrameIntervalTimeA = 200;
				InfinityTime = GetTickCount();
				PlayerJumpSpeed = 15.f;
				PlayerSpeed = 0.f;
				GetGravity = true;
				CameraManager::Get_Instance()->CameraShake(400.f, 5.f);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;

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
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS_HITBOX && OBJHP > 0) {
		if (!Player_Infinity_Enable && !pObj->GET_DEAD()) {
			dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 2);
			Player_Infinity_Enable = true;
			if (OBJHP <= 0) {
				PlayerSpeed = 0.f;
				PlayerJumpSpeed = 15.f;
				CameraManager::Get_Instance()->CameraShake(5000.f ,5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD; 
				
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
			else {
				FrameIntervalTimeA = 200;
				InfinityTime = GetTickCount();
				PlayerJumpSpeed = 15.f;
				PlayerSpeed = 0.f;
				GetGravity = true;
				CameraManager::Get_Instance()->CameraShake(400.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;

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
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_BOSS_HITBOX_CIRCLE && OBJHP > 0) {
		if (!Player_Infinity_Enable && !pObj->GET_DEAD()) {
			dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 2);
			Player_Infinity_Enable = true;
			if (OBJHP <= 0) {
				PlayerSpeed = 0.f;
				PlayerJumpSpeed = 15.f;
				CameraManager::Get_Instance()->CameraShake(5000.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;

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
			else {
				FrameIntervalTimeA = 200;
				InfinityTime = GetTickCount();
				PlayerJumpSpeed = 15.f;
				PlayerSpeed = 0.f;
				GetGravity = true;
				CameraManager::Get_Instance()->CameraShake(400.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;

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
	}

	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_MONSTER && OBJHP > 0 && pObj->Get_HP() > 0) {
		if(!Player_Infinity_Enable && !pObj->GET_DEAD()) {
		dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 1);
			Player_Infinity_Enable = true;

			if (OBJHP <= 0) {
				PlayerSpeed = 0.f;
				CameraManager::Get_Instance()->CameraShake(5000.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;

				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERSTATE);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_DamageSound.WAV", CHANNELID::SOUND_PLAYERSTATE, 1.1f);
			}

			else {
				FrameIntervalTimeA = 200;
				InfinityTime = GetTickCount();
				PlayerJumpSpeed = 15.f;
				PlayerSpeed = 0.f;
				GetGravity = true;
				CameraManager::Get_Instance()->CameraShake(400.f, 5.f);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;

				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERSTATE);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_DamageSound.WAV", CHANNELID::SOUND_PLAYERSTATE, 1.1f);
			}
			
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
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_MONSTER_HITBOX && OBJHP > 0) {
		if(!Player_Infinity_Enable && !pObj->GET_DEAD()) {
		dynamic_cast<MainUI*>(PlayerMainUI)->Remove_HP_Quantity(&OBJHP, 1);
			Player_Infinity_Enable = true;

			if (OBJHP <= 0) {
				PlayerSpeed = 0.f;
				CameraManager::Get_Instance()->CameraShake(5000.f, 5);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;
			}

			else {
				FrameIntervalTimeA = 200;
				InfinityTime = GetTickCount();
				PlayerJumpSpeed = 15.f;
				PlayerSpeed = 0.f;
				GetGravity = true;
				CameraManager::Get_Instance()->CameraShake(400.f, 5.f);
				Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;
			}
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
}

void PlayerObject::Release()	{
}

void PlayerObject::Player_Control() {

	if (KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::HOLD) && PlayerMovable == 1)
	{
		OBJINFO.CenterPosX += PlayerSpeed * PlayerDirection;
		if (PlayerDirection >= -1.f && PlayerDirection <= 1.f) {
			PlayerDirection += 0.35f;
		}
		else if (PlayerDirection < -1.f){ PlayerDirection = -1.f; }
		else if (PlayerDirection > 1.f) { PlayerDirection = 1.f;  }
	}
	else if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::HOLD) && PlayerMovable == 1)
	{
		OBJINFO.CenterPosX += PlayerSpeed * PlayerDirection;
		if (PlayerDirection >= -1.f && PlayerDirection <= 1.f) {
			PlayerDirection -= 0.35f;
		}
		else if (PlayerDirection < -1.f) { PlayerDirection = -1.f; }
		else if (PlayerDirection > 1.f) { PlayerDirection = 1.f; }
	}

	if (KEY_COMMAND(KEY::C, KEY_STATE::HOLD) && PlayerMovable == 1) {
		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L
			|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L) {
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_PARACHUTE_L;
			StartPixelIndex[2] = 0;
			PlayerJumpSpeed = -1.f;
			Gravity = 0;
			PlayerSpeed = 5.f;
		}

		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R
			|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R) {
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_PARACHUTE_R;
			StartPixelIndex[2] = 0;
			PlayerJumpSpeed = -1.f;
			Gravity = 0;
			PlayerSpeed = 5.f;
		}
	}
	if (KEY_COMMAND(KEY::C, KEY_STATE::UP) && PlayerMovable == 1) {
		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L){
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
			PlayerJumpSpeed = -3.f;
			Gravity = 1.f;
			PlayerSpeed = 10.f;
		}
		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R) {
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
			PlayerJumpSpeed = -3.f;
			Gravity = 1.f;
			PlayerSpeed = 10.f;
		}
		else {
			PlayerJumpSpeed = -3.f;
			Gravity = 1.f;
			PlayerSpeed = 10.f;
		}
	}

	if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_L) {
		PlayerSpeed -= 5.f;
		OBJINFO.CenterPosX += PlayerSpeed * PlayerDirection;
		if (PlayerSpeed < 10.f) {
			PlayerSpeed = 10.f;
		}
	}
	if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_R) {
		PlayerSpeed -= 5.f;
		OBJINFO.CenterPosX += PlayerSpeed * PlayerDirection;
		if (PlayerSpeed < 10.f) {
			PlayerSpeed = 10.f;
		}
	}
}

void PlayerObject::Player_Animation(HDC DC) {
	
	Player_Animation_OnHitState(DC);
	Player_Animation_Dash(DC);
	Player_Animation_Attack(DC);
	Player_Animation_Jump(DC);
	Player_Animation_MoveMent(DC);
	Player_Animation_ThreadSKILL(DC);
	Player_Animation_HealSKILL(DC);
	Player_Animation_Throw(DC);
}

void PlayerObject::Player_StateMachine() {
	
	if (KEY_COMMAND(KEY::F3, KEY_STATE::DOWN)) {
		int a = 0;
	}
	
	if (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DEAD && Current_MovementState != PLAYER_MOVE_STATE::PLAYER_NONE) {

		if (!(KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::HOLD)) && !(KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN))
			&& !(KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::HOLD)) && !(KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN))
			&& !(KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::HOLD)) && !(KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::DOWN))) {
			if (Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R )
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;
			if (Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L)
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_L;
		}
		if (KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
			SoundManager::Get_Instance()->PlaySoundW(L"Hornet_RunSound.WAV", CHANNELID::SOUND_PLAYERWP, 0.1f);
		}
		if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
			SoundManager::Get_Instance()->PlaySoundW(L"Hornet_RunSound.WAV", CHANNELID::SOUND_PLAYERWP, 0.1f);
		}
		if (KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::UP)) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
			//SoundManager::Get_Instance()->PlaySoundW(L"Hornet_RunSound.WAV", CHANNELID::SOUND_PLAYERWP, 0.4f);
		}
		if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::UP)) {
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
			//SoundManager::Get_Instance()->PlaySoundW(L"Hornet_RunSound.WAV", CHANNELID::SOUND_PLAYERWP, 0.4f);
		}
		if (KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::HOLD) || KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
			if ((Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L || Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L)
				&& Current_JumpState == PLAYER_JUMP_STATE::PLAYER_NONE) {
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_TURN_LTR;
			}
			else if (Previous_MovementState != PLAYER_MOVE_STATE::PLAYER_TURN_LTR) {
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
				Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
			}
		}

		if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::HOLD) || KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
			if ((Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R || Previous_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R)
				&& Current_JumpState == PLAYER_JUMP_STATE::PLAYER_NONE) {
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_TURN_RTL;
			}
			else if(Previous_MovementState != PLAYER_MOVE_STATE::PLAYER_TURN_RTL){
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
				Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
			}
		}

		else
		{
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R) {
				if (!OnGround) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
				}
				
			}
			else if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L) {
				if (!OnGround) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
				}
				
			}
		}
		
		if (KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::DOWN) && PlayerMovable == 1) {
			if (PlayerJumpCount < 2) {
				PlayerJumpSpeed = 20.f;
			}
			if ((Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R) && PlayerJumpCount == 1) {
				PlayerJumpCount++;
				Current_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R;
				return;
			}
			if ((Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L) && PlayerJumpCount == 1) {
				PlayerJumpCount++;
				Current_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L;
				return;
			}
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R 
				|| Current_MovementState == PLAYER_MOVE_STATE::PLAYER_TURN_LTR) {
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_R;
			}
			else if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L
				|| Current_MovementState == PLAYER_MOVE_STATE::PLAYER_TURN_RTL) {
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_L;
				
			}

			PlayerJumpCount++;

			}

		if (KEY_COMMAND(KEY::Z, KEY_STATE::DOWN) && PlayerMovable == 1) {

			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L
				|| Current_MovementState == PLAYER_MOVE_STATE::PLAYER_NONE) {
				PlayerSpeed = 20.f;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_DASH_L;
				PlayerEffectPos = { OBJINFO.CenterPosX, OBJINFO.CenterPosY };
				//Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
			}
				
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R) {
				PlayerSpeed = 20.f;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_DASH_R;
				PlayerEffectPos = { OBJINFO.CenterPosX, OBJINFO.CenterPosY };
				//Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
			}
				
			
		}

		if (KEY_COMMAND(KEY::SPACE, KEY_STATE::DOWN) && PlayerMovable == 1) {
			
			if ((Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_NONE
				|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R
				|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R) 
				&& (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_L) && (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R)
				&& (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DEAD))	{

				Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_ATTACK_R;
			}

			if ((Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L
				|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L
				|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L)
				&& (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_L) && (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R)
				&& (Current_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DEAD)) {

				Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_ATTACK_L;
			}
		}
		if (KEY_COMMAND(KEY::NUM_0, KEY_STATE::DOWN)) {
			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER_HITBOX, AbstractFactory<SkillObject>::Create(OBJINFO.CenterPosX, OBJINFO.CenterPosY));

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
			SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Wheel.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);

			if (PlayerDirection > 0) {
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_THROW_R;
			}
			else {
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_THROW_L;
			}
		}
		if (KEY_COMMAND(KEY::NUM_9, KEY_STATE::DOWN) && PlayerMovable == 1) {

			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L 
				|| Current_MovementState == PLAYER_MOVE_STATE::PLAYER_NONE) {
				GetGravity = false;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_THREAD_L;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
				PlayerMovable = -1;
			}


			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R) {
				GetGravity = false;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_THREAD_R;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
				PlayerMovable = -1;
			}
		}

		if (KEY_COMMAND(KEY::NUM_8, KEY_STATE::DOWN) && PlayerMovable == 1) {

			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L
				|| Current_MovementState == PLAYER_MOVE_STATE::PLAYER_NONE) {
				GetGravity = false;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_HEAL_L;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
				PlayerMovable = -1;
			}


			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R || Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R) {
				GetGravity = false;
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_HEAL_R;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
				PlayerMovable = -1;
			}
		}

		return;
	}
	if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_NONE && Current_JumpState == PLAYER_JUMP_STATE::PLAYER_NONE) {
		Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;
	}
}

void PlayerObject::Player_JumpDirection_Transition(){
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R && KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_L;
	}
	else if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L && KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_R;
	}
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R && KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
	}
	else if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L && KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
	}
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R && KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L;
	}
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L && KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R;
	}
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R && KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L;
	}
	else if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L && KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R;
	}
}

void PlayerObject::Player_NormalAttack() {
	if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_ATTACK_L) {
		HitBox->Set_Info(OBJINFO.CenterPosX - 75.f , OBJINFO.CenterPosY, 140.f, 50.f);
		dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
		dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(20);
	}
	else if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_ATTACK_R) {
		HitBox->Set_Info(OBJINFO.CenterPosX + 75.f, OBJINFO.CenterPosY, 140.f, 50.f);
		dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
		dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(20);
	}
	else {
		HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	}
}

void PlayerObject::Player_SkillAttack() {
	if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_L || Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_R) {
		HitBox->Set_Info(OBJINFO.CenterPosX, OBJINFO.CenterPosY, 250.f, 250.f);
		dynamic_cast<HitBoxObject*>(HitBox)->Activate_HitBox();
		dynamic_cast<HitBoxObject*>(HitBox)->Set_HitBoxDamage(20);
	}
	else if(Current_AttackState != PLAYER_ATTACK_STATE::PLAYER_ATTACK_R && Current_AttackState != PLAYER_ATTACK_STATE::PLAYER_ATTACK_L){
		HitBox->Set_Info(0.f, 0.f, 0.f, 0.f);
	}
}

void PlayerObject::Player_Animation_Attack(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_ATTACK_R) {
			PlayerSpeed = 5.f;
			if (Previous_AttackState != PLAYER_ATTACK_STATE::PLAYER_ATTACK_R) {
				Previous_AttackState = PLAYER_ATTACK_STATE::PLAYER_ATTACK_R;
				FileManager::Get_Instance()->Animation_Escape();
				StartPixelIndex[3] = 0;
				dwTime[3] = GetTickCount();
				int randomvalue = rand() % 3 + 1;

				if (randomvalue == 1) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}
				else if (randomvalue == 2) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}
				else if (randomvalue == 3) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack03.WAV", CHANNELID::SOUND_PLAYER, 1.1f);

				}
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Slash.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			}
			
			if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"SlashR", 500, 20, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
				Previous_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
				dynamic_cast<HitBoxObject*>(HitBox)->DeActivate_HitBox();
				PlayerSpeed = 10.f;
			}
		}
		if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_ATTACK_L) {
			PlayerSpeed = 5.f;
			if (Previous_AttackState != PLAYER_ATTACK_STATE::PLAYER_ATTACK_L) {
				Previous_AttackState = PLAYER_ATTACK_STATE::PLAYER_ATTACK_L;
				FileManager::Get_Instance()->Animation_Escape();
				int randomvalue = rand() % 3 + 1;

				if (randomvalue == 1) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}
				else if (randomvalue == 2) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}
				else if (randomvalue == 3) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Attack03.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
				}

				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Slash.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			}
			
			if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"SlashL", 500, 20, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
				Previous_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
				dynamic_cast<HitBoxObject*>(HitBox)->DeActivate_HitBox();
				PlayerSpeed = 10.f;
			}
		}
		

	}
}
void PlayerObject::Player_Animation_Dash(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_R) {
			if (Previous_SkillState != PLAYER_SKILL_STATE::PLAYER_DASH_R) {
				Previous_SkillState = PLAYER_SKILL_STATE::PLAYER_DASH_R;
				FileManager::Get_Instance()->Animation_Escape();
				StartPixelIndex[2] = 0;
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Dash.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			}
			if (PlayAnimation_Once(DC, L"Dash_Effect_R", &StartPixelIndex[2], 410, 20, &dwTime[2], { PlayerEffectPos.X - 130.f, PlayerEffectPos.Y + 10.f }, 0.5f, 0.5f)) {
				
				dwTime[2] = GetTickCount();
			}
			
			if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"DashR", 220, 40, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
				Previous_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;

				PlayerSpeed = 10.f;
			}
		}
		if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_L) {
			if (Previous_SkillState != PLAYER_SKILL_STATE::PLAYER_DASH_L) {
				Previous_SkillState = PLAYER_SKILL_STATE::PLAYER_DASH_L;
				FileManager::Get_Instance()->Animation_Escape();
				StartPixelIndex[2] = 0;
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Dash.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			}
			if (PlayAnimation_Once(DC, L"Dash_Effect_L", &StartPixelIndex[2], 410, 20, &dwTime[2], { PlayerEffectPos.X + 130.f, PlayerEffectPos.Y + 10.f }, 0.5f, 0.5f)) {
				
				dwTime[2] = GetTickCount();
			}
			//SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Dash.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"DashL", 220, 40, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
				Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
				Previous_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
				Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_L;

				PlayerSpeed = 10.f;
			}
		}
	}
}
void PlayerObject::Player_Animation_Jump(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_NONE && Current_SkillState != PLAYER_SKILL_STATE::PLAYER_THREAD_R) {
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_L)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_R)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_HEAL_L)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_HEAL_R)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THROW_L)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THROW_R)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_L)	{ return; }
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_DASH_R)	{ return; }
		
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R;
					FileManager::Get_Instance()->Animation_Escape();
					StartPixelIndex[2] = 0;
					StartPixelIndex[3] = 0;
					dwTime[2] = 0;
					dwTime[3] = 0;
					if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_DBJumpSound.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				
				PlayAnimation_Once(DC, L"DBJump_Effect", &StartPixelIndex[3], 500, 20, &dwTime[3], { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 100 }, 0.3f, 0.3f);
				if (PlayAnimation_Once(DC, L"DBJumpR", &StartPixelIndex[2], 250, 20, &dwTime[2], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
				}
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L;
					StartPixelIndex[2] = 0;
					StartPixelIndex[3] = 0;
					dwTime[2] = 0;
					dwTime[3] = 0;

					if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_DBJumpSound.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				
				PlayAnimation_Once(DC, L"DBJump_Effect", &StartPixelIndex[3], 500, 20, &dwTime[3], { OBJINFO.CenterPosX, OBJINFO.CenterPosY + 100 }, 0.3f, 0.3f);
				if (PlayAnimation_Once(DC, L"DBJumpL", &StartPixelIndex[2], 250, 20, &dwTime[2], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
				}
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_JUMP_R) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_R;
					FileManager::Get_Instance()->Animation_Escape();
					int randomvalue = rand() % 3 + 1;

					if (randomvalue == 1) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					else if (randomvalue == 2) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					else if (randomvalue == 3) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump03.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_JumpSound.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				FileManager::Get_Instance()->PlayAnimation_Once(DC, L"JumpR", 220, 15, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_JUMP_L) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_JUMP_L;
					FileManager::Get_Instance()->Animation_Escape();
					int randomvalue = rand() % 3 + 1;

					if (randomvalue == 1) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump01.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					else if (randomvalue == 2) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump02.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					else if (randomvalue == 3) {
						if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
							SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
							SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Jump03.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
						}
					}
					if (dynamic_cast<InventoryObject*>(Inventory)->Get_Render_Enable() != true) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_JumpSound.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				FileManager::Get_Instance()->PlayAnimation_Once(DC, L"JumpL", 220, 15, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_FALL_R) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
					FileManager::Get_Instance()->Animation_Escape();
				}
				FileManager::Get_Instance()->PlayAnimation_Once(DC, L"FallR", 220, 20, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L) {
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_FALL_L) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
					FileManager::Get_Instance()->Animation_Escape();
				}
				FileManager::Get_Instance()->PlayAnimation_Once(DC, L"FallL", 220, 20, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R) {

				PlayAnimation_Loop(DC, L"FlowR", &StartPixelIndex[4], 230, 50, {OBJINFO.CenterPosX, OBJINFO.CenterPosY}, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L) {

				PlayAnimation_Loop(DC, L"FlowL", &StartPixelIndex[4], 230, 50, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_PARACHUTE_R) {
				::Graphics g(DC);
				g.DrawImage(image[effectIndex++], (INT)OBJINFO.CenterPosX - (INT)CameraManager::Get_Instance()->GetOffset().X - 100,
					(INT)OBJINFO.CenterPosY - (INT)CameraManager::Get_Instance()->GetOffset().Y - 80, 200, 200);
				if (Previous_JumpState != PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R) {
					Previous_JumpState = PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R;

					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Nakhasan.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
				}
				if (PlayAnimation_Once(DC, L"ParaR", &StartPixelIndex[2], 230, 50, &dwTime[2], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R;
					StartPixelIndex[2] = 0;
					dwTime[2] = GetTickCount();
					effectIndex = 5;
				}
			}
			if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_PARACHUTE_L) {

				::Graphics g(DC);
				g.DrawImage(image[effectIndex++], (INT)OBJINFO.CenterPosX - (INT)CameraManager::Get_Instance()->GetOffset().X - 100,
					(INT)OBJINFO.CenterPosY - (INT)CameraManager::Get_Instance()->GetOffset().Y - 80, 200, 200); // (INT)OBJINFO.CenterPosX, (INT)OBJINFO.CenterPosY, 700, 300);
				if (StartPixelIndex[2] == 1) {
					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
					SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Nakhasan.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
				}
				if (PlayAnimation_Once(DC, L"ParaL", &StartPixelIndex[2], 230, 50, &dwTime[2], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L;
					StartPixelIndex[2] = 0;
					dwTime[2] = GetTickCount();
					effectIndex = 5;
				}
			}
		}
	}
}
void PlayerObject::Player_Animation_MoveMent(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_NONE && Current_SkillState == PLAYER_SKILL_STATE::PLAYER_NONE
			&& Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_NONE) {
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_R) {
				FileManager::Get_Instance()->PlayAnimation_Loop(DC, L"Idle_R", 200, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			else if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_IDLE_L) {
				FileManager::Get_Instance()->PlayAnimation_Loop(DC, L"Idle_L", 200, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_R) {
				PlayAnimation_Loop(DC, L"Run_R", &StartPixelIndex[8], 220, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			else if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_RUN_L) {
				
				PlayAnimation_Loop(DC, L"Run_L", &StartPixelIndex[8], 220, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
			}
			if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_TURN_LTR) {

				if (Previous_MovementState != PLAYER_MOVE_STATE::PLAYER_TURN_LTR) {
					Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_TURN_LTR;
					FileManager::Get_Instance()->Animation_Escape();
				}

				if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"LTR", 220, 15, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
					Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_R;
				}
			}
			else if (Current_MovementState == PLAYER_MOVE_STATE::PLAYER_TURN_RTL) {

				if (Previous_MovementState != PLAYER_MOVE_STATE::PLAYER_TURN_RTL) {
					Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_TURN_RTL;
					FileManager::Get_Instance()->Animation_Escape();
				}

				if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"RTL", 220, 15, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
					Previous_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
				}
			}
		}
	}
}
void PlayerObject::Player_Animation_OnHitState(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_DEAD) {
		Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
		Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
		Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
		if (Previous_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DEAD) {
			Previous_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DEAD;
			FileManager::Get_Instance()->Animation_Escape();
		}
		if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"Death", 260, 90, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			Previous_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
			Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
			Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
		}
	}
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R) {
		OBJINFO.CenterPosX += 5.f;
		//Current_AttackState = PLAYER_ATTACK_STATE::PLAYER_NONE;
		Current_MovementState = PLAYER_MOVE_STATE::PLAYER_NONE;
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
		//Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
		if (Previous_DefaultState != PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R) {
			Previous_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_DAMAGED_R;
			FileManager::Get_Instance()->Animation_Escape();
			StartPixelIndex[3] = 0;
			dwTime[3] = GetTickCount();
		}
		PlayAnimation_Once(DC, L"Damage_Effect", &StartPixelIndex[3], 1600, 10, &dwTime[3], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.5f, 0.5f);
		if (FileManager::Get_Instance()->PlayAnimation_Once(DC, L"Damaged", 260, 80, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			FrameIntervalTimeA = 10;
			Current_MovementState = PLAYER_MOVE_STATE::PLAYER_RUN_L;
			Previous_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
			Current_DefaultState = PLAYER_DEFAULT_STATE::PLAYER_NONE;
			PlayerSpeed = 10.f;
		}
	}
}
void PlayerObject::Player_Animation_ThreadSKILL(HDC DC) {
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_NONE) {
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_R) {
				

				if (SkillRoutine < 50) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
					PlayAnimation_Loop(DC, L"Silk_Thread_R", &StartPixelIndex[1], 563, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
					SkillRoutine++;
					PlayerJumpSpeed = 0.f;
				 }
			}
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THREAD_L) {
				if (SkillRoutine < 50) {
					Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
					PlayAnimation_Loop(DC, L"Silk_Thread_L", &StartPixelIndex[1], 563, 30, { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f);
					SkillRoutine++;
					PlayerJumpSpeed = 0.f;
				}
			}
			if (SkillRoutine == 5) {
				SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
				SoundManager::Get_Instance()->PlaySoundW(L"Hornet_ThreadStorm.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
			}
		}
	}
	if (SkillRoutine >= 50) {
		SILK -= 4;
		SkillRoutine = 0;
		Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
		GetGravity = true;
		PlayerMovable = 1;
		StartPixelIndex[1] = 0;
		Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_L;
	}
}
void PlayerObject::Player_Animation_HealSKILL(HDC DC)
{
	if (Current_DefaultState == PLAYER_DEFAULT_STATE::PLAYER_NONE) {
		if (Current_AttackState == PLAYER_ATTACK_STATE::PLAYER_NONE) {
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_HEAL_R) {
				Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
				if (StartPixelIndex[1] >= 22 && StartPixelIndex[1] <= 26) {
					::Graphics g(DC);
					g.DrawImage(image[abs(22 - StartPixelIndex[1])], (INT)OBJINFO.CenterPosX - (INT)CameraManager::Get_Instance()->GetOffset().X - 280, 
						(INT)OBJINFO.CenterPosY - (INT)CameraManager::Get_Instance()->GetOffset().Y - 110, 700 / 10 * 8, 300 / 10 * 8); // (INT)OBJINFO.CenterPosX, (INT)OBJINFO.CenterPosY, 700, 300);
				}
				if (StartPixelIndex[1] == 2){
					int randomvalue = rand() % 2 + 1;

					if (randomvalue == 1) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Vren01.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
					else if (randomvalue == 2) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Vren02.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				
				
				if (PlayAnimation_Once(DC, L"Heal_R", &StartPixelIndex[1], 400, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					PlayerJumpSpeed = 0.f;

					if (OBJHP <= 8)		OBJHP += 2;
					else if (OBJHP > 8) OBJHP = 10;

					Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
					GetGravity = true;
					PlayerMovable = 1;
					StartPixelIndex[1] = 0;
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;
				}
			}
			if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_HEAL_L) {
				Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
				if (StartPixelIndex[1] >= 22 && StartPixelIndex[1] <= 26) {
					::Graphics g(DC);
					g.DrawImage(image[abs(22 - StartPixelIndex[1])], (INT)OBJINFO.CenterPosX - (INT)CameraManager::Get_Instance()->GetOffset().X - 290,
						(INT)OBJINFO.CenterPosY - (INT)CameraManager::Get_Instance()->GetOffset().Y - 110, 700 / 10 * 8, 300 / 10 * 8); // (INT)OBJINFO.CenterPosX, (INT)OBJINFO.CenterPosY, 700, 300);
				}
				if (StartPixelIndex[1] == 2) {
					int randomvalue = rand() % 2 + 1;

					if (randomvalue == 1) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Vren01.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
					else if (randomvalue == 2) {
						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYERWP);
						SoundManager::Get_Instance()->PlaySoundW(L"Hornet_Vren02.WAV", CHANNELID::SOUND_PLAYERWP, 1.1f);
					}
				}
				if (PlayAnimation_Once(DC, L"Heal_L", &StartPixelIndex[1], 400, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
					PlayerJumpSpeed = 0.f;
					Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;

					Set_HP(OBJHP + 2);

					GetGravity = true;
					PlayerMovable = 1;
					StartPixelIndex[1] = 0;
					Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_L;				
				}
			}
		}
	}
}
void PlayerObject::Player_Animation_Throw(HDC DC) {
	if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THROW_R) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
		if (PlayAnimation_Once(DC, L"Throw_R", &StartPixelIndex[1], 300, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			PlayerJumpSpeed = 0.f;
			Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
			PlayerMovable = 1;
			StartPixelIndex[1] = 0;
			Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_R;
		}
	}
	if (Current_SkillState == PLAYER_SKILL_STATE::PLAYER_THROW_L) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_NONE;
		if (PlayAnimation_Once(DC, L"Throw_L", &StartPixelIndex[1], 300, 30, &dwTime[0], { OBJINFO.CenterPosX, OBJINFO.CenterPosY }, 0.6f, 0.6f)) {
			PlayerJumpSpeed = 0.f;
			Current_SkillState = PLAYER_SKILL_STATE::PLAYER_NONE;
			PlayerMovable = 1;
			StartPixelIndex[1] = 0;
			Current_MovementState = PLAYER_MOVE_STATE::PLAYER_IDLE_L;
		}
	}
}

void PlayerObject::Player_GravitySetting() {

	FLOAT	Past_PosY = OBJINFO.CenterPosY;
	if (PlayerJumpSpeed >= -30.f) {
		PlayerJumpSpeed -= Gravity;
		if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_NONE) {
			Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
		}
	}
	if ((Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_FALL_R
		|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_SLOW_FALL_R
		|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R
		|| Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_L || Current_JumpState == PLAYER_JUMP_STATE::PLAYER_DOUBLE_JUMP_R) &&
		(Current_SkillState == PLAYER_SKILL_STATE::PLAYER_NONE )) {
		GetGravity = true;
	}
	if (GetGravity) {
		OBJINFO.CenterPosY -= PlayerJumpSpeed;
	}
	
	if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_L && OBJINFO.CenterPosY > Past_PosY) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_L;
		FileManager::Get_Instance()->Animation_Escape();
	}
	else if (Current_JumpState == PLAYER_JUMP_STATE::PLAYER_JUMP_R && OBJINFO.CenterPosY > Past_PosY) {
		Current_JumpState = PLAYER_JUMP_STATE::PLAYER_FALL_R;
		FileManager::Get_Instance()->Animation_Escape();
	}
}
void PlayerObject::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + dwTime[9] < GetTickCount()) {
		*_SPF += 1;
		dwTime[9] = GetTickCount();

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
BOOL PlayerObject::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
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