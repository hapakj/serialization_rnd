set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(COMPILER_FLAG_WARNINGS "/W3")
	set(COMPILER_FLAG_TREAT_WARNING_AS_ERROR "/WX")
	set(COMPILER_FLAG_MULTIPLE_PROCESSES "/MP")
endif()
	
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(COMPILER_FLAG_WARNINGS "-Wall" "-Wextra" "-Wformat=2")
	set(COMPILER_FLAG_TREAT_WARNING_AS_ERROR "-Werror")
	set(COMPILER_FLAG_PEDANTIC "-Wpedantic")
	set(COMPILER_FLAG_OLD_STYLE_CAST "-Wold-style-cast")
endif()

set(COMPILER_FLAGS ${COMPILER_FLAG_WARNINGS}
                   ${COMPILER_FLAG_TREAT_WARNING_AS_ERROR}
				   ${COMPILER_FLAG_MULTIPLE_PROCESSES}
				   ${COMPILER_FLAG_PEDANTIC}
				   ${COMPILER_FLAG_OLD_STYLE_CAST})
add_compile_options(${COMPILER_FLAGS})

## workaround for Visual Studio build with Clang
if (WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options("-Wno-unused-command-line-argument")
endif()
