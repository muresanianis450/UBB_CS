from src.domain.domain import *
from src.repository.binary_repo import Client_repo_binary, Movie_repo_binary
from src.repository.repository import Repository


class MovieService:
    def __init__(self, repo: Repository):
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
        """Add a new movie to the repository."""
        newMovie = Movie(title, description, genre)
        self._repo.add(newMovie)
        return newMovie

    def remove(self, movie_id: int):
        """Remove a movie by its ID."""
        movie = self._repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} does not exist!")
        self._repo.remove(movie_id)

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
    def __init__(self, repo: Repository):
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
        """Add a new client to the repository."""
        newClient = Client(name)
        self._repo.add(newClient)
        return newClient


    def remove(self, client_id: int):
        """Remove a client by their ID."""
        client = self._repo.get_by_id(client_id)
        if not client:
            raise ValueError(f"Client with ID {client_id} does not exist!")
        self._repo.remove(client_id)

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
    def __init__(self, rental_repo: Repository, client_repo: Repository, movie_repo: Repository):
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
        """
        Rent a movie to a client.
        Ensures the client and movie exist, and the movie is not already rented.
        """
        # Validate the client exists
        client = self._client_repo.get_by_id(client_id)
        if not client:
            raise ValueError(f"Client with ID {client_id} does not exist.")

        # Validate the movie exists
        movie = self._movie_repo.get_by_id(movie_id)
        if not movie:
            raise ValueError(f"Movie with ID {movie_id} does not exist.")

        # Check if the movie is already rented
        for rental in self._rental_repo.get_all():
            if rental.movie_id == movie_id and rental.returned_date is None:
                raise ValueError(f"Movie '{movie.title}' is already rented.")

        # Create and save the rental
        rental = Rental(
            movie_id=movie_id,  # Ensure correct argument
            client_id=client_id,  # Ensure correct argument
            rented_date=rented_date,
            due_date=due_date,
            returned_date=None  # Default to None
        )
        self._rental_repo.add(rental)
        return rental

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

        # Update the returned_date
        rental.returned_date = returned_date
        self._rental_repo.update(rental.id, rental)  # Pass the rental ID and the updated rental object

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