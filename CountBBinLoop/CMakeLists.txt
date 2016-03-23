cmake_minimum_required(VERSION 3.0)

# LLVM detection part
set(LLVM_ROOT "" CACHE PATH "Root of LLVM install.")

# A bit of a sanity check:
if(NOT EXISTS ${LLVM_ROOT}/include/llvm)
	message(FATAL_ERROR
			"LLVM_ROOT (${LLVM_ROOT}) is invalid")
endif()

if(NOT EXISTS ${LLVM_ROOT}/bin/clang)
	message(FATAL_ERROR
			"clang not compiled with LLVM")
endif()

# Load various LLVM config stuff,
list(APPEND CMAKE_PREFIX_PATH
	"${LLVM_ROOT}/share/llvm/cmake")
find_package(LLVM REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions) #load additional config
include(AddLLVM) # used to add our own modules

