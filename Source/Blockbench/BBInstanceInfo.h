#pragma once
#include <DirectXMath.h>

struct BBInstanceInfo
{
	DirectX::XMFLOAT4X4 instanceMat;
	DirectX::XMFLOAT4 instanceColor;
	//XY, XY�œ����
	DirectX::XMFLOAT3X4 instanceUVOrigins;
	//XY, XY�œ����
	DirectX::XMFLOAT3X4 instanceUVSizes;
};