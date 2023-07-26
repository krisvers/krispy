#include <platform.h>

#ifdef KRISPY_PLATFORM_WINDOWS

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

platform_file_success_enum platform_file_open(platform_file_t * outfile, char * path) {
    HANDLE file = CreateFileA(path, READ_WRITE, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        file = CreateFileA(path, READ_ONLY, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    if (file == INVALID_HANDLE_VALUE) {
        file = CreateFileA(path, WRITE_ONLY, SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    if (file == INVALID_HANDLE_VALUE) {
        return PLATFORM_FILE_OPEN_ERROR;
    }

    *outfile = file;
    return PLATFORM_FILE_SUCCESS;
}

platform_file_success_enum platform_file_close(platform_file_t file) {
    if (CloseHandle(file) == 0) {
        return PLATFORM_FILE_CLOSE_ERROR;
    }

    return PLATFORM_FILE_SUCCESS;
}

platform_file_success_enum platform_file_read(platform_file_t file, i64 length, void * buffer) {
    DWORD read = 0;
    if (ReadFile(file, buffer, (DWORD) length, &read, NULL) == 0) {
        return PLATFORM_FILE_READ_ERROR;
    }

    return PLATFORM_FILE_SUCCESS;
}

platform_file_success_enum platform_file_write(platform_file_t file, i64 length, void * buffer) {
    DWORD written = 0;
    if (WriteFile(file, buffer, (DWORD) length, &written, NULL) == 0) {
        return PLATFORM_FILE_WRITE_ERROR;
    }

    return PLATFORM_FILE_SUCCESS;
}

platform_file_success_enum platform_file_length(platform_file_t file, u64 * outlen) {
    LARGE_INTEGER len;
    if (GetFileSizeEx(file, &len) == 0) {
        return PLATFORM_FILE_LENGTH_ERROR;
    }

    *outlen = len.QuadPart;
    return PLATFORM_FILE_SUCCESS;
}

platform_file_success_enum platform_file_time(platform_file_t file, f64 * outcreation, f64 * outaccess, f64 * outmod) {
    FILETIME creation;
    FILETIME access;
    FILETIME mod;
    if (GetFileTime(file, &creation, &access, &mod) == 0) {
        return PLATFORM_FILE_ATTRIBUTE_ERROR;
    }

    u64 t;
    t = *((u64 *) &creation);
    *outcreation = t * 10.0;
    t = *((u64 *) &access);
    *outaccess = t * 10.0;
    t = *((u64 *) &mod);
    *outmod = t * 10.0;
    return PLATFORM_FILE_SUCCESS;
}

static DWORD platform_map_enum_method[3] = {
    FILE_BEGIN,
    FILE_END,
    FILE_CURRENT,
};

platform_file_success_enum platform_file_seek(platform_file_t file, i64 offset, platform_file_seek_enum seek) {
    LARGE_INTEGER off;
    off.QuadPart = offset;
    if (SetFilePointerEx(file, off, NULL, platform_map_enum_method[seek]) == 0) {
        return PLATFORM_FILE_SEEK_ERROR;
    }

    return PLATFORM_FILE_SUCCESS;
}

#endif
