#include <stdio.h>

#define ERROR_PRINT(fmt, ...) fprintf(stderr, "[ERROR] %s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef DEBUG
#define INFO_PRINT(fmt, ...) fprintf(stderr, "[INFO] %s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, "[DEBUG] %s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) 
#define INFO_PRINT(fmt, ...)
#endif
  