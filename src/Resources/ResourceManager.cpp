#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& exec_path)
{
	size_t found = exec_path.find_last_of("/ \\");
	m_path = exec_path.substr(0, found);
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
	std::shared_ptr<Renderer::ShaderProgram> result = ShaderProgramMap.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (result->IsCompiled())
	{
		return result;
	}
	std::cerr << "Cant load shader program:\n" << "Vertex: " << vertexPath << '\n' << "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shaderName)
{
	ShaderMap::const_iterator it = ShaderProgramMap.find(shaderName);
	if (it != ShaderProgramMap.end())
	{
		return it->second;
	}
	std::cerr << "Cant find shader program: " << shaderName << std::endl;
	return nullptr;
}

std::string ResourceManager::GetFileString(const std::string& file_path) const
{
	std::ifstream in;
	in.open(m_path + '/' + file_path, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << in.rdbuf();
	return buffer.str();
}
