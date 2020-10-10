CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(AlgorithmLearning)

SET(CMAKE_CXX_FLAGS "-std=c++11")

ADD_EXECUTABLE(SortCookie SortCookie.cpp)
ADD_EXECUTABLE(BinarySearch BinarySearch.cpp)
ADD_EXECUTABLE(KMPTest KMPTest.cpp)
ADD_EXECUTABLE(SortMethodsTest SortMethods.cpp)