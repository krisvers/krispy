#ifndef KRISPY_KAPI_H
#define KRISPY_KAPI_H

#include <krispy.h>
#include <kplatform.h>

#ifdef KEXPORT
	#ifdef KRISPY_KPLATFORM_WINDOWS
		#define KAPI __declspec(dllexport)
	#else
		#define KAPI __attribute__((visibility("default")))
	#endif
#else
	#ifdef KRISPY_KPLATFORM_WINDOWS
		#define KAPI __declspec(dllimport)
	#else
		#define KAPI
	#endif
#endif

#endif
