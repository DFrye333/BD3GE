BD3GE
===

Let's build a game from the ground up. Rendering, physics, audio, input - all of that good stuff.

**TODO:**

* Libraries to consider adding:
	* OpenGL-FreeType (OGLFT) or implement my own very simple text rendering.
* More commenting!
* Try to remove log global? Put it in Game?
* Make config dynamically-loaded from a file, rather than hardcoded in constants
* Input:
	* Add custom mapping
	* Add DirectInput support
	* Add debouncing
* Build out wider/universal support for class member ownership (e.g. Renderable.owns_shader)?
* Implement SSE support for math.
* Convert std::string params to std::string& as appropriate?
* Convert static libs to dynamic where as appropriate.
* Replace std::map usages with a custom hash table?
* Start thinking about DOD:
    * Integrate slot maps where possible (in-progress).
* Add an orthogonal camera mode.
* Create a wrapper for the brushes.

**Linux Installation Dependencies:**

* Packages:
	* Core:
		* mesa-common-dev
		* libglew-dev
		* libopenal-dev
		* libogg-dev
		* libvorbis-dev
		* assimp-dev

* Linked Libraries:
	* -lGL
	* -lGLU
	* -lGLEW
	* -lX11
	* -lopenal
	* -logg
	* -lvorbis
	* -lvorbisfile