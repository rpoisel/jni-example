# make sure to set JAVA_HOME properly, e. g.
# export JAVA_HOME=/usr/lib/jvm/java-8-oracle
find_package(JNI)

add_library(interpreter SHARED
  interpreter.cpp
)

target_link_libraries(interpreter PRIVATE
  ${JNI_LIBRARIES}
)

target_include_directories(interpreter PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${JNI_INCLUDE_DIRS}
)
