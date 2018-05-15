/**
 * https://www.codeproject.com/articles/993067/calling-java-from-cplusplus-with-jni
 */

#include <interpreter.hpp>

#include <string>
#include <stdexcept>

  /*
  using namespace std;
  JNIEnv *env;
  JavaVMInitArgs vm_args;
  string optionClassPath = "-Djava.class.path=";
  optionClassPath += argv[1];
  JavaVMOption options;
  options.optionString = &optionClassPath[0u];
  vm_args.version = JNI_VERSION_1_6;
  vm_args.nOptions = 1;
  vm_args.options = &options;
  vm_args.ignoreUnrecognized = false;

  jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
  if (rc != JNI_OK) {
    // TO DO: error processing... 
    cin.get();
    exit(EXIT_FAILURE);
  }
  cout << "JVM load succeeded: Version ";
  jint ver = env->GetVersion();
  cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << endl;

  jclass cls2 = env->FindClass("MyTest");  // try to find the class
  if(cls2 == nullptr)
  {
    cerr << "ERROR: class not found !" << endl;
  }
  else
  {
    jmethodID ctor = env->GetMethodID(cls2, "<init>", "()V");
    if(ctor == nullptr)
    {
      cerr << "ERROR: constructor not found !" << endl;
    }
    else
    {
      jobject myo = env->NewObject(cls2, ctor);
      cout << "Object succesfully constructed !"<<endl;
    }
  }
  jvm->DestroyJavaVM();
  */

namespace Java
{

  std::string Interpreter::classpath = "";

  void Interpreter::setClassPath(std::string const& cp)
  {
    if (classpath != "")
    {
      throw std::invalid_argument("Classpath has already been set.");
    }
    classpath = cp;
  }

  Interpreter& Interpreter::getInstance(void)
  {
    static Interpreter interpreter;
    return interpreter;
  }

  Interpreter::Interpreter()
  {
    if (classpath == "")
    {
      throw std::runtime_error("Classpath has not been set yet.");
    }
    JavaVMInitArgs vm_args;
    std::string optionClassPath = "-Djava.class.path=";
    optionClassPath += classpath;
    JavaVMOption options;
    options.optionString = &optionClassPath[0u];
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = &options;
    vm_args.ignoreUnrecognized = false;

    jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (JNI_OK != rc)
    {
      jvm = nullptr;
      throw std::runtime_error("Cannot create JVM interpreter instance.");
    }
  }

  Interpreter::~Interpreter()
  {
    if (jvm)
    {
      jvm->DestroyJavaVM();
    }
  }

  uint8_t Interpreter::getVersionMajor() const
  {
    jint ver = env->GetVersion();
    return (ver >> 16) & 0x0f;
  }

  uint8_t Interpreter::getVersionMinor() const
  {
    jint ver = env->GetVersion();
    return ver & 0x0f;
  }

  Class Interpreter::getClass(std::string const& className) const
  {
    return Class(className, env);
  }

  Class::Class(std::string const& className, JNIEnv* env) :
    env(env)
  {
    clazz = env->FindClass(className.c_str());
    if (clazz == nullptr)
    {
      throw std::invalid_argument("Cannot find JAVA class in classpath.");
    }
    ctor = env->GetMethodID(clazz, "<init>", "()V");
    if (ctor == nullptr)
    {
      throw std::invalid_argument("Cannot find constructor for class '" + className + "'.");
    }
  }

  Object Class::getInstance(void) const
  {
    return Object();
  }
  
}
