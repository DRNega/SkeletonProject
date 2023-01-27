#include <DxLib.h>
#include <cassert>
#include "DrawFunctions.h"

namespace my
{
/// <summary>
/// �摜�����[�h����
/// </summary>
/// <param name="path">�p�X������</param>
/// <returns>�摜�̃n���h��</returns>

int MyLoadGraph(const TCHAR* path)
{
	int handle = LoadGraph(path);
	assert(handle >= 0);
	return handle;
}
int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg)
{
	return DrawRectRotaGraph(x, y, 
							left, top,
							width, height,
							scale, angle,
							handle, transFlg);
}
}//end of namespace my


