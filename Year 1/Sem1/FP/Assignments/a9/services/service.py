from src.domain.domain import *
from src.repository.binary_repo import Client_repo_binary, Movie_repo_binary
from src.repository.repository import Repository
from src.services.undo_service import FunctionCall, Operation, CascadedOperation

class MovieService:
    def __init__(self, undo_service, repo: Repository):
        self._undo_service = undo_service
        self._repo = repo


    def get(self, movie_id) -> Movie:
        """Retrieve a movie by its ID."""
        movie = self._repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} not found!")
        return movie

    def getAll(self):
        """Retrieve all movies."""
        return self._repo.get_all()

    def add(self, title: str, description: str, genre: str) -> Movie:
        new_movie = Movie(title, description, genre)
        self._repo.add(new_movie)

        # Record undo/redo operations
        undo = FunctionCall(self._repo.remove, new_movie.id)
        redo = FunctionCall(self._repo.add, new_movie)
        self._undo_service.recordUndo(Operation(undo, redo))

        return new_movie

    def remove(self, movie_id: int):
        movie = self._repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} does not exist.")
        self._repo.remove(movie_id)

        # Record undo/redo operations
        undo = FunctionCall(self._repo.add, movie)
        redo = FunctionCall(self._repo.remove, movie_id)
        self._undo_service.recordUndo(Operation(undo, redo))



    def search(self, query : str, field: str = None):

        query = query.lower()
        all_movies = self._repo.get_all()

        def matches(movie):
            if not field or field == "title":
                if query in movie.title.lower():
                    return True
            if not field or field == "genre":
                if query in movie.get_genre().lower():
                    return True
            if not field or field == "description":
                if query in movie.get_description().lower():
                    return True
            return False

        return [movie for movie in all_movies if matches(movie)]

    def get_by_id(self, movie_id):
        """
        Retrieve a movie by its ID using the movie repository.
        """
        movie = self._repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} not found!")
        return movie



class ClientService:
    def __init__(self, undo_service, repo: Repository):
        self._undo_service = undo_service
        self._repo = repo

    def get(self, client_id) -> Client:
        """Retrieve a client by their ID."""
        client = self._repo.get_by_id(client_id)
        if not client:
            raise ValueError(f"Client with ID {client_id} not found!")
        return client

    def getAll(self):
        """Retrieve all clients."""
        return self._repo.get_all()

    def add(self, name: str) -> Client:
        new_client = Client(name)
        self._repo.add(new_client)

        # Record undo/redo operations
        undo = FunctionCall(self._repo.remove, new_client.id)
        redo = FunctionCall(self._repo.add, new_client)
        self._undo_service.recordUndo(Operation(undo, redo))
        return new_client

    def remove(self, client_id: int):
        client = self._repo.get_by_id(client_id)
        if not client:
            raise ValueError(f"Client with ID {client_id} does not exist.")
        self._repo.remove(client_id)

        # Record undo/redo operations
        undo = FunctionCall(self._repo.add, client)
        redo = FunctionCall(self._repo.remove, client_id)
        self._undo_service.recordUndo(Operation(undo, redo))

    def search(self, query : str, field: str = None):
        query = query.lower()
        all_clients = self._repo.get_all()
        def matches(client):
            if not field or field == "name":
                if query in client.name.lower():
                    return True
            return False
        return [client for client in all_clients if matches(client)]

    def get_by_id(self, client_id) -> Client:
        """
        Retrieve a client by its ID from the repository.
        """
        client = self._repo.get_by_id(client_id)  # Use the repo's method to get client
        if not client:
            raise ValueError(f"Client with ID {client_id} not found!")
        return client


class RentalService:
    def __init__(self, undo_service, rental_repo: Repository, client_repo: Repository, movie_repo: Repository):
        self._undo_service = undo_service
        self._rental_repo = rental_repo
        self._client_repo = client_repo
        self._movie_repo = movie_repo

    def get(self, rental_id) -> Rental:
        """
        Retrieve a rental by its ID.
        """
        rental = self._rental_repo.get_by_id(rental_id)
        if not rental:
            raise ValueError(f"Rental with ID {rental_id} not found!")
        return rental

    def getAll(self):
        """
        Retrieve all rentals.
        """
        return self._rental_repo.get_all()

    def rent_movie(self, client_id, movie_id, rented_date, due_date):
        client = self._client_repo.get_by_id(client_id)
        movie = self._movie_repo.get_by_id(movie_id)
        rental = Rental(movie_id, client_id, rented_date, due_date)
        self._rental_repo.add(rental)

        # Record undo/redo operations
        undo = FunctionCall(self._rental_repo.remove, rental.id)
        redo = FunctionCall(self._rental_repo.add, rental)
        self._undo_service.recordUndo(Operation(undo, redo))

        return rental

    def delete_client_rentals(self, client_id):
        rentals = [
            rental for rental in self._rental_repo.get_all()
            if rental.client_id == client_id
        ]

        operations = []
        for rental in rentals:
            self._rental_repo.remove(rental.id)
            undo = FunctionCall(self._rental_repo.add, rental)
            redo = FunctionCall(self._rental_repo.remove, rental.id)
            operations.append(Operation(undo, redo))

        # Record the cascading operation
        cascaded_operation = CascadedOperation(*operations)
        self._undo_service.recordUndo(cascaded_operation)

    def return_movie(self, rental_id, returned_date):
        """
        Return a rented movie by updating its returned_date.
        """
        rental = self._rental_repo.get_by_id(rental_id)
        if not rental:
            raise ValueError(f"Rental with ID {rental_id} not found.")
        if rental.returned_date is not None:
            raise ValueError(f"Rental with ID {rental_id} has already been returned.")

        # Validate that the return date is not before the rented date
        if returned_date < rental.rented_date:
            raise ValueError("Returned date cannot be before the rented date.")

        # Store the old returned date (None in this case) for undo
        old_returned_date = rental.returned_date

        # Update the returned_date
        rental.returned_date = returned_date
        self._rental_repo.update(rental.id, rental)

        # Record undo/redo operations
        undo = FunctionCall(self._set_returned_date, rental.id, old_returned_date)
        redo = FunctionCall(self._set_returned_date, rental.id, returned_date)
        self._undo_service.recordUndo(Operation(undo, redo))

    def _set_returned_date(self, rental_id, returned_date):
        """
        Helper function to set the returned date of a rental.
        """
        rental = self._rental_repo.get_by_id(rental_id)
        if not rental:
            raise ValueError(f"Rental with ID {rental_id} not found.")

        rental.returned_date = returned_date
        self._rental_repo.update(rental.id, rental)

    def get_overdue_rentals(self, current_date):
        """
        Retrieve all rentals that are overdue.
        """
        overdue_rentals = []
        for rental in self._rental_repo.get_all():
            if rental.due_date < current_date and rental.returned_date is None:
                overdue_rentals.append(rental)
        return overdue_rentals

    def get_active_rentals_for_client(self, client_id):
        """
        Retrieve all active rentals for a specific client.
        """
        client = self._client_repo.get_by_id(client_id)
        if not client:
            raise ValueError(f"Client with ID {client_id} does not exist.")

        return [
            rental for rental in self._rental_repo.get_all()
            if rental.client_id == client_id and rental.returned_date is None
        ]

    def get_rentals_by_movie(self, movie_id):
        """
        Retrieve all rentals for a specific movie.
        """
        movie = self._movie_repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} does not exist.")

        return [
            rental for rental in self._rental_repo.get_all()
            if rental.movie_id == movie_id
        ]

    def delete_rental(self, rental_id):
        """
        Delete a rental by its ID.
        """
        rental = self._rental_repo.get_by_id(rental_id)
        if not rental:
            raise ValueError(f"Rental with ID {rental_id} does not exist.")
        self._rental_repo.remove(rental_id)

    def get_most_rented_movies(self):
        """
        Returns a list of movies sorted by total rental days in descending order.
        """
        rental_days = {}
        for rental in self._rental_repo.get_all():
            days = (rental.returned_date or date.today()) - rental.rented_date
            rental_days[rental.movie_id] = rental_days.get(rental.movie_id, 0) + days.days

        sorted_movies = sorted(
            rental_days.items(),
            key=lambda item: item[1],
            reverse=True
        )
        return [(self._movie_repo.get_by_id(movie_id), days) for movie_id, days in sorted_movies]

    def get_most_active_clients(self):
        """
        Returns a list of clients sorted by total rental days in descending order.
        """
        client_days = {}
        for rental in self._rental_repo.get_all():
            days = (rental.returned_date or date.today()) - rental.rented_date
            client_days[rental.client_id] = client_days.get(rental.client_id, 0) + days.days

        sorted_clients = sorted(
            client_days.items(),
            key=lambda item: item[1],
            reverse=True
        )
        return [(self._client_repo.get_by_id(client_id), days) for client_id, days in sorted_clients]

    def get_late_rentals(self, current_date):
        """
        Returns a list of late rentals sorted by days overdue in descending order.
        """
        late_rentals = []
        for rental in self._rental_repo.get_all():
            if rental.returned_date is None and rental.due_date < current_date:
                delay_days = (current_date - rental.due_date).days
                late_rentals.append((rental, delay_days))

        late_rentals.sort(key=lambda item: item[1], reverse=True)
        return late_rentals


"""client_repo = Client_repo_binary("clients.pickle")
client_service = ClientService(client_repo)
clients = generate_20_clients()

for client in clients:
    client_repo.add(client)

for client in client_service.search("Tracy","name"):
    print(client)
 # Ensure this uses the `__str__` method of the Client class

""""""
for movie in movie_repo:
    print(movie)"""