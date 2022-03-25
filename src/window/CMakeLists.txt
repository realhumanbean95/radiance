# window library configuration

add_library(window INTERFACE)

#set_target_properties(window PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::window ALIAS window )

target_include_directories( window INTERFACE include/ )

target_link_libraries( window INTERFACE project_options glfw::glfw glad::glad )