# drawable library configuration

add_library(drawable INTERFACE)

#set_target_properties(drawable PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::drawable ALIAS drawable )

target_include_directories( drawable INTERFACE include/ )

target_link_libraries( drawable INTERFACE project_options glad::glad radiance::shader radiance::texture )