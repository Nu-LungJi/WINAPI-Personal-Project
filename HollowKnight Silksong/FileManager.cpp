#include "PCH.h"
#include "FileManager.h"
FileManager* FileManager::Instance = nullptr;
FileManager::FileManager() : dwTime(GetTickCount()), StartPixelFrame(0), ResetComplete(false) {}
FileManager::~FileManager() { Release(); }

BitMap* FileManager::Find_BMPFile(const TCHAR* _KeyValue) {
	auto iter = find_if(FileMap.begin(), FileMap.end(), KeyFinder(_KeyValue));
	if (iter == FileMap.end())	return nullptr;
	return iter->second;
}
void FileManager::Update() {
	OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	OffsetY = CameraManager::Get_Instance()->GetOffset().Y;
}

void FileManager::Insert_BMPFile(const TCHAR* _FilePath, const TCHAR* _KeyValue) {
	auto iter = find_if(FileMap.begin(), FileMap.end(), KeyFinder(_KeyValue));
	if (iter == FileMap.end()) {
		BitMap* TempBitMap = new BitMap;
		TempBitMap->Load_BMPFile(_FilePath);
		FileMap.insert({ _KeyValue, TempBitMap });
	}
}
void FileManager::Append_Image(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _StartPosLeft, UINT _StartPosTop,
																FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();
	
	GdiTransparentBlt(_SubWindowDC, _StartPosLeft - OffsetX, _StartPosTop - OffsetY, Width * _MultipleWidth, Height * _MultipleHeight, MemDC, 0, 0,
		Width, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);
}
void FileManager::Append_Image(HDC _SubWindowDC, const TCHAR* _KeyValue, Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();
	
	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	FLOAT StartLeft = _CenterPos.X - Width * _MultipleWidth / 2.f;
	FLOAT StartTop  = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width* _MultipleWidth, Height* _MultipleHeight, MemDC, 0, 0,
		Width, Height, RGB(255, 0, 255));
	ReleaseDC(hWnd, MemDC);
}

void FileManager::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + dwTime < GetTickCount()) {
		StartPixelFrame++;
		dwTime = GetTickCount();

		if (StartPixelFrame >= _FrameEndIndex) {
			StartPixelFrame = 0;
		}
	}
	
	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		StartPixelFrame * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);

}

BOOL FileManager::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
							Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		StartPixelFrame * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (StartPixelFrame >= _FrameEndIndex - 1) {
		ResetComplete = false;
		return true;
	}

	if (_AnimSpeed + dwTime < GetTickCount() && StartPixelFrame < _FrameEndIndex-1) {
		StartPixelFrame++;
		dwTime = GetTickCount();
		
	}

	ReleaseDC(hWnd, MemDC);

	return false;
}


void FileManager::PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
							Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	UINT ReversePixelIndex = _FrameEndIndex - StartPixelFrame -1;

	if (_AnimSpeed + dwTime < GetTickCount()) {
		StartPixelFrame++;
		dwTime = GetTickCount();

		if (ReversePixelIndex == 0) {
			StartPixelFrame = 0;
		}
	}
	GdiTransparentBlt(_SubWindowDC, StartLeft, StartTop, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		ReversePixelIndex * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);

}
void FileManager::PlayAnimation_ReverseOnce(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
							Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	UINT ReversePixelIndex = _FrameEndIndex - StartPixelFrame;

	if (_AnimSpeed + dwTime < GetTickCount() && StartPixelFrame < _FrameEndIndex - 1) {
		StartPixelFrame++;
		dwTime = GetTickCount();

	}
	GdiTransparentBlt(_SubWindowDC, StartLeft, StartTop, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		ReversePixelIndex * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);
}


void FileManager::Release() {
	SAFE_DELETE_MAP<const TCHAR*, BitMap*>(FileMap);
}
void FileManager::Append_Image_Alpha(HDC _SubWindowDC, const TCHAR* _KeyValue, Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	FLOAT StartLeft = _CenterPos.X - Width * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	BLENDFUNCTION blend;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA;
	blend.BlendOp = 0;
	blend.SourceConstantAlpha = 20;

	GdiAlphaBlend(_SubWindowDC, 0, 0, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY, MemDC, 0, 0, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY, blend);

	//GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth, Height * _MultipleHeight, MemDC, 0, 0,
		//Width, Height, RGB(255, 0, 255));
	ReleaseDC(hWnd, MemDC);

}