## v0.1.0 (2023-10-20)

### Feat

- **object3d**: added static method to create Object3D from file
- **engine.hpp**: added new headers
- **object.hpp**: Entity is now a friend class
- **object3d**: added object3d
- **object**: added abstract class Object
- added one more abstraction level in mesh
- added m26 model
- **window**: added set_color using Color
- **model**: allow user to choose a default color for model
- **sphere.obj**: added sphere 3D object

### Fix

- **entity**: assert expr
- **object3d**: error when callign constructor Object3D()
- using GMesh instead of Mesh now
- **window.cpp**: minor error
- deleted docs
- using glFlush instead of SwapBuffers
- indices, now it's possible to use culling
- hand model removed and renamed indoali
- **def_fragment_shader.glsl**: fixed alpha attrib of temp_frag_color when doing specular light
- specular light bug when not loading specular map from material
- **engine.hpp**: added missing headers
- **object2d.cpp**: drawing simple mesh without disabling GL_CULL_FACE
- **def_fragment_shader.glsl**: lighting when the mesh isn't textured
- code style for namespace

### Refactor

- removed some warnings
- **object2d**: matrix is now obrigatory
- **window**: using delta t as default in Window::process_input
- **entity**: added polymorphism with Object class
- **model**: minor change in constructor and moved some member to protected
- using initializer lists
- **object2d**: now object2d inherit from Mesh
- **vao.cpp**: changed method param name
- fixed fps to 60
- removed unused header
- fixed mistyping
- **window.cpp**: removing the 60 fps "limit"
- **camera**: using delta V as one of the parameters for calculate the movement
- changed some things in floor scale
- using projection and view uniforms instead of the whole camera
- processing camera matrix inside shader
- removed warning
- removed glDisable(GL_CULL_FACE) when rendering simple meshes
- removed and added some headers
- using other file to do assimp things
- **main.cpp**: small changes
- **window**: Removed main_loop because it was not being used
- **mesh.hpp**: turn some members to private
- **main.cpp**: using inheritance and implemented main_loop as it was in window.cpp
- **window**: removed the code from main_loop
