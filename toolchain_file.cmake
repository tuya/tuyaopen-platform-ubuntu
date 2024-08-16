##
# @file toolchain_file.cmake
# @brief 
#/

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR Linux)

set(TOOLCHAIN_DIR "/usr")
set(TOOLCHAIN_INCLUDE
    ${TOOLCHAIN_DIR}/include
    )
set(TOOLCHAIN_LIB
    ${TOOLCHAIN_DIR}/lib/gcc
    )

set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/g++")

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_DIR})
set(CMAKE_INCLUDE_PATH
    ${TOOLCHAIN_INCLUDE}
    )
set(CMAKE_LIBRARY_PATH
    ${TOOLCHAIN_LIB}
    )

# -fsanitize=address -fno-omit-frame-pointer
set(CMAKE_C_FLAGS " -g")
