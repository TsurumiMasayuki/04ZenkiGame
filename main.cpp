#include <Windows.h>
#include <crtdbg.h>

#include "Game.h"

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:	//�E�B���h�E���j�����ꂽ
		PostQuitMessage(0);	//OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);	//�W���̏������s��
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX wndClass{};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WndProc;			//�E�B���h�E�v���V�[�W����ݒ�
	wndClass.lpszClassName = L"DirectXGame";				//�E�B���h�E�N���X��
	wndClass.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&wndClass);
	//�E�B���h�E�T�C�Y{X,Y,����,�c��}
	RECT wrc = { 0, 0, 1280, 720 };
	//�����ŃT�C�Y�␳
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�N���X�̍쐬
	HWND hwnd = CreateWindow(
		wndClass.lpszClassName,		//�N���X��
		L"DirectXGame",				//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,		//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,				//X���W(OS�ɔC����)
		CW_USEDEFAULT,				//Y���W(OS�ɔC����)
		wrc.right - wrc.left,		//�E�B���h�E����
		wrc.bottom - wrc.top,		//�E�B���h�E�c��
		nullptr,					//�e�E�B���h�E�n���h��
		nullptr,					//���j���[�n���h��
		wndClass.hInstance,			//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);					//�I�v�V����

	//�E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);

	Game game(wndClass.hInstance, hwnd);
	game.start();

	MSG msg{};	//���b�Z�[�W

	while (true)
	{
		//���b�Z�[�W�̊m�F
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	//�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&msg);	//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}

		//�I�����b�Z�[�W�������烋�[�v�𔲂���
		if (msg.message == WM_QUIT)
		{
			break;
		}

		//���t���[������
		game.update();

		//�Q�[���I�����Ă�Ȃ烋�[�v�I��
		if (game.isEnd()) break;
	}

	//�I������
	game.shutdown();
	GameDevice::getModelManager().endLoading();
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);

	return 0;
}