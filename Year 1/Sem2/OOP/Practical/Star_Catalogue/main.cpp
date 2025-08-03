#include <QApplication>
#include "StarWindow.h"
#include "Service.h"
#include "StarRepository.h"
#include "AstronomerRepository.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    StarRepository starRepo("stars.txt");
    AstronomerRepository astronomerRepo("astronomers.txt");
    Service service(starRepo, astronomerRepo);

    const auto& astronomers = astronomerRepo.getAll();
    std::vector<StarWindow*> windows;

    for (const auto& astronomer : astronomers) {
        auto* window = new StarWindow(service, astronomer);
        window->show();
        windows.push_back(window);
    }

    return app.exec();
}
