from jinja2.compiler import generate

from src.domain.domain import *
from src.repository.repository import Repository
import pickle

class Movie_repo_binary(Repository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        """Loads data from the binary file into _items."""
        try:
            with open(self._filename, "rb") as file:
                self._items = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._items = {}

    def _save(self):
        """Saves the _items dictionary to the binary file."""
        with open(self._filename, "wb") as file:
            pickle.dump(self._items, file)

    def add(self, item):
        """Overrides add to save changes to the file."""
        super().add(item)
        self._save()

    def remove(self, item_id):
        """Overrides remove to save changes to the file."""
        super().remove(item_id)
        self._save()



class Client_repo_binary(Repository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        try:
            with open(self._filename, "rb") as file:
                self._items = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._items = {}

    def _save(self):
        with open(self._filename, "wb") as file:
            pickle.dump(self._items, file)

    def add(self, client):
        super().add(client)
        self._save()

    def remove(self, client_id):
        super().remove(client_id)
        self._save()



class Rental_repo_binary(Repository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load()

    def _load(self):
        """Loads data from the binary file into _items."""
        try:
            with open(self._filename, "rb") as file:
                self._items = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._items = {}

    def _save(self):
        """Saves the _items dictionary to the binary file."""
        with open(self._filename, "wb") as file:
            pickle.dump(self._items, file)

    def add(self, rental):
        """Overrides add to save changes to the file."""
        super().add(rental)
        self._save()

    def remove(self, rental_id):
        """Overrides remove to save changes to the file."""
        super().remove(rental_id)
        self._save()

    def update(self, rental_id, updated_item):
        """Overrides update to save changes to the file."""
        super().update(rental_id, updated_item)
        self._save()


"""movies = generate_20_movies()
movie_binary_repo = Movie_repo_binary("movie.pickle")
for movie in movie_binary_repo:
    print(movie)
"""

"""clients = generate_20_clients()
client_binary_repo = Client_repo_binary("client.pickle")
for client in client_binary_repo:
    print(client)"""

"""rentals = generate_20_rentals()
rental_binary_repo = Rental_repo_binary("rental.pickle")
for rental in rental_binary_repo:
    print(rental)"""