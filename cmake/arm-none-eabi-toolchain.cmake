set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(ARM_NONE_EABI_TOOLCHAIN_PATH "/home/andrew/gcc-arm-none-eabi-10-2020-q4-major/bin")
#set(TOOLCHAIN_PREFIX ${ARM_NONE_EABI_TOOLCHAIN_PATH}/arm-none-eabi-)
#set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
#set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}as)
#set(CMAKE_AR ${TOOLCHAIN_PREFIX}ar)
#set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
#set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
#set(CMAKE_LD ${TOOLCHAIN_PREFIX}ld)
#set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_LD} <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>.axf <LINK_LIBRARIES>")
#set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_LD} <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>.axf <LINK_LIBRARIES>")

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
# set(CMAKE_C_LINK_EXECUTABLE "arm-none-eabi-ld <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>.axf <LINK_LIBRARIES>")
set(CMAKE_C_LINK_EXECUTABLE "arm-none-eabi-ld <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> <LINK_LIBRARIES> -o <TARGET>.axf ")
set(CMAKE_CXX_LINK_EXECUTABLE "arm-none-eabi-ld <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> <LINK_LIBRARIES> -o <TARGET>.axf")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
