#include "object.h"

namespace BD3GE {
	/*
	 *	Object class
	 */

	Object::Object() {}

	Object::Object(const Vector3 position, const Color color, const Vector3 velocity, const Drawable* drawable) {
		this->position.v.g.x = position.v.g.x;
		this->position.v.g.y = position.v.g.y;
		this->position.v.g.z = position.v.g.z;

		this->color = color;

		this->velocity.v.g.x = velocity.v.g.x;
		this->velocity.v.g.y = velocity.v.g.y;
		this->velocity.v.g.z = velocity.v.g.z;

		angle = 0.0;

		worldTransform.translate(this->position);

		this->drawable = drawable;

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// m_OGG = new Ogg(fileName);
		// m_OGG->play();

		shader = new Shader();

		setup();
	}

	Object::~Object() {
		delete drawable;
		drawable = NULL;

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
		glBufferData(GL_ARRAY_BUFFER, 4 * drawable->numVertices * sizeof(GLfloat), drawable->vertexPositionBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPosition);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawable->numIndices * sizeof(GLuint), drawable->indexPositionBuffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		// Cleanup for VAO.
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Object::move(void) {
		this->position.v.g.x += velocity.v.g.x;
		this->position.v.g.y += velocity.v.g.y;
		this->position.v.g.z += velocity.v.g.z;

		worldTransform.translate(position);
	}

	void Object::scale(float scaler) {
		worldTransform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		worldTransform.rotate(rotation);
	}

	void Object::render(Transform view_projection_transform) {
		// Setup for shader program.
		glUseProgram(shader->get_program_ID());

		GLfloat transformation_array[16];
		Transform worldViewProjectionTransform = view_projection_transform * worldTransform;
		worldViewProjectionTransform.to_float_array(transformation_array);

		glUniformMatrix4fv(glGetUniformLocation(shader->get_program_ID(), "transformation_matrix"), 1, GL_TRUE, transformation_array);

		// Update position.
		glUniform3f(glGetUniformLocation(shader->get_program_ID(), "offset"), worldViewProjectionTransform(3, 0), worldViewProjectionTransform(3, 1), worldViewProjectionTransform(3, 2));

		glUniform4f(glGetUniformLocation(shader->get_program_ID(), "in_color"), color.rgb.v.c.r, color.rgb.v.c.g, color.rgb.v.c.b, color.a);

		// Draw mesh using its VAO.
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, drawable->numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		glUseProgram(0);
	}

	void Object::set_velocity_X(float x) {
		velocity.v.g.x = x;
	}

	void Object::set_velocity_Y(float y) {
		velocity.v.g.y = y;
	}

	void Object::set_velocity_Z(float z) {
		velocity.v.g.z = z;
	}

	void Object::set_velocity(float x, float y, float z) {
		set_velocity_X(x);
		set_velocity_Y(y);
		set_velocity_Z(z);
	}

	void Object::set_velocity(Vector3 velocity) {
		velocity = velocity;
	}

	void Object::add_velocity_X(float x) {
		if (PLAYER_SPEED >= velocity.v.g.x && -PLAYER_SPEED <= velocity.v.g.x) {
			velocity.v.g.x += x;
		}
	}

	void Object::add_velocity_Y(float y) {
		if (PLAYER_SPEED >= velocity.v.g.y && -PLAYER_SPEED <= velocity.v.g.y) {
			velocity.v.g.y += y;
		}
	}

	void Object::add_velocity_Z(float z) {
		velocity.v.g.z += z;
	}
}
