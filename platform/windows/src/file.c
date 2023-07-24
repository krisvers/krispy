#include <krispy.h>
#include <platform/file.h>

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <fileapi.h>
#include <handleapi.h>

#define READ_WRITE (GENERIC_READ | GENERIC_WRITE)
#define READ_ONLY (GENERIC_READ)
#define WRITE_ONLY (GENERIC_WRITE)

#define SHARE (FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE)

kplatform_file_success_enum kplatform_file_open(kplatform_file_t * outfile, char * path) {
    HANDLE file = CreateFileA(path, READ_WRITE, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        file = CreateFileA(path, READ_ONLY, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    if (file == INVALID_HANDLE_VALUE) {
        file = CreateFileA(path, WRITE_ONLY, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    if (file == INVALID_HANDLE_VALUE) {
        return KPLATFORM_FILE_OPEN_ERROR;
    }

    *outfile = file;
    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_close(kplatform_file_t file) {
    if (CloseHandle(file) == 0) {
        return KPLATFORM_FILE_CLOSE_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_read(kplatform_file_t file, i64 length, void * buffer) {
    DWORD read = 0;
    if (ReadFile(file, buffer, (DWORD) length, &read, NULL) == 0) {
        return KPLATFORM_FILE_READ_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_write(kplatform_file_t file, i64 length, void * buffer) {
    DWORD written = 0;
    if (WriteFile(file, buffer, (DWORD) length, &written, NULL) == 0) {
        return KPLATFORM_FILE_WRITE_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_length(kplatform_file_t file, u64 * outlen) {
    LARGE_INTEGER len;
    if (GetFileSizeEx(file, &len) == 0) {
        return KPLATFORM_FILE_LENGTH_ERROR;
    }

    *outlen = len.QuadPart;
    return KPLATFORM_FILE_SUCCESS;
}

kplatform_file_success_enum kplatform_file_time(kplatform_file_t file, f64 * outcreation, f64 * outaccess, f64 * outmod) {
    FILETIME creation;
    FILETIME access;
    FILETIME mod;
    if (GetFileTime(file, &creation, &access, &mod) == 0) {
        return KPLATFORM_FILE_ATTRIBUTE_ERROR;
    }

    u64 t;
    t = *((u64 *) &creation);
    *outcreation = t * 10.0;
    t = *((u64 *) &access);
    *outaccess = t * 10.0;
    t = *((u64 *) &mod);
    *outmod = t * 10.0;
    return KPLATFORM_FILE_SUCCESS;
}

static DWORD kplatform_map_enum_method[3] = {
    FILE_BEGIN,
    FILE_END,
    FILE_CURRENT,
};

kplatform_file_success_enum kplatform_file_seek(kplatform_file_t file, i64 offset, kplatform_file_seek_enum seek) {
    LARGE_INTEGER off;
    off.QuadPart = offset;
    if (SetFilePointerEx(file, off, NULL, kplatform_map_enum_method[seek]) == 0) {
        return KPLATFORM_FILE_SEEK_ERROR;
    }

    return KPLATFORM_FILE_SUCCESS;
}