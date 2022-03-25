add_library(texture INTERFACE)

#set_target_properties(texture PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::texture ALIAS texture )

target_include_directories( texture INTERFACE include/ )

target_link_libraries( texture INTERFACE project_options glad::glad stb::stb)
