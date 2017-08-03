cmake_minimum_required (VERSION 2.6)
project (recenter_particles)

#include_directories( ${CMAKE_SOURCE_DIR}/Eigen/ )
add_executable(recenter_part	src/recenter_particles.cpp
								src/ParamsReader.cpp
								src/ParamsWriter.cpp
								src/StarHdr.cpp
								src/StarReader.cpp
								src/StarWriter.cpp
								src/ParReader.cpp
								src/ParWriter.cpp
								src/MrcHdr.cpp
								src/MrcsReader.cpp
								src/MrcsWriter.cpp
								src/SymEngine.cpp
								src/StringUtils.cpp)

#add_executable(recrop_part	src/recrop_particles.cpp
#				src/string_utils.cpp
#				src/mrc_hdr.cpp
#				src/mrc_reader.cpp
#				src/mrcs_writer.cpp
#				src/params_file_writer.cpp
#				src/par_file_writer.cpp
#				src/star_file_reader.cpp
#				src/star_file_writer.cpp
#				src/star_file_hdr.cpp)



