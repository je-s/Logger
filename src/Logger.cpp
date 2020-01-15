/*
    Copyright 2019 Jan-Eric Schober

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "Logger.hpp"

const std::string Logger::FILE_EXTENSION = ".log";

Logger::Logger( std::string name, std::string path, bool active, bool loggingActive, bool consoleOutputActive )
{
    setName( name );
    setPath( path );
    setFileName( getPath(), getName() );
    setActive( active );
    setLoggingActive( loggingActive );
    setConsoleOutputActive( consoleOutputActive );
}

std::string Logger::trimLine( std::string line )
{
    size_t firstChar = line.find_first_not_of( ' ' );

    if ( firstChar == std::string::npos )
    {
        return "";
    }

    size_t lastChar = line.find_last_not_of( ' ' );

    return line.substr( firstChar, ( lastChar - firstChar + 1 ) );
}

void Logger::setName( std::string name )
{
    this->name = trimLine( name );
}

std::string Logger::getName()
{
    return this->name;
}

void Logger::setPath( std::string path )
{
    path = trimLine( path );

    if ( path.back() != '/' )
    {
        path += '/';
    }

    this->path = path;
}

std::string Logger::getPath()
{
    return this->path;
}

void Logger::setActive( bool active )
{
    this->active = active;
}

bool Logger::isActive()
{
    return this->active;
}

void Logger::setLoggingActive( bool loggingActive )
{
    this->loggingActive = loggingActive;
}

bool Logger::isLoggingActive()
{
    return this->loggingActive;
}

void Logger::setConsoleOutputActive( bool consoleOutputActive )
{
    this->consoleOutputActive = consoleOutputActive;
}

bool Logger::isConsoleOutputActive()
{
    return this->consoleOutputActive;
}

void Logger::setFileName( std::string path, std::string name )
{
    this->fileName = std::string( path + name + FILE_EXTENSION );
}

std::string Logger::getFileName()
{
    return this->fileName;
}

void Logger::makeFile()
{
    // Make directory, if it doesn't already exist
    ::mkdir( getPath().c_str(), 0777 );

    // Create file, if it doesn't already exist
    std::ofstream file;
    file.open( getFileName(), std::ofstream::out | std::ofstream::app );
    file.close();
}

bool Logger::fileExists()
{
    return std::ifstream( getFileName() ).good();
}

void Logger::validateFile()
{
    if ( !fileExists() )
    {
        makeFile();
    }
}

void Logger::write( const std::string type, const std::string message )
{
    if ( !isActive() )
    {
        return;
    }
    
    std::time_t timeNow = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::stringstream logLine;
        logLine << "[" << std::put_time( std::localtime( &timeNow ), "%c" ) << "] " << type << " : " << message;

    if ( isConsoleOutputActive() )
    {
        std::cout << logLine.str() << std::endl;
    }
    
    if ( isLoggingActive() )
    {
        validateFile();
        std::ofstream file;
        file.open( getFileName(), std::ofstream::out | std::ofstream::app );

        if ( file.is_open() )
        {
            file << logLine.str() << std::endl;
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << getFileName() << std::endl;
        }
    }
}

void Logger::writeInfo( std::string message )
{
    write( LogType::INFO, message );
}

void Logger::writeWarn( std::string message )
{
    write( LogType::WARN, message );
}
void Logger::writeDebug( std::string message )
{
    write( LogType::DEBUG, message );
}

void Logger::writeError( std::string message )
{
    write( LogType::ERROR, message );
}
