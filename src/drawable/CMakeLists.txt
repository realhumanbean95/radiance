# drawable library configuration

add_library(drawable INTERFACE)

#set_target_properties(drawable PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::drawable ALIAS drawable )

target_include_directories( drawable INTERFACE include/ )

target_link_libraries( drawable INTERFACE project_options glfw::glfw glad::glad )


# Executable program configuration
add_executable(hello-drawable hello-drawable.cpp)

target_include_directories(hello-drawable PRIVATE include/)

target_link_libraries(
	hello-drawable 
	PRIVATE 
		project_options 
		glfw::glfw 
		glad::glad
		radiance::shader
)