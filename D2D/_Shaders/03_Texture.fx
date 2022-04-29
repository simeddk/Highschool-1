matrix World;
matrix View;
matrix Projection;

Texture2D TextureMap;

struct VertexInput
{
	float4 Position : Position;
	float2 Uv : Uv;
};

struct VertexOutput
{
	float4 Position : SV_Position;
	float2 Uv : Uv;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	
	output.Uv = input.Uv;
	
	return output;
}

//-> A * SrcBlend (op) B * DestBlend
BlendState Translucent
{
	BlendEnable[0] = true;
	SrcBlend[0] = SRC_ALPHA;
	DestBlend[0] = INV_SRC_ALPHA;
	BlendOp[0] = ADD;

	SrcBlendAlpha[0] = ONE;
	DestBlendAlpha[0] = ONE;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState AlphaToCoverageEnable
{
	AlphaToCoverageEnable = true;
	BlendEnable[0] = true;
	SrcBlend[0] = SRC_ALPHA;
	DestBlend[0] = INV_SRC_ALPHA;
	BlendOp[0] = ADD;

	SrcBlendAlpha[0] = ONE;
	DestBlendAlpha[0] = ONE;
	RenderTargetWriteMask[0] = 0x0F;
};


SamplerState samplerState;
float4 PS(VertexOutput input) : SV_Target
{
	return TextureMap.Sample(samplerState, input.Uv);
}

SamplerState LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
};

SamplerState PointSampler
{
	Filter = MIN_MAG_MIP_POINT;
};

uint Filter = 0;
float4 PS_Filter(VertexOutput input) : SV_Target
{
	if (Filter == 0)
		return TextureMap.Sample(LinearSampler, input.Uv);
	else
		return TextureMap.Sample(PointSampler, input.Uv);
}

float Time = 0;
float4 PS_Lerp(VertexOutput input) : SV_Target
{
	float4 diffuse = TextureMap.Sample(PointSampler, input.Uv);
	float4 red = float4(1, 0, 0, diffuse.a) + diffuse;

	float4 flipRed = lerp(diffuse, red, Time);
	
	float originAlpha = diffuse.a;
	float flipAlpha = lerp(originAlpha, 0.0f, 1 - Time);

	return float4(flipRed.rgb, flipAlpha);

}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));

		SetBlendState(Translucent, float4(0, 0, 0, 0), 0xFF);
	}

	pass P2
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));

		SetBlendState(AlphaToCoverageEnable, float4(0, 0, 0, 0), 0xFF);
	}

	pass P3
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_Filter()));

		SetBlendState(Translucent, float4(0, 0, 0, 0), 0xFF);
	}

	pass P4
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_Lerp()));

		SetBlendState(Translucent, float4(0, 0, 0, 0), 0xFF);
	}
}