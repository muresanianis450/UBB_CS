#include <QApplication>
#include "ProgrammerWindow.h"
#include "TaskRepository.h"
#include "TaskService.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TaskRepository repo("programmers.txt", "tasks.txt");
    TaskService service(repo);

    std::vector<Programmer> programmers = repo.getProgrammers();
    std::vector<ProgrammerWindow*> windows;

    for (const Programmer& p : programmers) {
        ProgrammerWindow* window = new ProgrammerWindow(service, p);
        window->setWindowTitle(QString::fromStdString(p.getName()));
        window->resize(600, 400);
        window->show();
        windows.push_back(window);
    }

    return app.exec();
}
