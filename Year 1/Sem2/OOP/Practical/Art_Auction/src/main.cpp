#include <QApplication>
#include <iostream>
#include "Repository.h"
#include "Service.h"
#include "AdminWindow.h"
#include "CollectorWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load users and items
    Repository repo("users.txt", "items.txt");
    repo.loadUsers();
    repo.loadItems();

    Service service(repo);

    // Create windows for all users based on type
    std::vector<AdminWindow*> adminWindows;
    std::vector<CollectorWindow*> collectorWindows;

    for (const auto& user : repo.getUsers()) {
        if (user.getType() == "administrator") {
            auto* admin = new AdminWindow(service);
            admin->setWindowTitle(QString::fromStdString("Admin: " + user.getName()));
            admin->show();
            adminWindows.push_back(admin);
        } else if (user.getType() == "collector") {
            auto* collector = new CollectorWindow(service,user.getId());
            collector->setWindowTitle(QString::fromStdString("Collector: " + user.getName()));
            collector->show();
            collectorWindows.push_back(collector);
        }
    }

    app.exec();
    repo.saveItems();
}