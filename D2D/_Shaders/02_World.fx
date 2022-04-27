matrix World;
matrix View;
matrix Projection;

float4 Color = float4(1, 0, 0, 1);

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


float4 PS_DiffuseColor(VertexOutput input) : SV_Target
{
	return Color;
}

float4 PS_Gradiant(VertexOutput input) : SV_Target
{
	return float4(input.Color, 1);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_DiffuseColor()));
	}

	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_Gradiant()));
	}
}