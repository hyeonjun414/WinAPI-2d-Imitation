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

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2& Normalize() // ������ ����ȭ
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
	KEY_STATE	eState; // Ű�� ���� ��
	bool		bPrevPush;	// ���� �����ӿ� �ش� Ű�� ���ȴ���
};

