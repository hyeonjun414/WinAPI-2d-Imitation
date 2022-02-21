#pragma once


// 오브젝트 그룹
enum class OBJ_GROUP
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BULLET,

	SIZE
};

// 키 상태
enum class KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점	
	HOLD,	// 누르고 있는 상태
	AWAY,	// 막 뗀 시점
};

// 키 종류
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
