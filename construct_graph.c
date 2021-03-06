#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <immintrin.h>
#include <string.h>


#include "norms.h"
#include "instrumentation.h"
#include "construct_graph.h"

static double *TheArray;

/**
 * Util methods within this class
 * @param weighted_adj_matrix
 * @param n
 * @param ret
 */

static int cmp(const void *a, const void *b){
    int ia = *(int *)a;
    int ib = *(int *)b;
    return (TheArray[ia] > TheArray[ib]) - (TheArray[ia] < TheArray[ib]);
}

static inline void calculate_diagonal_degree_matrix(double * weighted_adj_matrix, int n, double *ret){
    //ENTER_FUNC;
    NUM_ADDS(n*n);
    int i;
    for (i = 0; i < n-7; i+=8) {
        double d_i = 0,d_i1 = 0,d_i2= 0,d_i3 = 0,d_i4 = 0,d_i5 = 0,d_i6 = 0,d_i7 = 0;
        int j;
        for (j = 0; j < n-7;j+=8) {
            d_i += weighted_adj_matrix[i * n + j];
            d_i1 += weighted_adj_matrix[(i+1) * n + j];
            d_i2 += weighted_adj_matrix[(i+2) * n + j];
            d_i3 += weighted_adj_matrix[(i+3) * n + j];
            d_i4 += weighted_adj_matrix[(i+4) * n + j];
            d_i5 += weighted_adj_matrix[(i+5) * n + j];
            d_i6 += weighted_adj_matrix[(i+6) * n + j];
            d_i7 += weighted_adj_matrix[(i+7) * n + j];

            d_i += weighted_adj_matrix[i * n + j+1];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+1];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+1];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+1];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+1];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+1];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+1];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+1];

            d_i += weighted_adj_matrix[i * n + j+2];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+2];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+2];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+2];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+2];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+2];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+2];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+2];

            d_i += weighted_adj_matrix[i * n + j+3];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+3];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+3];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+3];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+3];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+3];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+3];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+3];

            d_i += weighted_adj_matrix[i * n + j+4];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+4];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+4];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+4];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+4];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+4];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+4];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+4];

            d_i += weighted_adj_matrix[i * n + j+5];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+5];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+5];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+5];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+5];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+5];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+5];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+5];

            d_i += weighted_adj_matrix[i * n + j+6];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+6];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+6];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+6];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+6];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+6];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+6];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+6];

            d_i += weighted_adj_matrix[i * n + j+7];
            d_i1 += weighted_adj_matrix[(i+1) * n + j+7];
            d_i2 += weighted_adj_matrix[(i+2) * n + j+7];
            d_i3 += weighted_adj_matrix[(i+3) * n + j+7];
            d_i4 += weighted_adj_matrix[(i+4) * n + j+7];
            d_i5 += weighted_adj_matrix[(i+5) * n + j+7];
            d_i6 += weighted_adj_matrix[(i+6) * n + j+7];
            d_i7 += weighted_adj_matrix[(i+7) * n + j+7];
        }
        for (; j < n;j++) {
            d_i += weighted_adj_matrix[i * n + j];
            d_i1 += weighted_adj_matrix[(i+1) * n + j];
            d_i2 += weighted_adj_matrix[(i+2) * n + j];
            d_i3 += weighted_adj_matrix[(i+3) * n + j];
            d_i4 += weighted_adj_matrix[(i+4) * n + j];
            d_i5 += weighted_adj_matrix[(i+5) * n + j];
            d_i6 += weighted_adj_matrix[(i+6) * n + j];
            d_i7 += weighted_adj_matrix[(i+7) * n + j];

        }
        ret[i] = d_i;
        ret[i+1] = d_i1;
        ret[i+2] = d_i2;
        ret[i+3] = d_i3;
        ret[i+4] = d_i4;
        ret[i+5] = d_i5;
        ret[i+6] = d_i6;
        ret[i+7] = d_i7;

    }

    for (; i < n; i++) {
        double d_i = 0;
        int j;
        for (j = 0; j < n;j++) {
            d_i += weighted_adj_matrix[i * n + j];


        }
        ret[i] = d_i;


    }


    //EXIT_FUNC;
}

void construct_fully_connected_matrix(double *points, int lines, int dim, double *ret) {
    //ENTER_FUNC;
    for (int i = 0; i < lines-3; i+=4) {
        for (int j = i+1; j < lines; j+=4) {

            ret[i * lines + j] = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            ret[(i+1) * lines + j] = fast_gaussian_similarity(&points[(i+1) * dim], &points[j * dim], dim);
            ret[(i+2) * lines + j] = fast_gaussian_similarity(&points[(i+2) * dim], &points[j * dim], dim);
            ret[(i+3) * lines + j] = fast_gaussian_similarity(&points[(i+3) * dim], &points[j * dim], dim);

            ret[i * lines + j+1] = fast_gaussian_similarity(&points[i * dim], &points[(j+1) * dim], dim);
            ret[(i+1) * lines + j+1] = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+1) * dim], dim);
            ret[(i+2) * lines + j+1] = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+1) * dim], dim);
            ret[(i+3) * lines + j+1] = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+1) * dim], dim);

            ret[i * lines + j+2] = fast_gaussian_similarity(&points[i * dim], &points[(j+2) * dim], dim);
            ret[(i+1) * lines + j+2] = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+2) * dim], dim);
            ret[(i+2) * lines + j+2] = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+2) * dim], dim);
            ret[(i+3) * lines + j+2] = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+2) * dim], dim);

            ret[i * lines + j+3] = fast_gaussian_similarity(&points[i * dim], &points[(j+3) * dim], dim);
            ret[(i+1) * lines + j+3] = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+3) * dim], dim);
            ret[(i+2) * lines + j+3] = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+3) * dim], dim);
            ret[(i+3) * lines + j+3] = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+3) * dim], dim);

        }
        for (int j = 0; j < i; ++j) {
            ret[i*lines+j] = ret[j*lines+i];
            ret[(i+1)*lines+j] = ret[j*lines+i+1];
            ret[(i+2)*lines+j] = ret[j*lines+i+2];
            ret[(i+3)*lines+j] = ret[j*lines+i+3];

        }
    }
    //EXIT_FUNC;
}

void construct_eps_neighborhood_matrix(double *points, int lines, int dim, double *ret) {
    //ENTER_FUNC;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < lines; ++j) {
            ret[i*lines + j] = l2_norm(&points[i*dim], &points[j*dim], dim) < EPS;
        }
    }
    //EXIT_FUNC;
}

void construct_knn_matrix(double *points, int lines, int dim, int k, double *ret) {
    //ENTER_FUNC;
    double vals[lines];
    int indices[lines];

    for (int i = 0; i < lines; ++i) {
        for(int ii = 0; ii < lines; ++ii) {
            indices[ii] = ii;
        }
        for (int j = 0; j < lines; ++j) {
            ret[i*lines + j] = 0.0;
            vals[j] = l2_norm(&points[i*dim], &points[j*dim], dim);
        }
        TheArray = vals;
        size_t len = sizeof(vals) / sizeof(*vals);
        qsort(indices, len, sizeof(*indices), cmp);
        for (int s = 0; s < k+1; ++s) {
            ret[i*lines + indices[s]] = (indices[s] != i) ? 1.0 : 0;
        }
    }
    //EXIT_FUNC;
}

/**
 * Normalized laplacian
 * @param weighted_adj_matrix
 * @param num_points
 * @param ret
 */

void construct_normalized_laplacian_sym_matrix(double *weighted_adj_matrix, int num_points, double *ret){
    //ENTER_FUNC;
    double sqrt_inv_degree_matrix[num_points];  // '1-d' array
    calculate_diagonal_degree_matrix(weighted_adj_matrix, num_points, sqrt_inv_degree_matrix); //load degree_matrix temporarily in sqrt_inv_degree_matrix
    NUM_SQRTS(num_points);
    for (int i =0; i < num_points; i++){
        sqrt_inv_degree_matrix[i] = 1.0/sqrt(sqrt_inv_degree_matrix[i]);
    }
    // compute D^(-1/2) W,  not sure if this code is optimal yet, how to avoid "jumping row"?  process one row each time enccourage spatial locality
    // but with this trick we avoid *0.0
    NUM_MULS(num_points * num_points);
    for (int i = 0; i < num_points; i++){
        for(int j = 0; j < num_points; j++){
            ret[i*num_points + j] = sqrt_inv_degree_matrix[i] * weighted_adj_matrix[i*num_points + j];
        }
    }
    // compute (D^(-1/2)*W)*D^(-1/2)
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            if (i == j) {
                NUM_ADDS(1); NUM_MULS(1);
                ret[i*num_points + j] = 1.0 - ret[i*num_points + j] * sqrt_inv_degree_matrix[j];
            } else {
                NUM_MULS(1);
                ret[i*num_points + j] = -ret[i*num_points + j] * sqrt_inv_degree_matrix[j];
            }
        }
    }
    //EXIT_FUNC;
}

void construct_normalized_laplacian_rw_matrix(double *weighted_adj_matrix, int num_points, double *ret) {
    //ENTER_FUNC;
    double inv_degree_matrix[num_points];
    calculate_diagonal_degree_matrix(weighted_adj_matrix, num_points, inv_degree_matrix); //load degree_matrix temporarily in sqrt_inv_degree_matrix
    NUM_SQRTS(num_points);
    for (int i = 0; i < num_points; i++){
        inv_degree_matrix[i] = 1.0/inv_degree_matrix[i];
    }
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            NUM_MULS(1);
            if (i == j) {
                NUM_ADDS(1);
                ret[i*num_points + j] = 1.0 - inv_degree_matrix[i] * weighted_adj_matrix[i*num_points + j];
            } else {
                ret[i*num_points + j] = -inv_degree_matrix[i] * weighted_adj_matrix[i*num_points + j];
            }
        }
    }
    //EXIT_FUNC;
}

/**
 * Unnormalized laplacian
 * @param points
 * @param n
 * @param dim
 * @param ret
 */

void oneshot_unnormalized_laplacian_base(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;
    NUM_MULS((n*n-n)/2);
    NUM_ADDS(n*n-n);
    for (int i = 0; i < n; i++) {
        double degi;
        degi =  0;
        double tmp;
        for (int j = i+1; j < n; j++) {
            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            degi+=tmp;
            ret[i*n+j] = tmp;
        }
        for (int k = 0; k < i; k++) {
            degi+=ret[k*n+i];
            ret[k*n+i] *= -1;
            ret[i*n+k] = ret[k*n+i];
        }
        ret[i*n+i] = degi;
    }
    //EXIT_FUNC;

}

// BUGGY -- DO NOT USE
void oneshot_unnormalized_laplacian_vec(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;
    NUM_MULS((n*n-n)/2);
    NUM_ADDS(n*n-n);
    __m256d v_tmp, v_degrees, zeros;
    zeros = _mm256_setzero_pd();

    for (int i = 0; i < n; i+=1) {
        v_degrees = zeros;
        int j;
        double tmp;
        double degi = 0;
        for (j = i+1; j < n-3; j+=4) {
            v_tmp = fast_gaussian_similarity_vec(&points[i * dim], &points[j * dim], dim);
            v_degrees = _mm256_add_pd(v_degrees, v_tmp);
            _mm256_storeu_pd(&ret[i*n+j], v_tmp);
        }
        for (; j < n; j++) {
            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            degi += tmp;
            ret[i*n+j] = tmp;
        }
        for (int k = 0; k < i; k++) {
            degi+=ret[k*n+i];
            ret[k*n+i] *= -1;
            // ret[i*n+k] = ret[k*n+i];
        }
        ret[i*n+i] = degi;
    }
    //EXIT_FUNC;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", ret[i*n + j]);
        }
        printf("\n");
    }

}


#define BLOCKSIZE_HD 32

//static void print_m256d(__m256d d) {
//    double *a = (double *) &d;
//    printf("vector: {%lf %lf %lf %lf}\n", a[0], a[1], a[2], a[3]);
//}

void oneshot_unnormalized_laplacian_blocked(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;

    double degrees[n];
    double tmp;
    memset(degrees, 0, n * sizeof(double));

    int i;
    for (i = 0; i < n-(BLOCKSIZE_HD-1); i += BLOCKSIZE_HD) {
        for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
            for (int j1 = i1+1; j1 < i+BLOCKSIZE_HD; j1 += 1) {
                NUM_ADDS(3+3);
                NUM_MULS(1+1);
                tmp = EXP(-0.5 * l2_norm_squared_vec(&points[i1 * dim], &points[j1 * dim], dim));
                ret[i1*n + j1] = -tmp;
                degrees[i1] += tmp;
                degrees[j1] += tmp;
            }
        }
        int j;
        for (j = i+BLOCKSIZE_HD; j < n-(BLOCKSIZE_HD-1); j += BLOCKSIZE_HD) {
            for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
                for (int j1 = j; j1 < j+BLOCKSIZE_HD; j1 += 1) {
                    NUM_ADDS(3+3);
                    NUM_MULS(1+1);
                    tmp = EXP(-0.5 * l2_norm_squared_vec(&points[i1 * dim], &points[j1 * dim], dim));
                    ret[i1*n + j1] = -tmp;
                    degrees[i1] += tmp;
                    degrees[j1] += tmp;
                }
            }
        }
        for (; j < n; j++) {
            for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
                NUM_ADDS(3+3);
                NUM_MULS(1+1);
                tmp = EXP(-0.5 * l2_norm_squared_vec(&points[i1 * dim], &points[j * dim], dim));
                ret[i1*n + j] = -tmp;
                degrees[i1] += tmp;
                degrees[j] += tmp;
            }
        }
    }
    for (; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            NUM_ADDS(3+3);
            NUM_MULS(1+1);
            tmp = EXP(-0.5 * l2_norm_squared_vec(&points[i * dim], &points[j * dim], dim));
            ret[i*n + j] = -tmp;
            degrees[i] += tmp;
            degrees[j] += tmp;
        }
    }

    for (int i = 0; i < n; i++) {
        NUM_MULS(1);
        ret[i*n + i] = degrees[i] * 0.5;
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%lf ", ret[i*n + j]);
    //     }
    //     printf("\n");
    // }

    //EXIT_FUNC;
}


void oneshot_unnormalized_laplacian_vec_blocked(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;

    double degrees[n];
    __m256d tmp_vec;
    double tmp;
    memset(degrees, 0, n * sizeof(double));

    int i;
    for (i = 0; i < n-(BLOCKSIZE_HD-1); i += BLOCKSIZE_HD) {
        for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
            int j1;
            for (j1 = i1+1; j1 < i+BLOCKSIZE_HD-3; j1 += 4) {
                //printf("scalar: {%lf %lf %lf %lf}\n", tmp1, tmp2, tmp3, tmp4);
                tmp_vec = fast_gaussian_similarity_vec(&points[i1 * dim], &points[j1 * dim], dim);
                //print_m256d(tmp_vec);
                _mm256_storeu_pd(&ret[i1*n + j1], -tmp_vec);
                // degrees[i1] += tmp1 + tmp2 + tmp3 + tmp4;
                NUM_ADDS(4+5+4);
                degrees[i1] += -ret[i1*n + j1] - ret[i1*n + j1+1] - ret[i1*n + j1+2] - ret[i1*n + j1+3];
                __m256d degreesj = _mm256_loadu_pd(&degrees[j1]);
                __m256d newdegrees = _mm256_add_pd(degreesj, tmp_vec);
                _mm256_storeu_pd(&degrees[j1], newdegrees);
                // degrees[j1] += tmp1;
                // degrees[j1+1] += tmp2;
                // degrees[j1+2] += tmp3;
                // degrees[j1+3] += tmp4;
            }
            for (; j1 < i+BLOCKSIZE_HD; j1++) {
                tmp = fast_gaussian_similarity(&points[i1 * dim], &points[j1 * dim], dim);
                NUM_ADDS(3);
                ret[i1*n + j1] = -tmp;
                degrees[i1] += tmp;
                degrees[j1] += tmp;
            }
        }
        int j;
        for (j = i+BLOCKSIZE_HD; j < n-(BLOCKSIZE_HD-1); j += BLOCKSIZE_HD) {
            for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
                int j1;
                for (j1 = j; j1 < j+BLOCKSIZE_HD-3; j1 += 4) {
                    // tmp = fast_gaussian_similarity_lowdim(&points[i1 * dim], &points[j1 * dim], dim);
                    // ret[i1*n + j1] = -tmp;
                    // degrees[i1] += tmp;
                    // degrees[j1] += tmp;
                    tmp_vec = fast_gaussian_similarity_vec(&points[i1 * dim], &points[j1 * dim], dim);
                    // tmp_vec = _mm256_set1_pd(1);
                    NUM_ADDS(4+5+4);
                    _mm256_storeu_pd(&ret[i1*n + j1], -tmp_vec);
                    degrees[i1] += -ret[i1*n + j1] - ret[i1*n + j1+1] -ret[i1*n + j1+2] - ret[i1*n + j1+3];
                    __m256d degreesj = _mm256_loadu_pd(&degrees[j1]);
                    __m256d newdegrees = _mm256_add_pd(degreesj, tmp_vec);
                    _mm256_storeu_pd(&degrees[j1], newdegrees);
                }
                for (; j < BLOCKSIZE_HD; j1++) {
                    tmp = fast_gaussian_similarity(&points[i1 * dim], &points[j * dim], dim);
                    NUM_ADDS(3);
                    ret[i1*n + j] = -tmp;
                    degrees[i1] += tmp;
                    degrees[j] += tmp;
                }
            }
        }
        for (; j < n; j++) {
            for (int i1 = i; i1 < i+BLOCKSIZE_HD; i1++) {
                tmp = fast_gaussian_similarity(&points[i1 * dim], &points[j * dim], dim);
                NUM_ADDS(3);
                ret[i1*n + j] = -tmp;
                degrees[i1] += tmp;
                degrees[j] += tmp;
            }
        }
    }
    for (; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            NUM_ADDS(3);
            ret[i*n + j] = -tmp;
            degrees[i] += tmp;
            degrees[j] += tmp;
        }
    }

    for (int i = 0; i < n; i++) {
        NUM_MULS(1);
        ret[i*n + i] = degrees[i] * 0.5;
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%lf ", ret[i*n + j]);
//        }
//        printf("\n");
//    }

    //EXIT_FUNC;
}

#define BLOCKSIZE_LD 8

void oneshot_unnormalized_laplacian_lowdim_blocked(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;

    double degrees[n];
    double tmp;
    memset(degrees, 0, n * sizeof(double));

    int i;
    for (i = 0; i < n-(BLOCKSIZE_LD-1); i += BLOCKSIZE_LD) {
        for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
            for (int j1 = i1+1; j1 < i+BLOCKSIZE_LD; j1 += 1) {
                NUM_ADDS(3+3);
                NUM_MULS(1+1);
                tmp = EXP(-0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[j1 * dim], dim));
                ret[i1*n + j1] = -tmp;
                degrees[i1] += tmp;
                degrees[j1] += tmp;
            }
        }
        int j;
        for (j = i+BLOCKSIZE_LD; j < n-(BLOCKSIZE_LD-1); j += BLOCKSIZE_LD) {
            for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
                for (int j1 = j; j1 < j+BLOCKSIZE_LD; j1 += 1) {
                    NUM_ADDS(3+3);
                    NUM_MULS(1+1);
                    tmp = EXP(-0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[j1 * dim], dim));
                    ret[i1*n + j1] = -tmp;
                    degrees[i1] += tmp;
                    degrees[j1] += tmp;
                }
            }
        }
        for (; j < n; j++) {
            for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
                NUM_ADDS(3+3);
                NUM_MULS(1+1);
                tmp = EXP(-0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[j * dim], dim));
                ret[i1*n + j] = -tmp;
                degrees[i1] += tmp;
                degrees[j] += tmp;
            }
        }
    }
    for (; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            NUM_ADDS(3+3);
            NUM_MULS(1+1);
            tmp = EXP(-0.5 * l2_norm_squared_lowdim(&points[i * dim], &points[j * dim], dim));
            ret[i*n + j] = -tmp;
            degrees[i] += tmp;
            degrees[j] += tmp;
        }
    }

    for (int i = 0; i < n; i++) {
        NUM_MULS(1);
        ret[i*n + i] = degrees[i] * 0.5;
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%lf ", ret[i*n + j]);
    //     }
    //     printf("\n");
    // }

    //EXIT_FUNC;
}

// DO NOT USE -- SLOWER THAN THE NON-VECTORIZED VERSION
void oneshot_unnormalized_laplacian_lowdim_vec_blocked(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;

    double degrees[n];
    double tmp;
    double tmp_array[4] __attribute__((aligned(32)));
    memset(degrees, 0, n * sizeof(double));

    int i;
    for (i = 0; i < n-(BLOCKSIZE_LD-1); i += BLOCKSIZE_LD) {
        for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
            int j1;
            for (j1 = i1+1; j1 < i+BLOCKSIZE_LD-3; j1 += 4) {
                NUM_MULS(4);
                tmp_array[0] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[j1 * dim], dim);
                tmp_array[1] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+1) * dim], dim);
                tmp_array[2] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+2) * dim], dim);
                tmp_array[3] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+3) * dim], dim);
                __m256d vec = _mm256_load_pd(tmp_array);
                vec = exp256_pd_fast(vec);
                _mm256_storeu_pd(&ret[i1*n + j1], -vec);
                NUM_ADDS(4+5+4);
                degrees[i1] += -ret[i1*n + j1] - ret[i1*n + j1+1] - ret[i1*n + j1+2] - ret[i1*n + j1+3];
                __m256d degreesj = _mm256_loadu_pd(&degrees[j1]);
                vec = _mm256_add_pd(degreesj, vec);
                _mm256_storeu_pd(&degrees[j1], vec);
            }
            for (; j1 < i+BLOCKSIZE_LD; j1++) {
                tmp = fast_gaussian_similarity_lowdim(&points[i1 * dim], &points[j1 * dim], dim);
                NUM_ADDS(3);
                ret[i1*n + j1] = -tmp;
                degrees[i1] += tmp;
                degrees[j1] += tmp;
            }
        }
        int j;
        for (j = i+BLOCKSIZE_LD; j < n-(BLOCKSIZE_LD-1); j += BLOCKSIZE_LD) {
            for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
                int j1;
                for (j1 = j; j1 < j+BLOCKSIZE_LD-3; j1 += 4) {
                    NUM_MULS(4);
                    tmp_array[0] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[j1 * dim], dim);
                    tmp_array[1] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+1) * dim], dim);
                    tmp_array[2] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+2) * dim], dim);
                    tmp_array[3] = -0.5 * l2_norm_squared_lowdim(&points[i1 * dim], &points[(j1+3) * dim], dim);
                    __m256d vec = _mm256_load_pd(tmp_array);
                    vec = exp256_pd_fast(vec);
                    _mm256_storeu_pd(&ret[i1*n + j1], -vec);
                    NUM_ADDS(4+5+4);
                    degrees[i1] += -ret[i1*n + j1] - ret[i1*n + j1+1] - ret[i1*n + j1+2] - ret[i1*n + j1+3];
                    __m256d degreesj = _mm256_loadu_pd(&degrees[j1]);
                    vec = _mm256_add_pd(degreesj, vec);
                    _mm256_storeu_pd(&degrees[j1], vec);
                }
                for (; j < BLOCKSIZE_LD; j1++) {
                    tmp = fast_gaussian_similarity_lowdim(&points[i1 * dim], &points[j * dim], dim);
                    NUM_ADDS(3);
                    ret[i1*n + j] = -tmp;
                    degrees[i1] += tmp;
                    degrees[j] += tmp;
                }
            }
        }
        for (; j < n; j++) {
            for (int i1 = i; i1 < i+BLOCKSIZE_LD; i1++) {
                tmp = fast_gaussian_similarity_lowdim(&points[i1 * dim], &points[j * dim], dim);
                NUM_ADDS(3);
                ret[i1*n + j] = -tmp;
                degrees[i1] += tmp;
                degrees[j] += tmp;
            }
        }
    }
    for (; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            tmp = fast_gaussian_similarity_lowdim(&points[i * dim], &points[j * dim], dim);
            NUM_ADDS(3);
            ret[i*n + j] = -tmp;
            degrees[i] += tmp;
            degrees[j] += tmp;
        }
    }

    for (int i = 0; i < n; i++) {
        NUM_MULS(1);
        ret[i*n + i] = degrees[i] * 0.5;
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%lf ", ret[i*n + j]);
    //     }
    //     printf("\n");
    // }

    //EXIT_FUNC;
}

void oneshot_unnormalized_laplacian_lowdim(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;
    // NUM_MULS((n*n-n)/2);
    // NUM_ADDS(n*n-n);
    for (int i = 0; i < n; i++) {
        double degi;
        degi =  0;
        double tmp;
        for (int j = i+1; j < n; j++) {
            tmp = fast_gaussian_similarity_lowdim(&points[i * dim], &points[j * dim], dim);
            NUM_ADDS(1);
            degi+=tmp;
            ret[i*n+j] = tmp;
        }
        for (int k = 0; k < i; k++) {
            degi+=ret[k*n+i];
            NUM_ADDS(1);
            ret[k*n+i] *= -1;
            NUM_MULS(1);
        }
        ret[i*n+i] = degi/2;
        NUM_DIVS(1);
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%lf ", ret[i*n+j]);
    //     }
    //     printf("\n");
    // }
    //EXIT_FUNC;

}

// BUGGY -- DO NOT USE
void oneshot_unnormalized_laplacian_roll(double *points, int n, int dim, double *ret) {
    //ENTER_FUNC;
    NUM_MULS((n*n-n)/2);
    NUM_ADDS(n*n-n);
    int i;
    for (i = 0; i < n; i++) {
        double degi, degi1, degi2, degi3, degi4, degi5, degi6, degi7;
        degi = degi1 = degi2 = degi3 = degi4 = degi5 = degi6 = degi7 = 0;
        double tmp;
        int j;
        for (j = i+1; j < n-7; j+=8) {

            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            degi+=tmp;
            ret[i*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[j * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[j * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[j * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[j * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[j * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[j * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[j * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+1) * dim], dim);
            degi+=tmp;
            ret[i*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+1) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+1) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+1) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+1) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+1) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+1) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+1) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+1] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+2) * dim], dim);
            degi+=tmp;
            ret[i*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+2) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+2) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+2) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+2) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+2) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+2) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+2) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+2] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+3) * dim], dim);
            degi+=tmp;
            ret[i*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+3) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+3) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+3) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+3) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+3) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+3) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+3) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+3] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+4) * dim], dim);
            degi+=tmp;
            ret[i*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+4) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+4) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+4) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+4) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+4) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+4) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+4) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+4] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+5) * dim], dim);
            degi+=tmp;
            ret[i*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+5) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+5) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+5) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+5) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+5) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+5) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+5) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+5] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+6) * dim], dim);
            degi+=tmp;
            ret[i*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+6) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+6) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+6) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+6) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+6) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+6) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+6) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+6] = tmp;

            tmp = fast_gaussian_similarity(&points[i * dim], &points[(j+7) * dim], dim);
            degi+=tmp;
            ret[i*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[(j+7) * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[(j+7) * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[(j+7) * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[(j+7) * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[(j+7) * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[(j+7) * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j+7] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[(j+7) * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j+7] = tmp;
        }
        for(; j < n; j++) {
            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            degi+=tmp;
            ret[i*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+1) * dim], &points[j * dim], dim);
            degi1+=tmp;
            ret[(i+1)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+2) * dim], &points[j * dim], dim);
            degi2+=tmp;
            ret[(i+2)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+3) * dim], &points[j * dim], dim);
            degi3+=tmp;
            ret[(i+3)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+4) * dim], &points[j * dim], dim);
            degi4+=tmp;
            ret[(i+4)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+5) * dim], &points[j * dim], dim);
            degi5+=tmp;
            ret[(i+5)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+6) * dim], &points[j * dim], dim);
            degi6+=tmp;
            ret[(i+6)*n+j] = tmp;

            tmp = fast_gaussian_similarity(&points[(i+7) * dim], &points[j * dim], dim);
            degi7+=tmp;
            ret[(i+7)*n+j] = tmp;
        }
        int k;
        for (k = 0; k < i-8; k+=8) {

            degi+=ret[k*n+i];
            ret[k*n+i] *= -1;
            ret[i*n+k] = ret[k*n+i];

            degi1+=ret[k*n+i+1];
            ret[k*n+i+1] *= -1;
            ret[(i+1)*n+k] = ret[k*n+i+1];

            degi2+=ret[k*n+i+2];
            ret[k*n+i+2] *= -1;
            ret[(i+2)*n+k] = ret[k*n+i+2];


            degi3+=ret[k*n+i+3];
            ret[k*n+i+3] *= -1;
            ret[(i+3)*n+k] = ret[k*n+i+3];


            degi4+=ret[k*n+i+4];
            ret[k*n+i+4] *= -1;
            ret[(i+4)*n+k] = ret[k*n+i+4];


            degi5+=ret[k*n+i+5];
            ret[k*n+i+5] *= -1;
            ret[(i+5)*n+k] = ret[k*n+i+5];


            degi6+=ret[k*n+i+6];
            ret[k*n+i+6] *= -1;
            ret[(i+6)*n+k] = ret[k*n+i+6];


            degi7+=ret[k*n+i+7];
            ret[k*n+i+7] *= -1;
            ret[(i+7)*n+k] = ret[k*n+i+7];


            degi+=ret[(k+1)*n+i];
            ret[(k+1)*n+i] *= -1;
            ret[i*n+k+1] = ret[(k+1)*n+i];


            degi1+=ret[(k+1)*n+i+1];
            ret[(k+1)*n+i+1] *= -1;
            ret[(i+1)*n+k+1] = ret[(k+1)*n+i+1];


            degi2+=ret[(k+1)*n+i+2];
            ret[(k+1)*n+i+2] *= -1;
            ret[(i+2)*n+k+1] = ret[(k+1)*n+i+2];


            degi3+=ret[(k+1)*n+i+3];
            ret[(k+1)*n+i+3] *= -1;
            ret[(i+3)*n+k+1] = ret[(k+1)*n+i+3];


            degi4+=ret[(k+1)*n+i+4];
            ret[(k+1)*n+i+4] *= -1;
            ret[(i+4)*n+k+1] = ret[(k+1)*n+i+4];


            degi5+=ret[(k+1)*n+i+5];
            ret[(k+1)*n+i+5] *= -1;
            ret[(i+5)*n+k+1] = ret[(k+1)*n+i+5];


            degi6+=ret[(k+1)*n+i+6];
            ret[(k+1)*n+i+6] *= -1;
            ret[(i+6)*n+k+1] = ret[(k+1)*n+i+6];


            degi7+=ret[(k+1)*n+i+7];
            ret[(k+1)*n+i+7] *= -1;
            ret[(i+7)*n+k+1] = ret[(k+1)*n+i+7];


            degi+=ret[(k+2)*n+i];
            ret[(k+2)*n+i] *= -1;
            ret[i*n+k+2] = ret[(k+2)*n+i];


            degi1+=ret[(k+2)*n+i+1];
            ret[(k+2)*n+i+1] *= -1;
            ret[(i+1)*n+k+2] = ret[(k+2)*n+i+1];


            degi2+=ret[(k+2)*n+i+2];
            ret[(k+2)*n+i+2] *= -1;
            ret[(i+2)*n+k+2] = ret[(k+2)*n+i+2];


            degi3+=ret[(k+2)*n+i+3];
            ret[(k+2)*n+i+3] *= -1;
            ret[(i+3)*n+k+2] = ret[(k+2)*n+i+3];


            degi4+=ret[(k+2)*n+i+4];
            ret[(k+2)*n+i+4] *= -1;
            ret[(i+4)*n+k+2] = ret[(k+2)*n+i+4];


            degi5+=ret[(k+2)*n+i+5];
            ret[(k+2)*n+i+5] *= -1;
            ret[(i+5)*n+k+2] = ret[(k+2)*n+i+5];

            degi6+=ret[(k+2)*n+i+6];
            ret[(k+2)*n+i+6] *= -1;
            ret[(i+6)*n+k+2] = ret[(k+2)*n+i+6];

            degi7+=ret[(k+2)*n+i+7];
            ret[(k+2)*n+i+7] *= -1;
            ret[(i+7)*n+k+2] = ret[(k+2)*n+i+7];


            degi+=ret[(k+3)*n+i];
            ret[(k+3)*n+i] *= -1;
            ret[i*n+k+3] = ret[(k+3)*n+i];



            degi1+=ret[(k+3)*n+i+1];
            ret[(k+3)*n+i+1] *= -1;
            ret[(i+1)*n+k+3] = ret[(k+3)*n+i+1];


            degi2+=ret[(k+3)*n+i+2];
            ret[(k+3)*n+i+2] *= -1;
            ret[(i+2)*n+k+3] = ret[(k+3)*n+i+2];


            degi3+=ret[(k+3)*n+i+3];
            ret[(k+3)*n+i+3] *= -1;
            ret[(i+3)*n+k+3] = ret[(k+3)*n+i+3];


            degi4+=ret[(k+3)*n+i+4];
            ret[(k+3)*n+i+4] *= -1;
            ret[(i+4)*n+k+3] = ret[(k+3)*n+i+4];


            degi5+=ret[(k+3)*n+i+5];
            ret[(k+3)*n+i+5] *= -1;
            ret[(i+5)*n+k+3] = ret[(k+3)*n+i+5];


            degi6+=ret[(k+3)*n+i+6];
            ret[(k+3)*n+i+6] *= -1;
            ret[(i+6)*n+k+3] = ret[(k+3)*n+i+6];


            degi7+=ret[(k+3)*n+i+7];
            ret[(k+3)*n+i+7] *= -1;
            ret[(i+7)*n+k+3] = ret[(k+3)*n+i+7];


            degi+=ret[(k+4)*n+i];
            ret[(k+4)*n+i] *= -1;
            ret[i*n+k+4] = ret[(k+4)*n+i];


            degi1+=ret[(k+4)*n+i+1];
            ret[(k+4)*n+i+1] *= -1;
            ret[(i+1)*n+k+4] = ret[(k+4)*n+i+1];


            degi2+=ret[(k+4)*n+i+2];
            ret[(k+4)*n+i+2] *= -1;
            ret[(i+2)*n+k+4] = ret[(k+4)*n+i+2];


            degi3+=ret[(k+4)*n+i+3];
            ret[(k+4)*n+i+3] *= -1;
            ret[(i+3)*n+k+4] = ret[(k+4)*n+i+3];


            degi4+=ret[(k+4)*n+i+4];
            ret[(k+4)*n+i+4] *= -1;
            ret[(i+4)*n+k+4] = ret[(k+4)*n+i+4];


            degi5+=ret[(k+4)*n+i+5];
            ret[(k+4)*n+i+5] *= -1;
            ret[(i+5)*n+k+4] = ret[(k+4)*n+i+5];


            degi6+=ret[(k+4)*n+i+6];
            ret[(k+4)*n+i+6] *= -1;
            ret[(i+6)*n+k+4] = ret[(k+4)*n+i+6];


            degi7+=ret[(k+4)*n+i+7];
            ret[(k+4)*n+i+7]*= -1;
            ret[(i+7)*n+k+4] = ret[(k+4)*n+i+7];


            degi+=ret[(k+5)*n+i];
            ret[(k+5)*n+i] *= -1;
            ret[i*n+k+5] = ret[(k+5)*n+i];


            degi1+=ret[(k+5)*n+i+1];
            ret[(k+5)*n+i+1] *= -1;
            ret[(i+1)*n+k+5] = ret[(k+5)*n+i+1];


            degi2+=ret[(k+5)*n+i+2];
            ret[(k+5)*n+i+2] *= -1;
            ret[(i+2)*n+k+5] = ret[(k+5)*n+i+2];


            degi3+=ret[(k+5)*n+i+3];
            ret[(k+5)*n+i+3] *= -1;
            ret[(i+3)*n+k+5] = ret[(k+5)*n+i+3];


            degi4+=ret[(k+5)*n+i+4];
            ret[(k+5)*n+i+4] *= -1;
            ret[(i+4)*n+k+5] = ret[(k+5)*n+i+4];


            degi5+=ret[(k+5)*n+i+5];
            ret[(k+5)*n+i+5] *= -1;
            ret[(i+5)*n+k+5] = ret[(k+5)*n+i+5];


            degi6+=ret[(k+5)*n+i+6];
            ret[(k+5)*n+i+6] *= -1;
            ret[(i+6)*n+k+5] = ret[(k+5)*n+i+6];


            degi7+=ret[(k+5)*n+i+7];
            ret[(k+5)*n+i+7] *= -1;
            ret[(i+7)*n+k+5] = ret[(k+5)*n+i+7];


            degi+=ret[(k+6)*n+i];
            ret[(k+6)*n+i] *= -1;
            ret[i*n+k+6] = ret[(k+6)*n+i];


            degi1+=ret[(k+6)*n+i+1];
            ret[(k+6)*n+i+1] *= -1;
            ret[(i+1)*n+k+6] = ret[(k+6)*n+i+1];



            degi2+=ret[(k+6)*n+i+2];
            ret[(k+6)*n+i+2] *= -1;
            ret[(i+2)*n+k+6] = ret[(k+6)*n+i+2];


            degi3+=ret[(k+6)*n+i+3];
            ret[(k+6)*n+i+3] *= -1;
            ret[(i+3)*n+k+6] = ret[(k+6)*n+i+3];


            degi4+=ret[(k+6)*n+i+4];
            ret[(k+6)*n+i+4] *= -1;
            ret[(i+4)*n+k+6] = ret[(k+6)*n+i+4];


            degi5+=ret[(k+6)*n+i+5];
            ret[(k+6)*n+i+5] *= -1;
            ret[(i+5)*n+k+6] = ret[(k+6)*n+i+5];


            degi6+=ret[(k+6)*n+i+6];
            ret[(k+6)*n+i+6] *= -1;
            ret[(i+6)*n+k+6] = ret[(k+6)*n+i+6];


            degi7+=ret[(k+6)*n+i+7];
            ret[(k+6)*n+i+7] *= -1;
            ret[(i+7)*n+k+6] = ret[(k+6)*n+i+7];


            degi+=ret[(k+7)*n+i];
            ret[(k+7)*n+i] *= -1;
            ret[i*n+k+7] = ret[(k+7)*n+i];



            degi1+=ret[(k+7)*n+i+1];
            ret[(k+7)*n+i+1] *= -1;
            ret[(i+1)*n+k+7] = ret[(k+7)*n+i+1];


            degi2+=ret[(k+7)*n+i+2];
            ret[(k+7)*n+i+2] *= -1;
            ret[(i+2)*n+k+7] = ret[(k+7)*n+i+2];


            degi3+=ret[(k+7)*n+i+3];
            ret[(k+7)*n+i+3] *= -1;
            ret[(i+3)*n+k+7] = ret[(k+7)*n+i+3];


            degi4+=ret[(k+7)*n+i+4];
            ret[(k+7)*n+i+4] *= -1;
            ret[(i+4)*n+k+7] = ret[(k+7)*n+i+4];



            degi5+=ret[(k+7)*n+i+5];
            ret[(k+7)*n+i+5] *= -1;
            ret[(i+5)*n+k+7] = ret[(k+7)*n+i+5];


            degi6+=ret[(k+7)*n+i+6];
            ret[(k+7)*n+i+6] *= -1;
            ret[(i+6)*n+k+7] = ret[(k+7)*n+i+6];


            degi7+=ret[(k+7)*n+i+7];
            ret[(k+7)*n+i+7] *= -1;
            ret[(i+7)*n+k+7] = ret[(k+7)*n+i+7];


        }
        for(; k < i; k++) {
            degi+=ret[k*n+i];
            ret[k*n+i] *= -1;
            ret[i*n+k] = ret[k*n+i];


            degi1+=ret[k*n+i+1];
            ret[k*n+i+1] *= -1;
            ret[(i+1)*n+k] = ret[k*n+i+1];


            degi2+=ret[k*n+i+2];
            ret[k*n+i+2]*= -1;
            ret[(i+2)*n+k] = ret[k*n+i+2];


            degi3+=ret[k*n+i+3];
            ret[k*n+i+3] *= -1;
            ret[(i+3)*n+k] = ret[k*n+i+3];


            degi4+=ret[k*n+i+4];
            ret[k*n+i+4]*= -1;
            ret[(i+4)*n+k] = ret[k*n+i+4];

            degi5+=ret[k*n+i+5];
            ret[k*n+i+5] *= -1;
            ret[(i+5)*n+k] = ret[k*n+i+5];


            degi6+=ret[k*n+i+6];
            ret[k*n+i+6] *= -1;
            ret[(i+6)*n+k] = ret[k*n+i+6];


            degi7+=ret[k*n+i+7];
            ret[k*n+i+7]*= -1;
            ret[(i+7)*n+k] = ret[k*n+i+7];

        }
        ret[i*n+i] = degi;
        ret[(i+1)*n+i+1] = degi1;
        ret[(i+2)*n+i+2] = degi2;
        ret[(i+3)*n+i+3] = degi3;
        ret[(i+4)*n+i+4] = degi4;
        ret[(i+5)*n+i+5] = degi5;
        ret[(i+6)*n+i+6] = degi6;
        ret[(i+7)*n+i+7] = degi7;


    }
    for(; i < n; i++) {
        double degi = 0;
        double tmp;
        for (int j = i+1; j < n; j++) {
            tmp = fast_gaussian_similarity(&points[i * dim], &points[j * dim], dim);
            degi+=tmp;
            ret[i*n+j] = tmp;
        }
        for (int j = 0; j < i; ++j) {
            degi+=ret[j*n+i];
            ret[j*n+i] *= -1;
            ret[i*n+j] = ret[j*n+i];
        }
        ret[i*n+i] = degi;
    }
    //EXIT_FUNC;
}

void construct_unnormalized_laplacian(double *graph, int n, double *ret) {
    //ENTER_FUNC;
    // double* degrees = (double *)malloc(n * n * sizeof(double));
    double degrees[n];
    calculate_diagonal_degree_matrix(graph, n, degrees);
    //NUM_ADDS(n*n);
    NUM_MULS(n*n);
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j+=4) {
            //if(i==j) continue; DON'T COMPUTE THE DIAGONAL ELEMENTS (BETTER WHEN VECTORIZING)
            ret[i * n + j] = -1 * graph[i * n + j];

            ret[i * n + j+1] = -1 * graph[i * n + j+1];

            ret[i * n + j+2] = -1 * graph[i * n + j+2];

            ret[i * n + j+3] = -1 * graph[i * n + j+3];


        }

        ret[i*n+i] = degrees[i];

    }

    //EXIT_FUNC;
}


/**
 * Generic methods for main.c
 * @param points
 * @param n
 * @param dim
 * @param ret
 */

void oneshot_unnormalized_laplacian(double *points, int n, int dim, double *ret) {
    oneshot_unnormalized_laplacian_base(points, n, dim, ret);
}
