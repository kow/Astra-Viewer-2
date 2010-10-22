void main(void) 
{ 
        // Anaglyph Shader KL
	
	// Transform the pos to screen space
	//gl_Position = ftransform();
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// use the first set of texture coord in the frag shader
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
		
}