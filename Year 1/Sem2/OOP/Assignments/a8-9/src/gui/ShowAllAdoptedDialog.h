#ifndef SHOWALLADOPTEDDIALOG_H
#define SHOWALLADOPTEDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "../adoption/AdoptionList.h"

class ShowAllAdoptedDialog : public QDialog {
    Q_OBJECT

public:
    explicit ShowAllAdoptedDialog(std::unique_ptr<AdoptionList> adoptionList, QWidget* parent = nullptr);

private:
    void populateTable(const std::vector<Dog>& dogs);
};

#endif // SHOWALLADOPTEDDIALOG_H