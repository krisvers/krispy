#ifndef KRISPY_PLATFORM_FILE_H
#define KRISPY_PLATFORM_FILE_H

#include <krispy.h>
#include <kplatform.h>

#ifdef KRISPY_KPLATFORM_WINDOWS
    /* Win32 handles files using HANDLEs (essentially a void *) */
    typedef void * kplatform_file_t;
#else
    /* POSIX uses int for file descriptors */
    typedef int kplatform_file_t;
#endif

typedef enum KplatformFileSuccessEnum {
    KPLATFORM_FILE_LENGTH_ERROR = -10,
    KPLATFORM_FILE_ATTRIBUTE_ERROR = -9,
    KPLATFORM_FILE_WRITE_ERROR = -8,
    KPLATFORM_FILE_READ_ERROR = -7,
    KPLATFORM_FILE_SEEK_ERROR = -6,
    KPLATFORM_FILE_CLOSE_ERROR = -5,
    KPLATFORM_FILE_OPEN_ERROR = -4,
    KPLATFORM_FILE_WRITE_ONLY_ERROR = -3,
    KPLATFORM_FILE_READ_ONLY_ERROR = -2,
    KPLATFORM_FILE_UNKNOWN_ERROR = -1,
    KPLATFORM_FILE_SUCCESS = 0,
    KPLATFORM_FILE_READ_ONLY,
    KPLATFORM_FILE_WRITE_ONLY,
} kplatform_file_success_enum;

typedef enum KplatformFileSeekEnum {
    KPLATFORM_FILE_SEEK_START = 0,
    KPLATFORM_FILE_SEEK_END,
    KPLATFORM_FILE_SEEK_CURRENT,
} kplatform_file_seek_enum;

/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_open(kplatform_file_t * outfile, char * path);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_close(kplatform_file_t file);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_read(kplatform_file_t file, i64 length, void * buffer);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_write(kplatform_file_t file, i64 length, void * buffer);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_length(kplatform_file_t file, u64 * outlen);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_time(kplatform_file_t file, f64 * outcreation, f64 * outaccess, f64 * outmod);
/* negative return values are always errors, but there are non-zero successful return values */
/* check `kplatform_file_success_enum` or `enum KplatformFileSeekEnum` */
kplatform_file_success_enum kplatform_file_seek(kplatform_file_t file, i64 offset, kplatform_file_seek_enum seek);

#endif
