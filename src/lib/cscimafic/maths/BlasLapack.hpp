#ifndef BlasLapackHPP
#define BlasLapackHPP

//------------------------------------------------------------------------------
// blas entry points

extern "C" double ddot_(int* N,double* DX,int* INCX,double* DY,int* INCY);
extern "C" void dgemv_(char* trans,int* M, int* N, double* ALPHA,
                      double* A,int* LDA,double* X,int* INCX,double* BETA,double* Y,int* INCY);

extern "C" void dgemm_(char* transa, char* transb,int* M,int* N,int* K,double* alpha,
                       double* a,int* lda,double* b,int* ldb,double* beta,double* c, int* ldc);

//------------------------------------------------------------------------------
// lapack entry points

extern "C" void dsyev_(char* jobz,char* uplo,int* n,double* a,int* lda,double* w,
                       double* work,int* lwork,int* info);

extern "C" void dgetrf_(int* m,int* n,double* a,int* lda,int* ipiv,int* info);
extern "C" void dgetrs_(char* trans,int* n,int* nrhs,double* a,int* lda,int* ipiv,double* b,int* ldb,int* info);
extern "C" void dgelsd_(int* m,int* n,int* nrhs,double* a,int* lda, double* b,int* ldb,
                        double* s, double* rcond, int* rank,
                        double* work, int* lwork, int* iwork, int* info);
extern "C" void dgels_(char* trans,int* m,int* n,int* nrhs,double* a,int* lda, double* b,int* ldb,
                        double* work, int* lwork, int* info);
extern "C" void dgetri_(int* m,double* a,int* lda,int* ipiv,double* work, int* lwork,int* info);

// SVD - simple driver
extern "C" void dgesvd_(char* jobu,char* jobvt,int* m,int* n,double* a,int* lda,double* s,double* u,int* ldu,
                        double* vt,int* ldvt,double* work,int* lwork,int* info);

// SVD - divide and conquer
extern "C" void dgesdd_(char* jobz,int* m,int* n,double* a,int* lda,double* s,double* u,int* ldu,
                        double* vt,int* ldvt,double* work,int* lwork,int* iwork,int* info);

// Cholesky factorization
extern "C" void dpotrf_(char* uplo,int* n,double* a,int* lda,int* info);
extern "C" void dpotri_(char* uplo,int* n,double* a,int* lda,int* info);

//------------------------------------------------------------------------------

#endif
