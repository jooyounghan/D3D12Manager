#include "Header.hlsli"

float4 main(PSInput input) : SV_TARGET
{
    return float4(input.uv, 0.0f, 1.0f);
}