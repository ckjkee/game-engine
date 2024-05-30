#pragma once

#include <string>
#include <memory>
#include <map>



namespace Renderer {
	class ShaderProgram;
}

class ResourceManager
{
public:
	using ShaderMap = std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>;

	ResourceManager(const std::string& exec_path);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName);

private:
    std::string GetFileString(const std::string& file_path) const;

	ShaderMap ShaderProgramMap;
	std::string m_path;
};