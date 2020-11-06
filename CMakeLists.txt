CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(AlgorithmLearning)

SET(CMAKE_CXX_FLAGS "-std=c++11")

ADD_EXECUTABLE(SortCookie SortCookie.cpp)
ADD_EXECUTABLE(BinarySearch BinarySearch.cpp)
ADD_EXECUTABLE(KMPTest KMPTest.cpp)
ADD_EXECUTABLE(SortMethodsTest SortMethods.cpp)
ADD_EXECUTABLE(LinkList LinkList.cpp)
ADD_EXECUTABLE(LISTest LIS.cpp)
ADD_EXECUTABLE(StrTest StrReletive.cpp)
ADD_EXECUTABLE(UnionFind UnionFind.cpp)
Add_EXECUTABLE(DijkstraTest PathPlanning/dijkstra.cpp)
