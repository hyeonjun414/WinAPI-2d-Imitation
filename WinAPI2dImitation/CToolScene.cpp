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
	
	// ��޸��� ������� ���̾�α׸� ���� ����Ѵ�.
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
			return;		// Ÿ���� ���� ��ġ ����
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

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd;					// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}
void CToolScene::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd; // �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}





// Ÿ�� ���̾�α� �ڽ��� �޽��� ó����.
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
			// �Էµ� ���� ��ȯ��Ų��.
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