cmake_minimum_required(VERSION 3.6)
project(jni-example CXX)

# make sure to set JAVA_HOME properly, e. g.
# export JAVA_HOME=/usr/lib/jvm/java-8-oracle
find_package(JNI)

add_executable(jni_example
  main.cpp
)

target_link_libraries(jni_example PUBLIC
  ${JNI_LIBRARIES}
)

target_include_directories(jni_example PUBLIC
  ${JNI_INCLUDE_DIRS}
)
