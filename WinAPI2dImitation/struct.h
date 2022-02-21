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
} Vec2;

struct tKeyInfo
{
	KEY_STATE	eState; // Ű�� ���� ��
	bool		bPrevPush;	// ���� �����ӿ� �ش� Ű�� ���ȴ���
};

