#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	LARGE_INTEGER	m_llCurCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llPrevCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��
	unsigned int	m_uiFPS;		// �ʴ� ������
	double			m_dDT;			// �����Ӵ� ��

public:
	void update();	// �Ź� FPS�� DeltaTime�� ������ �Ǿ���Ѵ�.
	void init();	// Ÿ�� �Ŵ��� �ʱ�ȭ

	unsigned int	GetFPS() { return m_uiFPS; }	// 1�ʿ� ����� �������� �������� Ȯ��
	double			GetDT()  { return m_dDT; }		// 1�����ӿ� �� �ʰ� �ɷȴ��� Ȯ��
};

