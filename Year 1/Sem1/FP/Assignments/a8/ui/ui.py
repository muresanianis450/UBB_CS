from colorama import Fore, Style, init
from src.domain.domain import Movie, Client, Rental
from src.repository.binary_repo import Movie_repo_binary, Client_repo_binary, Rental_repo_binary
from src.services.service import MovieService, RentalService, ClientService
from faker import Faker
from datetime import timedelta, date
import random
from src.ui.repository_factory import *

# Initialize colorama
init(autoreset=True)
class UI:
    def __init__(self, movie_service: MovieService, client_service: ClientService, rental_service: RentalService):
        self._movie_service = movie_service
        self._client_service = client_service
        self._rental_service = rental_service

    def print_pink(self, text):
        print(f"{Fore.MAGENTA}{text}{Style.RESET_ALL}")

    def print_menu(self):
        self.print_pink("\nMenu:")
        self.print_pink("1. Manage")
        self.print_pink("2. Rent / Return a Movie")
        self.print_pink("3. Search Movies or Clients")
        self.print_pink("4. Generate 20 Random Items")
        self.print_pink("0. Exit")

    def print_manage_menu(self):
        self.print_pink("\nManage:")
        self.print_pink("1. Movies")
        self.print_pink("2. Clients")
        self.print_pink("0. Back")

    def print_submenu(self):
        self.print_pink("\nOptions:")
        self.print_pink("1. Add")
        self.print_pink("2. Remove")
        self.print_pink("3. List All")
        self.print_pink("0. Back")

    def manage_movies(self):
        while True:
            self.print_submenu()
            subchoice = input(self.color_input("Choose an option: "))

            match subchoice:
                case "1":
                    try:
                        title = input(self.color_input("Enter Movie Title: "))
                        description = input(self.color_input("Enter Movie Description: "))
                        genre = input(self.color_input("Enter Movie Genre: "))
                        movie = self._movie_service.add(title, description, genre)
                        self.print_pink(f"Movie added: {movie}")
                    except ValueError as e:
                        self.print_pink(f"Error: {e}")

                case "2":
                    try:
                        movie_id = int(input(self.color_input("Enter the ID of the movie to remove: ")))
                        self._movie_service.remove(movie_id)
                        self.print_pink(f"Movie with ID {movie_id} removed successfully.")
                    except ValueError as e:
                        self.print_pink(f"Error: {e}")

                case "3":
                    movies = self._movie_service.getAll()
                    for movie in movies:
                        self.print_pink(movie)

                case "0":
                    break

                case _:
                    self.print_pink("Invalid option. Try again!")

    def color_input(self, prompt):
        return f"{Fore.MAGENTA}{prompt}{Style.RESET_ALL}"

    def manage_clients(self):
        while True:
            self.print_submenu()
            subchoice = input(self.color_input("Choose an option: "))

            match subchoice:
                case "1":
                    try:
                        name = input(self.color_input("Enter Client Name: "))
                        client = self._client_service.add(name)
                        self.print_pink(f"Client added: {client}")
                    except ValueError as e:
                        self.print_pink(f"Error: {e}")

                case "2":
                    try:
                        client_id = int(input(self.color_input("Enter the ID of the client to remove: ")))
                        self._client_service.remove(client_id)
                        self.print_pink(f"Client with ID {client_id} removed successfully.")
                    except ValueError as e:
                        self.print_pink(f"Error: {e}")

                case "3":
                    clients = self._client_service.getAll()
                    for client in clients:
                        self.print_pink(client)

                case "0":
                    break

                case _:
                    self.print_pink("Invalid option. Try again!")

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
                    returned_date = date.today()  # Use today's date as the returned date
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
                clients = self._client_service.getAll()
                movies = self._movie_service.getAll()

                if not clients:
                    print("No clients available! Generate clients first.")
                    return
                if not movies:
                    print("No movies available! Generate movies first.")
                    return

                for _ in range(20):
                    # Randomly select a client and a movie
                    client = random.choice(clients)
                    movie = random.choice(movies)

                    # Ensure the movie is not already rented
                    active_rentals = self._rental_service.get_rentals_by_movie(movie.id)
                    if any(rental.returned_date is None for rental in active_rentals):
                        continue  # Skip if the movie is already rented

                    # Generate random rental dates
                    rented_date = date.today() - timedelta(days=random.randint(1, 30))
                    due_date = rented_date + timedelta(days=random.randint(1, 14))

                    # Randomly decide if the movie was returned
                    if random.choice([True, False]):  # 50% chance the movie has been returned
                        returned_date = rented_date + timedelta(days=random.randint(1, (due_date - rented_date).days))
                    else:
                        returned_date = None

                    try:
                        self._rental_service.rent_movie(client.id, movie.id, rented_date, due_date)
                        if returned_date:
                            # Mark the rental as returned
                            rental = self._rental_service.getAll()[-1]  # Get the last added rental
                            self._rental_service.return_movie(rental.id, returned_date)
                    except ValueError as e:
                        print(f"Skipped rental generation: {e}")

                print("20 random rentals generated successfully!")

            case "0":
                return

            case _:
                print("Invalid option. Try again!")

    def run(self):
        while True:
            self.print_menu()
            choice = input(self.color_input("Choose an option: "))

            match choice:
                case "1":
                    self.print_manage_menu()
                    manage_choice = input(self.color_input("Choose an option: "))
                    match manage_choice:
                        case "1":
                            self.manage_movies()
                        case "2":
                            self.manage_clients()
                        case "0":
                            continue
                        case _:
                            self.print_pink("Invalid option.")

                case "2":
                    self.rent_or_return_movie()

                case "3":
                    self.search()

                case "4":
                    self.generate_20_random_items()
                case "0":

                    self.print_pink("Exiting the application. Goodbye!")
                    break

                case _:
                    self.print_pink("Invalid option. Try again!")


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
