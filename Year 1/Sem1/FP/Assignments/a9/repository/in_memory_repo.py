from src.repository.repository import Repository


class Movie_repo_inmemory(Repository):
    def __init__(self):
        super().__init__()

class Client_repo_inmemory(Repository):
    def __init__(self):
        super().__init__()

class Rental_repo_inmemory(Repository):
    def __init__(self):
        super().__init__()