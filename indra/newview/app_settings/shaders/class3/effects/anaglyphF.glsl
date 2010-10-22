//  KL anaglyph shader
//  (c)2010 Kirstenlee Cinquetti

uniform sampler2DRect leftTex, rightTex;


uniform float OffsetS;
uniform float OffsetT;


void main(void)
{
        vec3 left = texture2DRect(leftTex, gl_TexCoord[0].st ).rgb;
	
	vec3 right = texture2DRect(rightTex, gl_TexCoord[0].st + vec2(OffsetS,OffsetT)).rgb;
	
	vec3 col, coeff = vec3(0.15, 0.15, 0.7);
	
	col.r = left.r;
	
	// for amber blue left.g for color anaglyph right.g, for mono comment out
	col.g = right.g;
	
	//apply blue with its coeff
	col.b =  dot(right,coeff);

	gl_FragColor = vec4(col, 1.0);
   
}