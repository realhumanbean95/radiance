# math library configuration

add_library(math INTERFACE)

#set_target_properties(math PROPERTIES LINKER_LANGUAGE CXX)

add_library( radiance::math ALIAS math )

target_include_directories( math INTERFACE include/ )

target_link_libraries( math INTERFACE project_options glm::glm)

