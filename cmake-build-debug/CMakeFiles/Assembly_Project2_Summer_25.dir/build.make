# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Assembly_Project2_Summer_25.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Assembly_Project2_Summer_25.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Assembly_Project2_Summer_25.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assembly_Project2_Summer_25.dir/flags.make

CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj: CMakeFiles/Assembly_Project2_Summer_25.dir/flags.make
CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj: D:/Assembly/Assembly\ Project/Assembly_Project2_Summer-25/Main.cpp
CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj: CMakeFiles/Assembly_Project2_Summer_25.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj"
	"D:\CLion 2024.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj -MF CMakeFiles\Assembly_Project2_Summer_25.dir\Main.cpp.obj.d -o CMakeFiles\Assembly_Project2_Summer_25.dir\Main.cpp.obj -c "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\Main.cpp"

CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.i"
	"D:\CLion 2024.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\Main.cpp" > CMakeFiles\Assembly_Project2_Summer_25.dir\Main.cpp.i

CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.s"
	"D:\CLion 2024.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\Main.cpp" -o CMakeFiles\Assembly_Project2_Summer_25.dir\Main.cpp.s

# Object files for target Assembly_Project2_Summer_25
Assembly_Project2_Summer_25_OBJECTS = \
"CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj"

# External object files for target Assembly_Project2_Summer_25
Assembly_Project2_Summer_25_EXTERNAL_OBJECTS =

Assembly_Project2_Summer_25.exe: CMakeFiles/Assembly_Project2_Summer_25.dir/Main.cpp.obj
Assembly_Project2_Summer_25.exe: CMakeFiles/Assembly_Project2_Summer_25.dir/build.make
Assembly_Project2_Summer_25.exe: CMakeFiles/Assembly_Project2_Summer_25.dir/linkLibs.rsp
Assembly_Project2_Summer_25.exe: CMakeFiles/Assembly_Project2_Summer_25.dir/objects1.rsp
Assembly_Project2_Summer_25.exe: CMakeFiles/Assembly_Project2_Summer_25.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Assembly_Project2_Summer_25.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Assembly_Project2_Summer_25.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assembly_Project2_Summer_25.dir/build: Assembly_Project2_Summer_25.exe
.PHONY : CMakeFiles/Assembly_Project2_Summer_25.dir/build

CMakeFiles/Assembly_Project2_Summer_25.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Assembly_Project2_Summer_25.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Assembly_Project2_Summer_25.dir/clean

CMakeFiles/Assembly_Project2_Summer_25.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25" "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25" "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug" "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug" "D:\Assembly\Assembly Project\Assembly_Project2_Summer-25\cmake-build-debug\CMakeFiles\Assembly_Project2_Summer_25.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Assembly_Project2_Summer_25.dir/depend

