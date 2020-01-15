#include "../src/Logger.hpp"

int main()
{
    Logger log( "test", "./logs" );

    log.writeInfo( "testinfo" );
    log.writeWarn( "testwarn" );
    log.writeDebug( "testdebug" );
    log.writeError( "testerror" );

    return 0;
}
