#include "ShowOneByOneDialog.h"
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
ShowOneByOneDialog::ShowOneByOneDialog(Service& service, const QString& whereToSaveFile,QWidget *parent)
    : QDialog(parent), service(service), currentIndex(0) , whereToSaveFile(whereToSaveFile){

    setWindowTitle("Show Dogs One by One");
    resize(400, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    nameLabel = new QLabel(this);
    breedLabel = new QLabel(this);
    ageLabel = new QLabel(this);
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(300, 300);
    imageLabel->setScaledContents(true);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(breedLabel);
    mainLayout->addWidget(ageLabel);
    mainLayout->addWidget(imageLabel);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    adoptButton = new QPushButton("Adopt");
    nextButton = new QPushButton("Next");
    exitButton = new QPushButton("Exit");

    buttonLayout->addWidget(adoptButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(exitButton);

    mainLayout->addLayout(buttonLayout);

    connect(adoptButton, &QPushButton::clicked, this, &ShowOneByOneDialog::onAdoptClicked);
    connect(nextButton, &QPushButton::clicked, this, &ShowOneByOneDialog::onNextClicked);
    connect(exitButton, &QPushButton::clicked, this, &QDialog::accept);

    std::string fileType = whereToSaveFile.toStdString();
    if (fileType == "csv")
        adoptionList = std::make_unique<CSVAdoptionList>();
    else if (fileType == "html")
        adoptionList = std::make_unique<HTMLAdoptionList>();
    else
        adoptionList = nullptr;

    show_one_by_one();
}

void ShowOneByOneDialog::show_one_by_one() {
    dogs = service.getAllDogs();
    if (!dogs.empty()) {
        displayDog(dogs[currentIndex]);
    } else {
        nameLabel->setText("No dogs available.");
    }
}

void ShowOneByOneDialog::displayDog(const Dog& dog) {
    nameLabel->setText("Name: " + QString::fromStdString(dog.getName()));
    breedLabel->setText("Breed: " + QString::fromStdString(dog.getBreed()));
    ageLabel->setText("Age: " + QString::number(dog.getAge()));
    loadImageFromLocal(QString::fromStdString(dog.getPhotography()));
}

void ShowOneByOneDialog::onNextClicked() {
    if (dogs.empty()) return;
    currentIndex = (currentIndex + 1) % dogs.size();
    displayDog(dogs[currentIndex]);
}

void ShowOneByOneDialog::onAdoptClicked() {
    if (dogs.empty()) return;

    Dog dog = dogs[currentIndex];
    service.adoptDog(dog);         // Add to adopted list
    service.removeDog(dog);        // Remove from repo

    // Save to file
    if (adoptionList) {
        adoptionList->addDog(dog);
        adoptionList->saveToFile(whereToSaveFile.toStdString() == "csv" ? "adoption_list.csv" : "adoption_list.html");
        QMessageBox::information(this, "Success", "Dog adopted successfully!");
    }

    // Refresh dog list
    dogs = service.getAllDogs();

    if (dogs.empty()) {
        nameLabel->setText("No more dogs available.");
        breedLabel->clear();
        ageLabel->clear();
        imageLabel->clear();
        return;
    }

    currentIndex %= dogs.size();
    displayDog(dogs[currentIndex]);
}

void ShowOneByOneDialog::loadImageFromLocal(const QString& filePath) {
    // Convert to absolute path if it's relative or not already
    qDebug() << "Loading image from path:" << filePath;
    QString correctedPath = QDir::toNativeSeparators(filePath);
    qDebug() << "Corrected path:" << correctedPath;

    // Load the image into a QPixmap
    QPixmap pixmap;
    if (!pixmap.load(filePath)) {
        qDebug() << "Image loading failed.";
        imageLabel->setText("Image loading failed.");
        return;
    }

    qDebug() << "Image loaded successfully.";
    imageLabel->setText("Image loaded successfully.");
    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}