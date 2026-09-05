#include "PCH.h"
#include "StoreUI.h"
StoreUI::StoreUI() : dwTime(GetTickCount()), Swinging(false), Selecting(-1), Purchasing(-1), Deciding(-1), Completed(false),
CameraOffset{ 0.f, 0.f }, Open_Store(-1), Close_Store(1), Slot_CurrentIndex(2), Slot_PastIndex(2), SwingValue(0.f), StartPixelFrame{0} , Closing(false){
}
StoreUI::~StoreUI() { Release(); }

void StoreUI::Initialize() {
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09L.bmp", L"PointerL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09R.bmp", L"PointerR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Store_Slot_Top.bmp",				L"Slot_Top");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Store_Slot_Bottom.bmp",				L"Slot_Bottom");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Selector.bmp",						L"Selector");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Item01.bmp",						L"Item01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Item02.bmp",						L"Item02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Item03.bmp",						L"Item03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/Item04.bmp",						L"Item04");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/ItemPrice01.bmp",					L"ItemPrice01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/ItemPrice02.bmp",					L"ItemPrice02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/ItemPrice03.bmp",					L"ItemPrice03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Store/ItemPrice04.bmp",					L"ItemPrice04");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Fleur/Store_Top_Anim.bmp",				L"Fleur_Top");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Fleur/Store_Bottom_Anim.bmp",				L"Fleur_Bottom");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Temp.bmp", L"Temp");

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();

	ButtonYes = new ButtonObject(DEFAULT_WINDOW_CX / 2 + 250, DEFAULT_WINDOW_CY / 2 + 100, 55.f, 30.f, L"예", BTN_TAG::BTN_YES);
	ButtonNo = new ButtonObject(DEFAULT_WINDOW_CX / 2 + 250, DEFAULT_WINDOW_CY / 2 + 150, 135.f, 30.f, L"아니오", BTN_TAG::BTN_NO);

	ButtonYes->Initialize();
	ButtonNo->Initialize();

	ItemList.push_back({ L"Temp", L"Temp", L"Temp" , 0 });
	ItemList.push_back({ L"Temp", L"Temp", L"Temp" , 0 });
	ItemList.push_back({ L"Item01", L"ItemPrice01", L"마테리움 " , 180 });
	ItemList.push_back({ L"Item02", L"ItemPrice02", L"묵주 묶음" , 240 });
	ItemList.push_back({ L"Item03", L"ItemPrice03", L"진주 묵주" , 340 });
	ItemList.push_back({ L"Item04", L"ItemPrice04", L"부싯 보석" , 90 });
	ItemList.push_back({ L"Temp", L"Temp", L"Temp" , 0 });
	ItemList.push_back({ L"Temp", L"Temp", L"Temp" , 0 });

	SerifFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("SourceHanSerif-Light"));
}
int StoreUI::Update()	{
	ButtonYes->Update();
	ButtonNo->Update();
	return 0;
}
void StoreUI::Late_Update()	{	}
void StoreUI::Render(HDC DC) {
	STORE_DefaultSetting(DC);
	STORE_DisplayTextAnimation(DC);
}
void StoreUI::Release() {
	SAFE_DELETE(ButtonYes);
	SAFE_DELETE(ButtonNo);
}
void StoreUI::STORE_DefaultSetting(HDC DC) {
	if (dynamic_cast<NPC*>(StoreManager)->Get_NPCTag() == NPC_TAG::NPC_BIGPULP
		&& fabsf(StoreManager->Get_Pos().X - Player->Get_Pos().X) < 200.f) {

		HPEN myPen = CreatePen(PS_NULL, 0, RGB(0, 255, 0));
		HGDIOBJ oldPen = SelectObject(DC, myPen);

		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);

		SetBkMode(DC, TRANSPARENT);
		SetTextColor(DC, RGB(255, 255, 255));

		CameraManager::Get_Instance()->Set_TempOffset(CameraOffset);
		if (Closing) {
			PlayAnimation_Reverse(DC, L"Fleur_Top", &StartPixelFrame[0], 820, 20,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 275.f }, 0.68f, 0.68f);
			PlayAnimation_Reverse(DC, L"Fleur_Bottom", &StartPixelFrame[1], 820, 20,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y + 225.f }, 0.67f, 0.67f);

			if (StartPixelFrame[0] == -1 && StartPixelFrame[1] == -1) {
				
				Closing = false;
			}
		}
		BOOL SoundTrigger = false;
		if (KEY_COMMAND(KEY::H, KEY_STATE::DOWN)) {
			if (Open_Store == 1) { 
				Closing = true; }
			Open_Store *= -1;
			Selecting *= -1;
			Close_Store *= -1;
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"NPC_BigPulp_Sound02.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
		if (Open_Store == 1 && Selecting == 1) {

			if (CameraOffset.X < 200.f)
				CameraOffset.X += 20.f;
			if (CameraOffset.X > 160.f) {

				HFONT OldFont = (HFONT)SelectObject(DC, SerifFont);

				dynamic_cast<PlayerObject*>(Player)->Set_PlayerMoveState(PLAYER_MOVE_STATE::PLAYER_IDLE_R);
				dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(0.f);
				dynamic_cast<PlayerObject*>(Player)->Set_PlayerJumpState(-1);

				Rectangle(DC, DEFAULT_WINDOW_CX / 2, DEFAULT_WINDOW_CY / 2 - 280, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 230);

				PlayAnimation_Once_Stable(DC, L"Fleur_Top", &StartPixelFrame[0], 820, 30,
					{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 275.f }, 0.68f, 0.68f);
				PlayAnimation_Once_Stable(DC, L"Fleur_Bottom", &StartPixelFrame[1], 820, 30,
					{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y + 225.f }, 0.67f, 0.67f);

				if (Slot_CurrentIndex >= 2 && Slot_CurrentIndex <= 5 && Selecting) {
					FileManager::Get_Instance()->Append_Image(DC, L"Slot_Top", { CameraManager::Get_Instance()->GetLookAt().X + 120.f, CameraManager::Get_Instance()->GetLookAt().Y - 85.f }, 0.5f, 0.5f);
					FileManager::Get_Instance()->Append_Image(DC, L"Slot_Bottom", { CameraManager::Get_Instance()->GetLookAt().X + 120.f,CameraManager::Get_Instance()->GetLookAt().Y + 28.f }, 0.5f, 0.5f);
					FileManager::Get_Instance()->Append_Image(DC, L"Selector", { CameraManager::Get_Instance()->GetLookAt().X + 120.f, CameraManager::Get_Instance()->GetLookAt().Y - 30.f }, 1.f, 0.8f);
				}

				if (KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::DOWN) && Selecting) {
					if (Slot_CurrentIndex >= 2) {
						Slot_PastIndex = Slot_CurrentIndex;
						Slot_CurrentIndex--;

						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
						SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
					}
					if (Slot_CurrentIndex == 1) { Slot_CurrentIndex = 2; }
				}
				if (KEY_COMMAND(KEY::ARROW_DOWN, KEY_STATE::DOWN) && Selecting) {
					if (Slot_CurrentIndex <= 5) {
						Slot_PastIndex = Slot_CurrentIndex;
						Slot_CurrentIndex++;

						SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
						SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
					}
					if (Slot_CurrentIndex == 6) { Slot_CurrentIndex = 5; }
				}
				if (KEY_COMMAND(KEY::RETURN, KEY_STATE::DOWN) && Selecting) {
					Selecting *= -1;
					Purchasing *= -1;

					SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
					SoundManager::Get_Instance()->PlaySoundW(L"SelectSound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
				}
				STORE_SlotAnimation(DC);
				return;
			}
		}
		if (Close_Store == 1) {
			if (CameraOffset.X >= 0.f)
				CameraOffset.X -= 20.f;
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerSpeed(10.f);
			dynamic_cast<PlayerObject*>(Player)->Set_PlayerJumpState(1);
			SelectObject(DC, oldBrush);
			DeleteObject(myBrush);

			SelectObject(DC, oldPen);
			DeleteObject(myPen);
		}

		if (Deciding == 1) {
			STORE_CompletePurchase(DC);
			PlayAnimation_Once_Stable(DC, L"Fleur_Top", &StartPixelFrame[0], 820, 50,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 275.f }, 0.68f, 0.68f);
			PlayAnimation_Once_Stable(DC, L"Fleur_Bottom", &StartPixelFrame[1], 820, 50,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y + 225.f }, 0.67f, 0.67f);
		}
		if (Purchasing == 1) {
			STORE_BeforePurchase(DC);
			PlayAnimation_Once_Stable(DC, L"Fleur_Top", &StartPixelFrame[0], 820, 50,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 275.f }, 0.68f, 0.68f);
			PlayAnimation_Once_Stable(DC, L"Fleur_Bottom", &StartPixelFrame[1], 820, 50,
				{ CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y + 225.f }, 0.67f, 0.67f);
		}
	}
}
void StoreUI::STORE_SlotAnimation(HDC DC) {
	RECT rt = { DEFAULT_WINDOW_CX / 2 + 200, DEFAULT_WINDOW_CY / 2 - 250, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 - 200 };
	if (Slot_CurrentIndex != Slot_PastIndex) {
		if (Slot_CurrentIndex > Slot_PastIndex) {
			Swinging = true;
			if (SwingValue < 100.f) {
				//FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 228.f - SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f - SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f - SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f - SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 172.f - SwingValue }, 0.5f, 0.5f);

				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f - SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f - SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f - SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 2].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y + 172.f - SwingValue }, 0.4f, 0.4f);

				SwingValue += 20.f;
			}
			else {
				Slot_PastIndex = Slot_CurrentIndex;
				SwingValue = 0;
				Swinging = false;
			}
		}
		else if (Slot_CurrentIndex < Slot_PastIndex) {
			Swinging = true;
			if (SwingValue < 100.f) {
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 228.f + SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f + SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f + SwingValue }, 0.5f, 0.5f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f + SwingValue }, 0.5f, 0.5f);
				//FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 172.f + SwingValue }, 0.5f, 0.5f);

				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 2].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 228.f + SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex - 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f + SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f + SwingValue }, 0.4f, 0.4f);
				FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex + 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f + SwingValue }, 0.4f, 0.4f);

				SwingValue += 20.f;
			}
			else {
				Slot_PastIndex = Slot_CurrentIndex;
				SwingValue = 0;
				Swinging = false;
			}
		}
	}
	if (Slot_CurrentIndex >= 2 && Slot_CurrentIndex <= 5 && !Swinging && Selecting == 1) {
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex - 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 228.f }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex - 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex + 1].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex + 2].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 60.f, CameraManager::Get_Instance()->GetLookAt().Y + 172.f }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex - 2].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 228.f }, 0.4f, 0.4f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex - 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f }, 0.4f, 0.4f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y - 28.f }, 0.4f, 0.4f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex + 1].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y + 72.f }, 0.4f, 0.4f);
		FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_CurrentIndex + 2].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 150.f, CameraManager::Get_Instance()->GetLookAt().Y + 172.f }, 0.4f, 0.4f);

	}
	DrawText(DC, ItemList[Slot_CurrentIndex].ItemName, 5, &rt, DT_CENTER | DT_CENTER);
}
void StoreUI::STORE_BeforePurchase(HDC DC) {
	RECT rt = { DEFAULT_WINDOW_CX / 2 + 100, DEFAULT_WINDOW_CY / 2 - 250, DEFAULT_WINDOW_CX / 2 + 400, DEFAULT_WINDOW_CY / 2 - 200 };
	Rectangle(DC, DEFAULT_WINDOW_CX / 2, DEFAULT_WINDOW_CY / 2 - 280, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 230);

	DrawText(DC, ItemList[Slot_PastIndex].ItemName, 5, &rt, DT_CENTER | DT_CENTER);

	FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f }, 0.8f, 0.8f);
	FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemPriceImageName, { CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 30.f }, 0.5f, 0.5f);

	RECT PurchaseRt = { DEFAULT_WINDOW_CX / 2 , DEFAULT_WINDOW_CY / 2, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 50 };

	DrawText(DC, L"아이템을 구입합니까?", 11, &PurchaseRt, DT_CENTER | DT_CENTER);

	ButtonYes->Render(DC);
	ButtonNo->Render(DC);

	if ((dynamic_cast<ButtonObject*>(ButtonYes)->Get_BTNTAG() == BTN_TAG::BTN_YES
		&& dynamic_cast<ButtonObject*>(ButtonYes)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK)
		|| ((KEY_COMMAND(KEY::RETURN, KEY_STATE::DOWN) && ButtonIndex == 1))) {
		if (dynamic_cast<PlayerObject*>(Player)->Get_MukJu() >= ItemList[Slot_PastIndex].ItemPrice) {
			Deciding = 1;
			Purchasing = -1;
			ButtonIndex = -1;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"SelectSound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);

		}
		else if (dynamic_cast<PlayerObject*>(Player)->Get_MukJu() < ItemList[Slot_PastIndex].ItemPrice) {
			PayMukJu = true;
			dwTime = GetTickCount();
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"SwapWeaponFail.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}
	if (PayMukJu && dwTime + 1500 >= GetTickCount()) {
		RECT PayRT = { DEFAULT_WINDOW_CX / 2 , DEFAULT_WINDOW_CY / 2 + 180, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 210 };
		DrawText(DC, L"묵주가 부족합니다", 9, &PayRT, DT_CENTER | DT_CENTER);

	}
	else if (dwTime + 1500 <= GetTickCount()) {
		PayMukJu = false;
	}
	if ((dynamic_cast<ButtonObject*>(ButtonNo)->Get_BTNTAG() == BTN_TAG::BTN_NO
		&& dynamic_cast<ButtonObject*>(ButtonNo)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK)
		|| ((KEY_COMMAND(KEY::RETURN, KEY_STATE::DOWN) && ButtonIndex == 0))) {
		Purchasing = -1;
		Selecting = 1;
		ButtonIndex = -1;

		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SelectSound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);

		dwTime = GetTickCount();

		return;
	}

	if (dynamic_cast<ButtonObject*>(ButtonYes)->Get_BTNTAG() == BTN_TAG::BTN_YES
		&& dynamic_cast<ButtonObject*>(ButtonYes)->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { CameraManager::Get_Instance()->GetLookAt().X + 200.f, CameraManager::Get_Instance()->GetLookAt().Y + 100.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { CameraManager::Get_Instance()->GetLookAt().X + 300.f, CameraManager::Get_Instance()->GetLookAt().Y + 100.f }, 0.375f, 0.375f);
		ButtonIndex = 1;
	}
	if (dynamic_cast<ButtonObject*>(ButtonNo)->Get_BTNTAG() == BTN_TAG::BTN_NO
		&& dynamic_cast<ButtonObject*>(ButtonNo)->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { CameraManager::Get_Instance()->GetLookAt().X + 180.f, CameraManager::Get_Instance()->GetLookAt().Y + 150.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { CameraManager::Get_Instance()->GetLookAt().X + 320.f, CameraManager::Get_Instance()->GetLookAt().Y + 150.f }, 0.375f, 0.375f);
		ButtonIndex = 0;
	}

	if (dynamic_cast<ButtonObject*>(ButtonYes)->Get_BTNTAG() == BTN_TAG::BTN_YES
		&& ButtonIndex == 1) {
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { CameraManager::Get_Instance()->GetLookAt().X + 200.f, CameraManager::Get_Instance()->GetLookAt().Y + 100.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { CameraManager::Get_Instance()->GetLookAt().X + 300.f, CameraManager::Get_Instance()->GetLookAt().Y + 100.f }, 0.375f, 0.375f);

	}
	if (dynamic_cast<ButtonObject*>(ButtonNo)->Get_BTNTAG() == BTN_TAG::BTN_NO
		&& ButtonIndex == 0) {
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { CameraManager::Get_Instance()->GetLookAt().X + 180.f, CameraManager::Get_Instance()->GetLookAt().Y + 150.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { CameraManager::Get_Instance()->GetLookAt().X + 320.f, CameraManager::Get_Instance()->GetLookAt().Y + 150.f }, 0.375f, 0.375f);
	}

	if (KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::DOWN) && Purchasing) {
		if (ButtonIndex == 1) { ButtonIndex = 0; }
		if (ButtonIndex == 0) { ButtonIndex = 1; }
		if (ButtonIndex == -1) { ButtonIndex = 0; }
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
	}
	if (KEY_COMMAND(KEY::ARROW_DOWN, KEY_STATE::DOWN) && Purchasing) {
		if (ButtonIndex == 0) { ButtonIndex = 1; }
		if (ButtonIndex == 1) { ButtonIndex = 0; }
		if (ButtonIndex == -1) { ButtonIndex = 0; }
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
	}
}
void StoreUI::STORE_CompletePurchase(HDC DC){
	RECT rt = { DEFAULT_WINDOW_CX / 2 + 100, DEFAULT_WINDOW_CY / 2 - 250, DEFAULT_WINDOW_CX / 2 + 400, DEFAULT_WINDOW_CY / 2 - 200 };
	Rectangle(DC, DEFAULT_WINDOW_CX / 2, DEFAULT_WINDOW_CY / 2 - 280, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 230);

	DrawText(DC, ItemList[Slot_PastIndex].ItemName, 5, &rt, DT_CENTER | DT_CENTER);

	FileManager::Get_Instance()->Append_Image(DC, ItemList[Slot_PastIndex].ItemImageName, { CameraManager::Get_Instance()->GetLookAt().X + 250.f, CameraManager::Get_Instance()->GetLookAt().Y - 128.f }, 0.8f, 0.8f);

	RECT PurchaseRt = { DEFAULT_WINDOW_CX / 2 , DEFAULT_WINDOW_CY / 2, DEFAULT_WINDOW_CX / 2 + 500, DEFAULT_WINDOW_CY / 2 + 50 };

	DrawText(DC, L"아이템 구입함", 8, &PurchaseRt, DT_CENTER | DT_CENTER);

	if (KEY_COMMAND(KEY::RETURN, KEY_STATE::DOWN)) {
		Selecting = 1;
		Deciding = -1;

		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SelectSound.WAV", CHANNELID::SOUND_EFFECT, 1.1f);

		dynamic_cast<InventoryObject*>(dynamic_cast<PlayerObject*>(Player)->Get_Inventory())->Register_DefaultItem(ItemList[Slot_PastIndex].ItemImageName, 1);

		Completed = true;
		}
}
void StoreUI::STORE_DisplayTextAnimation(HDC DC) {
	if (Completed) {

		dynamic_cast<MainUI*>(dynamic_cast<PlayerObject*>(Player)->Get_PlayerMainUI())->Set_MukJuQuantity_ToAppend(ItemList[Slot_PastIndex].ItemPrice);
		Completed = false;
	}
}
void StoreUI::PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
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
void StoreUI::PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
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