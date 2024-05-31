#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class Texture2D {
	public:
		Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
				  const unsigned int channels = 4, 
			      const GLenum filter = GL_NEAREST, 
			      const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D(Texture2D&& rhs) noexcept;
		Texture2D& operator=(Texture2D&& rhs) noexcept;
		~Texture2D();

		void Bind() const;
	private:
		GLuint t_ID_;
		GLenum t_mode_;
		unsigned int t_width_;
		unsigned int t_height_;

	};
}//end of Renderer namespace