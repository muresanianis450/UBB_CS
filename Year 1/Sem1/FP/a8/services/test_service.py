import unittest
from src.services.service import MovieService, ClientService, RentalService
from datetime import datetime, timedelta
from src.domain.domain import *
class InMemoryRepository:
    def __init__(self):
        self._data = {}
        self._next_id = 1

    def add(self, item):
        item.id = self._next_id  # Assign an auto-incrementing ID
        self._data[self._next_id] = item
        self._next_id += 1
        return item

    def get_by_id(self, item_id):
        return self._data.get(item_id)

    def get_all(self):
        return list(self._data.values())

    def remove(self, item_id):
        if item_id in self._data:
            del self._data[item_id]

    def update(self, item_id, new_item):
        if item_id in self._data:
            self._data[item_id] = new_item


class TestMovieService(unittest.TestCase):
    def setUp(self):
        self.repo = InMemoryRepository()
        self.service = MovieService(self.repo)

    def test_add_movie(self):
        movie = self.service.add("Inception", "Dreams within dreams", "Sci-Fi")
        assert movie.title == "Inception"
        assert len(self.repo.get_all()) == 1

    def test_get_movie(self):
        movie = self.service.add("Inception", "Dreams within dreams", "Sci-Fi")
        retrieved_movie = self.service.get(movie.id)
        assert retrieved_movie == movie

    def test_remove_movie(self):
        movie = self.service.add("Inception", "Dreams within dreams", "Sci-Fi")
        self.service.remove(movie.id)
        assert len(self.repo.get_all()) == 0

    def test_search_movie(self):
        self.service.add("Inception", "Dreams within dreams", "Sci-Fi")
        results = self.service.search("dream")
        assert len(results) == 1
        assert results[0].title == "Inception"

    def test_get_all_movies(self):
        self.service.add("Inception", "Dreams within dreams", "Sci-Fi")
        self.service.add("Titanic", "Ship sinks", "Romance")
        assert len(self.service.getAll()) == 2


class TestClientService(unittest.TestCase):
    def setUp(self):
        self.repo = InMemoryRepository()
        self.service = ClientService(self._repo)

    def test_add_client(self):
        client = self.service.add("John Doe")
        assert client.name == "John Doe"
        assert len(self.repo.get_all()) == 1

    def test_get_client(self):
        client = self.service.add("John Doe")
        retrieved_client = self.service.get(client.id)
        assert retrieved_client == client

    def test_remove_client(self):
        client = self.service.add("John Doe")
        self.service.remove(client.id)
        assert len(self.repo.get_all()) == 0

    def test_search_client(self):
        self.service.add("John Doe")
        results = self.service.search("john")
        assert len(results) == 1
        assert results[0].name == "John Doe"

    def test_get_all_clients(self):
        self.service.add("John Doe")
        self.service.add("Jane Doe")
        assert len(self.service.getAll()) == 2

class TestRentalService(unittest.TestCase):
    def setUp(self):
        self.movie_repo = InMemoryRepository()
        self.client_repo = InMemoryRepository()
        self.rental_repo = InMemoryRepository()
        self.service = RentalService(self.rental_repo, self.client_repo, self.movie_repo)

    def test_rent_movie(self):
        client = self.client_repo.add(Client("John Doe"))
        movie = self.movie_repo.add(Movie("Inception", "Dreams within dreams", "Sci-Fi"))
        rented_date = datetime.now()
        due_date = rented_date + timedelta(days=7)

        rental = self.service.rent_movie(client.id, movie.id, rented_date, due_date)
        assert rental.client_id == client.id
        assert rental.movie_id == movie.id
        assert len(self.rental_repo.get_all()) == 1

    def test_return_movie(self):
        client = self.client_repo.add(Client("John Doe"))
        movie = self.movie_repo.add(Movie("Inception", "Dreams within dreams", "Sci-Fi"))
        rented_date = datetime.now()
        due_date = rented_date + timedelta(days=7)

        rental = self.service.rent_movie(client.id, movie.id, rented_date, due_date)
        returned_date = datetime.now()
        self.service.return_movie(rental.id, returned_date)

        updated_rental = self.rental_repo.get_by_id(rental.id)
        assert updated_rental.returned_date == returned_date

    def test_get_overdue_rentals(self):
        client = self.client_repo.add(Client("John Doe"))
        movie = self.movie_repo.add(Movie("Inception", "Dreams within dreams", "Sci-Fi"))
        rented_date = datetime.now() - timedelta(days=10)
        due_date = rented_date + timedelta(days=5)

        rental = self.service.rent_movie(client.id, movie.id, rented_date, due_date)
        overdue_rentals = self.service.get_overdue_rentals(datetime.now())

        assert len(overdue_rentals) == 1
        assert rental in overdue_rentals

    def test_get_active_rentals_for_client(self):
        client = self.client_repo.add(Client("John Doe"))
        movie = self.movie_repo.add(Movie("Inception", "Dreams within dreams", "Sci-Fi"))
        rented_date = datetime.now()
        due_date = rented_date + timedelta(days=7)

        rental = self.service.rent_movie(client.id, movie.id, rented_date, due_date)
        active_rentals = self.service.get_active_rentals_for_client(client.id)

        assert len(active_rentals) == 1
        assert rental in active_rentals

    def test_get_rentals_by_movie(self):
        client = self.client_repo.add(Client("John Doe"))
        movie = self.movie_repo.add(Movie("Inception", "Dreams within dreams", "Sci-Fi"))
        rented_date = datetime.now()
        due_date = rented_date + timedelta(days=7)

        rental = self.service.rent_movie(client.id, movie.id, rented_date, due_date)
        rentals_by_movie = self.service.get_rentals_by_movie(movie.id)

        assert len(rentals_by_movie) == 1
        assert rental in rentals_by_movie



