#include "PCH.h"
#include "GameObject.h"

GameObject::GameObject() {
	ZeroMemory(&OBJRECT, sizeof(OBJRECT));
	ZeroMemory(&OBJINFO, sizeof(OBJINFO));
	DEAD = false;
}
GameObject::~GameObject() { }
void GameObject::Update_RECT()
{
	OBJRECT.left	= LONG(OBJINFO.CenterPosX - (OBJINFO.Width / 2.f));
	OBJRECT.top		= LONG(OBJINFO.CenterPosY - (OBJINFO.Height / 2.f));
	OBJRECT.right	= LONG(OBJINFO.CenterPosX + (OBJINFO.Width / 2.f));
	OBJRECT.bottom	= LONG(OBJINFO.CenterPosY + (OBJINFO.Height / 2.f));
}