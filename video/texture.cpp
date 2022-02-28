#include "texture.h"

namespace BD3GE {
	Texture::Texture() : data(nullptr), width(0), height(0), quantity_channels(0), desired_quantity_channels(0) {}

	Texture::Texture(std::string texture_file_path) : Texture() {
		this->desired_quantity_channels = 0; // All channels
		// TODO: Solve the issue of shared textures - don't want a separate load for umpteen identical textures
		this->data = stbi_load(texture_file_path.c_str(), &this->width, &this->height, &this->quantity_channels, this->desired_quantity_channels);
		if (this->data == nullptr) {
			g_log.write(Log::TYPE::ERR, "Texture load failure: " + std::string(texture_file_path));
			return;
		}
		g_log.write(Log::TYPE::INFO, "Texture load success: " + std::string(texture_file_path));
	}

	Texture::Texture(Texture& other) : Texture() {
		*this = other;
	}

	Texture::~Texture() {
		stbi_image_free(data);
		data = nullptr;
	}

	Texture& Texture::operator=(Texture& other) {
		this->width = other.width;
		this->height = other.height;
		this->quantity_channels = other.quantity_channels;
		this->desired_quantity_channels = other.desired_quantity_channels;
		if (other.data) {
			stbi_image_free(this->data);
			size_t data_size = get_data_size();
			this->data = new unsigned char[data_size];
			std::memcpy(this->data, other.data, data_size);
		}

		return *this;
	}

	size_t Texture::get_data_size() {
		return (size_t)width * (size_t)height * (size_t)quantity_channels;
	}
}