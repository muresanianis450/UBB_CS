from src.ui.ui import UI
from src.ui.repository_factory import *
from src.services.service import *
from src.services.undo_service import *
def start_ui_mode():
    # Load settings and initialize repositories before UI mode selection
    settings = load_settings("settings.properties")
    repositories = initialize_repositories(settings)

    # Access repositories
    movies_repo = repositories["movies"]
    clients_repo = repositories["clients"]
    rentals_repo = repositories["rentals"]

    # Create an undo service instance
    undo_service = UndoService()

    # Initialize services with repositories
    movie_service = MovieService(undo_service, movies_repo)
    client_service = ClientService(undo_service, clients_repo)
    rental_service = RentalService(undo_service, rentals_repo, clients_repo, movies_repo)

    ui = UI(movie_service, client_service, rental_service,undo_service)
    ui.run()


if __name__ == "__main__":
    start_ui_mode()
