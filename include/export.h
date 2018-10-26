#ifndef INCLUDE_EXPORT_H_
#define INCLUDE_EXPORT_H_

#if defined(STANDALONE_BUILD)
#if defined(WIN32)

#if defined(BASE_IMPLEMENTATION)
#define MLLIB_EXPORT__declspec(dllexport)
#else
#define MLLIB_EXPORT__declspec(dllimport)
#endif  // defined(BASE_IMPLEMENTATION)

#else  // defined(WIN32)
#define MLLIB_EXPORT__attribute__((visibility("default")))
#endif

#else  // defined(STANDALONE_BUILD)
#define MLLIB_EXPORT
#endif

#endif  // INCLUDE_EXPORT_H_
