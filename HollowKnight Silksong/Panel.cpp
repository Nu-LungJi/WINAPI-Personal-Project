#include "PCH.h"
#include "Panel.h"

Panel::Panel() { }

Panel::Panel(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, const TCHAR* _TW, UINT _FontSize) {
	wmemcpy(TextWord, _TW, sizeof(_TW));
	OBJINFO = { _X, _Y, _WTH, _HGT };
	SerifFont = CreateFont(FontSize, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("SourceHanSerif-Light"));
}

Panel::~Panel() { Release(); }

void Panel::Initialize()
{
	SelectFont = true;
}

void Panel::Update()
{
}

void Panel::Late_Update()
{
}

void Panel::Render(HDC DC)
{
	SetBkMode(DC, TRANSPARENT);

	if (SelectFont) {
		HFONT OldFont = (HFONT)SelectObject(DC, SerifFont);
		SelectFont = false;
	}

	SetTextColor(DC, RGB(255, 255, 255));

	DrawText(DC, TextWord, lstrlen(TextWord), &OBJRECT, DT_CENTER | DT_VCENTER);
}

void Panel::Release()
{
}

void Panel::Change_FontSize(UINT _Size) {
	FontSize = _Size;

	SerifFont = CreateFont(FontSize, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("SourceHanSerif-Light"));

	SelectFont = true;
}
