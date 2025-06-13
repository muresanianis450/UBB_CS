from src.domain.Students import Student

class StudentService:
    def __init__(self, repository):
        self._repository = repository
        self._undo_stack = []

    def add_student(self, student_id, name, group):
        """
        Adds a new student to the repository.

        Raises:
            ValueError: If a student with the same `student_id` already exists in the repository.
        """
        # Check if a student with the same ID already exists
        if any(student.student_id == student_id for student in self._repository.get_all()):
            raise ValueError(f"Student ID {student_id} already exists.")

        # Create the new student and add it to the repository
        student = Student(student_id, name, group)
        self._undo_stack.append(self._repository.get_all())
        self._repository.add(student)

    def delete_students_by_group(self, group):
        self._undo_stack.append(self._repository.get_all())
        self._repository.remove(lambda student: student.group == group)

    def get_students(self):
        return self._repository.get_all()

    def undo(self):
        if not self._undo_stack:
            raise ValueError("No actions to undo.")
        previous_state = self._undo_stack.pop()
        self._repository._data = previous_state
