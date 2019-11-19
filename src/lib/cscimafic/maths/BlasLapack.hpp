#ifndef BlasLapackHPP
#define BlasLapackHPP

#ifdef HAVE_MKL_ILP64
// 64-bit integer - ILP64
typedef long int BL_INT;
#else
// standard 32-bit integer
typedef int BL_INT;
#endif

//------------------------------------------------------------------------------
// blas entry points

extern "C" double ddot_(BL_INT* N,double* DX,BL_INT* INCX,double* DY,BL_INT* INCY);
extern "C" void dgemv_(char* trans,BL_INT* M, BL_INT* N, double* ALPHA,
                      double* A,BL_INT* LDA,double* X,BL_INT* INCX,double* BETA,double* Y,BL_INT* INCY);

extern "C" void dgemm_(char* transa, char* transb,BL_INT* M,BL_INT* N,BL_INT* K,double* alpha,
                       double* a,BL_INT* lda,double* b,BL_INT* ldb,double* beta,double* c, BL_INT* ldc);

//------------------------------------------------------------------------------
// lapack entry points

extern "C" void dsyev_(char* jobz,char* uplo,BL_INT* n,double* a,BL_INT* lda,double* w,
                       double* work,BL_INT* lwork,BL_INT* info);

extern "C" void dgetrf_(BL_INT* m,BL_INT* n,double* a,BL_INT* lda,BL_INT* ipiv,BL_INT* info);
extern "C" void dgetrs_(char* trans,BL_INT* n,BL_INT* nrhs,double* a,BL_INT* lda,BL_INT* ipiv,double* b,BL_INT* ldb,BL_INT* info);
extern "C" void dgelsd_(BL_INT* m,BL_INT* n,BL_INT* nrhs,double* a,BL_INT* lda, double* b,BL_INT* ldb,
                        double* s, double* rcond, BL_INT* rank,
                        double* work, BL_INT* lwork, BL_INT* iwork, BL_INT* info);
extern "C" void dgels_(char* trans,BL_INT* m,BL_INT* n,BL_INT* nrhs,double* a,BL_INT* lda, double* b,BL_INT* ldb,
                        double* work, BL_INT* lwork, BL_INT* info);
extern "C" void dgetri_(BL_INT* m,double* a,BL_INT* lda,BL_INT* ipiv,double* work, BL_INT* lwork,BL_INT* info);

// SVD - simple driver
extern "C" void dgesvd_(char* jobu,char* jobvt,BL_INT* m,BL_INT* n,double* a,BL_INT* lda,double* s,double* u,BL_INT* ldu,
                        double* vt,BL_INT* ldvt,double* work,BL_INT* lwork,BL_INT* info);

// SVD - divide and conquer
extern "C" void dgesdd_(char* jobz,BL_INT* m,BL_INT* n,double* a,BL_INT* lda,double* s,double* u,BL_INT* ldu,
                        double* vt,BL_INT* ldvt,double* work,BL_INT* lwork,BL_INT* iwork,BL_INT* info);

// Cholesky factorization
extern "C" void dpotrf_(char* uplo,BL_INT* n,double* a,BL_INT* lda,BL_INT* info);
extern "C" void dpotri_(char* uplo,BL_INT* n,double* a,BL_INT* lda,BL_INT* info);
extern "C" void dpotrs_(char* uplo,BL_INT* n,BL_INT* nrhs,double* a,BL_INT* lda,double* b,BL_INT* ldb,BL_INT* info);

//------------------------------------------------------------------------------

#endif
