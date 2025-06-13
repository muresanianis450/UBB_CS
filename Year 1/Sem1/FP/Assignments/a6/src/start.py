#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from ui import print_menu
from test import testing

def main():
    print_menu()

if __name__ == "__main__":
    testing()
    main()

