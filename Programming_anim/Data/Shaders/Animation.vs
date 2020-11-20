attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float 	u_alpha;
uniform		float		u_currentFrame;
uniform		float		u_numFrames;

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	//v_uv = a_uv;
	v_uv = vec2 (a_uv.x*(1.0/u_numFrames)+(1.0/u_numFrames)*u_currentFrame, a_uv.y);
}
   