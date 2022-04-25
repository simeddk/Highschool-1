matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
	float4 Position : Position;
	float3 Color : Color;
};

struct VertexOutput
{
	float4 Position : SV_Position;
	float3 Color : Color;
};

VertexOutput VS(VertexInput input)
{
	VertexInput output;
	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	output.Color = input.Color;
	
	return output;
}

float4 Color = float4(1, 0, 0, 1);
float4 PS(VertexOutput input) : SV_Target
{
	return Color;
	//return float4(1, 0, 0, 1);
	//return float4(0.55f, 0.67f, 1.0f, 1.0f);
	//return float4(input.Color, 1);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}