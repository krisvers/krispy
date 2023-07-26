#ifndef KRISPY_PLATFORM_FILE_H
#define KRISPY_PLATFORM_FILE_H

#include <krispy.h>
#include <platform.h>

#ifdef KRISPY_PLATFORM_WINDOWS
    /* Win32 handles files using HANDLEs (essentially a void *) */
    typedef void * platform_file_t;
#else
    /* POSIX uses int for file descriptors */
    typedef int platform_file_t;
#endif

typedef enum PlatformFileSuccessEnum {
    PLATFORM_FILE_LENGTH_ERROR = -10,
    PLATFORM_FILE_ATTRIBUTE_ERROR = -9,
    PLATFORM_FILE_WRITE_ERROR = -8,
    PLATFORM_FILE_READ_ERROR = -7,
    PLATFORM_FILE_SEEK_ERROR = -6,
    PLATFORM_FILE_CLOSE_ERROR = -5,
    PLATFORM_FILE_OPEN_ERROR = -4,
    PLATFORM_FILE_WRITE_ONLY_ERROR = -3,
    PLATFORM_FILE_READ_ONLY_ERROR = -2,
    PLATFORM_FILE_UNKNOWN_ERROR = -1,
    PLATFORM_FILE_SUCCESS = 0,
    PLATFORM_FILE_READ_ONLY,
    PLATFORM_FILE_WRITE_ONLY,
} platform_file_success_enum;

typedef enum PlatformFileSeekEnum {
    PLATFORM_FILE_SEEK_START = 0,
    PLATFORM_FILE_SEEK_END,
    PLATFORM_FILE_SEEK_CURRENT,
} platform_file_seek_enum;

/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_open(platform_file_t * outfile, char * path);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_close(platform_file_t file);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_read(platform_file_t file, i64 length, void * buffer);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_write(platform_file_t file, i64 length, void * buffer);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_length(platform_file_t file, u64 * outlen);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_time(platform_file_t file, f64 * outcreation, f64 * outaccess, f64 * outmod);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `platform_file_success_enum` or `enum PlatformFileSuccessEnum` */
platform_file_success_enum platform_file_seek(platform_file_t file, i64 offset, platform_file_seek_enum seek);

#endif
