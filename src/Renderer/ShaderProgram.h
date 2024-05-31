#pragma once
#include <string>
#include <glad/glad.h>

namespace Renderer {

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertextShader, std::string& fragmentShader);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram& operator=(ShaderProgram&& other) noexcept;
		~ShaderProgram();

		bool IsCompiled() const;

		void Use() const;

		void SetInt(const std::string& name, const GLint value);

	private:

		bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

		bool m_isCompiled_ = false;
		GLuint m_ID_ = 0; 
	};
}//end namespace Rederer