BD3GE
===

Let's build a game from the ground up. Rendering, physics, audio, input - all of that good stuff.

**TODO:**

* Libraries to consider adding:
	* OpenGL-FreeType (OGLFT) or implement my own very simple text rendering.
* Finish Matrix4 inverse functionality.
* Encapsulate GL stuff into a more general Video class.
* Encapsulate AL/OGG stuff into a more general Audio class. 
* More commenting!
* Support file I/O paths driven by environment variables.
* Add arbitraryily-sized matrices?
* Settle on some styling conventions.
* Try to remove log global? Put it in Game?
* I need a Material class to represent visual information about surfaces, and this class should have its own Shader.
* Rework "scene" so that it's not so heavy on game logic
* Make config dynamically-loaded from a file, rather than hardcoded in constants
* Input:
    * Add custom mapping
	* Add DirectInput support

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