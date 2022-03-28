# math library configuration

add_library(math INTERFACE)

#set_target_properties(math PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::math ALIAS math )

target_include_directories( math INTERFACE include/ )

target_link_libraries( math INTERFACE project_options )

# Executable program configuration
add_executable(hello-math hello-math.cpp)

target_include_directories(hello-math PRIVATE include/)

target_link_libraries(
	hello-math 
	PRIVATE 
		project_options 
		radiance::window
		radiance::shader
		radiance::drawable
		radiance::texture
		glm::glm
)

