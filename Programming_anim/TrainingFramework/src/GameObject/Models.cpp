#include "Models.h"
#include "utilities.h" 

Models::Models(const std::string& fileName, GLuint type)
{

	std::ifstream modelFile(fileName, std::ios::binary);
	if (!modelFile.is_open())
	{
		LOGE("ERROR %s \n", fileName);
		return;
	}
	LOGI("Load Models:%s\t\t", fileName);

	GLuint iNumVertex = 0;
	Vertex* verticesData;
	GLuint* Indices;
	if (type == NFG)
	{
		char* buffer;
		std::string strtmp;
		float posX, posY, posZ, normX, normY, normZ, binormX, binormY, binormZ, tgtX, tgtY, tgtZ, uvX, uvY;
		//read data from file
		modelFile.seekg(0, modelFile.end);
		size_t bufSize = modelFile.tellg();
		modelFile.seekg(0, modelFile.beg);

		buffer = new char[bufSize + 1];
		modelFile.read(buffer, bufSize);

		buffer[bufSize] = '\0';
		std::stringstream ss(buffer);

		std::getline(ss, strtmp, '\n');
		int rs = sscanf(strtmp.c_str(), "NrVertices: %d", &iNumVertex);
		verticesData = new Vertex[iNumVertex];
		for (GLuint i = 0; i < iNumVertex; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf(strtmp.c_str(), "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &posX, &posY, &posZ, &normX, &normY, &normZ, &binormX, &binormY, &binormZ, &tgtX, &tgtY, &tgtZ, &uvX, &uvY);
			verticesData[i].position.x = posX;
			verticesData[i].position.y = posY;
			verticesData[i].position.z = posZ;

			verticesData[i].normal.x = normX;
			verticesData[i].normal.y = normY;
			verticesData[i].normal.z = normZ;

			verticesData[i].bitangent.x = binormX;
			verticesData[i].bitangent.y = binormY;
			verticesData[i].bitangent.z = binormZ;

			verticesData[i].tangent.x = binormX;
			verticesData[i].tangent.y = binormY;
			verticesData[i].tangent.z = binormZ;

			verticesData[i].uv.x = uvX;
			verticesData[i].uv.y = uvY;
		}
		std::getline(ss, strtmp, '\n');

		rs = sscanf(strtmp.c_str(), "NrIndices: %d", &m_iNumIndices);
		Indices = new GLuint[m_iNumIndices];
		GLuint a, b, c;
		for (GLuint i = 0; i < m_iNumIndices / 3; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf(strtmp.c_str(), " %*d.  %d,  %d,  %d", &a, &b, &c);
			Indices[3 * i + 0] = a;
			Indices[3 * i + 1] = b;
			Indices[3 * i + 2] = c;
		}
	}

	//buffer object
	glGenBuffers(1, &m_iVboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVboID);
	glBufferData(GL_ARRAY_BUFFER, iNumVertex * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//if(m_iIboID == 0)
	{
		glGenBuffers(1, &m_iIboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iNumIndices * sizeof(GLuint), Indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	modelFile.close();
	LOGI("Done.\n");
}


Models::~Models()
{
}

GLuint Models::GetVertexObject()
{
	return m_iVboID;
}
GLuint Models::GetIndiceObject()
{
	return m_iIboID;
}
GLuint Models::GetNumIndiceObject()
{
	return m_iNumIndices;
}
void Models::SetModelId(GLuint id)
{
	m_iModelID = id;
}
GLuint Models::GetModelId()
{
	return
		m_iModelID;
}