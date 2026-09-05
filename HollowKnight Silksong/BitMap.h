#pragma once
class BitMap {
public:
	BitMap() {};
	~BitMap() {};

public:
	void Initialize()			{};
	void Update()				{};
	void LateUpdate()			{};
	void Render(HDC DC)			{};
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {};
	void Release()				{};

public:
  	HDC		Get_SubDC()		{ return SubDC; }

	UINT	Get_BMPWidth()	{ return BitMapINFO.bmWidth; }
	UINT	Get_BMPHeight() { return BitMapINFO.bmHeight; }

	void	Load_BMPFile(const TCHAR* _FilePath);

private:
	HDC		SubDC;

	HBITMAP	NewBitMap;
	HBITMAP OldBitMap;
	BITMAP	BitMapINFO;
};

