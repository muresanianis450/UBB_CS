from src.domain.Students import Student
from src.repository.memory_repository import BaseRepository  # Assume this is an in-memory repository
from src.services.service import StudentService


def test_add_student():
    repository = BaseRepository()  # Use a mock or in-memory repository
    service = StudentService(repository)

    # Test 1: Add a single student and check the repository
    service.add_student(1, "Alice", 101)
    students = service.get_students()
    assert len(students) == 1, "Student was not added correctly"
    assert students[0].student_id == 1, "Student ID mismatch"
    assert students[0].name == "Alice", "Student name mismatch"
    assert students[0].group == 101, "Student group mismatch"

    # Test 2: Add another student and check the repository
    service.add_student(2, "Bob", 102)
    students = service.get_students()
    assert len(students) == 2, "Second student was not added correctly"
    assert students[1].student_id == 2, "Second student ID mismatch"
    assert students[1].name == "Bob", "Second student name mismatch"
    assert students[1].group == 102, "Second student group mismatch"

    # Test 3: Adding a student with a valid but unusual name
    service.add_student(3, "Élodie", 104)
    students = service.get_students()
    assert len(students) == 3, "Third student was not added correctly"
    assert students[2].name == "Élodie", "Student name with special characters mismatch"

    # Test 4: Ensure undo stack is updated after adding a student
    undo_stack_size_before = len(service._undo_stack)
    service.add_student(4, "David", 105)
    undo_stack_size_after = len(service._undo_stack)
    assert undo_stack_size_after == undo_stack_size_before + 1, "Undo stack was not updated after adding a student"



