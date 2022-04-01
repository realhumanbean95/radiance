# camera library configuration

add_library(camera INTERFACE)

#set_target_properties(camera PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::camera ALIAS camera )

target_include_directories( camera INTERFACE include/ )

target_link_libraries( camera INTERFACE project_options
	radiance::math )