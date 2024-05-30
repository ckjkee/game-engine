#pragma once
#include <string>
#include <glad/glad.h>

namespace Renderer {

	class ShaderProgram
	{
	public:

		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram&) = delete;

		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram(ShaderProgram&& other) noexcept;

		ShaderProgram& operator=(ShaderProgram&& other) noexcept;

		ShaderProgram(const std::string& vertextShader, std::string& fragmentShader);

		~ShaderProgram();

		bool IsCompiled() const;

		void Use() const;

	private:

		bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

		bool m_isCompiled = false;
		GLuint m_ID = 0; 
	};
}//end namespace Rederer