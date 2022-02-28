// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

// framework.h에서 타임스탬프 경고 발생
// 메인 파일인 WInAPI2dImitation.cpp에서만 헤더 만들기를
// 다른 파일 전부는 헤더 사용으로 지정하여 해결함.


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#pragma comment(lib, "Msimg32.lib")

// STL
#include <vector>
#include <list>
#include <map>
#include <chrono>
#include <random>
#include <assert.h>
using namespace std; // --> 같은 이름을 지닌 기능과 겹치지 않도록 유의

// 사용자 정의 클래스
#include "Logger.h"
#include "enumClass.h"
#include "struct.h"
#include "SelectGDI.h"
#include "function.h"

#include "CSingleton.h"
#include "CCore.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CResourceManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CEventManager.h"


// 정의
#define WINSTARTX 100     
#define WINSTARTY 100         
#define WINSIZEX 1280         
#define WINSIZEY 720
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
#define PI	3.141592f
#define DEG(value) value * PI / 180
#define GRAVITY 9.8f;

// 매크로
#define SINGLE(manager) manager::GetInst()
#define DT (float)CTimeManager::GetInst()->GetDT()
#define KEYCHECK(vk_Key) CKeyManager::GetInst()->GetKeyState(vk_Key)
#define LOG(str) Logger::debug(str);
#define CLONE(type) type* Clone() {return new type(*this);}

// 외부 변수 참조 -> 외부 클래스에 변수가 존재함을 알림.
extern HINSTANCE	hInst;
extern HWND			hWnd;

