#include "PCH.h"
#include "BitMap.h"

void BitMap::Load_BMPFile(const TCHAR* _FilePath) {
	HDC DC = GetDC(hWnd);
	SubDC = CreateCompatibleDC(DC);

	ReleaseDC(hWnd, DC);

	NewBitMap = (HBITMAP)LoadImage(NULL, _FilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(SubDC, NewBitMap);

	GetObject(NewBitMap, sizeof(BITMAP), &BitMapINFO);

	ReleaseDC(hWnd, SubDC);
}
