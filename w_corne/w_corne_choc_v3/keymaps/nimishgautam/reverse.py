def reverse_elements(input_string):
    elements = [element.strip() for element in input_string.split(',')]
    reversed_elements = elements[::-1]
    return ', '.join(reversed_elements)

if __name__ == "__main__":
    import sys

    # Reading the input string from the command line arguments
    if len(sys.argv) > 1:
        input_string = sys.argv[1]
        reversed_string = reverse_elements(input_string)
        print(reversed_string)
    else:
        print("Please provide a string as a command line argument.")
