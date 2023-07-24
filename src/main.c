#include <krispy.h>
#include <platform/file.h>

int printf(const char *, ...);
int main(void) {
    kplatform_file_t file;
    kplatform_file_success_enum ret = kplatform_file_open(&file, "./test.txt");
    printf("%d\n", ret);
    if (ret < KPLATFORM_FILE_SUCCESS) {
        printf("file open\n");
        return 1;
    }

    u64 len;
    ret = kplatform_file_length(file, &len);
    printf("%d\n", ret);
    if (ret < KPLATFORM_FILE_SUCCESS) {
        printf("file length\n");
        return 2;
    }
    char buffer[len + 1];
    buffer[len] = '\0';

    ret = kplatform_file_read(file, len, buffer);
    printf("%d\n", ret);
    if (ret < KPLATFORM_FILE_SUCCESS) {
        printf("file read\n");
        return 3;
    }

    printf("%s\n", buffer);

    ret = kplatform_file_close(file);
    printf("%d\n", ret);
    if (ret < KPLATFORM_FILE_SUCCESS) {
        printf("file close\n");
        return 4;
    }

    return 0;
}
