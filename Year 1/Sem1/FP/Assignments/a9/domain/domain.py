import random
from datetime import date, timedelta
from faker import Faker

"""def generate_20_movies():
    fake = Faker()
    genres = ["Action", "Drama", "Sci-Fi", "Fantasy", "Comedy",
              "Adventure", "Romance", "Thriller", "Animation"]

    movies = []

    for _ in range(20):
        title = fake.text(max_nb_chars=10).strip('.')
        description = fake.text(max_nb_chars=25).strip('.')
        genre = random.choice(genres)
        movie = Movie(title,description,genre)
        movies.append(movie)
    return movies"""

"""def generate_20_rentals():
    rentals = []

    for _ in range(20):
        # Generate a random rented_date within the past 60 days
        rented_date = date.today() - timedelta(days=random.randint(1, 60))

        # Generate a due_date within 1 to 14 days after the rented_date
        due_date = rented_date + timedelta(days=random.randint(1, 14))

        # Generate a returned_date:
        # - Either the movie is returned (within the due date range or slightly late)
        # - Or it hasn't been returned yet (None)
        if random.choice([True, False]):  # 50% chance the movie has been returned
            returned_date = rented_date + timedelta(days=random.randint(1, (due_date - rented_date).days + 3))
        else:
            returned_date = None

        # Create a Rental instance
        rental = Rental(rented_date, due_date, returned_date)
        rentals.append(rental)
    return rentals"""

def generate_20_clients():
    clients = []
    fake = Faker()
    for _ in range(20):
        name = fake.first_name().strip('.')
        client = Client(name)
        clients.append(client)
    return clients

class Movie:
    #class level used to track used ids
    used_ids = set()

    def __init__(self,title,description,genre,movie_id=None):
        self.__movie_id = self.get_movie_id()
        self.__title = title
        self.__description = description
        self.__genre = genre

    @classmethod
    def get_movie_id(cls):
        #generate an unique id
        id = random.randint(1000,9999)
        while id in cls.used_ids:
            id = random.randint(1000,9999)
        cls.used_ids.add(id) #store the id in the class-level set
        return id

    @property
    def id(self):
        return self.__movie_id

    @property
    def title(self):
        return self.__title

    def get_description(self):
        return self.__description

    def get_genre(self):
        return self.__genre


    def __str__(self):
        return (  # Return the string representation
            f"ID: {self.__movie_id}, TITLE: {self.__title}, "
            f"GENRE: {self.__genre}, DESCRIPTION: {self.__description}"
        )
    #compare if two has the same id
    def __eq__(self, other):
        if type(other) != Movie:
            return False
        return self.__movie_id == other.__movie_id

class Client:
    used_ids = set()

    def __init__(self, name, client_id=None):
        if client_id is None:
            self.__client_id = self.set_client_id()
        else:
            self.__client_id = client_id
            Client.used_ids.add(client_id)
        self._name = name

    @classmethod
    def set_client_id(cls):
        id = random.randint(1000, 9999)
        while id in cls.used_ids:
            id = random.randint(1000, 9999)
        cls.used_ids.add(id)
        return id

    @property
    def id(self):
        return self.__client_id

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        self._name = name

    def __eq__(self, other):
        if type(other) != Client:
            return False
        return self.__client_id == other.__client_id

    def __str__(self):
        return f"ID: {self.__client_id}, NAME: {self._name}"

class Rental():
    used_ids = set()
    def __init__(self, movie_id, client_id, rented_date, due_date, returned_date=None):
        self.__rental_id = self.get_rental_id()
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date
        self.movie_id = movie_id
        self.client_id = client_id


    @classmethod
    def get_rental_id(cls):
        id = random.randint(1000,9999)
        while id in cls.used_ids:
            id = random.randint(1000,9999)
        cls.used_ids.add(id)
        return id

    @property
    def id(self):
        return self.__rental_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def due_date(self):
        return self.__due_date

    @property
    def returned_date(self):
        return self.__returned_date

    @returned_date.setter
    def returned_date(self, value):
        if self.__returned_date is not None:
            raise ValueError("This movie has already been returned.")
        self.__returned_date = value

#the lenght of from which the movie starts
    def __len__(self):
        if self.__due_date is not None:
            return (self.__due_date - self.__rented_date).days + 1
        today = date.today()
        return (today - self.__rented_date).days + 1

    def __str__(self):
        return (
            f"Rental ID: {self.id}, Rented Date: {self.rented_date}, "
            f"Due Date: {self.due_date}, Returned Date: {self.returned_date}"
        )




"""rentals = generate_20_rentals()

for rental in rentals:
    print(rental)"""