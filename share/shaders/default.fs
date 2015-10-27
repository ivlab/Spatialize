#version 300 es
precision mediump float;
in vec2 texCoord;
in vec3 pos;
in vec3 norm;

out vec4 color;

uniform sampler2D tex;
uniform vec4 lightPositions[10];
uniform vec4 lightK[10];
uniform int lightCount;
uniform vec3 viewdir;
uniform bool hasTexCoords;
uniform bool clip;

void main()
{   
	//if (pos.z > 0.0 && clip) { discard; }

	color = vec4(0.7,0.7,0.7,1.0);
	if (hasTexCoords)
	{
		color = vec4(texture(tex, texCoord));
	}
    
    vec3 I = vec3(0.0);
    
    for(int i = 0; i < lightCount; i++) {
    	vec3 L = normalize(lightPositions[i].xyz-pos);
    	vec3 N = norm;
    	vec3 H =  normalize(L-normalize(viewdir));
    	float ka = lightK[i].x;
    	float kd = lightK[i].y;
    	float ks = lightK[i].z;
    	float n = lightK[i].w;
    	
    	float LdotN = dot(L,N);
    	float HdotN = dot(H,N);
    	float diffVal = 1.0f;
    	float specVal = 1.0f;
    	if (LdotN < 0.0) { diffVal = 0.3; }
    	if (HdotN < 0.0) { specVal = 0.2; }
    	I += ka*color.xyz + diffVal*kd*color.xyz*max(0,abs(LdotN)) + specVal*ks*vec3(1.0)*pow(min(1.0,max(0,abs(HdotN))),n);
    }
    
    I.x = min(1.0, I.x);
    I.y = min(1.0, I.y);
    I.z = min(1.0, I.z);
    
    color = vec4(I,color.a);
}
