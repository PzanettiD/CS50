from cs50 import get_int


def main():
    while (True):
        # Makes sure that the user inputs an int.

        u_cc_number = input("Number: ")
        if (u_cc_number.isdigit()):
            cc_number = int(u_cc_number)
            if (cc_number > 0):
                break
    digits = []
    total_sum = 0
    for i in range(16):
        # Loads every digit of the user's input in a list

        digit = (cc_number % 10**(i + 1)) // (10**i)
        digits.append(digit)
    for j in range(1, 16, 2):
        # Every odd position of the digits must be multiplied by two

        digits[j] *= 2
        if digits[j] >= 10:
            # If when multiplied a certain digit is bigger than 10, than its value becomes the sum of its digits

            digits[j] = (digits[j] % 10) + ((digits[j % 100]) // 10)
    for l in range(16):
        # Calculates the sum of the card's digits

        total_sum += digits[l]
    if total_sum % 10 == 0 and cc_number > 1000000000000:
        # Conditions to determine if the card is valid.

        if cc_number > 10000000000000 and cc_number < 999999999999999:
            if digits[14] == 3:
                if digits[13] == 5 or digits[13] == 8:
                    print("AMEX")
                else:
                    print("INVALID")
        if cc_number > 999999999999999:
            if digits[15] == 8:
                print("VISA")
            elif digits[15] == 1:
                if digits[14] == 1 or digits[14] == 2 or digits[14] == 3 or digits[14] == 4 or digits[14] == 5:
                    print("MASTERCARD")
                else:
                    print("INVALID")
        if cc_number < 9999999999999:
            print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()