// --------
#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_fma (unsigned char a, unsigned char b);
#endif
#ifdef PWIDTH_16
void fn_posit_p_fma (unsigned short a, unsigned short b);
#endif
#ifdef PWIDTH_24
void fn_posit_p_fma (unsigned int a, unsigned int b);
#endif
#ifdef PWIDTH_32
void fn_posit_p_fma (unsigned int a, unsigned int b);
#endif
#endif
void fn_posit_fma (float a, float b);
float fn_float_fma (float a, float b, float acc);


// --------
void fn_init_p_quire (unsigned int initVal);
void fn_init_quire (float initVal);


// --------
#ifdef POSIT
#ifdef PWIDTH_8
unsigned char fn_read_p_quire (void);
#endif
#ifdef PWIDTH_16
unsigned short fn_read_p_quire (void);
#endif
#ifdef PWIDTH_24
unsigned int fn_read_p_quire (void);
#endif
#ifdef PWIDTH_32
unsigned int fn_read_p_quire (void);
#endif
#endif

float fn_read_quire (void);


// --------
#ifdef POSIT
#ifdef PWIDTH_8
unsigned char fn_posit_p_vdp (int r, unsigned char a[], unsigned char b[]);
#endif
#ifdef PWIDTH_16
unsigned short fn_posit_p_vdp (int r, unsigned short a[], unsigned short b[]);
#endif
#ifdef PWIDTH_24
unsigned int fn_posit_p_vdp (int r, unsigned int a[], unsigned int b[]);
#endif
#ifdef PWIDTH_32
unsigned int fn_posit_p_vdp (int r, unsigned int a[], unsigned int b[]);
#endif
#endif
float fn_posit_vdp (int r, float a[], float b[]);
float fn_float_vdp (int r, float a[], float b[]);
float fn_float_optimized_vdp (int r, float a[], float b[]);


// --------
#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_gemv          (unsigned char  v_acc[], int r, unsigned char  a[][VSZ], unsigned char b[]);
#endif
#ifdef PWIDTH_16
void  fn_posit_p_gemv         (unsigned short v_acc[], int r, unsigned short a[][VSZ], unsigned short b[]);
#endif
#ifdef PWIDTH_24
void n_posit_p_gemv           (unsigned int   v_acc[], int r, unsigned int   a[][VSZ], unsigned int b[]);
#endif
#ifdef PWIDTH_32
void n_posit_p_gemv           (unsigned int   v_acc[], int r, unsigned int   a[][VSZ], unsigned int b[]);
#endif
#endif
void fn_posit_gemv            (float v_acc[], int r, float a[][VSZ], float b[]);
void fn_float_gemv            (float v_acc[], int r, float a[][VSZ], float b[]);
void fn_float_optimized_gemv  (float v_acc[], int r, float a[][VSZ], float b[]);

// --------
#ifdef POSIT
#ifdef PWIDTH_8
void fn_posit_p_gemm          (unsigned char  m_acc[][VSZ], int r, unsigned char  a[][VSZ], unsigned char  b[][VSZ]);
#endif
#ifdef PWIDTH_16
void  fn_posit_p_gemm         (unsigned short m_acc[][VSZ], int r, unsigned short a[][VSZ], unsigned short b[][VSZ]);
#endif
#ifdef PWIDTH_24
void n_posit_p_gemm           (unsigned int   m_acc[][VSZ], int r, unsigned int   a[][VSZ], unsigned int   b[][VSZ]);
#endif
#ifdef PWIDTH_32
void n_posit_p_gemm           (unsigned int   m_acc[][VSZ], int r, unsigned int   a[][VSZ], unsigned int   b[][VSZ]);
#endif
#endif
void fn_posit_gemm            (float m_acc[][VSZ], int r, float a[][VSZ], float b[][VSZ]);
void fn_float_gemm            (float m_acc[][VSZ], int r, float a[][VSZ], float b[][VSZ]);
void fn_float_optimized_gemm  (float m_acc[][VSZ], int r, float a[][VSZ], float b[][VSZ]);