#include "ShaderProgram.h"
#include <iostream>


namespace Renderer {
	ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	{
		m_ID_ = std::move(other.m_ID_);
		m_isCompiled_ = std::move(other.m_isCompiled_);

		other.m_ID_ = 0;
		other.m_isCompiled_ = false;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
	{
		glDeleteProgram(m_ID_);
		m_ID_ = std::move(other.m_ID_);
		m_isCompiled_ = std::move(other.m_isCompiled_);

		other.m_ID_ = 0;
		other.m_isCompiled_ = false;

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
		m_ID_= glCreateProgram();
		glAttachShader(m_ID_, vertexShaderID);
		glAttachShader(m_ID_, fragmentShaderID);
		glLinkProgram(m_ID_);


		GLint success;
		glGetProgramiv(m_ID_, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID_, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infolog << std::endl;
			
		}
		else
		{
			m_isCompiled_ = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	
	

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID_);
	}

	bool ShaderProgram::IsCompiled() const
	{
		return m_isCompiled_;
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_ID_);
	}

	void ShaderProgram::SetInt(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(m_ID_, name.c_str()), value);
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