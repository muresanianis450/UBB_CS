#include <QApplication>
#include "Service.h"
#include "PresenterWindow.h"
#include "ParticipantWindow.h"
#include <vector>
#include <string>
#include <memory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try {
        Repository repo("participants.txt", "questions.txt");
        Service service(repo);

        // Create presenter window
        auto presenterWindow = std::make_unique<PresenterWindow>(service);
        presenterWindow->show();

        // Create and show participant windows
        std::vector<std::unique_ptr<ParticipantWindow>> participantWindows;

        for (const auto& participant : repo.getParticipants()) {
            participantWindows.emplace_back(std::make_unique<ParticipantWindow>(service, participant.getName()));
            participantWindows.back()->show();
        }

        return app.exec();
    } catch (const std::exception& e) {
        qCritical("Exception: %s", e.what());
        return -1;
    }
}
