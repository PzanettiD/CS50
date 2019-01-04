import sys


def main():
    if len(sys.argv) != 2:
        # Verifies if there is too many or too few arguments in the command line
        print("Usage ./caesar k")
        sys.exit(1)
    else:
        # Uses the user's input as plaintext
        k = int(sys.argv[1])
        s = input("plaintext: ")
        print("ciphertext: ", end="")
        for i in range(len(s)):
            # Encrypts the plaintext, given a key in the command line argument

            if s[i].isalpha():
                # If the plaintext is alphabetical, transform it's characters into numbers
                if s[i].islower():
                    p = ord(s[i]) - 97
                else:
                    p = ord(s[i]) - 65
                c = (p + k) % 26
                if s[i].islower():
                    letter = chr(c + 97)
                    print(f"{letter}", end="")
                else:
                    letter = chr(c + 65)
                    print(f"{letter}", end="")
            else:
                print(f"{s[i]}", end="")
        print()


if __name__ == "__main__":
    main()