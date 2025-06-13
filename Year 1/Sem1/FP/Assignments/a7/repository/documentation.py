
from src.repository.memory_repository import *
from src.repository.json_file_repository import *
from src.repository.text_file_repository import *
from pdoc import *


def documentation():
    f = open("docs.html", "wt")
    f.write(pdoc("json_file_repository.py",""))
    f.write(pdoc("memory_repository.py", ""))
    f.write(pdoc("text_file_repository.py",""))

    f.close()

documentation()