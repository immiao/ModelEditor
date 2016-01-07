///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.fx
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Shader File
//
///////////////////////////////////////////////////////////////

//matrix WorldMatrix;
//matrix ViewMatrix;
//matrix ProjectionMatrix;
matrix gWolrdViewProjMatrix;
matrix gRoleWolrdViewProjMatrix;
float4x4 gBoneTransforms[96];
float g_fElapsedTime;
// Vertex Shader
//void VS(float4 Pos: POSITION,
//	float4 Color: COLOR,
//	out float4 oPos: SV_POSITION,
//	out float4 oColor: COLOR)
//{
//    oPos = Pos;
//	oColor = Color;
//}
Texture2D txDiffuse;
SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS(float3 Pos : POSITION, float4 Color : COLOR)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    //output.Pos = mul(Pos, WorldMatrix);
    //output.Pos = mul(output.Pos, ViewMatrix);
    //output.Pos = mul(output.Pos, ProjectionMatrix);
	output.Pos = mul(float4(Pos, 1.0f), gWolrdViewProjMatrix);
    output.Color = Color;
    return output;
}

VS_OUTPUT SkinnedVS(float3 Pos : POSITION, float4 Color : COLOR, float3 Weight : WEIGHT, uint4 BoneIndices : BONEINDICES,
					float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float weights[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	weights[0] = Weight.x;
	weights[1] = Weight.y;
	weights[2] = Weight.z;
	weights[3] = 1.0f - weights[0] - weights[1] - weights[2];

	float3 posL = float3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < 4; ++i)
	{
	    posL += weights[i]*mul(float4(Pos, 1.0f), gBoneTransforms[BoneIndices[i]]).xyz;
	}
	//posL.x += 100 * g_fElapsedTime;
	//posL.y += Transition.y;
	//posL.z += 100 * g_fElapsedTime;
	//posL = Pos;
	output.Pos = mul(float4(posL, 1.0f), gRoleWolrdViewProjMatrix);
	output.Color = Color;
	output.Tex = Tex;

	return output;
}

VS_OUTPUT StopSkinnedVS(float3 Pos : POSITION, float4 Color : COLOR, float3 Weight : WEIGHT, uint4 BoneIndices : BONEINDICES,
						float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    //output.Pos = mul(Pos, WorldMatrix);
    //output.Pos = mul(output.Pos, ViewMatrix);
    //output.Pos = mul(output.Pos, ProjectionMatrix);
	output.Pos = mul(float4(Pos, 1.0f), gRoleWolrdViewProjMatrix);
    output.Color = Color;
	output.Tex = Tex;
    return output;
}

// Pixel Shader
float4 TexPS(VS_OUTPUT input): SV_Target
{
    return txDiffuse.Sample(samLinear, input.Tex) * input.Color;
}

float4 PS(VS_OUTPUT input): SV_Target
{
    return input.Color;
}

technique11 Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}

technique11 SkinnedRender
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, SkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, TexPS()));
    }
}

technique11 StopSkinnedRender
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, StopSkinnedVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, TexPS()));
    }
}