import random

def getRandomName() -> str:
    first_names = [
        "Andrei", "Ioana", "Maria", "Mihai", "Elena", "Alexandru", "Cristina",
        "Darius", "Ana", "Vlad", "Iulia", "Radu", "Sofia", "Florin",
        "Gabriel", "Diana", "Cosmin", "Claudia", "Victor", "Larisa"
    ]
    return random.choice(first_names)

def getid()-> int:
    return  random.randint(911,917)
class Student:
    def __init__(self, student_id: int, name: str, group: int):
        self.student_id = student_id
        self.name = name
        self.group = group

    def __str__(self):
        return f"ID: {self.student_id}, Name: {self.name}, Group: {self.group}"



def generateNrandomStudents(n: int) -> list[Student]:
    students = []
    for _ in range(n):
        student = Student(getid(),getRandomName(), random.randint(911, 917))
        students.append(student)
    return students


