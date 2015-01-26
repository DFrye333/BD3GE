Game Prototype 0
=

Let's build a game from the ground up. Rendering, physics, audio - all of that good stuff.

**TODO:**

* Finish Matrix4 inverse functionality.
* Consider moving away from a single monolithic master include file.
* Implement system logging.
* The majority of the rendering code currently lives in the physics/ directory. I need to figure that out. Maybe move object.h/object.cpp to utility/ and object::render() into the Shader class? I need to create a Scene class at some point to group together all scene objects, and render from there. Reference Coaster code more.
* Encapsulate OGG stuff into a more general Audio class. 
* More commenting!