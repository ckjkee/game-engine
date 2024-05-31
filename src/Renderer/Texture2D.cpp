#include "Texture2D.h"
namespace Renderer
{
	Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int channels, const GLenum filter, const GLenum wrapMode)
		:t_width_(width), t_height_(height)
	{
		switch (channels)
		{
		case 4:
			t_mode_ = GL_RGBA;
			break;
		case 3:
			t_mode_ = GL_RGB;
			break;
		default:
			t_mode_ = GL_RGBA;
			break;
		}
		glGenTextures(1, &t_ID_);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t_ID_);
		glTexImage2D(GL_TEXTURE_2D, 0, t_mode_, t_width_, t_height_, 0, t_mode_, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(Texture2D&& rhs) noexcept
	{
		t_ID_ = std::move(rhs.t_ID_);
		t_mode_ = std::move(rhs.t_mode_);
		t_width_ = std::move(rhs.t_width_);
		t_height_ = std::move(rhs.t_height_);
	}

	Texture2D& Texture2D::operator=(Texture2D&& rhs) noexcept
	{
		t_ID_ = std::move(rhs.t_ID_);
		t_mode_ = std::move(rhs.t_mode_);
		t_width_ = std::move(rhs.t_width_);
		t_height_ = std::move(rhs.t_height_);
		return *this;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &t_ID_);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, t_ID_);
	}
}//Renderer namespace end

