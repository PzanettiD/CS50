import sys


def main():
    if len(sys.argv) != 2:
        # Veryfies if there are too many or too few command line arguments
        print("Usage: ./vigenere k")
        sys.exit(1)

    key = sys.argv[1]
    key_index = []
    for i in range(len(key)):
        # Uses the command line argument as a key, and stores it's characters in a list
        if (key[i].isalpha()):
            if (key[i].isupper()):
                key_num = ord(key[i]) - 65
                key_index.append(key_num)
            else:
                key_num = ord(key[i]) - 97
                key_index.append(key_num)
        else:
            # If the key is not made of alphabetical characters, then return 1
            print("Usage: ./vigenere k")
            sys.exit(1)

    # Uses user's input as plaintext
    s = input("plaintext: ")
    slength = len(s)
    counter = 0

    print("ciphertext: ", end="")
    for j in range(slength):
        # Encrypts the plaintext with the given key
        if s[j].isalpha():
            if s[j].isupper():
                s_num = ord(s[j]) - 65
            else:
                s_num = ord(s[j]) - 97

            # Algorithm to make a character out of the sum of the plaintext + keys
            cipher_char = (s_num + key_index[(j - counter) % len(key)]) % 26

            if s[j].isupper():
                cipher_letter = chr(cipher_char + 65)
                print(f"{cipher_letter}", end="")
            else:
                cipher_letter = chr(cipher_char + 97)
                print(f"{cipher_letter}", end="")
        else:
            counter += 1
            print(f"{s[j]}", end="")
    print()


if __name__ == "__main__":
    main()