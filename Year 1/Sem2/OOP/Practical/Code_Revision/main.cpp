// Main.cpp
#include <QApplication>
#include "Repository.h"
#include "Service.h"
#include "ProgrammerWindow.h"
//#include "StatisticsWindow.h" // not yet defined

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Repository repo{"programmers.txt", "source.txt"};
    Service service{repo};

    std::vector<ProgrammerWindow*> windows;
    for (const auto& p : service.getProgrammers()) {
        auto* w = new ProgrammerWindow(service, p);
        service.addObserver(w);
        w->show();
        windows.push_back(w);
    }

    // StatisticsWindow* stats = new StatisticsWindow(service);
    // service.addObserver(stats);
    // stats->show();

    return app.exec();
}