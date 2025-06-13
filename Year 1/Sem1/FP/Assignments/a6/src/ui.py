from functions import *


def print_menu():
    array = generate_numbers()
    history = [array[:]]  # To support undo
    display_numbers(array)
    while True:

        print("\nMenu:")
        print("(A) Add number")
        print("(B) Modify numbers")
        print("(C) Display numbers")
        print("(E) Undo")
        print("(X) Exit")
        choice = input("Select an option: ").strip().upper()


        try:
            match choice:
                case "A":
                    action = input("Choose 'add' or 'insert': ").strip().lower()
                    if action == "add":
                        real = int(input("Enter real part: "))
                        imaginary = int(input("Enter imaginary part: "))
                        array = add_number(array, real, imaginary)
                        history.append(array[:])
                        display_numbers(array)
                    elif action == "insert":
                        real = int(input("Enter real part: "))
                        imaginary = int(input("Enter imaginary part: "))
                        index = int(input("Enter index: "))
                        array = insert_number(array, real, imaginary, index)
                        history.append(array[:])
                        display_numbers(array)
                    else:
                        print("Invalid action")


                case "B":
                    sub_choice = input("Choose remove or replace: ").strip().lower()
                    if sub_choice == "remove":
                        sub_action = input("Enter 'position' or 'interval': ").strip().lower()
                        if sub_action == "position":
                            index = int(input("Enter index: "))
                            array = remove_number_position(array, index)
                        elif sub_action == "interval":
                            start = int(input("Enter start index: "))
                            end = int(input("Enter end index: "))
                            array = remove_number_interval(array, start, end)
                        else:
                            print("Invalid removal type")
                    elif sub_choice == "replace":
                        try:
                            real_old = int(input("Enter real part of old number: "))
                            imaginary_old = int(input("Enter imaginary part of old number: "))
                            real_new = int(input("Enter real part of new number: "))
                            imaginary_new = int(input("Enter imaginary part of new number: "))
                            array = replace_number(array, create_number(real_old, imaginary_old), real_new, imaginary_new)

                        except ValueError:
                            print("Invalid input! Please enter valid integers.")
                        else:
                            print("Invalid modification type")
                    history.append(array[:])
                    display_numbers(array)

                case "C":
                    sub_choice = input("Choose 'list', 'list real', or 'list modulo': ").strip().lower()
                    if sub_choice == "list":
                       display_numbers(array)
                    elif sub_choice == "list real":
                        start = int(input("Enter start index: "))
                        end = int(input("Enter end index: "))
                        print(list_real_range(array, start, end))
                    elif sub_choice == "list modulo":
                        operator = input("Enter operator ('<', '=', '>'): ").strip()
                        value = float(input("Enter comparison value: "))
                        print(list_modulo(array, operator, value))
                    else:
                        print("Invalid listing type")

                case "E":
                    if len(history) > 1:
                        history.pop()
                        array = history[-1][:]
                        #[-1] accesses the new last element after the .pop()
                        #[:] creates a copy of history in array, otherwise history will be directly affected by changes in array
                        display_numbers(array)
                    else:
                        print("Nothing to undo!")

                case "X":
                    print("Exiting program.")
                    break

                case _:
                    print("Invalid choice, please try again.")

        except Exception as e:
            print(f"Error: {e}")


if __name__ == "__main__":

    print_menu()
