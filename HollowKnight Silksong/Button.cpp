#include "PCH.h"
#include "Button.h"
ButtonObject::ButtonObject()  {				}
ButtonObject::ButtonObject(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, const TCHAR* _TW, BTN_TAG _BT, UINT _FontSize)
{
	ZeroMemory(TextWord, sizeof(TextWord));
	lstrcpyW(TextWord, _TW);
	OBJINFO = { _X, _Y, _WTH, _HGT };
	Button_Tag = _BT;
	FontSize = _FontSize;
}
ButtonObject::~ButtonObject() { Release();	}

void ButtonObject::Initialize()
{
	Test = true;
	SerifFont = CreateFont(FontSize, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("SourceHanSerif-Light"));
}

int ButtonObject::Update() {
	Update_RECT();
	if (ButtonEvent() == BTN_EVENT::BTN_HOVER) {

	}
	return OBJ_ALIVE;
}

void ButtonObject::Late_Update()	{	}

void ButtonObject::Render(HDC DC) {

	SetBkMode(DC, TRANSPARENT);

	if (Test) {
		HFONT OldFont = (HFONT)SelectObject(DC, SerifFont);
		Test = false;
	}
	

	//SetTextColor(DC, (255, 255, 255));
	
	DrawText(DC, TextWord, lstrlen(TextWord), &OBJRECT, DT_CENTER | DT_VCENTER);
}
void ButtonObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)	{	}
void ButtonObject::Release()	{	}

BTN_EVENT ButtonObject::ButtonEvent() {

	POINT CursorPos{};
	GetCursorPos(&CursorPos);
	ScreenToClient(hWnd, &CursorPos);

	if (PtInRect(&OBJRECT, CursorPos)) {
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)	return BTN_EVENT::BTN_ONCLICK;
		else										return BTN_EVENT::BTN_HOVER;
	}						
	return BTN_EVENT::BTN_NOEVENT;

}
