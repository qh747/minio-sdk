#include <iostream>
#include <miniocpp/client.h>
#include "testMinio.h"

void TestUploadObject() {
    // Create S3 base URL.
    minio::s3::BaseUrl base_url("http://ip_addr:port", false);

    // Create credential provider.
    minio::creds::StaticProvider provider("user_name", "user_passwd");

    // Create S3 client.
    minio::s3::Client client(base_url, &provider);

    // Create upload object arguments.
    minio::s3::UploadObjectArgs args;
    args.bucket = "bucket_name";
    args.object = "remote_file_name";
    args.filename = "local_path/local_file_name";

    // Call upload object.
    minio::s3::UploadObjectResponse resp = client.UploadObject(args);

    // Handle response.
    if (resp) {
        std::cout << "file is successfully uploaded to minio server" << std::endl;
    } 
    else {
        std::cout << "unable to upload object; " << resp.Error().String() << std::endl;
    }
}

void TestDownloadObject() {
    // Create S3 base URL.
    minio::s3::BaseUrl base_url("http://ip_addr:port", false);

    // Create credential provider.
    minio::creds::StaticProvider provider("user_name", "user_passwd");

    // Create S3 client.
    minio::s3::Client client(base_url, &provider);

    // Create download object arguments.
    minio::s3::DownloadObjectArgs args;
    args.bucket = "bucket_name";
    args.object = "remote_file_name";
    args.filename = "local_path/local_file_name";

    // Call download object.
    minio::s3::DownloadObjectResponse resp = client.DownloadObject(args);

    // Handle response.
    if (resp) {
        std::cout << "my-object is successfully downloaded" << std::endl;
    } 
    else {
        std::cout << "unable to download object; " << resp.Error().String() << std::endl;
    }
}