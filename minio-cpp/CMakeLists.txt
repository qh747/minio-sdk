# CMake版本要求
cmake_minimum_required(VERSION 3.10)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 版本信息
set(MINIO_CPP_MAJOR_VERSION "0")
set(MINIO_CPP_MINOR_VERSION "3")
set(MINIO_CPP_PATCH_VERSION "0")
set(MINIO_CPP_VERSION_STRING "${MINIO_CPP_MAJOR_VERSION}.${MINIO_CPP_MINOR_VERSION}.${MINIO_CPP_PATCH_VERSION}")

# 查找系统依赖库
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

# 工程信息
project(miniocpp
  DESCRIPTION "MinIO C++ Client SDK provides simple APIs to access S3 compatible object storage"
  VERSION ${MINIO_CPP_VERSION_STRING}
  LANGUAGES C CXX
)

# 编译选项
option(MINIO_CPP_TEST "Build tests" ON)

# 参与编译的文件
aux_source_directory(${CMAKE_SOURCE_DIR}/src MINIO_CPP_SOURCES)
aux_source_directory(${CMAKE_SOURCE_DIR}/include/miniocpp MINIO_CPP_HEADERS)

# 设置静态库名称
set(MINIO_LIB_NAME "miniocpp")

# 设置静态库路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 编译静态库
add_library(${MINIO_LIB_NAME} STATIC ${MINIO_CPP_SOURCES} ${MINIO_CPP_HEADERS})
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_properties(${MINIO_LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# 链接std c++ fs库
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0 AND NOT MINGW)
  target_link_libraries(${MINIO_LIB_NAME} PUBLIC stdc++fs)
endif()

# 链接curlpp库
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/include)
target_link_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/lib)
target_link_libraries(${MINIO_LIB_NAME} PUBLIC curlpp)

# 链接curl库
target_link_libraries(${MINIO_LIB_NAME} PUBLIC ${CURL_LIBRARIES})

# 链接inih库
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/include)
target_link_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/lib)
target_link_libraries(${MINIO_LIB_NAME} PUBLIC INIReader)

# 链接json库
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/json/install/include)

# 链接pugixml库
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/include)
target_link_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/lib)
target_link_libraries(${MINIO_LIB_NAME} PUBLIC pugixml)

# 链接openssl库
target_link_libraries(${MINIO_LIB_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# 链接zlib库
target_include_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/include)
target_link_directories(${MINIO_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/lib)
target_link_libraries(${MINIO_LIB_NAME} PUBLIC z)

set(MINIO_3RD_LIBS)
set(MINIO_3RD_DIRS)
set(MINIO_3RD_HEADERS)

list(APPEND MINIO_3RD_HEADERS 
  ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/include
  ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/include
  ${CMAKE_SOURCE_DIR}/../3rd/json/install/include
  ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/include
  ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/include
)

list(APPEND MINIO_3RD_DIRS 
  ${CMAKE_SOURCE_DIR}/../3rd/curlpp/install/lib
  ${CMAKE_SOURCE_DIR}/../3rd/inih_cmake/install/lib
  ${CMAKE_SOURCE_DIR}/../3rd/pugixml/install/lib
  ${CMAKE_SOURCE_DIR}/../3rd/zlib-1.3.1/install/lib
)

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0 AND NOT MINGW)
  list(APPEND MINIO_3RD_LIBS stdc++fs)
endif()

list(APPEND MINIO_3RD_LIBS 
  curlpp
  OpenSSL::SSL 
  OpenSSL::Crypto
  INIReader 
  pugixml
  z
)

# 测试程序
if (MINIO_CPP_TEST)
  # 可执行程序输出路径
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

  set(EXAMPLE_APPS
    MakeBucket
    RemoveBucket
    BucketExists
    ListBuckets
    StatObject
    RemoveObject
    DownloadObject
    UploadObject
    GetObject
    ListObjects
    PutObject
    CopyObject
    ComposeObject
    RemoveObjects
    SelectObjectContent
    ListenBucketNotification
    DeleteBucketPolicy
    GetBucketPolicy
    SetBucketPolicy
    DeleteBucketNotification
    GetBucketNotification
    SetBucketNotification
    DeleteBucketEncryption
    GetBucketEncryption
    SetBucketEncryption
    GetBucketVersioning
    SetBucketVersioning
    DeleteBucketReplication
    GetBucketReplication
    SetBucketReplication
    DeleteBucketLifecycle
    GetBucketLifecycle
    SetBucketLifecycle
    DeleteBucketTags
    GetBucketTags
    SetBucketTags
    DeleteObjectLockConfig
    GetObjectLockConfig
    SetObjectLockConfig
    DeleteObjectTags
    GetObjectTags
    SetObjectTags
    DisableObjectLegalHold
    EnableObjectLegalHold
    IsObjectLegalHoldEnabled
    GetObjectRetention
    SetObjectRetention
    GetPresignedObjectUrl
    GetPresignedPostFormData
    PutObjectProgress
    GetObjectProgress
  )

  foreach(target ${EXAMPLE_APPS})
    add_executable(${target} examples/${target}.cc)

    target_include_directories(${target} PRIVATE ${MINIO_3RD_HEADERS})
    target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    target_link_directories(${target} PRIVATE ${MINIO_3RD_DIRS})

    target_link_libraries(${target} PRIVATE ${MINIO_LIB_NAME})
    target_link_libraries(${target} PRIVATE ${${MINIO_3RD_LIBS}})
    
  endforeach()

  add_executable(tests tests/tests.cc)

  target_include_directories(tests PRIVATE ${MINIO_3RD_HEADERS})
  target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

  target_link_directories(tests PRIVATE ${MINIO_3RD_DIRS})
  
  target_link_libraries(tests PRIVATE ${MINIO_LIB_NAME})
  target_link_libraries(tests ${${MINIO_3RD_LIBS}})
  
endif()