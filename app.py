from timeit import timeit

def memorize(func):
    c = {}
    def w(*args, **kwargs):
        if args in c:
            return c[args]
        ans = func(*args, **kwargs)
        c[args] = ans
        return ans
    return w

@memorize
def fibo(n):
    if n <= 1:
        return n;
    return fibo(n - 1) + fibo(n - 2)

time = timeit("fibo(100)", setup="from __main__ import fibo", number=10000)
print(time)
