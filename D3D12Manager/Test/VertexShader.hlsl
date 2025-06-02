struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

cbuffer CameraCB : register(b0)
{
    float4x4 viewProj;
};

StructuredBuffer<float4> positions : register(t0);
Texture2D<float4> diffuseTex : register(t1);
SamplerState samp : register(s0);
RWTexture2D<float4> uavTex : register(u0);

[RootSignature(
    "CBV(b0)," // CameraCB
    "SRV(t0)," // StructuredBuffer
    "SRV(t1)," // Texture2D
    "UAV(u0)" // RWTexture2D
)]
PSInput main(VSInput input, uint vertexID : SV_VertexID)
{
    PSInput result;
    float4 pos = positions[vertexID];
    result.position = mul(viewProj, pos);
    result.uv = input.uv;
    return result;
}