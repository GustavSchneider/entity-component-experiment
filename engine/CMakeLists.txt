set ( FILES
  base_component.cpp
  mesh_renderer_component.cpp
  mesh_renderer_system.cpp
  mesh_component.cpp
  mesh_system.cpp
  transform_system.cpp
  message_handler.cpp
  message_system.cpp
  camera_component.cpp
  camera_system.cpp
  scene.cpp
  )
add_library (engine STATIC ${FILES})
include_directories(../gl ../libs/glm)
