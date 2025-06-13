#include "gui.h"
#include <algorithm>
#include <cctype>

namespace {
int parseProbability(const QString& input) {
    std::string str = input.toStdString();
    std::string number;
    std::copy_if(str.begin(), str.end(), std::back_inserter(number), ::isdigit);
    return number.empty() ? -1 : std::stoi(number);
}
}

GUI::GUI(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainItems = new QListWidget();
    filterInput = new QLineEdit();
    hourInput = new QLineEdit();
    descriptionInput = new QLineEdit();
    showButton = new QPushButton("Show intervals and total time");

    QLabel *l1 = new QLabel("Filter by probability:");
    QLabel *l2 = new QLabel("Search by starting time in hours:");
    QLabel *l3 = new QLabel("Search by weather type");

    mainLayout->addWidget(mainItems);
    mainLayout->addWidget(l1);
    mainLayout->addWidget(filterInput);
    mainLayout->addWidget(l2);
    mainLayout->addWidget(hourInput);
    mainLayout->addWidget(l3);
    mainLayout->addWidget(descriptionInput);
    mainLayout->addWidget(showButton);

    setLayout(mainLayout);

    populateList();

    QObject::connect(filterInput, &QLineEdit::textChanged, this, &GUI::populateList);
    QObject::connect(hourInput, &QLineEdit::textChanged, this, &GUI::populateList);
    QObject::connect(showButton, &QPushButton::clicked, this, &GUI::showAnswer);
}

void GUI::populateList() {
    mainItems->clear();
    // Priority: probability filter, then hour filter, else show all
    if (!filterInput->text().isEmpty()) {
        int prob = parseProbability(filterInput->text());
        if (prob == -1) return;
        for (const auto& x : service.filterWeather(prob)) {
            mainItems->addItem(QString::fromStdString(x.toString()));
        }
    } else if (!hourInput->text().isEmpty()) {
        bool ok = false;
        int hour = hourInput->text().toInt(&ok);
        if (!ok) return;
        for (const auto& x : service.filterByStartHour(hour)) {
            mainItems->addItem(QString::fromStdString(x.toString()));
        }
    } else {
        for (const auto& x : service.getWeather()) {
            mainItems->addItem(QString::fromStdString(x.toString()));
        }
    }
}

void GUI::showAnswer() {
    auto ans = service.getAnswer(hourInput->text().toInt(),
                                 descriptionInput->text().toStdString());

    QWidget *window = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel(
        QString::fromStdString(std::to_string(ans.first) + " hours of " +
                               descriptionInput->text().toStdString() +
                               " after " + hourInput->text().toStdString()));

    if (ans.first == 0) {
        QMessageBox::warning(this, "warning", "no intervals");
        return;
    }

    QListWidget *items = new QListWidget();
    for (const auto& x : ans.second) {
        items->addItem(QString::fromStdString(x.toString()));
    }

    layout->addWidget(label);
    layout->addWidget(items);

    window->setLayout(layout);
    window->show();
}