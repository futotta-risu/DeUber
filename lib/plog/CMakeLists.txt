cmake_minimum_required(VERSION 3.10)
project(PLOG LANGUAGES CXX)

add_library(PLOG INTERFACE)
target_include_directories(PLOG INTERFACE include/)