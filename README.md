BD3GE
===

Let's build a game from the ground up. Rendering, physics, audio - all of that good stuff.

**TODO:**

* Libraries to consider adding:
	* OpenGL-FreeType (OGLFT) or implement my own very simple text rendering.
	* Open Asset Import Library (Assimp)
* Finish Matrix4 inverse functionality.
* Encapsulate GL stuff into a more general Video class.
* Encapsulate AL/OGG stuff into a more general Audio class. 
* More commenting!
* Support file I/O paths driven by environment variables.
* Add arbitraryily-sized matrices?
* Convert all camel-case to underscore.
* Try to remove log global? Put it in Game?
* Move constructor initialization from body to initializer lists where possible.
* I need a Material class to represent visual information about surfaces, and this class should have its own Shader.
* Add "this" keyword where it makes sense to do so.

**Linux Installation Dependencies:**

* Packages:
	* Core:
		* mesa-common-dev
		* libglew-dev
		* libopenal-dev
		* libogg-dev
		* libvorbis-dev
		* assimp-dev
	* Extra:
		* freeglut3-dev

* Linked Libraries:
	* -lGL
	* -lGLU
	* -lGLEW
	* -lX11
	* -lopenal
	* -logg
	* -lvorbis
	* -lvorbisfile