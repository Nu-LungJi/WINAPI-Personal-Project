#pragma once

struct Vector2D {
	Vector2D() {};
	Vector2D(FLOAT _VX, FLOAT _VY) : X(_VX), Y(_VY) {}

public:
	FLOAT X, Y;

public:
	FLOAT Length() { return sqrt(X*X+Y*Y); }
	Vector2D& Normalize(){
		float fLen = Length();

		X /= fLen;
		Y /= fLen;

		return *this;
	}

public:
	Vector2D operator +(Vector2D _other) { return { X + _other.X, Y + _other.Y }; }
	Vector2D operator -(Vector2D _other) { return { X - _other.X, Y - _other.Y }; }
	Vector2D operator *(Vector2D _other) { return { X * _other.X, Y * _other.Y }; }
	Vector2D operator *(FLOAT _Value) { return { X * _Value, Y * _Value }; }
};

struct INFO {
	FLOAT	CenterPosX, CenterPosY;
	FLOAT	Width, Height;
};
struct KeyINFO {
	KEY_STATE	Current_KeyState;
	BOOL		Prev_KeyState;
};