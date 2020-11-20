#ifdef ANDROID
#include "../../Utilities/esShader.cpp"
#endif //android

#include "Shaders.h"

Shaders::Shaders()
{

}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader (vertexShader);
	glDeleteShader (fragmentShader);
}

GLint Shaders::Init(const std::string& fileVertexShader, const std::string& fileFragmentShader)
{
	LOGI("Compile Shader:%s\t%s\t\t\n",fileVertexShader,fileFragmentShader);
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);
	if ( vertexShader == 0 )
	{
		LOGE("ERR VS %s\n",fileVertexShader);
		return -1;
	}
	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);
	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		LOGE("ERR FS %s\n",fileFragmentShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	iTextureLoc[0]  = glGetUniformLocation(program,"u_texture0");
	iTextureLoc[1]  = glGetUniformLocation(program,"u_texture1");
	iTextureLoc[2]  = glGetUniformLocation(program,"u_texture2");
	iTextureLoc[3]  = glGetUniformLocation(program,"u_texture3");
	iTextureLoc[4]  = glGetUniformLocation(program,"u_texture4");
	LOGI("Done %s %s \n",fileVertexShader,fileFragmentShader);
	return 0;
}

GLuint Shaders::GetAttribLocation(const std::string& str)
{
	return glGetAttribLocation(program,str.c_str());
}

GLuint Shaders::GetUniformLocation(const std::string& str)
{
	return glGetUniformLocation(program,str.c_str());
}

void Shaders::SetShaderID(GLuint id)
{
	m_iShaderID=id;
}
GLuint Shaders::GetShaderID()
{
	return m_iShaderID;
}
void Shaders::EnableTest(GLuint gl_test)
{
	glEnable(gl_test);
}
void Shaders::EnableAlpha(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}