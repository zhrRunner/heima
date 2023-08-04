cmake_minimum_required(VERSION 3.23)
project(reservation_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(reservation_system 机房预约系统.cpp Identity.h student.h student.cpp teacher.h teacher.cpp manager.h manager.cpp globalFile.h computerRoom.h orderFile.h orderFile.cpp)
