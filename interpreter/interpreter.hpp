#pragma once

#include <jni.h>

#include <string>
#include <cstdint>

namespace Java
{

  class Object
  {
  };

  class Class
  {
    public:
      Class(std::string const& className, JNIEnv* env);
      virtual ~Class() {}

      Object getInstance(void) const;

    private:
      JNIEnv* env;
      jclass clazz;
      jmethodID ctor;
  };

  class Interpreter
  {
    public:
      static void setClassPath(std::string const& cp);
      static Interpreter& getInstance(void);

      virtual ~Interpreter();

      uint8_t getVersionMajor() const;
      uint8_t getVersionMinor() const;

      Class getClass(std::string const& className) const;

    private:
      explicit Interpreter();
      Interpreter(const Interpreter&);
      Interpreter& operator = (const Interpreter&);

      static std::string classpath;
      JavaVM *jvm;
      JNIEnv *env;
  };

}
