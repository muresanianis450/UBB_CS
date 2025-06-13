from src.domain.domain import Movie, Client, Rental
from src.repository.binary_repo import Movie_repo_binary, Client_repo_binary, Rental_repo_binary
from src.services.service import MovieService, RentalService, ClientService
from src.services.undo_service import *
from faker import Faker
from datetime import timedelta, date
import random
from src.ui.repository_factory import *

class UI:
    def __init__(self, movie_service: MovieService, client_service: ClientService, rental_service: RentalService, undo_service):
        self._movie_service = movie_service
        self._client_service = client_service
        self._rental_service = rental_service
        self._undo_service = undo_service

    def print_menu(self):
        print("\nMenu:")
        print("1. Manage")
        print("2. Rent / Return a Movie")
        print("3. Search Movies or Clients")
        print("4. Generate 20 Random Items")
        print("5. Statistics")
        print("6. Undo")
        print("7. Redo")
        print("0. Exit")

    def undo(self):
        try:
            self._undo_service.undo()
            print("Undo successful!")
        except UndoError as e:
            print(f"Error: {e}")

    def redo(self):
        try:
            self._undo_service.redo()
            print("Redo successful!")
        except UndoError as e:
            print(f"Error: {e}")



    def print_statistics_menu(self):
        print("\nStatistics:")
        print("1. Most rented movies")
        print("2. Most active clients")
        print("3. Late rentals")
        print("0. Back")

    def statistics(self):
        while True:
            self.print_statistics_menu()
            choice = input("Choose an option: ")

            match choice:
                case "1":  # Most rented movies
                    try:
                        most_rented_movies = self._rental_service.get_most_rented_movies()
                        print("\nMost Rented Movies:")
                        for rank, (movie, days) in enumerate(most_rented_movies, start=1):
                            if movie is None:  # Handle cases where the movie is not found
                                print(f"{rank}. [Unknown Movie] (Total Rental Days: {days})")
                            else:
                                print(f"{rank}. {movie.title} (ID: {movie.id}, Total Rental Days: {days})")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "2":  # Most active clients
                    try:
                        most_active_clients = self._rental_service.get_most_active_clients()
                        print("\nMost Active Clients:")
                        for rank, (client, days) in enumerate(most_active_clients, start=1):
                            if client is None:  # Handle cases where the client is not found
                                print(f"{rank}. [Unknown Client] (Total Rental Days: {days})")
                            else:
                                print(f"{rank}. {client.name} (ID: {client.id}, Total Rental Days: {days})")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "3":  # Late rentals
                    try:
                        current_date = date.today()
                        late_rentals = self._rental_service.get_late_rentals(current_date)
                        print("\nLate Rentals:")
                        for rental, delay_days in late_rentals:
                            print(
                                f"Rental ID: {rental.id}, Movie ID: {rental.movie_id}, Client ID: {rental.client_id}, "
                                f"Due Date: {rental.due_date}, Overdue by {delay_days} days"
                            )
                    except ValueError as e:
                        print(f"Error: {e}")

                case "0":
                    return

                case _:
                    print("Invalid option. Try again!")

    def print_manage_menu(self):
        print("\nManage:")
        print("1. Movies")
        print("2. Clients")
        print("0. Back")

    def print_submenu(self):
        print("\nOptions:")
        print("1. Add")
        print("2. Remove")
        print("3. List All")
        print("0. Back")

    def manage_movies(self):
        while True:
            self.print_submenu()
            subchoice = input("Choose an option: ")

            match subchoice:
                case "1":
                    try:
                        title = input("Enter Movie Title: ")
                        description = input("Enter Movie Description: ")
                        genre = input("Enter Movie Genre: ")
                        movie = self._movie_service.add(title, description, genre)
                        print(f"Movie added: {movie}")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "2":
                    try:
                        movie_id = int(input("Enter the ID of the movie to remove: "))
                        self._movie_service.remove(movie_id)
                        print(f"Movie with ID {movie_id} removed successfully.")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "3":
                    movies = self._movie_service.getAll()
                    for movie in movies:
                        print(movie)

                case "0":
                    break

                case _:
                    print("Invalid option. Try again!")

    def manage_clients(self):
        while True:
            self.print_submenu()
            subchoice = input("Choose an option: ")

            match subchoice:
                case "1":
                    try:
                        name = input("Enter Client Name: ")
                        client = self._client_service.add(name)
                        print(f"Client added: {client}")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "2":
                    try:
                        client_id = int(input("Enter the ID of the client to remove: "))
                        self._client_service.remove(client_id)
                        print(f"Client with ID {client_id} removed successfully.")
                    except ValueError as e:
                        print(f"Error: {e}")

                case "3":
                    clients = self._client_service.getAll()
                    for client in clients:
                        print(client)

                case "0":
                    break

                case _:
                    print("Invalid option. Try again!")

    def rent_or_return_movie(self):
        print("\nRent or Return a Movie:")
        print("1. Rent a Movie")
        print("2. Return a Movie")
        print("3. List All Rentals")
        print("0. Back")

        choice = input("Choose an option: ")

        match choice:
            case "1":
                try:
                    client_id = int(input("Enter Client ID: "))
                    movie_id = int(input("Enter Movie ID: "))
                    rented_date = date.today()
                    due_date = rented_date + timedelta(days=random.randint(1, 14))
                    self._rental_service.rent_movie(client_id, movie_id, rented_date, due_date)
                    print(f"Movie rented successfully! Due date: {due_date}")
                except ValueError as e:
                    print(f"Error: {e}")

            case "2":
                try:
                    rental_id = int(input("Enter Rental ID: "))
                    returned_date = date.today()
                    self._rental_service.return_movie(rental_id, returned_date)
                    print(f"Rental with ID {rental_id} returned successfully!")
                except ValueError as e:
                    print(f"Error: {e}")

            case "3":
                rentals = self._rental_service.getAll()
                print("All Rentals:")
                for rental in rentals:
                    print(f"Rental ID: {rental.id}, Movie ID: {rental.movie_id}, Client ID: {rental.client_id}, "
                          f"Rented Date: {rental.rented_date}, Due Date: {rental.due_date}, Returned Date: {rental.returned_date}")

            case "0":
                return

            case _:
                print("Invalid option. Try again!")

    def search(self):
        print("\nSearch:")
        print("1. Search Movies")
        print("2. Search Clients")
        print("0. Back")

        choice = input("Choose an option: ")

        match choice:
            case "1":
                query = input("Enter search query for movies: ")
                results = self._movie_service.search(query)
                print("Matching Movies:")
                for movie in results:
                    print(movie)

            case "2":
                query = input("Enter search query for clients: ")
                results = self._client_service.search(query)
                print("Matching Clients:")
                for client in results:
                    print(client)

            case "0":
                return

            case _:
                print("Invalid option. Try again!")

    def generate_20_random_items(self):
        print("\nGenerate Random Items:")
        print("1. Generate 20 Random Movies")
        print("2. Generate 20 Random Clients")
        print("3. Generate 20 Random Rentals")
        print("0. Back")

        choice = input("Choose an option: ")

        match choice:
            case "1":
                fake = Faker()
                for _ in range(20):
                    title = fake.sentence(nb_words=3).strip(".")
                    description = fake.text(max_nb_chars=50)
                    genre = random.choice(["Action", "Comedy", "Drama", "Horror", "Sci-Fi", "Romance"])
                    self._movie_service.add(title, description, genre)
                print("20 random movies generated successfully!")

            case "2":
                fake = Faker()
                for _ in range(20):
                    name = fake.name()
                    client = self._client_service.add(name)
                print("20 random clients generated successfully!")

            case "3":
                # Code to generate 20 random rentals
                print("20 random rentals generated successfully!")

            case "0":
                return

            case _:
                print("Invalid option. Try again!")


    def run(self):
        movies = self._movie_service.getAll()
        print("All Movies:")
        for movie in movies:
            print(movie)

        print()
        print("All Clients:")
        clients = self._client_service.getAll()
        for client in clients:
            print(client)

        print()

        rentals = self._rental_service.getAll()
        print("All Rentals:")
        for rental in rentals:
            print(f"Rental ID: {rental.id}, Movie ID: {rental.movie_id}, Client ID: {rental.client_id}, "
                  f"Rented Date: {rental.rented_date}, Due Date: {rental.due_date}, Returned Date: {rental.returned_date}")


        while True:
            self.print_menu()
            choice = input("Choose an option: ")

            match choice:
                case "1":
                    self.print_manage_menu()
                    manage_choice = input("Choose an option: ")
                    match manage_choice:
                        case "1":
                            self.manage_movies()
                        case "2":
                            self.manage_clients()
                        case "0":
                            continue
                        case _:
                            print("Invalid option.")

                case "2":
                    self.rent_or_return_movie()

                case "3":
                    self.search()

                case "4":
                    self.generate_20_random_items()

                case "5":
                    self.statistics()

                case "6":
                    self.undo()

                case "7":
                    self.redo()

                case "0":
                    print("Exiting the application. Goodbye!")
                    break

                case _:
                    print("Invalid option. Try again!")


# Main Program

"""settings = load_settings("settings.properties")
repositories = initialize_repositories(settings)

# Access repositories
movies_repo = repositories["movies"]
clients_repo = repositories["clients"]
rentals_repo = repositories["rentals"]



movie_service = MovieService(movies_repo)
client_service= ClientService(clients_repo)
rental_service = RentalService(rentals_repo,client_service,movie_service)"""

# Initialize the UI and run the application
"""ui = UI(movie_service, client_service, rental_service)"""
"""ui.run()"""