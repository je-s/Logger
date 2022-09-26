# Logger
Logger is a minimalistic logger class, which allows to log arbitrary message-types to a file. Also, the log is (or can) be mirrored to `std::cout`, and writing to a file or the complete logging mechanism can be deactivated.

# Folder structure
* `src`  contains the source code (`Logger` class).
* `test` contains a test application to test the correct functionality.

# Including and compiling SimpleException in a project
In order to use Logger, `<path>/Logger/src/Logger.hpp` needs to be included.
In order to compile Logger, following files need to be compiled and linked:
* `<path>/Logger/src/LogType.hpp`
* `<path>/Logger/src/Logger.hpp`

# Usage
## Basic usage
1. Instantiate a new `Logger`-Object with a name and a path: `Logger log( "<logName>", "<path>" );`.
    1.  A file with `<logName>.log` gets created in <path>, if it doesn't exist yet.
2. Write several log lines:
```
log.writeInfo( "testinfo" );
log.writeWarn( "testwarn" );
log.writeDebug( "testdebug" );
log.writeError( "testerror" );
log.write( "custom", "testcustom" );
```
3. If creating the file or writing to it fails, an error message will be printed on `std::cerr`.

## Notes
Since Logger is using streams to interact with files and `std::cout`, writing to such a stream is usually synchronized. But in the cases of string-concatenation with the `+`-operator for example, it is possible that data races will occur while writing to a stream.
To avoid this, construct ephemeral string objects in the case of concatenation (`std::string( "a" + "b" )`) or use `std::stringstream` to compose a string before passing it to one of Logger's `write`-functions.

# License
```
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
```