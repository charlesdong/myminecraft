#include "program.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;

const GLenum PROGRAM = 0;

Program::Program()
{
}

void Program::load(const char * vPath, const char * fPath)
{
	const char * vCode = readFile(vPath);
	const char * fCode = readFile(fPath);
	unsigned int vShader = makeShader(vCode, GL_VERTEX_SHADER);
	unsigned int fShader = makeShader(fCode, GL_FRAGMENT_SHADER);
	makeProgram(vShader, fShader);
}

unsigned int Program::makeShader(const char * code, GLenum type) const
{
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	if (!checkErrors(shader, type))
	{
		const char * log = getInfoLog(shader, type);
		cout << "ERROR: Shader compilation failed, type: " << getTypeName(type) << ", info log:\n" << log << endl;
		delete[] log;
	}
	return shader;
}

void Program::makeProgram(unsigned int vShader, unsigned int fShader)
{
	prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);
	if (!checkErrors(prog, PROGRAM))
	{
		const char * log = getInfoLog(prog, PROGRAM);
		cout << "ERROR: Program linking failed, info log:\n" << log << endl;
		delete[] log;
	}
}

const char * Program::readFile(const char * path) const
{
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
		cout << "ERROR: Unable to open shader file " << path << " (maybe not exist)\n";
	int size;
	fin.seekg(0, ios_base::end);
	size = (int)fin.tellg();		// returns a std::streamoff value, convert to int
	fin.seekg(0, ios_base::beg);
	char * content = new char[size + 1]{ '\0' };
	size = 0;
	char ch = fin.get();
	while (ch != EOF)
	{
		content[size] = ch;
		size++;
		ch = fin.get();
	}
	return content;
}

bool Program::checkErrors(unsigned int id, GLenum type) const
{
	int status;
	if (type != PROGRAM)
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	else
		glGetProgramiv(id, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

const char * Program::getInfoLog(unsigned int id, GLenum type) const
{
	char * log;
	int len;
	if (type != PROGRAM)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		log = new char[len + 1];
		glGetShaderInfoLog(id, len + 1, nullptr, log);
	}
	else
	{
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
		log = new char[len + 1];
		glGetProgramInfoLog(id, len + 1, nullptr, log);
	}
	return log;
}

const char * Program::getTypeName(GLenum type) const
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return "VERTEX";
	case GL_FRAGMENT_SHADER:
		return "FRAGMENT";
	default:
		return "UNKNOWN";
	}
}