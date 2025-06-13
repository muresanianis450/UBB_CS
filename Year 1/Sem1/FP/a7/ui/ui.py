from src.services.service import StudentService
from src.repository.memory_repository import MemoryRepository
from src.domain.Students import Student, getRandomName
from src.repository.text_file_repository import TextFileRepository
from src.repository.binary_file_repository import BinaryFileRepository
from src.repository.json_file_repository import JsonFileRepository
from src.services.test import test_add_student
import random

class StudentUI:
    def __init__(self, service):
        self._service = service

    def print_menu(self):
        print("\nMenu:")
        print("1. Add a student")
        print("2. Display all students")
        print("3. Delete students in a group")
        print("4. Undo last operation")
        print("0. Exit")

    def add_student(self):
        try:
            student_id = int(input("Enter student ID: "))
            name = input("Enter student name: ")
            group = int(input("Enter student group: "))
            self._service.add_student(student_id, name, group)
        except ValueError as e:
            print(f"Error: {e}")

    def add_10_students(self):
        """
        Adds 10 random students to the repository.
        """
        for i in range(10):
            student_id = random.randint(911,917) # Generate random unique ID
            name = getRandomName()  # Get random student name
            group = random.randint(911, 917)  # Random group between 911 and 917
            self._service.add_student(student_id, name, group)
        print("10 random students added successfully.")

    def display_students(self):
        students = self._service.get_students()
        if not students:
            print("No students found.")
        else:
            for student in students:
                print(student)

    def delete_students_by_group(self):
        try:
            group = int(input("Enter the group to delete: "))
            self._service.delete_students_by_group(group)
        except ValueError as e:
            print(f"Error: {e}")

    def undo(self):
        try:
            self._service.undo()
            print("Undo successful.")
        except ValueError as e:
            print(f"Error: {e}")

    def start(self):
        while True:
            self.print_menu()
            choice = input("Choose an option: ")
            if choice == "1":
                self.add_student()
            elif choice == "2":
                self.display_students()
            elif choice == "3":
                self.delete_students_by_group()
            elif choice == "4":
                self.undo()
            elif choice == "0":
                print("Goodbye!")
                break
            else:
                print("Invalid option. Please try again.")

if __name__ == "__main__":
    test_add_student()

    # Switch between repositories by uncommenting the desired one
    #repo = MemoryRepository()
    #repo = TextFileRepository("students.txt")
    repo = BinaryFileRepository("students.pickle")  # Binary repository
    #repo = JsonFileRepository("students.json")
    service = StudentService(repo)
    ui = StudentUI(service)

    #ui.add_10_students()  # Add 10 random students
    ui.start()  # Start the menu-driven application
