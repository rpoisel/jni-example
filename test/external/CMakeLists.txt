add_library(Catch2 INTERFACE)

target_include_directories(Catch2 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/Catch2/single_include
)
