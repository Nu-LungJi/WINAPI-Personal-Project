#pragma once
class FileManager {
	COMPONENT_SINGLETON(FileManager)

public:
	void Update();

public:
	BitMap* Find_BMPFile(const TCHAR* _KeyValue);
	void	Insert_BMPFile(const TCHAR* _FilePath, const TCHAR* _KeyValue);



	void	Append_Image(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _StartPosLeft, UINT _StartPosTop,
							FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void	Append_Image(HDC _SubWindowDC, const TCHAR* _KeyValue, Vector2D _CenterPos,
		FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);



	void	PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	BOOL	PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);



	void	PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	void	PlayAnimation_ReverseOnce(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	void Append_Image_Alpha(HDC _SubWindowDC, const TCHAR* _KeyValue, Vector2D _CenterPos, FLOAT _MultipleWidth = 1.F, FLOAT _MultipleHeight = 1.F);

	void	FileMap_Reset() { SAFE_DELETE_MAP(FileMap); }

	void	FrameStartPoint_Reset() { StartPixelFrame = 0; ResetComplete = true; }

	void	Animation_Escape() { 
		StartPixelFrame = 0; ResetComplete = true;
	}

	void	Release();

private:
	map<const TCHAR*, BitMap*>	FileMap;
	DWORD						dwTime;
	INT						StartPixelFrame;
	BOOL					ResetComplete;

	FLOAT  OffsetX;
	FLOAT  OffsetY;

};

