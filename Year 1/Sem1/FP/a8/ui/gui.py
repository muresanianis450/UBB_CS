import tkinter as tk
from tkinter import messagebox
from src.domain.domain import Movie, Client, Rental
from src.services.service import MovieService, ClientService, RentalService
from datetime import date, timedelta
from src.ui.ui import UI
from src.ui.repository_factory import *
from faker import Faker
import random
class GUI(UI):
    def __init__(self, movie_service: MovieService, client_service: ClientService, rental_service: RentalService):
        super().__init__(movie_service, client_service, rental_service)
        self.window = tk.Tk()
        self.window.title("Movie Rental System")
        self.create_main_menu()

    def create_main_menu(self):
        # Clear the window
        for widget in self.window.winfo_children():
            widget.destroy()

        # Main Menu Buttons
        tk.Button(self.window, text="Manage", command=self.manage_menu).pack(pady=10)
        tk.Button(self.window, text="Rent / Return a Movie", command=self.rent_or_return_movie).pack(pady=10)
        tk.Button(self.window, text="Search Movies or Clients", command=self.search).pack(pady=10)
        tk.Button(self.window, text="Generate 20 Random Items", command=self.generate_20_random_items).pack(pady=10)
        tk.Button(self.window, text="List All Rentals", command=self.list_all_rentals).pack(pady=10)  # New button
        tk.Button(self.window, text="Exit", command=self.window.quit).pack(pady=10)

    def manage_menu(self):
        # Clear the window and show the manage menu
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Button(self.window, text="Manage Movies", command=self.manage_movies).pack(pady=10)
        tk.Button(self.window, text="Manage Clients", command=self.manage_clients).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.create_main_menu).pack(pady=10)

    def manage_movies(self):
        # Clear the window and show options for managing movies
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Button(self.window, text="Add Movie", command=self.add_movie).pack(pady=10)
        tk.Button(self.window, text="Remove Movie", command=self.remove_movie).pack(pady=10)
        tk.Button(self.window, text="List All Movies", command=self.list_movies).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_menu).pack(pady=10)

    def manage_clients(self):
        # Clear the window and show options for managing clients
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Button(self.window, text="Add Client", command=self.add_client).pack(pady=10)
        tk.Button(self.window, text="Remove Client", command=self.remove_client).pack(pady=10)
        tk.Button(self.window, text="List All Clients", command=self.list_clients).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_menu).pack(pady=10)

    def add_client(self):
        def submit_client():
            name = entry_name.get()
            try:
                client = self._client_service.add(name)
                messagebox.showinfo("Success", f"Client added: {client}")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Client Name:").pack(pady=5)
        entry_name = tk.Entry(self.window)
        entry_name.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_client).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_clients).pack(pady=10)

    def remove_client(self):
        def submit_remove_client():
            try:
                client_id = int(entry_client_id.get())
                self._client_service.remove(client_id)
                messagebox.showinfo("Success", f"Client with ID {client_id} removed successfully.")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter the ID of the client to remove:").pack(pady=5)
        entry_client_id = tk.Entry(self.window)
        entry_client_id.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_remove_client).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_clients).pack(pady=10)

    def list_clients(self):
        # List all clients in the window
        for widget in self.window.winfo_children():
            widget.destroy()

        clients = self._client_service.getAll()
        for client in clients:
            tk.Label(self.window, text=client).pack(pady=5)

        tk.Button(self.window, text="Back", command=self.manage_clients).pack(pady=10)

    def add_movie(self):
        def submit_movie():
            title = entry_title.get()
            description = entry_description.get()
            genre = entry_genre.get()
            try:
                movie = self._movie_service.add(title, description, genre)
                messagebox.showinfo("Success", f"Movie added: {movie}")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        # Create window to input movie details
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Movie Title:").pack(pady=5)
        entry_title = tk.Entry(self.window)
        entry_title.pack(pady=5)
        tk.Label(self.window, text="Enter Movie Description:").pack(pady=5)
        entry_description = tk.Entry(self.window)
        entry_description.pack(pady=5)
        tk.Label(self.window, text="Enter Movie Genre:").pack(pady=5)
        entry_genre = tk.Entry(self.window)
        entry_genre.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_movie).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_movies).pack(pady=10)

    def remove_movie(self):
        def submit_remove_movie():
            try:
                movie_id = int(entry_movie_id.get())
                self._movie_service.remove(movie_id)
                messagebox.showinfo("Success", f"Movie with ID {movie_id} removed successfully.")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter the ID of the movie to remove:").pack(pady=5)
        entry_movie_id = tk.Entry(self.window)
        entry_movie_id.pack(pady=5)
        tk.Button(self.window, text="Submit", command=submit_remove_movie).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.manage_movies).pack(pady=10)

    def list_movies(self):
        # List all movies in the window
        for widget in self.window.winfo_children():
            widget.destroy()

        movies = self._movie_service.getAll()
        for movie in movies:
            tk.Label(self.window, text=movie).pack(pady=5)

        tk.Button(self.window, text="Back", command=self.manage_movies).pack(pady=10)

    def list_all_rentals(self):
        # Clear the window and display all rentals
        for widget in self.window.winfo_children():
            widget.destroy()

        # Fetch rentals from the rental service
        rentals = self._rental_service.getAll()

        # Display rentals in the GUI
        tk.Label(self.window, text="All Rentals", font=("Arial", 16)).pack(pady=10)
        if rentals:
            for rental in rentals:
                rental_info = (f"Rental ID: {rental.id}, Movie ID: {rental.movie_id}, Client ID: {rental.client_id}, "
                               f"Rented Date: {rental.rented_date}, Due Date: {rental.due_date}, "
                               f"Returned Date: {rental.returned_date if rental.returned_date else 'Not Returned'}")
                tk.Label(self.window, text=rental_info).pack(anchor="w", padx=20, pady=5)
        else:
            tk.Label(self.window, text="No rentals available.").pack(pady=10)

        # Add a back button to return to the rent/return menu
        tk.Button(self.window, text="Back", command=self.rent_or_return_movie).pack(pady=10)
    def rent_or_return_movie(self):
        # Clear the window and show options for renting or returning a movie
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Button(self.window, text="Rent a Movie", command=self.rent_movie).pack(pady=10)
        tk.Button(self.window, text="Return a Movie", command=self.return_movie).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.create_main_menu).pack(pady=10)

    def rent_movie(self):
        def submit_rent():
            try:
                movie_id = int(entry_movie_id.get())
                client_id = int(entry_client_id.get())
                rental_date = date.today()
                due_date = rental_date + timedelta(days=7)  # Example: 7-day rental period
                rental = self._rental_service.rent_movie(movie_id, client_id, rental_date, due_date)
                messagebox.showinfo("Success", f"Rental created successfully: {rental}")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Movie ID:").pack(pady=5)
        entry_movie_id = tk.Entry(self.window)
        entry_movie_id.pack(pady=5)

        tk.Label(self.window, text="Enter Client ID:").pack(pady=5)
        entry_client_id = tk.Entry(self.window)
        entry_client_id.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_rent).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.rent_or_return_movie).pack(pady=10)

    def return_movie(self):
        def submit_return():
            try:
                rental_id = int(entry_rental_id.get())
                self._rental_service.return_movie(rental_id,date.today())
                messagebox.showinfo("Success", f"Rental with ID {rental_id} has been returned successfully.")
            except ValueError as e:
                messagebox.showerror("Error", f"Error: {e}")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Rental ID:").pack(pady=5)
        entry_rental_id = tk.Entry(self.window)
        entry_rental_id.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_return).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.rent_or_return_movie).pack(pady=10)

    def search(self):
        # Clear the window and show options for searching movies or clients
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Button(self.window, text="Search Movies", command=self.search_movies).pack(pady=10)
        tk.Button(self.window, text="Search Clients", command=self.search_clients).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.create_main_menu).pack(pady=10)

    def search_movies(self):
        def submit_movie_search():
            search_query = entry_search.get()
            results = self._movie_service.search(search_query)
            if results:
                result_text = "\n".join([str(movie) for movie in results])
                messagebox.showinfo("Search Results", result_text)
            else:
                messagebox.showinfo("Search Results", "No movies found matching the query.")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Movie Search Query:").pack(pady=5)
        entry_search = tk.Entry(self.window)
        entry_search.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_movie_search).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.search).pack(pady=10)

    def search_clients(self):
        def submit_client_search():
            search_query = entry_search.get()
            results = self._client_service.search(search_query)
            if results:
                result_text = "\n".join([str(client) for client in results])
                messagebox.showinfo("Search Results", result_text)
            else:
                messagebox.showinfo("Search Results", "No clients found matching the query.")

        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Enter Client Search Query:").pack(pady=5)
        entry_search = tk.Entry(self.window)
        entry_search.pack(pady=5)

        tk.Button(self.window, text="Submit", command=submit_client_search).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.search).pack(pady=10)

    def generate_20_random_items(self):
        fake = Faker()

        def generate_movies():
            for _ in range(20):
                title = fake.sentence(nb_words=3).strip(".")
                description = fake.text(max_nb_chars=50)
                genre = random.choice(["Action", "Comedy", "Drama", "Horror", "Sci-Fi", "Romance"])
                try:
                    self._movie_service.add(title, description, genre)
                except ValueError as e:
                    print(f"Skipped movie generation: {e}")  # Log the error
            messagebox.showinfo("Success", "20 random movies have been generated!")

        def generate_clients():
            for _ in range(20):
                name = fake.name()
                try:
                    self._client_service.add(name)
                except ValueError as e:
                    print(f"Skipped client generation: {e}")  # Log the error
            messagebox.showinfo("Success", "20 random clients have been generated!")

        def generate_rentals():
            movies = self._movie_service.getAll()
            clients = self._client_service.getAll()

            if not movies or not clients:
                messagebox.showerror("Error", "No movies or clients available to generate rentals!")
                return

            for _ in range(20):
                client = random.choice(clients)
                movie = random.choice(movies)

                # Check if the movie is already rented
                active_rentals = self._rental_service.get_rentals_by_movie(movie.id)
                if any(rental.returned_date is None for rental in active_rentals):
                    continue  # Skip if the movie is already rented

                # Generate rental and due dates
                rented_date = date.today() - timedelta(days=random.randint(1, 30))
                due_date = rented_date + timedelta(days=random.randint(1, 14))

                # Randomly decide if the movie has been returned
                if random.choice([True, False]):
                    returned_date = rented_date + timedelta(days=random.randint(1, (due_date - rented_date).days))
                else:
                    returned_date = None

                try:
                    self._rental_service.rent_movie(client.id, movie.id, rented_date, due_date)
                    if returned_date:
                        # Mark the rental as returned
                        rental = self._rental_service.getAll()[-1]  # Get the most recent rental
                        self._rental_service.return_movie(rental.id, returned_date)
                except ValueError as e:
                    print(f"Skipped rental generation: {e}")  # Log the error
            messagebox.showinfo("Success", "20 random rentals have been generated!")

        # Clear the window and display submenu options
        for widget in self.window.winfo_children():
            widget.destroy()

        tk.Label(self.window, text="Choose an option to generate 20 random items:").pack(pady=10)

        tk.Button(self.window, text="Generate 20 Movies", command=generate_movies).pack(pady=10)
        tk.Button(self.window, text="Generate 20 Clients", command=generate_clients).pack(pady=10)
        tk.Button(self.window, text="Generate 20 Rentals", command=generate_rentals).pack(pady=10)
        tk.Button(self.window, text="Back", command=self.create_main_menu).pack(pady=10)

    def run(self):
        # Run the GUI application
        self.window.mainloop()


"""# In the main program:
settings = load_settings("settings.properties")
repositories = initialize_repositories(settings)

# Access repositories
movies_repo = repositories["movies"]
clients_repo = repositories["clients"]
rentals_repo = repositories["rentals"]



movie_service = MovieService(movies_repo)
client_service= ClientService(clients_repo)
rental_service = RentalService(rentals_repo,client_service,movie_service)"""

# Initialize the UI and run the application
"""gui = GUI(movie_service, client_service, rental_service)""""""
gui.run()"""

#TODO list all rentals, generate 20 rentals button 