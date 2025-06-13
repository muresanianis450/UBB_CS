import pickle
from src.repository.base_repository import BaseRepository

class BinaryFileRepository(BaseRepository):
    """
    A repository implementation that stores data in a binary file using Python's `pickle` module.

    This class extends the `BaseRepository` to provide functionality for persisting entities
    in a binary file format. It automatically loads data from the file upon initialization
    and saves data to the file after any modifications.

    Attributes:
        _filename (str): The name of the binary file used for data storage.
        _data (list): The in-memory list of entities loaded from the file.
    """

    def __init__(self, filename):
        """
        Initializes the BinaryFileRepository.

        Args:
            filename (str): The name of the file used to store the data.
        """
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        """
        Loads data from the binary file into memory.

        If the file does not exist or is empty, an empty list is initialized as the data store.
        """
        try:
            with open(self._filename, "rb") as file:
                self._data = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._data = []

    def _save(self):
        """
        Saves the in-memory data to the binary file.

        This method overwrites the existing file content with the current state of the data.
        """
        with open(self._filename, "wb") as file:
            pickle.dump(self._data, file)

    def add(self, entity):
        """
        Adds a new entity to the repository.

        After adding the entity, the repository's state is saved to the binary file.

        Args:
            entity: The entity to add to the repository.
        """
        super().add(entity)
        self._save()

    def remove(self, condition):
        """
        Removes entities from the repository that match a given condition.

        After removing the matching entities, the repository's state is saved to the binary file.

        Args:
            condition (callable): A function that returns `True` for entities to be removed.
        """
        super().remove(condition)
        self._save()
