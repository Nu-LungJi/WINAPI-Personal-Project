#include "PCH.h"
#include "KeyManager.h"
KeyManager* KeyManager::Instance = nullptr;
KeyManager::KeyManager() {
	ZeroMemory(KEY_STATE, sizeof(KEY_STATE));
}
KeyManager::~KeyManager() { Release(); }
int KeyMapping[(int)KEY::LAST] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, // 0 - 9
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
			'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
	VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_MENU,
	VK_ESCAPE, VK_SPACE, VK_RETURN,
	VK_LBUTTON, VK_RBUTTON, 
};
void KeyManager::Initialize() {
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		KeySet.push_back(KeyINFO{ KEY_STATE::NONE, false });
	}
}
void KeyManager::Update() {
	HWND Handle = GetFocus();
	if (Handle != NULL) {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			if (GetAsyncKeyState(KeyMapping[i]) && 0x8000) {
				if (KeySet[i].Prev_KeyState == true) { // 누르고 있는 상태
					KeySet[i].Current_KeyState = KEY_STATE::HOLD;
				}
				else {
					KeySet[i].Current_KeyState = KEY_STATE::DOWN;
				}
				KeySet[i].Prev_KeyState = true;
			}
			else {
				if (KeySet[i].Prev_KeyState == true) { // 키를 뗀 상태
					KeySet[i].Current_KeyState = KEY_STATE::UP;
				}
				else {
					KeySet[i].Current_KeyState = KEY_STATE::NONE;
				}
				KeySet[i].Prev_KeyState = false;
			}
		}
	}
	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			KeySet[i].Prev_KeyState = false;

			if (KeySet[i].Current_KeyState == KEY_STATE::HOLD ||
				KeySet[i].Current_KeyState == KEY_STATE::DOWN) {
				KeySet[i].Current_KeyState = KEY_STATE::UP;
			}
			else if (KeySet[i].Current_KeyState == KEY_STATE::UP) {
				KeySet[i].Current_KeyState = KEY_STATE::NONE;
			}
		}
	}
}

void KeyManager::Late_Update() {
	for (int i = 0; i < VK_OEM_CLEAR; ++i) {
		if (KEY_STATE[i] && !(GetAsyncKeyState(i) & 0x8000))
			KEY_STATE[i] = !KEY_STATE[i];

		if (!KEY_STATE[i] && (GetAsyncKeyState(i) & 0x8000))
			KEY_STATE[i] = !KEY_STATE[i];
	}
}

BOOL KeyManager::KEY_DOWN(INT _KEY) {
	if (!KEY_STATE[_KEY] && GetAsyncKeyState(_KEY) && 0x8000){
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return true;
	}
	return false;
}
BOOL KeyManager::KEY_UP(INT _KEY)	{
	if (KEY_STATE[_KEY] && !GetAsyncKeyState(_KEY) && 0x8000) {
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return true;
	}
	return false;
}
