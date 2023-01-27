#include <DxLib.h>
#include <cassert>
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "InputState.h"
#include "DrawFunctions.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;

	SceneManager sceneManager;
	sceneManager.ChangeScene(new TitleScene(sceneManager));

	while (ProcessMessage() != -1) 
	{
		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		//Frame Per Second
		auto fps = GetFPS();	

		//ï`âÊñΩóﬂêî
		auto drawcall = GetDrawCallCount();	

		DrawFormatString(10, 30, 0xffffff, L"FPS = %2.2f", fps);
		DrawFormatString(10, 60, 0xffffff, L"DC = %d", drawcall);
		
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}