# Flag is the secret and will be in the format CS2107{50m3th1ng}

# 3 things to import
from Crypto.Cipher import AES
from random import randbytes
from Crypto.Util.Padding import pad

# Randomly generated key!
cipher = AES.new(randbytes(16),AES.MODE_ECB)
secret = "[REDACTED]"
code = open("herring.py","rb").read()

with open("test_output","wb") as f:
    for i in code:
        f.write(cipher.encrypt(pad(bytes([i]),16)))