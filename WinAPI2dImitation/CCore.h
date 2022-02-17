#pragma once
class CCore
{
	SINGLETON(CCore);
public :
	void update(); // 게임 업데이트
	void render(); // 게임 그리기
};

