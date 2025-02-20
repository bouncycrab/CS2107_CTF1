import random

FLAG = "REDACTED"

print("Hey, see if you can get the next hexadecimal value!")

while True:
    # Original challenge was simply random.randbytes(4)
    # which meant you just needed to iterate through 624 times
    # instead of 312 times but splitting the hex into 2 to submit
    correct = random.randbytes(8).hex()
    guess = input("Your guess: ")
    if guess == correct:
        print(f"Wow, you must be so lucky! Here's your flag: {FLAG}")
        break
    else:
        print(f"Unlucky, the correct number was {correct}. Try again!")
