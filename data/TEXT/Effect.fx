//--------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------
float4x4 g_view;
float4x4 g_proj;
texture g_tex;

//--------------------------------------------------
// �e�N�X�`��
//--------------------------------------------------
sampler tipSampler = sampler_state {
	texture = <g_tex>;
	MipFilter = LINEAR;
	MinFilter = POINT;
	MagFilter = POINT;
};

//--------------------------------------------------
// ���_���ˉe��Ԃֈړ�
//--------------------------------------------------
float4 TransVertex(
	float4 vtx,
	float4x4 mtxWorld,
	float4x4 view,
	float4x4 proj)
{
	vtx = mul(vtx, mtxWorld);
	vtx = mul(vtx, view);
	vtx = mul(vtx, proj);
	return vtx;
}

//--------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
//--------------------------------------------------
struct VS_OUT {
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
	float4 col : COLOR;
};

//--------------------------------------------------
// ���_�V�F�[�_�v���O����
//--------------------------------------------------
VS_OUT vsMain(
	float2 pos : POSITION,
	float2 localUV : TEXCOORD0,
	float4 worldPos : COLOR0,
	float4 col : COLOR1,
	float2 size : TEXCOORD1
) {
	VS_OUT Out;

	float s = sin(worldPos.w);
	float c = cos(worldPos.w);

	float4x4 world = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		worldPos.x, worldPos.y, worldPos.z, 1.0f };

	Out.pos = TransVertex(float4(pos.x * size.x, pos.y * size.y, 0.0f, 1.0f), world, g_view, g_proj);

	Out.uv = localUV;
	Out.col = col;

	return Out;
}

//--------------------------------------------------
// �s�N�Z���V�F�[�_�v���O����
//--------------------------------------------------
float4 psMain(VS_OUT In) : COLOR0{
	return tex2D(tipSampler, In.uv) * In.col;
}

//--------------------------------------------------
// �e�N�j�b�N
//--------------------------------------------------
technique tech {
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}
}
