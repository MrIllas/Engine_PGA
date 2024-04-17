///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#ifdef FB_TO_QUAD

#if defined(VERTEX) ///////////////////////////////////////////////////

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

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

layout(binding = 0, std140) uniform GlobalsParams
{
    vec3 uCamPosition;
    uint uLightCount;
    Light uLight[16];
};

in vec2 vTexCoord;

uniform sampler2D uAlbedo;
uniform sampler2D uNormals;
uniform sampler2D uPosition;
uniform sampler2D uViewDir;
layout(location = 0) out vec4 oColor;

void CalculateBlitVars(in Light light, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
     vec3 vNormal = texture(uNormals, vTexCoord).xyz;
     vec3 vViewDir = texture(uViewDir, vTexCoord).xyz;
     vec3 lightDir = normalize(light.direction);

     float ambientStrenght = 0.2;
     ambient = ambientStrenght * light.color;

     float diff = max(dot(vNormal,lightDir), 0.0);
     diffuse = diff * light.color;

     float specularStrenght = 0.1;
     vec3 reflectDir = reflect(-lightDir, vNormal);
     vec3 normalViewDir = normalize(vViewDir);
     float spec = pow(max(dot(normalViewDir, reflectDir), 0.0), 32);
     specular = specularStrenght * spec * light.color;
}

void main()
{
vec4 textureColor = texture(uAlbedo, vTexCoord);
vec4 finalColor = vec4(0.0f);

    for(int i=0; i< uLightCount; ++i)
    {
        vec3 lightResult = vec3(0.0);
        vec3 ambient = vec3(0.0);
        vec3 diffuse = vec3(0.0);
        vec3 specular = vec3(0.0);

        if(uLight[i].type == 0) //directional light 
        {
            Light light = uLight[i];
            CalculateBlitVars(light, ambient, diffuse, specular);

            lightResult = ambient + diffuse + specular;
            finalColor += vec4(lightResult, 1.0) * textureColor;
        }
        else //point light
        {
            Light light = uLight[i];
            float constant = 1.0;
            float lineal = 0.09;
            float quadratic = 0.032;
            float distance = length(light.position - texture(uPosition, vTexCoord).xyz);
            float attenuation = 1.0 / (constant + lineal * distance + quadratic * (distance * distance));

            CalculateBlitVars(light, ambient, diffuse, specular);

            lightResult = (ambient * attenuation) + (diffuse * attenuation) + (specular * attenuation);
            finalColor += vec4(lightResult, 1.0) * textureColor;
        }
    }

    oColor = finalColor;
}

#endif
#endif


// NOTE: You can write several shaders in the same file if you want as
// long as you embrace them within an #ifdef block (as you can see above).
// The third parameter of the LoadProgram function in engine.cpp allows
// chosing the shader you want to load by name.
