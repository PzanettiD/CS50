def mario(P):
    # Function to draw a mario-like obstacle, with #, where height = P

    for i in range(P):
        # Draws the # of the obstacle

        k = i + 1
        for a in range(P - k):
            print(" ", end="")
        for b in range(k):
            print("#", end="")

        print("  ", end="")

        for c in range(k):
            print("#", end="")
        print()


def main():
    while(True):
        # Certifies that the user inputs a int of size between 0 and 23

        u_input = input("Height: ")
        if u_input.isdigit():
            n = int(u_input)
            if n >= 0 and n <= 23:
                break

    # Calls the function mario, giving the user's input as the height
    mario(n)


if __name__ == "__main__":
    main()