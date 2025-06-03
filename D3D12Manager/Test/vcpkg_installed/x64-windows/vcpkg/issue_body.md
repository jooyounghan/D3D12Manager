Package: minizip:x64-windows@1.3.1#1

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.43.34809.0
-    vcpkg-tool version: 2025-03-22-d4dd14112c2026ee57e59f966ecfa3b9137bd143
    vcpkg-scripts version: 654410ee8e 2025-06-01 (9 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached madler-zlib-v1.3.1.tar.gz
-- Cleaning sources at C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/vcpkg/downloads/madler-zlib-v1.3.1.tar.gz
-- Applying patch 0001-remove-ifndef-NOUNCRYPT.patch
-- Applying patch 0002-add-declaration-for-mkdir.patch
-- Applying patch pkgconfig.patch
-- Applying patch android-fileapi.patch
-- Using source at C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean
-- Found external ninja('1.12.1').
-- Configuring x64-windows
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v
    Working Directory: C:/vcpkg/buildtrees/minizip/x64-windows-rel/vcpkg-parallel-configure
    Error code: 1
    See logs for more information:
      C:\vcpkg\buildtrees\minizip\config-x64-windows-dbg-CMakeConfigureLog.yaml.log
      C:\vcpkg\buildtrees\minizip\config-x64-windows-rel-CMakeConfigureLog.yaml.log
      C:\vcpkg\buildtrees\minizip\config-x64-windows-out.log

Call Stack (most recent call first):
  C:/Users/rsfnq/OneDrive/바탕 화면/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:269 (vcpkg_execute_required_process)
  buildtrees/versioning_/versions/minizip/bb8016593efa5220d1b877c27cd8612862c13d81/portfile.cmake:41 (vcpkg_cmake_configure)
  scripts/ports.cmake:206 (include)



```

<details><summary>C:\vcpkg\buildtrees\minizip\config-x64-windows-dbg-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineSystem.cmake:205 (message)"
      - "CMakeLists.txt:2 (project)"
    message: |
      The system is: Windows - 10.0.26100 - AMD64
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:17 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:64 (__determine_compiler_id_test)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Compiling the C compiler identification source file "CMakeCCompilerId.c" succeeded.
      Compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe 
      Build flags: /nologo;/DWIN32;/D_WINDOWS;/utf-8;/MP
      Id flags:  
      
      The output was:
      0
      CMakeCCompilerId.c
      
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.exe"
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.obj"
      
      The C compiler identification is MSVC, found in:
        C:/vcpkg/buildtrees/minizip/x64-windows-dbg/CMakeFiles/3.30.3/CompilerIdC/CMakeCCompilerId.exe
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:1243 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:250 (CMAKE_DETERMINE_MSVC_SHOWINCLUDES_PREFIX)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Detecting C compiler /showIncludes prefix:
        main.c
        참고: 포함 파일: C:\\vcpkg\\buildtrees\\minizip\\x64-windows-dbg\\CMakeFiles\\ShowIncludes\\foo.h
        
      Found prefix "참고: 포함 파일: "
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:74 (try_compile)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/vcpkg/buildtrees/minizip/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kiaioa"
      binary: "C:/vcpkg/buildtrees/minizip/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kiaioa"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/rsfnq/OneDrive/\ubc14\ud0d5 \ud654\uba74/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/vcpkg/buildtrees/minizip/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kiaioa'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_ca3db
        [1/2] C:\\PROGRA~1\\MICROS~4\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\cl.exe  /nologo   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_ca3db.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_ca3db.dir\\ /FS -c "C:\\Program Files\\CMake\\share\\cmake-3.30\\Modules\\CMakeCCompilerABI.c"
        [2/2] C:\\WINDOWS\\system32\\cmd.exe /C "cd . && "C:\\Program Files\\CMake\\bin\\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\\cmTC_ca3db.dir --rc=C:\\PROGRA~2\\WI3CF2~1\\10\\bin\\100226~1.0\\x64\\rc.exe --mt=C:\\PROGRA~2\\WI3CF2~1\\10\\bin\\100226~1.0\\x64\\mt.exe --manifests  -- C:\\PROGRA~1\\MICROS~4\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\link.exe /nologo CMakeFiles\\cmTC_ca3db.dir\\CMakeCCompilerABI.c.obj  /out:cmTC_ca3db.exe /implib:cmTC_ca3db.lib /pdb:cmTC_ca3db.pdb /version:0.0 /machine:x64  /nologo    /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib && cd ."
        
      exitCode: 0
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:218 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Parsed C implicit link information:
        link line regex: [^( *|.*[/\\])(ld[0-9]*(\\.[a-z]+)?|link\\.exe|lld-link(\\.exe)?|CMAKE_LINK_STARTFILE-NOTFOUND|([^/\\]+-)?ld|collect2)[^/\\]*( |$)]
        linker tool regex: [^[ 	]*(->|")?[ 	]*(([^"]*[/\\])?(ld[0-9]*(\\.[a-z]+)?|link\\.exe|lld-link(\\.exe)?))("|,| |$)]
        linker tool for 'C': C:/PROGRA~1/MICROS~4/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe
        implicit libs: []
        implicit objs: []
        implicit dirs: []
        implicit fwks: []
      
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/Internal/CMakeDetermineLinkerId.cmake:40 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:255 (cmake_determine_linker_id)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Running the C compiler's linker: "C:/PROGRA~1/MICROS~4/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe" "-v"
      Microsoft (R) Incremental Linker Version 14.43.34809.0
      Copyright (C) Microsoft Corporation.  All rights reserved.
```
</details>

<details><summary>C:\vcpkg\buildtrees\minizip\config-x64-windows-rel-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineSystem.cmake:205 (message)"
      - "CMakeLists.txt:2 (project)"
    message: |
      The system is: Windows - 10.0.26100 - AMD64
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:17 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:64 (__determine_compiler_id_test)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Compiling the C compiler identification source file "CMakeCCompilerId.c" succeeded.
      Compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe 
      Build flags: /nologo;/DWIN32;/D_WINDOWS;/utf-8;/MP
      Id flags:  
      
      The output was:
      0
      CMakeCCompilerId.c
      
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.exe"
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.obj"
      
      The C compiler identification is MSVC, found in:
        C:/vcpkg/buildtrees/minizip/x64-windows-rel/CMakeFiles/3.30.3/CompilerIdC/CMakeCCompilerId.exe
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:1243 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerId.cmake:250 (CMAKE_DETERMINE_MSVC_SHOWINCLUDES_PREFIX)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Detecting C compiler /showIncludes prefix:
        main.c
        참고: 포함 파일: C:\\vcpkg\\buildtrees\\minizip\\x64-windows-rel\\CMakeFiles\\ShowIncludes\\foo.h
        
      Found prefix "참고: 포함 파일: "
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:74 (try_compile)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/vcpkg/buildtrees/minizip/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-q5zde1"
      binary: "C:/vcpkg/buildtrees/minizip/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-q5zde1"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/rsfnq/OneDrive/\ubc14\ud0d5 \ud654\uba74/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/vcpkg/buildtrees/minizip/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-q5zde1'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_98c11
        [1/2] C:\\PROGRA~1\\MICROS~4\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\cl.exe  /nologo   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_98c11.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_98c11.dir\\ /FS -c "C:\\Program Files\\CMake\\share\\cmake-3.30\\Modules\\CMakeCCompilerABI.c"
        [2/2] C:\\WINDOWS\\system32\\cmd.exe /C "cd . && "C:\\Program Files\\CMake\\bin\\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\\cmTC_98c11.dir --rc=C:\\PROGRA~2\\WI3CF2~1\\10\\bin\\100226~1.0\\x64\\rc.exe --mt=C:\\PROGRA~2\\WI3CF2~1\\10\\bin\\100226~1.0\\x64\\mt.exe --manifests  -- C:\\PROGRA~1\\MICROS~4\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\link.exe /nologo CMakeFiles\\cmTC_98c11.dir\\CMakeCCompilerABI.c.obj  /out:cmTC_98c11.exe /implib:cmTC_98c11.lib /pdb:cmTC_98c11.pdb /version:0.0 /machine:x64  /nologo    /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib && cd ."
        
      exitCode: 0
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:218 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Parsed C implicit link information:
        link line regex: [^( *|.*[/\\])(ld[0-9]*(\\.[a-z]+)?|link\\.exe|lld-link(\\.exe)?|CMAKE_LINK_STARTFILE-NOTFOUND|([^/\\]+-)?ld|collect2)[^/\\]*( |$)]
        linker tool regex: [^[ 	]*(->|")?[ 	]*(([^"]*[/\\])?(ld[0-9]*(\\.[a-z]+)?|link\\.exe|lld-link(\\.exe)?))("|,| |$)]
        linker tool for 'C': C:/PROGRA~1/MICROS~4/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe
        implicit libs: []
        implicit objs: []
        implicit dirs: []
        implicit fwks: []
      
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/Internal/CMakeDetermineLinkerId.cmake:40 (message)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeDetermineCompilerABI.cmake:255 (cmake_determine_linker_id)"
      - "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:2 (project)"
    message: |
      Running the C compiler's linker: "C:/PROGRA~1/MICROS~4/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe" "-v"
      Microsoft (R) Incremental Linker Version 14.43.34809.0
      Copyright (C) Microsoft Corporation.  All rights reserved.
```
</details>

<details><summary>C:\vcpkg\buildtrees\minizip\config-x64-windows-out.log</summary>

```
[1/2] "C:/Program Files/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/CMake/bin/cmake.exe" "C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean/contrib/minizip" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/vcpkg/packages/minizip_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DENABLE_BZIP2=OFF" "-DDISABLE_INSTALL_TOOLS=ON" "-DPACKAGE_VERSION=1.3.1" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/vcpkg/" "-D_VCPKG_INSTALLED_DIR=C:/Users/rsfnq/OneDrive/바탕 화면/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows/" "-DVCPKG_MANIFEST_INSTALL=OFF"
FAILED: ../CMakeCache.txt 
"C:/Program Files/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/CMake/bin/cmake.exe" "C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean/contrib/minizip" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/vcpkg/packages/minizip_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DENABLE_BZIP2=OFF" "-DDISABLE_INSTALL_TOOLS=ON" "-DPACKAGE_VERSION=1.3.1" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/vcpkg/" "-D_VCPKG_INSTALLED_DIR=C:/Users/rsfnq/OneDrive/바탕 화면/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows/" "-DVCPKG_MANIFEST_INSTALL=OFF"
-- The C compiler identification is MSVC 19.43.34809.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
Exit code 0xc0000409

[2/2] "C:/Program Files/CMake/bin/cmake.exe" -E chdir "../../x64-windows-dbg" "C:/Program Files/CMake/bin/cmake.exe" "C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean/contrib/minizip" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_INSTALL_PREFIX=C:/vcpkg/packages/minizip_x64-windows/debug" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DENABLE_BZIP2=OFF" "-DDISABLE_INSTALL_TOOLS=ON" "-DPACKAGE_VERSION=1.3.1" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/vcpkg/" "-D_VCPKG_INSTALLED_DIR=C:/Users/rsfnq/OneDrive/바탕 화면/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows/" "-DVCPKG_MANIFEST_INSTALL=OFF" "-DDISABLE_INSTALL_HEADERS=ON" "-DDISABLE_INSTALL_TOOLS=ON"
FAILED: ../../x64-windows-dbg/CMakeCache.txt 
"C:/Program Files/CMake/bin/cmake.exe" -E chdir "../../x64-windows-dbg" "C:/Program Files/CMake/bin/cmake.exe" "C:/vcpkg/buildtrees/minizip/src/v1.3.1-2a3c4cf735.clean/contrib/minizip" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_INSTALL_PREFIX=C:/vcpkg/packages/minizip_x64-windows/debug" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DENABLE_BZIP2=OFF" "-DDISABLE_INSTALL_TOOLS=ON" "-DPACKAGE_VERSION=1.3.1" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/vcpkg/" "-D_VCPKG_INSTALLED_DIR=C:/Users/rsfnq/OneDrive/바탕 화면/Project/D3D12Manager/D3D12Manager/Test/vcpkg_installed/x64-windows/" "-DVCPKG_MANIFEST_INSTALL=OFF" "-DDISABLE_INSTALL_HEADERS=ON" "-DDISABLE_INSTALL_TOOLS=ON"
-- The C compiler identification is MSVC 19.43.34809.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
Exit code 0xc0000409

ninja: build stopped: subcommand failed.
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "d3d12manager",
  "version-semver": "0.0.1",
  "dependencies": [
    "d3dx12",
    "directx-dxc",
    "assimp"
  ],
  "builtin-baseline": "654410ee8e11f0610c11a4a49a8827a84be5e187",
  "overrides": [
    {
      "name": "d3dx12",
      "version-string": "may2021"
    },
    {
      "name": "directx-dxc",
      "version-date": "2025-02-20"
    },
    {
      "name": "assimp",
      "version": "5.4.3"
    }
  ]
}

```
</details>
