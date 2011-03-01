#version 120

varying vec2 vary_fragcoord;
uniform vec2 screen_res;

void main(void) 
{ 
        // Anaglyph Shader KL
	
	// Transform the pos to screen space
	gl_Position = ftransform();
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        //vary_fragcoord = (pos.xy*0.5+0.5)*screen_res;
	
	// use the first set of texture coord in the frag shader
	gl_TexCoord[0] = gl_MultiTexCoord0;	
		
}