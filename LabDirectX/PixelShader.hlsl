struct VS_OUTPUT
{
	float4 poos : SV_POSITION;
	float4 color : COLOR;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{ 
	return input.color;
} 