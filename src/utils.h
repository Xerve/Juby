#ifndef utils_h
#define utils_h

#define isNullChar(X) (iscntrl(X) || isspace(X))
#define err(X, Y, Z) panic(X, Object_name(Y)); return Z

typedef enum { false, true } bool;

extern bool _panic;

inline void panic(char* message, char* arg);
inline void recover(bool verbose);

#endif
