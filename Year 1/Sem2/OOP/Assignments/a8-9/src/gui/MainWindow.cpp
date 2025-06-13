  //
  // Created by mures on 5/11/2025.
  //

  #include "MainWindow.h"
  #include "AddDogDialog.h"
  #include "RemoveDogDialog.h"
  #include "UpdateDogDialog.h"
  #include "ShowListDogsDialog.h"
  #include "ShowOneByOneDialog.h"
  #include "ShowByBreedDialog.h"
#include "ShowAllAdoptedDialog.h"
#include "ChartDialog.h"
  MainWindow::MainWindow(Service& service, QWidget *parent)
      : QMainWindow(parent), service(service), stackedWidget(new QStackedWidget(this)){

    setCentralWidget(stackedWidget); // Set the central widget of the main window
      stackedWidget->addWidget(createStartPage());// Add the start page
      stackedWidget->addWidget(createModePage());// Add the user page
      stackedWidget->addWidget(createAdminPage());// Add the admin page
      stackedWidget->addWidget(createUserPage());// Add the user page
  stackedWidget->setCurrentIndex(0); // Show start page first
    }
  QWidget* MainWindow::createStartPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QPushButton *csvButton = new QPushButton("CSV");
    QPushButton *htmlButton = new QPushButton("HTML");

    connect(csvButton, &QPushButton::clicked, this, [this]() {
      this->whereToSaveFile = "csv";
      goToModePage();
    });
    connect(htmlButton, &QPushButton::clicked, this, [this]() {
      this->whereToSaveFile= "html";
      goToModePage();
    });

    layout->addWidget(csvButton);
    layout->addWidget(htmlButton);

    return page;
    }

  QWidget* MainWindow::createModePage() {

  QWidget *page = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout(page);

  QPushButton *adminButton = new QPushButton("Admin Mode");
  QPushButton *userButton = new QPushButton("User Mode");

  connect(adminButton, &QPushButton::clicked, this, &MainWindow::goToAdminPage);
    connect(userButton,&QPushButton::clicked, this, &MainWindow::goToUserPage);
  layout->addWidget(adminButton);
  layout->addWidget(userButton);
    QPushButton* showChartButton = new QPushButton("Show Chart");
    layout->addWidget(showChartButton);
    connect(showChartButton, &QPushButton::clicked, this, [this]() {
    try {
        std::string type = whereToSaveFile;
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);

      auto adoptionList = AdoptionListFactory::createAdoptionList(type);
      auto dogs = adoptionList->getAdoptedDogs(); // Assuming getDogs() returns a std::vector<Dog>
      ChartDialog dialog(dogs, this);
        dialog.exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
});


  return page;
  }


  QWidget* MainWindow::createAdminPage() {

    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    this->setWindowTitle("Admin Mode");
    QPushButton *addButton = new QPushButton("ADD DOG");
    QPushButton *removeButton = new QPushButton("REMOVE DOG");
    QPushButton *updateButton = new QPushButton("UPDATE DOG");
    QPushButton *printButton = new QPushButton("PRINT ALL DOGS");

    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(updateButton);
    layout->addWidget(printButton);

    connect(addButton, &QPushButton::clicked, this, [this]() {
          AddDogDialog dialog(this->service,  QString::fromStdString(this->whereToSaveFile),this);
          dialog.exec();
      });
    connect(removeButton, &QPushButton::clicked, this,[this]() {
      RemoveDogDialog dialog(this->service,this);
      dialog.exec();
    });

    connect(updateButton, &QPushButton::clicked,this,[this]() {
      UpdateDogDialog dialog(this->service,this);
      dialog.exec();
    });

    connect(printButton, &QPushButton::clicked,this,[this]() {
      ShowListDogsDialog dialog(this->service,this);
      dialog.exec();
    });

    return page;
  }

  void MainWindow::goToUserPage() const {
    stackedWidget->setCurrentIndex(3); // User Page index
  }

  void MainWindow::goToModePage() const {
    stackedWidget->setCurrentIndex(1); //Mode Page Index
  }

  void MainWindow::goToAdminPage() const {
    stackedWidget->setCurrentIndex(2);// Admin Page index
  }

  QWidget *MainWindow::createUserPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    this->setWindowTitle("User Mode");

    QPushButton *showDogsButton = new QPushButton("Show Dogs");
    QPushButton *showByBreedButton = new QPushButton("Show by Breed");
    QPushButton *printCurrentButton = new QPushButton("Print Current Adopted Dogs");
    QPushButton *printAdoptionButton = new QPushButton("Print Adoption List");


    layout->addWidget(showDogsButton);
    layout->addWidget(showByBreedButton);
    layout->addWidget(printCurrentButton);
    layout->addWidget(printAdoptionButton);

    connect(showDogsButton, &QPushButton::clicked, this,[this](){
      ShowOneByOneDialog dialog(this->service,QString::fromStdString(this->whereToSaveFile),this);
      dialog.exec();
    });
    connect(showByBreedButton, &QPushButton::clicked,this,[this]() {
      ShowByBreedDialog dialog(this->service,QString::fromStdString(this->whereToSaveFile),this);
      dialog.exec();
    });
    connect(printAdoptionButton, &QPushButton::clicked, this, [this]() {
    try {
        // Capitalize for factory input
        std::string type = whereToSaveFile;
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        auto adoptionList = AdoptionListFactory::createAdoptionList(type);
        ShowAllAdoptedDialog dialog(std::move(adoptionList), this);
        dialog.exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
});
    return page;
  };
