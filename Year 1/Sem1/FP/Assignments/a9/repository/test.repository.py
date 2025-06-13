# test_repository.py

import pytest
from datetime import date, timedelta
from src.domain.domain import Movie, Client, Rental, generate_20_clients
from src.repository.repository import Repository
from src.repository.in_memory_repo import *

# Test Movie class
def test_movie_creation():
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")
    assert movie.title == "Inception"
    assert movie.get_description() == "A mind-bending thriller"
    assert movie.get_genre() == "Sci-Fi"
    assert isinstance(movie.id, int)


# Test Client class
def test_client_creation():
    client = Client("John Doe")
    assert client.name == "John Doe"
    assert isinstance(client.id, int)


# Test Rental class
def test_rental_creation():
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")
    client = Client("John Doe")
    rental = Rental(movie.id, client.id, date.today(), date.today() + timedelta(days=7))

    assert rental.movie_id == movie.id
    assert rental.client_id == client.id
    assert rental.rented_date == date.today()
    assert rental.due_date == date.today() + timedelta(days=7)


# Test Repository add and get by ID methods
def test_repository_add():
    repo = Repository()
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")
    repo.add(movie)

    retrieved_movie = repo.get_by_id(movie.id)
    assert retrieved_movie == movie


def test_repository_remove():
    repo = Repository()
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")
    repo.add(movie)
    repo.remove(movie.id)

    retrieved_movie = repo.get_by_id(movie.id)
    assert retrieved_movie is None


# Test in-memory repository (Movie_repo_inmemory)
def test_movie_repo_inmemory():
    movie_repo = Movie_repo_inmemory()
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")

    movie_repo.add(movie)
    assert len(movie_repo) == 1
    retrieved_movie = movie_repo.get_by_id(movie.id)
    assert retrieved_movie == movie


# Test Client_repo_inmemory
def test_client_repo_inmemory():
    client_repo = Client_repo_inmemory()
    client = Client("John Doe")

    client_repo.add(client)
    assert len(client_repo) == 1
    retrieved_client = client_repo.get_by_id(client.id)
    assert retrieved_client == client


# Test Rental_repo_inmemory
def test_rental_repo_inmemory():
    rental_repo = Rental_repo_inmemory()
    movie = Movie("Inception", "A mind-bending thriller", "Sci-Fi")
    client = Client("John Doe")
    rental = Rental(movie.id, client.id, date.today(), date.today() + timedelta(days=7))

    rental_repo.add(rental)
    assert len(rental_repo) == 1
    retrieved_rental = rental_repo.get_by_id(rental.id)
    assert retrieved_rental == rental


# Test generating 20 clients
def test_generate_20_clients():
    clients = generate_20_clients()
    assert len(clients) == 20
    assert all(isinstance(client, Client) for client in clients)