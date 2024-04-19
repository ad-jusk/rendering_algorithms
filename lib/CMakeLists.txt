add_library(lodepng lodepng/lodepng.cpp lodepng/lodepng.h)

add_library(stb stb/stb_image.h)

set_target_properties(stb PROPERTIES LINKER_LANGUAGE CXX)