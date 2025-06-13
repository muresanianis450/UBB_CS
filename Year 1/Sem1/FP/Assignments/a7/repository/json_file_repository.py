import json
from src.repository.memory_repository import BaseRepository
from src.domain.Students import Student


class JsonFileRepository(BaseRepository):
    """
    A repository implementation that stores data in a JSON file.

    This class extends the `BaseRepository` to provide functionality for persisting entities
    (e.g., `Student` objects) in a JSON file. It automatically loads data from the file upon
    initialization and saves data to the file after any modifications.

    Attributes:
        _filename (str): The name of the JSON file used for data storage.
    """

    def __init__(self, filename):
        """
        Initializes the JsonFileRepository.

        Args:
            filename (str): The name of the file used to store the data.
        """
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        """
        Loads data from the JSON file into memory.

        The JSON file is expected to contain a list of dictionaries, where each dictionary
        represents a `Student` entity with the keys: `student_id`, `name`, and `group`.

        If the file does not exist, or if there is an error during loading, the repository
        will be initialized as empty.

        Raises:
            ValueError: If the JSON file does not contain a list or an entry is invalid.
        """
        try:
            with open(self._filename, "r") as file:
                data = json.load(file)
                if not isinstance(data, list):
                    raise ValueError("JSON file does not contain a list.")
                for entry in data:
                    if not all(key in entry for key in ["student_id", "name", "group"]):
                        raise ValueError(f"Invalid entry in JSON file: {entry}")
                    student = Student(
                        student_id=entry["student_id"],
                        name=entry["name"],
                        group=entry["group"]
                    )
                    self.add(student)
        except FileNotFoundError:
            # File doesn't exist yet; initialize an empty repository
            self._data = []
        except (ValueError, json.JSONDecodeError) as e:
            print(f"Error loading JSON file: {e}. Starting with an empty repository.")
            self._data = []

    def _save(self):
        """
        Saves the current in-memory data to the JSON file.

        The `Student` objects are serialized into dictionaries and stored in the file.
        """
        with open(self._filename, "w") as file:
            json.dump([student.__dict__ for student in self._data], file, indent=4)

    def add(self, entity):
        """
        Adds a new `Student` entity to the repository.

        After adding the entity, the repository's state is saved to the JSON file.

        Args:
            entity (Student): The `Student` entity to add to the repository.
        """
        super().add(entity)
        self._save()

    def remove(self, condition):
        """
        Removes entities from the repository that match a given condition.

        After removing the matching entities, the repository's state is saved to the JSON file.

        Args:
            condition (callable): A function that returns `True` for entities to be removed.
        """
        super().remove(condition)
        self._save()
