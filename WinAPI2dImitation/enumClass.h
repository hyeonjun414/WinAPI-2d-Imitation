#pragma once


// ������Ʈ �׷�
enum class OBJ_GROUP
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BULLET,

	SIZE
};

// Ű ����
enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����	
	HOLD,	// ������ �ִ� ����
	AWAY,	// �� �� ����
};

// Ű ����
enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,Z,X,C,V,B,
	ALT,LSHIFT,CTRL,
	SPACE,ENTER,ESC,

	SIZE
};
