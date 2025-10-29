# MINIO UBUNTU

## 1.Before compiled

- make sure openssl and curl has been installed.

``` bash

1. install openssl

  (1) sudo apt install openssl
  (2) openssl version

2. install curl

  (1) sudo apt install curl
  (2) curl --version

```

### 1.1 curlpp 

``` bash

1. cd 3rd/curlpp
2. cmake -B build --install-prefix=your_path/minio-sdk/3rd/curlpp/install
3. cmake --build build -j3
4. cmake --install build

```

### 1.2 inih_cmake 

``` bash

1. cd 3rd/inih_cmake
2. cmake -B build --install-prefix=your_path/minio-sdk/3rd/inih_cmake/install
3. cmake --build build -j3
4. cmake --install build

```

### 1.3 json 

``` bash

1. cd 3rd/json
2. cmake -B build --install-prefix=your_path/minio-sdk/3rd/json/install
3. cmake --build build -j3
4. cmake --install build

```

### 1.4 pugixml 

``` bash

1. cd 3rd/pugixml
2. cmake -B build --install-prefix=your_path/minio-sdk/3rd/pugixml/install
3. cmake --build build -j3
4. cmake --install build

```

## 2.minio-cpp

``` bash

1. cd minio-cpp
2. cmake -B build
3. cmake --build build -j3

```