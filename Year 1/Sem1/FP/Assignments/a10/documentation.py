from pdoc import pdoc

def documentation():
    with open("docs.html", "wt") as f:
        f.write(pdoc('connect_four.application.game_manager'))
        f.write(pdoc('connect_four.tests.tests'))
        f.write(pdoc('connect_four.ui.ui'))
        f.write(pdoc('connect_four.ui.gui'))

documentation()