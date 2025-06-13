from src.domain.domain import Movie, Client, Rental, generate_20_clients

class RepositoryError(Exception):
    pass

class DuplicateIdError(RepositoryError):
    pass

class IdNotFountError(RepositoryError):
    pass

class RepositoryIterator():
    def __init__(self,data):
        self.__data = data
        self.__pos = -1

    def __next__(self):
        self.__pos += 1
        if len(self.__data) == self.__pos:
            #we have run out of elements in the data structure
            raise StopIteration()
        return self.__data[self.__pos]

class Repository:
    def __init__(self):
        self._items = {}

    def add(self, item):
        # Check the type of the item and select the unique ID accordingly
        if isinstance(item, Movie):
            item_id = item.id
        elif isinstance(item, Client):
            item_id = item.id
        elif isinstance(item, Rental):
            item_id = item.id
        else:
            raise ValueError("Unknown item type!")

        # Check if the item already exists in the repository
        if item_id in self._items:
            raise ValueError(f"Item with ID {item_id} already exists!")

        # Add the item to the repository
        self._items[item_id] = item

    def remove(self, item_id):
        if item_id not in self._items:
            raise ValueError(f"Item with ID {item_id} does not exist!")
        del self._items[item_id]

    def update(self, item_id, updated_item):
        if item_id not in self._items:
            raise ValueError(f"Item with ID {item_id} does not exist!")
        self._items[item_id] = updated_item

    def __iter__(self):
        return RepositoryIterator(list(self._items.values()))
    def get_all(self):
        return list(self._items.values())

    def __len__(self):
        return len(self._items)

    def __getitem__(self,item):
        if item not in self._items:
            return None
        return self._items[item]

    def get_by_id(self, item_id):
        return self._items.get(item_id, None)

"""repo = Repository()
clients = generate_20_clients()
for client in clients:
    repo.add(client)"""