#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<complex>
#include<math.h>
using namespace std;
typedef complex<double> C;

const int N = 1048580;
const double pi = acos(-1.0);
complex<double> a[N], b[N], c[N];
char s[N];
int n, n1, n2, m, r[N], L;

void FFT(C *a, int tag){
	for(int i = 0; i < n; i++)
        if(i < r[i])
            swap(a[i], a[r[i]]);
	for(int i = 1; i < n; i<<=1){
		C bot(cos(pi/i), tag * sin(pi/i));
		for(int j = 0; j < n; j += (i << 1)){
			C w(1, 0);
			for(int k = 0; k < i; k++, w*=bot){
				C x = a[j + k], y=w * a[i + j + k];
				a[j + k] = x + y; a[i + j + k] = x - y;
			}
		}
	}if(tag == -1)
        for(int i = 0; i < n; i++)
            a[i] /= n;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output_.txt","w",stdout);
	scanf("%s",s);
    n1 = strlen(s) - 1;
    std::reverse(s, s + n1 + 1);
	for(int i = 0; i <= n1; i++)
        a[i] = s[i] - '0'; 
    scanf("%s",s);
	n2 = strlen(s) - 1;
    std::reverse(s, s + n2 + 1);
	for(int i = 0; i <= n2; i++)
        b[i] = s[i] - '0'; 
    m = n1 + n2;
	for(n = 1; n <= m; n <<= 1)
        L++;
	for(int i = 0; i < n; i++)
        r[i] = (r[i >> 1] >> 1)|((i & 1) << (L - 1));
	FFT(a, 1);FFT(b, 1);
	for(int i = 0; i < n; i++)
        c[i] = a[i] * b[i];
	FFT(c, -1);
	for(int i = 0; i <= m; i++){
        c[i + 1] += (int)(c[i].real() + .5) / 10;
        c[i] = (int)(c[i].real() + .5) % 10;
    }
    if(((int)(c[m + 1].real() + .5)) > 0)
        printf("%d", (int)(c[m + 1].real() + .5));
    for(int i = m; i >= 0; i--)
        printf("%d", (int)(c[i].real() + .5));
    printf("\n");
    return 0;
} 