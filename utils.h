#ifndef utils_h
#define utils_h

#define isNullChar(X) (iscntrl(X) || isspace(X))

typedef enum { false, true } bool;

extern bool _panic;

inline void panic(char* message, char* arg);
inline void recover(bool verbose);

#endif