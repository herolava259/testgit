precision mediump float;

uniform 	vec4 		u_color;
//uniform 	sampler2D 	u_texture0;

varying 	vec2 		v_uv;

void main()
{
	gl_FragColor = u_color;
}
