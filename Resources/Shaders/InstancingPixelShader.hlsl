struct PS_IN
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
	float3 worldPos : TEXCOORD1;
	float4 color : TEXCOORD2;
};

struct PS_OUT
{
	float4 target0 : SV_TARGET0;
};

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

PS_OUT main(PS_IN input) : SV_TARGET
{
	PS_OUT result;
	
	float4 color = input.color;

	result.target0 = color;

	return result;
}