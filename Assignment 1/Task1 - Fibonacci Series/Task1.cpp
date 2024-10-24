#include <iostream>

using namespace std;

#define ll long long

/// @brief Function to compute Fibonacci using Recursion
/// @param n long long
/// @return long long
/// @details Time Complexity: O(2^n)
ll fibonacciRecursion(ll n){
    if(n <= 1)
        return n;
    return fibonacciRecursion(n-1) + fibonacciRecursion(n-2);
}

/// @brief Function to multiply two matrices
/// @param f 2x2 matrix
/// @param m 2x2 matrix
void multiply(ll f[2][2], ll m[2][2]){
    ll f00 = f[0][0] * m[0][0] + f[0][1] * m[1][0];
    ll f01 = f[0][0] * m[0][1] + f[0][1] * m[1][1];
    ll f10 = f[1][0] * m[0][0] + f[1][1] * m[1][0];
    ll f11 = f[1][0] * m[0][1] + f[1][1] * m[1][1];

    f[0][0] = f00;
    f[0][1] = f01;
    f[1][0] = f10;
    f[1][1] = f11;
}

/// @brief Function to compute power of a matrix
/// @param f 2x2 matrix
/// @param n long long
void power(ll f[2][2], ll n){
    if(n <= 1)
        return;

    ll m[2][2] = {{1, 1}, {1, 0}};
    power(f, n/2);
    multiply(f, f);

    if(n%2)
        multiply(f, m);
}

/// @brief Function to compute Fibonacci using Matrix Exponentiation
/// @param n long long
/// @return long long
/// @details Time Complexity: O(log n)
ll fibonacciMatrix(ll n){
    if(n <= 1)
        return n;
    ll f[2][2] = {{1, 1}, {1, 0}};
    power(f, n-1);
    return f[0][0];
}

/// @brief Function to compute Fibonacci using Iteration
/// @param n long long
/// @return long long
/// @details Time Complexity: O(n)
ll fibonacciDP(ll n){
    if(n <= 1)
        return n;
    ll arr[n+1];
    arr[0] = 0;
    arr[1] = 1;
    for (ll i = 2; i <= n; ++i)
        arr[i] = arr[i-1] + arr[i-2];
    return arr[n];
}