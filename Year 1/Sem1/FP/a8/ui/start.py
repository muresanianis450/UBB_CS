from src.ui.ui import UI
from src.ui.gui import GUI
from src.ui.repository_factory import *
from src.services.service import *

def start_ui_mode():
    # Load settings and initialize repositories before UI mode selection
    settings = load_settings("settings.properties")
    repositories = initialize_repositories(settings)

    # Access repositories
    movies_repo = repositories["movies"]
    clients_repo = repositories["clients"]
    rentals_repo = repositories["rentals"]

    # Initialize services with repositories
    movie_service = MovieService(movies_repo)
    client_service = ClientService(clients_repo)
    rental_service = RentalService(rentals_repo, clients_repo, movies_repo)

    mode = input("Choose UI mode (1 for text-based, 2 for graphical): ")
    if mode == "1":
        # Initialize text-based UI and run it
        ui = UI(movie_service, client_service, rental_service)
        ui.run()  # Runs the text-based UI
    elif mode == "2":
        # Initialize graphical UI and run it
        gui = GUI(movie_service, client_service, rental_service)
        gui.run()  # Starts the graphical UI
    else:
        print("Invalid choice! Exiting.")

if __name__ == "__main__":
    start_ui_mode()


