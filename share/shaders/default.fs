#version 300 es
precision mediump float;
in vec2 texCoord;

out vec4 color;

uniform sampler2D tex;

void main()
{    
	color = vec4(1.0,0.0,0.0,1.0);
    //color = vec4(texture(tex, texCoord));
}
