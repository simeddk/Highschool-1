matrix World;

cbuffer CB_PerFrame
{
	matrix View;
	matrix Projection;
}

Texture2D DiffuseMap;

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

SamplerState LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
};

float4 PS(VertexOutput input) : SV_Target
{
	return DiffuseMap.Sample(LinearSampler, input.Uv);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));

		SetBlendState(Translucent, float4(0, 0, 0, 0), 0xFF);
	}
}