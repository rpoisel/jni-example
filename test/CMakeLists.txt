add_subdirectory(java)
add_subdirectory(external)

add_executable(ObjectsApp
  main_objects.cpp
  main_catch2.cpp
)
 
target_link_libraries(ObjectsApp
  interpreter
  Catch2
)

get_target_property(MyTestJarFile MyTest JAR_FILE)
add_test(NAME ObjectsTest COMMAND $<TARGET_FILE:ObjectsApp> --classpath ${MyTestJarFile})
