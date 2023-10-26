// File: A2_S8_20220008_4.cpp
// Purpose: Solving Problem no. 4
// Author: Ahmed Osama Fathy.
// Section: S8
// ID: 20220008
// TA: Khaled Ahmed
// Date: 26 Oct 2023
#include <iostream>
#include <vector>

const int N = 1e8;
bool isPrime[N];
std::vector<int> primes;
void sieve() {
    for (bool &i: isPrime)
        i = true;

    for (long long i = 2; i < N; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (long long j = i * i; j < N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}


int main() {
    sieve();
    while (true) {
        printf("Enter 0 to Quit!\n");
        printf("Enter a number to print all primes from 1 -> n\n>> ");
        int n;
        std::cin >> n;
        if(n <= 0) return 0;
        for (int i = 0; i < primes.size() && primes[i] <= n; ++i) {
            printf("%d ", primes[i]);
        }
        puts("");
    }
}
