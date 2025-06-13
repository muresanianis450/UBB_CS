from src.repository.repository import Repository
from src.domain.domain import *
from datetime import datetime

class Movie_repo_text(Repository):
    def __init__(self,file_name):
        super().__init__()
        self.__file_name = file_name
        self.__loadfile()

    def __loadfile(self):
        lines = []
        try:
            fin = open(self.__file_name, "rt")
            lines = fin.readlines()
            fin.close()
        except IOError:
            open(self.__file_name, "wt").close()  # Create an empty file

        for line in lines:
            current_line = line.split(",")
            new_movie = Movie(current_line[0].strip(),current_line[1].strip(),current_line[2].strip(),current_line[3].strip())
            super().add(new_movie)

    def __savefile(self):
        fout = open(self.__file_name, "wt")

        for movie in self.get_all():
            moviestring = ( f"{movie.id},{movie.title},{movie.get_description()},"
                            f"{movie.get_genre()}\n" )
            fout.write(moviestring)
        fout.close()

    def add(self,movie : Movie):
        super().add(movie)
        self.__savefile()


class Client_repo_text(Repository):
    def __init__(self,file_name):
        super().__init__()
        self.__file_name = file_name
        self.__loadfile()

    def __loadfile(self):
        lines = []
        try:
            with open(self.__file_name, "rt") as fin:
                lines = fin.readlines()
        except IOError:
            open(self.__file_name, "wt").close()

        for line in lines:
            current_line = line.strip().split(",")
            # Ensure the first part is ID and the second part is name
            client_id = int(current_line[0].strip())
            client_name = current_line[1].strip()
            new_client = Client(client_name, client_id)  # Pass name first, then ID
            super().add(new_client)

    def __savefile(self):
        fout = open(self.__file_name, "wt")
        for client in self.get_all():
            client_string = f"{client.id},{client.name}\n"
            fout.write(client_string)
        fout.close()

    def add(self, client: Client):
        super().add(client)
        self.__savefile()


class Rental_repo_text(Repository):
    def __init__(self,file_name):
        super().__init__()
        self.__file_name = file_name
        self.__loadfile()

    def __loadfile(self):
        lines = []
        try:
            fin = open(self.__file_name, "rt")
            lines = fin.readlines()
            fin.close()
        except IOError:
            open(self.__file_name, "wt").close()

        for line in lines:
            current_line = line.split(",")
            # Parse the rental ID
            rental_id = int(current_line[0].strip())

            # Parse the dates from string to datetime.date
            rented_date = datetime.strptime(current_line[1].strip(), "%Y-%m-%d").date()
            due_date = datetime.strptime(current_line[2].strip(), "%Y-%m-%d").date()

            # Check if returned_date is empty; if so, set it to None
            returned_date_str = current_line[3].strip()
            returned_date = None
            if returned_date_str:
                returned_date = datetime.strptime(returned_date_str, "%Y-%m-%d").date()

            # Create a new Rental object with parsed values
            new_rental = Rental(rented_date, due_date, returned_date, rental_id)

            # Add the rental to the repository
            super().add(new_rental)


    def __savefile(self):
        with open(self.__file_name, "wt") as fout:
            for rental in self.get_all():  # Iterate over all rentals
                returned_date_str = rental.returned_date.strftime("%Y-%m-%d") if rental.returned_date else ""
                rental_string = f"{rental.id},{rental.rented_date.strftime('%Y-%m-%d')},{rental.due_date.strftime('%Y-%m-%d')},{returned_date_str}\n"
                fout.write(rental_string)

    def add(self, rental: Rental):
        super().add(rental)  # Add rental to the repository
        self.__savefile()  # Save to file after addition


"""movie_repo = Textfilemovie("movie.txt")
movies = generate_20_movies()
for movie in movies:
   movie_repo.add(movie)"""

"""client_repo = Client_repo_text("client.txt")
clients = generate_20_clients()
for client in clients:
    client_repo.add(client)"""

"""rental_repo = Rental_repo_text("rental.txt")
rentals = generate_20_rentals()
for rental in rentals:
    rental_repo.add(rental)"""