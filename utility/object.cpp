#include "object.h"

namespace BD3GE {
	/*
	 *	Object class
	 */

	Object::Object() {}

	Object::Object(const Vector3 position, const Vector3 color, const Vector3 velocity, const aiMesh* mesh) {
		// Initialize position attributes.
		m_position.v.g.x = position.v.g.x;
		m_position.v.g.y = position.v.g.y;
		m_position.v.g.z = position.v.g.z;

		// Initialize color attributes.
		m_color.v.c.r = color.v.c.r;
		m_color.v.c.g = color.v.c.g;
		m_color.v.c.b = color.v.c.b;

		// Initialize velocity attributes.
		m_velocity.v.g.x = velocity.v.g.x;
		m_velocity.v.g.y = velocity.v.g.y;
		m_velocity.v.g.z = velocity.v.g.z;

		m_angle = 0.0;

		m_world_transform.translate(m_position);

		this->mesh = new Mesh(mesh);

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// m_OGG = new Ogg(fileName);
		// m_OGG->play();

		shader = new Shader();

		setup();
	}

	Object::~Object() {
		delete mesh;
		mesh = NULL;

		delete shader;
		shader = NULL;
	}

	void Object::setup() {
		// Generate VAO.
		glGenVertexArrays(1, &vao);

		// Generate VBOs.
		glGenBuffers(1, &vboPosition);
		glGenBuffers(1, &iboPosition);

		// Setup for VAO.
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
		glBufferData(GL_ARRAY_BUFFER, 4 * mesh->m_num_vertices * sizeof(GLfloat), mesh->m_vertex_position_buffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPosition);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_num_indices * sizeof(GLuint), mesh->m_index_position_buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		// Cleanup for VAO.
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Object::move(void) {
		m_position.v.g.x += m_velocity.v.g.x;
		m_position.v.g.y += m_velocity.v.g.y;
		m_position.v.g.z += m_velocity.v.g.z;

		m_world_transform.translate(m_position);
	}

	void Object::scale(float scaler) {
		m_world_transform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		m_world_transform.rotate(rotation);
	}

	void Object::render(Transform view_projection_transform) {
		// Setup for shader program.
		glUseProgram(shader->get_program_ID());

		GLfloat transformation_array[16];
		Transform worldViewProjectionTransform = view_projection_transform * m_world_transform;
		worldViewProjectionTransform.to_float_array(transformation_array);

		glUniformMatrix4fv(glGetUniformLocation(shader->get_program_ID(), "transformation_matrix"), 1, GL_TRUE, transformation_array);

		// Update position.
		glUniform3f(glGetUniformLocation(shader->get_program_ID(), "offset"), worldViewProjectionTransform(3, 0), worldViewProjectionTransform(3, 1), worldViewProjectionTransform(3, 2));

		glUniform4f(glGetUniformLocation(shader->get_program_ID(), "in_color"), m_color.v.c.r, m_color.v.c.g, m_color.v.c.b, 1.0f);

		// Draw mesh using its VAO.
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, mesh->m_num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		glUseProgram(0);
	}

	void Object::set_velocity_X(float x) {
		m_velocity.v.g.x = x;
	}

	void Object::set_velocity_Y(float y) {
		m_velocity.v.g.y = y;
	}

	void Object::set_velocity_Z(float z) {
		m_velocity.v.g.z = z;
	}

	void Object::set_velocity(float x, float y, float z) {
		set_velocity_X(x);
		set_velocity_Y(y);
		set_velocity_Z(z);
	}

	void Object::set_velocity(Vector3 velocity) {
		m_velocity = velocity;
	}

	void Object::add_velocity_X(float x) {
		if (PLAYER_SPEED >= m_velocity.v.g.x && -PLAYER_SPEED <= m_velocity.v.g.x) {
			m_velocity.v.g.x += x;
		}
	}

	void Object::add_velocity_Y(float y) {
		if (PLAYER_SPEED >= m_velocity.v.g.y && -PLAYER_SPEED <= m_velocity.v.g.y) {
			m_velocity.v.g.y += y;
		}
	}

	void Object::add_velocity_Z(float z) {
		m_velocity.v.g.z += z;
	}
}
