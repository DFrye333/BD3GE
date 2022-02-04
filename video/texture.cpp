#include "texture.h"

namespace BD3GE {
	Texture::Texture(std::string textureFilePath) : Texture(GL_TEXTURE0, textureFilePath) {}

	Texture::Texture(int textureId, std::string textureFilePath) : width(0), height(0), quantity_channels(0), data(nullptr), textureId(textureId) {
		this->desired_quantity_channels = 0; // All channels
		// TODO: Solve the issue of shared textures - don't want a separate load for umpteen identical textures
		this->data = stbi_load(textureFilePath.c_str(), &this->width, &this->height, &this->quantity_channels, this->desired_quantity_channels);
		if (this->data == nullptr) {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Texture load failure: " + std::string(textureFilePath));
			return;
		}
		g_log.write(BD3GE::LOG_TYPE::INFO, "Texture load success: " + std::string(textureFilePath));

		glGenTextures(1, &this->tboHandle);

		glActiveTexture(GL_TEXTURE0 + this->textureId);
		glBindTexture(GL_TEXTURE_2D, this->tboHandle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint format = 0;
		switch (quantity_channels) {
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture() {
		stbi_image_free(data);
		data = nullptr;
	}
}