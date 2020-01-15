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

#ifndef LOGGER_HPP
#define LOGGER_HPP

// Standard Libraries
#include <iostream> // std::cout, std::endl
#include <iomanip> // std::put_time
#include <fstream> // std::ofstream
#include <sstream> // std::stringstream
#include <string> //std::string
#include <ctime> // std::localtime
#include <chrono> // std::chrono::system_clock
#include <sys/stat.h> // ::mkdir
#include <sys/types.h> // ::mkdir

// Standard Log Types
#include "LogType.hpp" // LogType

class Logger
{
private:
    // Constants
    static const std::string FILE_EXTENSION;

    // Variables
    std::string name;
    std::string path;
    bool active;
    bool loggingActive;
    bool consoleOutputActive;
    std::string fileName;

    // Private Methods
    void makeFile();
    void validateFile();
    void setName( std::string name );
    void setPath( std::string path);
    void setFileName( std::string path, std::string name );

public:
    // Constructor
    Logger( std::string name, std::string path = "./logs/", bool active = true, bool loggingActive = true, bool consoleOutputActive = true );

    // Public Methods
    std::string trimLine( std::string line );
    std::string getName();
    std::string getPath();
    void setActive( bool active );
    bool isActive();
    void setLoggingActive( bool loggingActive );
    bool isLoggingActive();
    void setConsoleOutputActive( bool active );
    bool isConsoleOutputActive();
    std::string getFileName();
    bool fileExists();
    void write( std::string type, std::string message );
    void writeInfo( std::string message );
    void writeWarn( std::string message );
    void writeDebug( std::string message );
    void writeError( std::string message );
};

#endif // LOGGER_HPP