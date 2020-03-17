#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "lightning.h"

Shader::Shader() {
	const char* vertexShaderSource = R"(#version 330 core
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec2 aTexCoord;
	//layout(location = 1) in vec3 aColor;

	//out vec3 ourColor;
	out vec2 TexCoord;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(aPos, 1.0);
		//gl_Position = vec4(aPos, 1.0);
		//ourColor = aColor;
		TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	}
	)";

	const char* fragmentShaderSource = R"(#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;
	
	uniform sampler2D texture1;
	uniform sampler2D texture2;
	//uniform vec4 vertexColor;
	//out vec4 vertexColor;

	void main()
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
		//FragColor = vertexColor;
		//vertexColor = vec4(1.0,0.0,0.0,1.0);
	}
	)";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success = 0;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

void Shader::useProgram() {
	glUseProgram(shaderProgram);
}

//void Shader::settingTex(string tex, int ind) {
//	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), ind);
//	//glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 1);
//}

void Shader::settingTex() {
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
}

void Shader::setModelMatrix(const glm::mat4 &m) {
	auto location = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setViewMatrix(const glm::mat4 &v) {
	auto location = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(v));
}

//void Shader::setColor() {
//	glUniform4f(glGetUniformLocation(shaderProgram, "vertexColor"),1.0, 0.0, 0.0, 1.0f);
//}

void Shader::settingMatrix(const glm::mat4 &p){
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &p[0][0]);
}

Buffer::Buffer(const vector<float>& _vertices, const vector<int>& _indices) {
	unsigned VBO, EBO;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(float), _indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindVertexArray(0);
}

void Buffer::bind() {
	glBindVertexArray(vao);
}

Buffer::~Buffer(){
	glDeleteVertexArrays(1, &vao);
}

//Texture::Texture(const char& info)
//	:path(info)
//{ }

unsigned int buildTexture(const char* path){
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// setting the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// setting texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (nrChannels == 3) {
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else{
			std::cout << "Failed to load texture" << std::endl;
		}
	}

	else {
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_set_flip_vertically_on_load(true);
	}

	stbi_image_free(data);

	return texture;
}