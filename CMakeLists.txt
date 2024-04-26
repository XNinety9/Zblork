cmake_minimum_required(VERSION 3.16)
project(Zblork LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Zblork src/main.cpp)
target_link_libraries(Zblork PRIVATE sfml-system sfml-audio sfml-graphics)
target_compile_features(Zblork PRIVATE cxx_std_17)

# Copy the sound file to the build directory
configure_file(assets/sound-asset.wav ${CMAKE_CURRENT_BINARY_DIR}/assets/sound-asset.wav COPYONLY)
# Add the sound file to the executable target
target_sources(Zblork PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/assets/sound-asset.wav)

if(WIN32)
    add_custom_command(
        TARGET Zblork
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Zblork>
        VERBATIM)
endif()

install(TARGETS Zblork)
