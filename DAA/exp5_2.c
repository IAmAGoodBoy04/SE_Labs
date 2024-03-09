#include <stdio.h>
#include <limits.h>

#define N 100 // Assuming the maximum number of matrices does not exceed 100

// Function to print the m matrix (costs)
void printCostMatrix(int m[N][N], int n) {
    printf("Cost Matrix M:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j)
                printf("%10d", m[i][j]);
            else
                printf("          "); // Align for better readability
        }
        printf("\n");
    }
}

// Function to print the s matrix (optimal splits)
void printSplitMatrix(int s[N][N], int n) {
    printf("Split Matrix S (0 indicates no split):\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i < j)
                printf("%10d", s[i][j]);
            else
                printf("          "); // Align for better readability
        }
        printf("\n");
    }
}

// Auxiliary function to print the optimal parenthesization
void printOptimalParens(int s[N][N], int i, int j) {
    if (i == j)
        printf("M%d", i);
    else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void MatrixChainOrder(int p[], int n) {
    int m[N][N];
    int s[N][N];

    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications is %d\n", m[1][n-1]);
    printf("Optimal Parenthesization: ");
    printOptimalParens(s, 1, n-1);
    printf("\n\n");

    printCostMatrix(m, n);
    printf("\n");
    printSplitMatrix(s, n);
}

int main() {
    int p[] = {10, 100, 5, 50, 20, 15, 30, 25, 40, 20, 30}; // Example dimensions for 10 matrices
    int n = sizeof(p)/sizeof(p[0]);

    MatrixChainOrder(p, n);

    return 0;
}
