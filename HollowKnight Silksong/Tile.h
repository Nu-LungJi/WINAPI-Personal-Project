#pragma once
#include "GameObject.h"
class Tile : public GameObject
{
public:
	Tile();
	virtual ~Tile();

public:
	void Initialize()		override;
	int  Update()			override;
	void Late_Update()		override;
	void Render(HDC hDC)	override;
	void Release()			override;

private:
	int			m_iDrawID;
	int			m_iOption;
	BOOL		m_EnableTiling;
	FLOAT		m_TileScale;
	INT			m_DrawOption;

public:
	int		Get_DrawID() { return m_iDrawID; }
	int		Get_Option() { return m_iOption; }
	BOOL	Get_EnableTiling() { return m_EnableTiling; }
	INT		Get_DrawOption() { return m_DrawOption; }

	void	Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void	Set_Option(int iOption) { m_iOption = iOption; }
	void	Set_EnableTiling(BOOL _TLN) { m_EnableTiling = _TLN; }
	void	Set_DrawOption(int i) { m_DrawOption = i; }


	// GameObject을(를) 통해 상속됨
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;

};

