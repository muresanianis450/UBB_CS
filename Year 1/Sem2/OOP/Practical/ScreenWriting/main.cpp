#include <QApplication>
#include "ScreenWritingGUI.h"
#include "Service.h"
#include "WriterRepository.h"
#include "IdeaRepository.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Initialize repositories from files
    WriterRepository writerRepo("writers.txt");
    IdeaRepository ideaRepo("ideas.txt");

    // Initialize service with references
    Service service(writerRepo, ideaRepo);

    // Create and show GUI windows for each writer
    // Create and show GUI windows for each writer
    std::vector<std::unique_ptr<ScreenwritingGUI>> windows;
    for (const auto& writer : writerRepo.getAll()) {
        auto gui = std::make_unique<ScreenwritingGUI>(service, writer);
        gui->show();
        windows.push_back(std::move(gui));  // keep pointers alive
    }

    return app.exec();
}
