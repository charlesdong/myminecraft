#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOCATION glGetUniformLocation(prog, name)

// shader program
class Program
{
private:
	unsigned int prog;

	unsigned int makeShader(const char * code, GLenum type) const;
	void makeProgram(unsigned int vShader, unsigned int fShader);
	const char * readFile(const char * path) const;
	bool checkErrors(unsigned int id, GLenum type) const;
	const char * getInfoLog(unsigned int id, GLenum type) const;
	const char * getTypeName(GLenum type) const;
public:
	Program();
	void load(const char * vPath, const char * fPath);

	void use() const
	{
		glUseProgram(prog);
	}

	void clear() const
	{
		glDeleteProgram(prog);
	}

	void setVec3f(const char * name, const glm::vec3 & vec) const
	{
		glUniform3fv(LOCATION, 1, glm::value_ptr(vec));
	}

	void setMat3f(const char * name, const glm::mat3 & mat) const
	{
		glUniformMatrix3fv(LOCATION, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void setMat4f(const char * name, const glm::mat4 & mat) const
	{
		glUniformMatrix4fv(LOCATION, 1, GL_FALSE, glm::value_ptr(mat));
	}
};

#endif