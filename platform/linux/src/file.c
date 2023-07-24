#include <krispy.h>
#include <platform/file.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#define __USE_XOPEN2K8
#include <sys/stat.h>

kplatform_file_success_enum kplatform_file_open(kplatform_file_t * outfile, char * path) {
    kplatform_file_t file = open(path, O_RDWR);
    kplatform_file_success_enum success = KPLATFORM_FILE_SUCCESS;
    if (file == -1) {
        file = open(path, O_RDONLY);
        success = KPLATFORM_FILE_READ_ONLY;
    }
    if (file == -1) {
        file = open(path, O_WRONLY);
        success = KPLATFORM_FILE_WRITE_ONLY;
    }
    if (file == -1) {
        success = KPLATFORM_FILE_OPEN_ERROR;
        return success;
    }

    *outfile = file;
    return success;
}

kplatform_file_success_enum kplatform_file_close(kplatform_file_t file) {
    if (close(file) == -1) {
        return KPLATFORM_FILE_CLOSE_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_read(kplatform_file_t file, i64 length, void * buffer) {
    if (read(file, buffer, length) != length) {
        return KPLATFORM_FILE_READ_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_write(kplatform_file_t file, i64 length, void * buffer) {
    if (write(file, buffer, length) != length) {
        return KPLATFORM_FILE_WRITE_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_length(kplatform_file_t file, u64 * outlen) {
    off_t prev = lseek(file, (off_t) 0, SEEK_CUR);
    off_t offset = lseek(file, (off_t) 0, SEEK_END);
    if (offset == -1) {
        lseek(file, prev, SEEK_SET);
        return KPLATFORM_FILE_LENGTH_ERROR;
    }

    lseek(file, prev, SEEK_SET);
    *outlen = (u64) offset;
    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_time(kplatform_file_t file, f64 * outcreation, f64 * outaccess, f64 * outmod) {
    struct stat st;
    if (fstat(file, &st) == -1) {
        return KPLATFORM_FILE_ATTRIBUTE_ERROR;
    }

    *outcreation = st.st_ctim.tv_nsec / 1000.0 + st.st_ctim.tv_sec * 1000.0;
    *outaccess = st.st_atim.tv_nsec / 1000.0 + st.st_atim.tv_sec * 1000.0;
    *outmod = st.st_mtim.tv_nsec / 1000.0 + st.st_mtim.tv_sec * 1000.0;
    return KPLATFORM_FILE_SUCCESS;
}

static int kplatform_map_enum_whence[3] = {
    SEEK_SET,
    SEEK_END,
    SEEK_CUR,
};

kplatform_file_success_enum kplatform_file_seek(kplatform_file_t file, i64 offset, kplatform_file_seek_enum seek) {
    off_t off = lseek(file, (off_t) offset, kplatform_map_enum_whence[seek]);
    if (off == -1) {
        return KPLATFORM_FILE_SEEK_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}
