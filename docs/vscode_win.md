Due to choosing to work on this project using VS Code and Cmake when on windows (is that blasphemous to the Visual Studio C++ gods?),
Building with Cmake and GCC has given me some issues, especially with having MSVC also installed via Visual Studio. Wanted to keep a record of my .vscode for windows here, rather than commit that folder to version control.

### launch.json
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/gengproto.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "${env:GDB_PATH}",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "cmake build"
        }
    ]
}
```

### settings.json
```
{
    "files.associations": {
        "algorithm": "cpp",
        "array": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "cctype": "cpp",
        "charconv": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "compare": "cpp",
        "concepts": "cpp",
        "cstdarg": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cstring": "cpp",
        "ctime": "cpp",
        "cwchar": "cpp",
        "cwctype": "cpp",
        "deque": "cpp",
        "exception": "cpp",
        "format": "cpp",
        "functional": "cpp",
        "initializer_list": "cpp",
        "ios": "cpp",
        "iosfwd": "cpp",
        "iostream": "cpp",
        "istream": "cpp",
        "iterator": "cpp",
        "limits": "cpp",
        "list": "cpp",
        "locale": "cpp",
        "memory": "cpp",
        "new": "cpp",
        "numbers": "cpp",
        "numeric": "cpp",
        "optional": "cpp",
        "ostream": "cpp",
        "queue": "cpp",
        "random": "cpp",
        "ranges": "cpp",
        "span": "cpp",
        "stdexcept": "cpp",
        "streambuf": "cpp",
        "string": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "typeinfo": "cpp",
        "unordered_map": "cpp",
        "utility": "cpp",
        "variant": "cpp",
        "vector": "cpp",
        "xfacet": "cpp",
        "xhash": "cpp",
        "xiosbase": "cpp",
        "xlocale": "cpp",
        "xlocbuf": "cpp",
        "xlocinfo": "cpp",
        "xlocmes": "cpp",
        "xlocmon": "cpp",
        "xlocnum": "cpp",
        "xloctime": "cpp",
        "xmemory": "cpp",
        "xstring": "cpp",
        "xtr1common": "cpp",
        "xutility": "cpp",
        "*.tcc": "cpp",
        "memory_resource": "cpp",
        "string_view": "cpp",
        "cinttypes": "cpp"
    },
    "cmake.generator": "Ninja",  // or "Unix Makefiles" if you prefer
    "cmake.configureSettings": {
        "CMAKE_C_COMPILER": "C:\\msys64\\ucrt64\\bin\\gcc.exe",
        "CMAKE_CXX_COMPILER": "C:\\msys64\\ucrt64\\bin\\gcc.exe"
    },
    "cmake.preferredGenerators": [
        "Ninja",
        "Unix Makefiles"
    ]
}
```

Note that you may want or need to update the CMAKE compiler paths if you have a different location or wish to use a different compiler

### tasks.json
```
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "cmake build",
            "command": "cmake --build ${workspaceFolder}/build",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```