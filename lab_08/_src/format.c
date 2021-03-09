#include <main.h>

struct Matrix *fread_coord_matrix(FILE *fd, enum MatrixMemoryType type);
struct Matrix *fread_plain_matrix(FILE *fd, enum MatrixMemoryType type);

void fwrite_coord_matrix(FILE *fd, struct Matrix *m);
void fwrite_plain_matrix(FILE *fd, struct Matrix *m);

struct Matrix *fread_matrix(FILE *fd, enum MatrixMemoryType type) {
#if defined(FORMAT_PLAIN)
    return fread_plain_matrix(fd, type);
#elif defined(FORMAT_COORD)
    return fread_coord_matrix(fd, type);
#else
#error "Read matrix format not defined"
#endif
}

void fwrite_matrix(FILE *fd, struct Matrix *m) {
#if defined(FORMAT_PLAIN)
    fwrite_plain_matrix(fd, m);
#elif defined(FORMAT_COORD)
    fwrite_coord_matrix(fd, m);
#else
#error "Read matrix format not defined"
#endif
}
