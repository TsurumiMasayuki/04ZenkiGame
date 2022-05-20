#include "DefaultInclude.hlsli"

struct VS_IN
{
	float4 pos : POSITION;
	float4 normal : NORMAL;
	float2 uv : TEXCOORD;
	uint4 boneIndices : BONEINDICES;
	float4 boneWeights : BONEWEIGHTS;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
	float3 worldPos : TEXCOORD1;
};

struct SkinOutput
{
	float4 pos;
	float3 normal;
};

cbuffer skinBuffer : register(b1)
{
	float4x4 skinning[32];
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.pos = mul(input.pos, wvp);
	output.worldPos = mul(input.pos, world).xyz;
	float3x3 normalMat = (float3x3)world;
	output.normal = mul(input.normal.xyz, normalMat);
	output.uv = input.uv;
	return output;
}