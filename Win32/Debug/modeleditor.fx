///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.fx
// Creator  : Miao Kaixiang
// Date     : 2015-7-17 15:00:00
// Comment  : Shader File
//
///////////////////////////////////////////////////////////////

matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjectionMatrix;

// Vertex Shader
//void VS(float4 Pos: POSITION,
//	float4 Color: COLOR,
//	out float4 oPos: SV_POSITION,
//	out float4 oColor: COLOR)
//{
//    oPos = Pos;
//	oColor = Color;
//}
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos, WorldMatrix);
    output.Pos = mul(output.Pos, ViewMatrix);
    output.Pos = mul(output.Pos, ProjectionMatrix);
    output.Color = Color;
    return output;
}
                                                                                            
// Pixel Shader
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