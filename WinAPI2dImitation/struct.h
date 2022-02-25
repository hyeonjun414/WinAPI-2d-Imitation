#pragma once



struct iPoint
{
	int x;
	int y;
};

typedef struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2& operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vector2 operator+(const Vector2& _other)
	{
		return Vector2(this->x + _other.x, this->y + _other.y);
	}
	Vector2 operator-(const Vector2& _other)
	{
		return Vector2(this->x - _other.x, this->y - _other.y);
	}
	Vector2 operator*(const Vector2& _other)
	{
		return Vector2(this->x * _other.x, this->y * _other.y);
	}
	Vector2 operator/(const Vector2& _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		return Vector2(this->x / _other.x, this->y / _other.y);
	}

	Vector2& operator+=(const Vector2& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& _other)
	{
		x -= _other.x;
		y -= _other.y;
		return *this;
	}
	Vector2& operator*=(const Vector2& _other)
	{
		x *= _other.x;
		y *= _other.y;
		return *this;
	}
	Vector2& operator/=(const Vector2& _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		x /= _other.x;
		y /= _other.y;
		return *this;
	}


	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2& Normalize() // 벡터의 정규화
	{
		float fLen = Length();

		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;
		return *this;
	}

} Vec2;

struct tKeyInfo
{
	KEY_STATE	eState; // 키의 상태 값
	bool		bPrevPush;	// 이전 프레임에 해당 키가 눌렸는지
};

