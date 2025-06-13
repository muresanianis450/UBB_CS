class BaseRepository:
    def __init__(self):
        self._data = []

    def add(self, entity):
        self._data.append(entity)

    def remove(self, condition):
        self._data = [entity for entity in self._data if not condition(entity)]

    def get_all(self):
        return self._data.copy()
