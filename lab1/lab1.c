#include <emmintrin.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

class Timer
{
    time_point<steady_clock> m_Start;

public:
    Timer()
    {
        m_Start = high_resolution_clock::now();
    }

    ~Timer()
    {
        auto stop = high_resolution_clock::now();
        const auto durationMs = duration_cast<milliseconds>(stop - m_Start) % 1000;
        const auto durationSec = duration_cast<seconds>(stop - m_Start);
        printf("DURATION: %lld.%lld \n", durationSec.count(), durationMs.count());
    }
};

void normal(float* a, int N)
{
    for (int i = 0; i < N; ++i)
        a[i] = sqrt(a[i]);
}

void normal(float* a, float* b, int N)
{
    for (int i = 0; i < N; ++i)
        a[i] = sqrt(a[i]) + sqrt(b[i]);
}

void sse(float* a, int N)
{
    // We assume N % 4 == 0. 
    int nb_iters = N / 4;
    __m128* ptr = (__m128*)a;

    for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)
        _mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

void sse(float* a, const float* b, int N)
{
    int nb_iters = N / 16;

    __m128i* l = (__m128i*)a;
    __m128i* r = (__m128i*)b;

    for (int i = 0; i < nb_iters; ++i, ++l, ++r)
        _mm_store_si128(l, _mm_add_epi8(*l, *r));
}

int main(int argc, char** argv)
{
    int N = 10000000000;

    float* a = new float[N];
    //a = (float*)_aligned_malloc(16, N * sizeof(float));

    for (int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    {
        Timer t;
        normal(a, N);
    }

    for (int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    {
        Timer t;
        sse(a, N);
    }

    {
        Timer t;
        normal(a, a, N);
    }

    {
        Timer t;
        sse(a, a, N);
    }

    delete[] a;
    a = nullptr;
}
