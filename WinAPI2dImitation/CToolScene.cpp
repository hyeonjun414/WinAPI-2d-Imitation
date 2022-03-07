#include "framework.h"
#include "CToolScene.h"
#include "CTexture.h"
#include "resource.h"
#include "CTile.h"
#include "commdlg.h"

INT_PTR CALLBACK TileWndProc(HWND, UINT, WPARAM, LPARAM);

CToolScene::CToolScene()
{
}

CToolScene::CToolScene(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Update()
{
	CScene::Update();
	if (KEYCHECK(KEY::ESC) == KEY_STATE::TAP)
		CHANGESCENE(SCENE_TYPE::START);

	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(-1, 0), 300);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(1, 0), 300);
	}
	if (KEYCHECK(KEY::W) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(0, -1), 300);
	}
	if (KEYCHECK(KEY::S) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(0, 1), 300);
	}

	SetTileIdx();
}


void CToolScene::Enter()
{
	SINGLE(CCameraManager)->SetWorldSize(Vec2(10000, 10000));
	SINGLE(CCameraManager)->SetLookAt(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	
	// 모달리스 방식으로 다이얼로그를 띄우고 출력한다.
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWndProc);
	ShowWindow(m_hWnd, SW_SHOW);
}

void CToolScene::Exit()
{
	DeleteGroup(OBJ_TYPE::TILE);
	EndDialog(m_hWnd, IDOK);
}

void CToolScene::SetIdx(UINT _idx)
{
	m_iIdx = _idx;
}

void CToolScene::SetTileIdx()
{
	if (KEYCHECK(KEY::LBTN)==KEY_STATE::HOLD)
	{
		Vec2 vMousePos = SINGLE(CKeyManager)->GetMousePos();
		vMousePos = SINGLE(CCameraManager)->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)vMousePos.y / CTile::SIZE_TILE;

		if (vMousePos.x < 0.f || iTileX <= iCol ||
			vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
		((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
	}
}
void CToolScene::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");
	assert(pFile);

	UINT	xCount = GetTileX();
	UINT	yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	
	const vector<CGameObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}
void CToolScene::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}
void CToolScene::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}





// 타일 다이얼로그 박스의 메시지 처리기.
INT_PTR CALLBACK TileWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			// 입력된 값을 반환시킨다.
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(OBJ_TYPE::TILE);
			pToolScene->CreateTile(x, y);

		}
		else if (LOWORD(wParam) == IDC_BUTTON_TILE)
		{
			int m_iIdx = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			CTexture* pTex = SINGLE(CResourceManager)->FindTexture(L"Tile");

			UINT iWidth = pTex->Width();
			UINT iHeight = pTex->Height();

			UINT iMaxY = iHeight / CTile::SIZE_TILE;
			UINT iMaxX = iWidth / CTile::SIZE_TILE;

			UINT iCurY = (m_iIdx / iMaxX) % iMaxY;
			UINT iCurX = (m_iIdx % iMaxX);

			StretchBlt(GetDC(hDlg),
				(int)(100),
				(int)(150),
				(int)(CTile::SIZE_TILE) * 2,
				(int)(CTile::SIZE_TILE) * 2,
				pTex->GetDC(),
				(int)(iCurX * CTile::SIZE_TILE),
				(int)(iCurY * CTile::SIZE_TILE),
				(int)(CTile::SIZE_TILE),
				(int)(CTile::SIZE_TILE),
				SRCCOPY);

			//BitBlt(GetDC(hDlg),
			//	(int)(150),
			//	(int)(150),
			//	(int)(CTile::SIZE_TILE),
			//	(int)(CTile::SIZE_TILE),
			//	pTex->GetDC(),
			//	(int)(iCurX * CTile::SIZE_TILE),
			//	(int)(iCurY * CTile::SIZE_TILE),
			//	SRCCOPY);

			pToolScene->SetIdx(m_iIdx);
		}
		break;
	}
	return (INT_PTR)FALSE;
}