#pragma once

#ifdef _WIN32
  #define freyr_EXPORT __declspec(dllexport)
#else
  #define freyr_EXPORT
#endif

freyr_EXPORT void freyr();
