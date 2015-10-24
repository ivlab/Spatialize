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

void main()
{   
	color = vec4(1.0,0.0,0.0,1.0);
	if (hasTexCoords)
	{
		color = vec4(texCoord,0.0,1.0);
	} 
	
    //color = vec4(texture(tex, texCoord));
    
    vec3 I = vec3(0.0);
    
    for(int i = 0; i < lightCount; i++) {
    	vec3 L = normalize(lightPositions[i].xyz-pos);
    	vec3 N = norm;
    	vec3 H =  normalize(L-normalize(viewdir));
    	float ka = lightK[i].x;
    	float kd = lightK[i].y;
    	float ks = lightK[i].z;
    	float n = lightK[i].w;
    	I += ka*color.xyz + kd*color.xyz*max(0,dot(L,N)) + ks*vec3(1.0)*pow(max(0,dot(H,N)),n);
    }
    
    I.x = min(1.0, I.x);
    I.y = min(1.0, I.y);
    I.z = min(1.0, I.z);
    
    color = vec4(I,1.0);
}
