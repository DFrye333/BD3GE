#include "cubemap.h"

namespace BD3GE {
	Cubemap::Cubemap(std::string cubemap_directory_path) {
		g_log->write(Log::TYPE::INFO, "Cubemap loading: " + cubemap_directory_path);

		this->renderable_id = TextureManager::load_cubemap(cubemap_directory_path);

		const size_t skybox_shader_id = ShaderManager::get_shader_id(ShaderManifest("skybox.vert", "skybox.frag"));

		Transform cube_face_transform;

		unsigned short size = 10000;

		cube_face_transform.set_position(Vector3(0.5f * size, 0, 0));
		cube_face_transform.set_orientation_y(-BD3GE::PI / 2);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::RIGHT), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));

		cube_face_transform.set_position(Vector3(-0.5f * size, 0, 0));
		cube_face_transform.set_orientation_y(BD3GE::PI / 2);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::LEFT), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));

		cube_face_transform.set_position(Vector3(0, 0.5f * size, 0));
		cube_face_transform.set_orientation_x(BD3GE::PI / 2);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::TOP), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));

		cube_face_transform.set_position(Vector3(0, -0.5f * size, 0));
		cube_face_transform.set_orientation_x(-BD3GE::PI / 2);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::BOTTOM), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));

		cube_face_transform.set_position(Vector3(0, 0, 0.5f * size));
		cube_face_transform.set_orientation_y(BD3GE::PI);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::BACK), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));

		cube_face_transform.set_position(Vector3(0, 0, -0.5f * size));
		cube_face_transform.set_orientation_y(0);
		renderable_units.emplace_back(new RectangleBrush(new CubeMappedMaterial(skybox_shader_id, this->renderable_id, CubeMappedMaterial::FACE::FRONT), 1.0f * size, 1.0f * size, new TransformNode{ nullptr, cube_face_transform }));
	}
}