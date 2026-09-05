#pragma once
#include "GameObject.h"

#define NPC_BIGPULP_PIXELFRAME				300
#define NPC_BIGBUG_PIXELFRAME				220
#define NPC_GHOUL_PIXELFRAME				140
#define NPC_FLEA_PIXELFRAME					130
#define NPC_PULP_PIXELFRAME					140
#define NPC_PULP_FAMILY_PIXELFRAME			230
#define NPC_SHERMA_PIXELFRAME				175
#define NPC_SPECIAL_SHERMA_PIXELFRAME		160

class NPC : public GameObject {
public:
	NPC();
	NPC(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, NPC_TAG _Tag);
	virtual ~NPC();

public:
	void Initialize()		override;
	int  Update()			override;
	void Late_Update()		override;
	void Render(HDC DC)		override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void Release()			override;
	
	NPC_TAG	Get_NPCTag() { return Tag; }
	void TalkNPC(HDC DC);

	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

private:
	GameObject*				Player;

	NPC_TAG					Tag;
	DWORD					dwTime;
	INT						TalkingPass;
	INT						StartPixelFrame[20];

	BOOL					SignFlag;
	BOOL					TalkWithNPC;

};

