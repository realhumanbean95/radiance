
# shader library configuration

add_library(shader INTERFACE)

#set_target_properties(shader PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::shader ALIAS shader )

target_include_directories( shader INTERFACE include/ )

target_link_libraries( shader INTERFACE project_options glfw::glfw glad::glad )


# Executable program configuration
add_executable(hello-shader hello-shader.cpp)

target_include_directories(hello-shader PRIVATE include/)

target_link_libraries( hello-shader PRIVATE project_options glfw::glfw glad::glad)
