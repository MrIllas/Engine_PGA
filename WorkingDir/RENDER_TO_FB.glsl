///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#ifdef TEXTURED_GEOMETRY

#if defined(VERTEX) ///////////////////////////////////////////////////

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal
layout(location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = vec4(aPosition, 1.0);
}

#elif defined(FRAGMENT) ///////////////////////////////////////////////

struct Light
{
	uint type;
	vec3 color;
	vec3 direction;
	vec3 position;
};

layout(binding=0, std140) uniform GlobalParams
{
	vec3 uCamPosition;
	uint uLightCount;
	Light uLight[16];
};

in vec2 vTexCoord;
in vec3 vPosition;
in vec3 vNormal;
in vec3 vViewDir;

uniform sampler2D uTexture;

layout(location = 0) out vec4 oAlbedo;
layout(location = 0) out vec4 oNormals;
layout(location = 0) out vec4 oPosition;

void main()
{
	oColor = texture(uTexture, vTexCoord);
	oNormals = vec4(vNormal, 1.0);
	oPosition = vec4(vPosition, 1.0);
}

#endif
#endif