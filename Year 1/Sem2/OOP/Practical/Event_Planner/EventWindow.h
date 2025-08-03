#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "EventService.h"

class EventWindow : public QWidget, public Observer {
  Q_OBJECT
private:
  EventService& service;
  QListWidget* eventList;
  QListWidget* popularList;
  QLineEdit* nameInput;
  QLineEdit* attenderInput;
  QPushButton* addAttenderButton;

  void updateEventList();
  void updatePopularList();

public:
  EventWindow(EventService& s, QWidget* parent = nullptr);
  ~EventWindow() override = default;

  void update() override;

  private slots:
      void handleAddAttender();
};
