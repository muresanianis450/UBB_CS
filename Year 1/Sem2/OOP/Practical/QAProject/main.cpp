#include <QApplication>
#include "UserWindow.h"
#include "Service.h"
#include "Repository.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    Repository repo("users.txt", "questions.txt", "answers.txt");

    Service service(repo);

    const auto& users = repo.getUsers();

    std::vector<UserWindow*> windows;
    for (const auto& user : users) {
        auto* window = new UserWindow(service, user);
        window->show();
        windows.push_back(window);
    }

    return app.exec();
}
