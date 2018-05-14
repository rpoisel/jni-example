/**
 * https://www.codeproject.com/articles/993067/calling-java-from-cplusplus-with-jni
 */

#include <jni.h>

#include <iostream>
#include <cstdlib>
#include <cstring>

int main(void)
{
  using namespace std;
  JavaVM *jvm;
  JNIEnv *env;
  JavaVMInitArgs vm_args;
  string optionClassPath = "-Djava.class.path=." ;
  JavaVMOption options;
  options.optionString = &optionClassPath[0u];
  vm_args.version = JNI_VERSION_1_6;
  vm_args.nOptions = 1;
  vm_args.options = &options;
  vm_args.ignoreUnrecognized = false;
  
  jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
  if (rc != JNI_OK) {
    // TO DO: error processing... 
    cin.get();
    exit(EXIT_FAILURE);
  }
  cout << "JVM load succeeded: Version ";
  jint ver = env->GetVersion();
  cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << endl;

  // TO DO: add the code that will use JVM <============  (see next steps)

  jvm->DestroyJavaVM();
  cin.get();
}
