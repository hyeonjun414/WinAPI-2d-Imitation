// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// STL
#include <vector>
#include <list>
#include <map>
#include <chrono>
#include <random>
using namespace std; // --> 같은 이름을 지닌 기능과 겹치지 않도록 유의

// 사용자 정의 클래스

#include "Logger.h"
#include "enumClass.h"
#include "struct.h"

#include "CSingleton.h"
#include "CCore.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"


// 정의
#define WINSTARTX 100     
#define WINSTARTY 100         
#define WINSIZEX 1280         
#define WINSIZEY 720
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

// 매크로
#define DT CTimeManager::GetInst()->GetDT();
#define KEYCHECK(vk_Key) CKeyManager::GetInst()->GetKeyState(vk_Key)

// 외부 변수 참조 -> 외부 클래스에 변수가 존재함을 알림.
extern HINSTANCE	hInst;
extern HWND			hWnd;