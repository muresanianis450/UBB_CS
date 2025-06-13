from src.repository.base_repository import BaseRepository
from src.domain.Students import Student


class TextFileRepository(BaseRepository):
    """
    A repository implementation that stores data in a text file.

    This class extends the `BaseRepository` to provide functionality for persisting entities
    (e.g., `Student` objects) in a text file. It automatically loads data from the file upon
    initialization and saves data to the file after any modifications.

    Attributes:
        _filename (str): The name of the text file used for data storage.
    """

    def __init__(self, filename):
        """
        Initializes the TextFileRepository.

        Args:
            filename (str): The name of the file used to store the data.
        """
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        """
        Loads data from the text file into memory.

        Each line in the file represents a `Student` entity, stored as `student_id,name,group`.
        The method reads and parses the file, creating `Student` objects and adding them to the repository.

        If the file does not exist, no data is loaded.
        """
        try:
            with open(self._filename, "r") as file:
                for line in file:
                    student_id, name, group = line.strip().split(",")
                    self.add(Student(int(student_id), name, int(group)))
        except FileNotFoundError:
            pass

    def _save(self):
        """
        Saves the in-memory data to the text file.

        Each `Student` object is written as a line in the format `student_id,name,group`.
        """
        with open(self._filename, "w") as file:
            for student in self.get_all():
                file.write(f"{student.student_id},{student.name},{student.group}\n")

    def add(self, entity):
        """
        Adds a new entity to the repository.

        After adding the entity, the repository's state is saved to the text file.

        Args:
            entity (Student): The `Student` entity to add to the repository.
        """
        super().add(entity)
        self._save()

    def remove(self, condition):
        """
        Removes entities from the repository that match a given condition.

        After removing the matching entities, the repository's state is saved to the text file.

        Args:
            condition (callable): A function that returns `True` for entities to be removed.
        """
        super().remove(condition)
        self._save()
