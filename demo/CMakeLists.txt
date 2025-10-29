# cmake版本要求
cmake_minimum_required(VERSION 3.22)

# 工程名称
project(minio_demo)

# 设置编译器
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置为debug可调试
set(CMAKE_BUILD_TYPE Debug)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 查找系统依赖库
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# 可执行程序输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 参与编译的文件
aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_FILES)

# 生成可执行程序
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接minio库
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../minio-cpp/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../minio-cpp/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE miniocpp)

# 链接std c++ fs库
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0 AND NOT MINGW)
  target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)
endif()

# 链接openssl库
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# 链接zlib库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC z)

# 链接json库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/json/install/include)

# 链接pugixml库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml)

# 链接inih库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC INIReader)

# 链接curlpp库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC curlpp)

# 链接curl库
target_link_libraries(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES})