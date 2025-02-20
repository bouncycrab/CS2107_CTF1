from Crypto.Util.number import getPrime, bytes_to_long, isPrime
from Crypto.PublicKey import RSA
from base64 import b64encode

flag = "REDACTED"


def getNextPrime(num):
    is_prime = False
    while not is_prime:
        num += 1
        is_prime = isPrime(num)
    return num


p = getPrime(1024)
q = getNextPrime(p)
n = p * q
e = 65537

key = RSA.construct((n, e)).export_key().decode()

with open("key", "w") as f:
    f.write(key)

m = bytes_to_long(flag.encode())
c = pow(m, e, n)

with open("output", "w") as f:
    f.write(f"c = {c}")
