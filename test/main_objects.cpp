#include <interpreter.hpp>

#include <catch.hpp>

extern std::string classpath;

static bool classPathHasBeenSet = false;

TEST_CASE( "Create a JAVA interpreter instance", "[interpreter]" )
{
  if (!classPathHasBeenSet)
  {
    Java::Interpreter::setClassPath(classpath);
    classPathHasBeenSet = true;
  }
  Java::Interpreter& interpreter = Java::Interpreter::getInstance();

  SECTION ( "Check interpreter version" )
  {
    REQUIRE( interpreter.getVersionMajor() == 1 );
    REQUIRE( interpreter.getVersionMinor() == 8 );
  }

  SECTION ( "Getting a class representation" )
  {
    Java::Class clazz = interpreter.getClass("MyTest");
  }
}

