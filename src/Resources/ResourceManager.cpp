#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& exec_path)
{
	size_t found = exec_path.find_last_of("/ \\");
	m_path_ = exec_path.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = GetFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}
	std::string fragmentString = GetFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::ShaderProgram> result = ShaderProgramMap_.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (result->IsCompiled())
	{
		return result;
	}
	std::cerr << "Cant load shader program:\n" << "Vertex: " << vertexPath << '\n' << "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shaderName)
{
	ShaderMap::const_iterator it = ShaderProgramMap_.find(shaderName);
	if (it != ShaderProgramMap_.end())
	{
		return it->second;
	}
	std::cerr << "Cant find shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath) 
{
	int channels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path_ + '/' + texturePath).c_str(), &width, &height,&channels,0);

	if (!pixels)
	{
		std::cerr << "Cant load image!" << texturePath << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture2D> new_texture = textures_.emplace(textureName, std::make_shared<Renderer::Texture2D>
		(width, 
		height, 
		pixels,
		channels, 
		GL_NEAREST,
		GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return new_texture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture(const std::string& textureName)
{
	TextureMap::const_iterator it = textures_.find(textureName);
	if (it != textures_.end())
	{
		return it->second;
	}
	std::cerr << "Cant find texture: " << textureName << std::endl;
	return nullptr;
}

std::string ResourceManager::GetFileString(const std::string& file_path) const
{
	std::ifstream in;
	in.open(m_path_ + '/' + file_path, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << in.rdbuf();
	return buffer.str();
}
