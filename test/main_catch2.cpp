#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

std::string classpath;

int main( int argc, char* argv[] )
{
  Catch::Session session;

  using namespace Catch::clara;
  auto cli 
    = session.cli() // Get Catch's composite command line parser
    | Opt( classpath, "classpath" ) // bind variable to a new option, with a hint string
           ["-p"]["--classpath"]    // the option names it will respond to
         ("JAVA classpath");        // description string for the help output

  session.cli( cli ); 

  int returnCode = session.applyCommandLine( argc, argv );
  return returnCode ? returnCode : session.run();
}

