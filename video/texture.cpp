#include "texture.h"

namespace BD3GE {
	Texture::Texture(std::string textureFilePath) : width(0), height(0), quantityChannels(0), data(NULL) {
		this->desiredQuantityChannels = 0; // All channels
		this->data = stbi_load(textureFilePath.c_str(), &this->width, &this->height, &this->quantityChannels, this->desiredQuantityChannels);
		if (!this->data) {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Texture load failure: " + std::string(textureFilePath));
		}
	}

	Texture::~Texture() {
		stbi_image_free(data);
	}
}