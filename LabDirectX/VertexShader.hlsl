struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color : COLOR;
}; 
 
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;  
	float4 color : COLOR;
};
 
//参数是是从上一个管道状态传过来的，即Input Assembler (IA) stage
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = float4(input.pos, 1.0f);
	output.color = input.color;
	return output;
}