#include "Text.h"
#include "Font.h"
#include "Shaders.h"


extern GLint screenWidth;
extern GLint screenHeight;


void Text::CaculateWorldMatrix()
{
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);
	m_WorldMat = m_Sc * m_T;
}


Text::Text(std::shared_ptr<Shaders> sha, std::shared_ptr<Font> font, std::string text, TEXT_COLOR color, float size)
{
	m_Vec3Position = Vector3(0, 0, 0);
	m_Vec2DPos = Vector2(0, 0);

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);
	m_font = font;
	m_text = text;
	m_Color = EnumToVector(color);
	m_pShader = sha;
	m_scale = Vector2(size, size);
}

Text::~Text()
{
}

void Text::Init()
{
}

void Text::Draw()
{
	GLuint iTempShaderVaribleGLID = -1;

	glUseProgram(m_pShader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_font->getArrBuffer());


	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}


	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
	if (iTempShaderVaribleGLID != -1)
		glUniform4fv(iTempShaderVaribleGLID, 1, &m_Color.x);

	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_texture");
	if (iTempShaderVaribleGLID != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_font->getTextFontAdd());
		glUniform1i(iTempShaderVaribleGLID, 0);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float sx = 1.0f / screenWidth * m_scale.x;
	float sy = 1.0f / screenHeight * m_scale.y;
	float x = m_Vec3Position.x;
	float y = m_Vec3Position.y;

	FT_GlyphSlot glyphSlot = m_font->getFtGlyph();
	for (const char* p = m_text.c_str(); *p; p++)
	{
		if (FT_Load_Char(m_font->getFtFace(), *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyphSlot->bitmap.width,
			glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyphSlot->bitmap.buffer
		);
		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = -y - glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::Update(GLfloat deltatime)
{
}



void Text::setFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

void Text::setText(std::string text) {
	m_text = text;
}



Vector4 Text::EnumToVector(TEXT_COLOR color)
{
	Vector4 vecColor;
	switch (color)
	{
	case TEXT_COLOR::WHILE:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::RED:
		vecColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::GREEN:
		vecColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::BLUE:
		vecColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::YELLOW:
		vecColor = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::PURPLE:
		vecColor = Vector4(0.5f, 0.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::CYAN:
		vecColor = Vector4(0.0f, 0.9f, 0.9f, 1.0f);
		break;
	default:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	return vecColor;
}

void Text::Set2DPosition(GLfloat width, GLfloat height)
{
	m_Vec2DPos.x = width;
	m_Vec2DPos.y = height;

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

void Text::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}