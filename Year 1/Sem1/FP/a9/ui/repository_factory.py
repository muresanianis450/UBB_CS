
from src.repository.repository import Repository
from src.repository.binary_repo import Movie_repo_binary, Client_repo_binary, Rental_repo_binary
from src.repository.in_memory_repo import Movie_repo_inmemory, Client_repo_inmemory, Rental_repo_inmemory
from src.repository.textfile_repo import Movie_repo_text, Client_repo_text, Rental_repo_text

import configparser

def initialize_repositories(settings):
    repository_type = settings.get("repository")
    if not repository_type:
        raise ValueError("The 'repository' setting is missing or invalid.")

    repositories = {}

    if repository_type == "inmemory":
        # In-memory repositories
        repositories["movies"] = Movie_repo_inmemory()
        repositories["clients"] = Client_repo_inmemory()
        repositories["rentals"] = Rental_repo_inmemory()

    elif repository_type == "binaryfiles":
        # Binary file repositories
        repositories["movies"] = Movie_repo_binary(settings.get("movies", "movies.pickle"))
        repositories["clients"] = Client_repo_binary(settings.get("clients", "clients.pickle"))
        repositories["rentals"] = Rental_repo_binary(settings.get("rentals", "rentals.pickle"))

    elif repository_type == "textfiles":
        # Text file repositories
        repositories["movies"] = Movie_repo_text(settings.get("movies", "movies.txt"))
        repositories["clients"] = Client_repo_text(settings.get("clients", "clients.txt"))
        repositories["rentals"] = Rental_repo_text(settings.get("rentals", "rentals.txt"))

    else:
        raise ValueError(f"Unsupported repository type: {repository_type}")

    return repositories


def load_settings(file_path="settings.properties"):
    config = configparser.ConfigParser()
    config.read(file_path)

    try:
        settings = {
            "repository": config.get("DEFAULT", "repository"),
            "movies": config.get("DEFAULT", "movies"),
            "clients": config.get("DEFAULT", "clients"),
            "rentals": config.get("DEFAULT", "rentals"),
        }
    except configparser.NoSectionError as e:
        print(f"Error: Missing section in the config file: {e}")
        raise
    except configparser.NoOptionError as e:
        print(f"Error: Missing option in the config file: {e}")
        raise
    except Exception as e:
        print(f"Error: Unexpected error while loading settings: {e}")
        raise

    return settings
