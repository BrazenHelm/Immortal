Texture2D tex		: register(t0);
Texture2D depthMap	: register(t1);
SamplerState smplr	: register(s0);

struct PSInputType
{
	float4 worldPos : WorldPosition;
	float4 viewPos : ViewPosition;
	float3 normal : Normal;
	float4 pos : SV_Position;
	float2 tex : TexCoord;
	float4 lightViewPos : LightView;
};

cbuffer LightBuffer
{
	float3 lightPos;
	float3 ambient;
	float3 diffuseColor;
	float diffuseIntensity;
	float attConst;
	float attLin;
	float attQuad;
};

cbuffer ObjectBuffer
{
	float3 material;
	float specularIntensity;
	float specularPower;
};

float4 main(PSInputType input) : SV_Target
{
	float bias = 0.0001f;

	float3 diffuse = { 0.f, 0.f, 0.f };
	float3 specular = { 0.f, 0.f, 0.f };
	
	float2 projTexCoord;
	projTexCoord.x = input.lightViewPos.x / input.lightViewPos.w / 2.f + 0.5f;
	projTexCoord.y = -input.lightViewPos.y / input.lightViewPos.w / 2.f + 0.5f;

	if (saturate(projTexCoord.x) == projTexCoord.x &&
		saturate(projTexCoord.y) == projTexCoord.y)
	{
		float depthValue = depthMap.Sample(smplr, projTexCoord).r;
		float lightDepthValue = input.lightViewPos.z / input.lightViewPos.w - bias;

		if (lightDepthValue < depthValue)
		{
			//return float4(0.f, 1.f, 1.f, 1.f);
			const float3 vecToLight = lightPos - (float3)input.viewPos;
			const float distToLight = length(vecToLight);
			const float3 dirToLight = vecToLight / distToLight;

			const float att = 1.f /
				(attConst + attLin * distToLight + attQuad * (distToLight * distToLight));

			diffuse =
				diffuseColor * diffuseIntensity * att * max(0.f, dot(dirToLight, input.normal));

			const float3 w = input.normal * dot(vecToLight, input.normal);
			const float3 r = w * 2.f - vecToLight;

			specular =
				diffuseColor * diffuseIntensity * att * specularIntensity
				* pow(max(0.f, dot(normalize(-r), normalize((float3)input.viewPos))), specularPower);
		}
		//return float4(1.f, 1.f, 0.f, 1.f);
	}

	float4 texColor = tex.Sample(smplr, input.tex);
	
	return float4(saturate(diffuse + ambient + specular) * material * texColor.xyz, 1.f);
}