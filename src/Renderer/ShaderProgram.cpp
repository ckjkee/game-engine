#include "ShaderProgram.h"
#include <iostream>


namespace Renderer {
	ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	{
		m_ID = std::move(other.m_ID);
		m_isCompiled = std::move(other.m_isCompiled);

		other.m_ID = 0;
		other.m_isCompiled = false;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = std::move(other.m_ID);
		m_isCompiled = std::move(other.m_isCompiled);

		other.m_ID = 0;
		other.m_isCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(const std::string& vertexShader, std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "Fragment Shader compile time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);


		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infolog << std::endl;
			
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	
	

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	bool ShaderProgram::IsCompiled() const
	{
		return m_isCompiled;
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_ID);
	}

	bool ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << infolog << std::endl;
			return false;
		}
		return true;
	}
}//end of Renderer