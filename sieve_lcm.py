
n = 1000

ind = dict()
primes = [];
is_prime = [True for _ in range(n+1)]

is_prime[0] = is_prime[1] = False

def sieve():
    cur_ind = 0
    for i in range(2,n+1):
        if (is_prime[i]):
            primes.append(i)
            ind[i] = cur_ind
            cur_ind += 1
            if (i**2 <= n):
                for j in range(i*i, n+1, i):
                    is_prime[j] = False

def process(powers, num):
    for prime in primes:
        if prime > num:
            break
        cnt = 0
        while num % prime == 0:
            num /= prime
            cnt += 1
        
        powers[ind[prime]] = max(powers[ind[prime]], cnt)
        

def lcm(*args):
    powers = [0 for _ in primes]
    for num in args:
        process(powers, num)

    res = 1
    for i in range(len(primes)):
        res *= primes[i] ** powers[i]
        
    return res

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def main():
    sieve()
    
main()
