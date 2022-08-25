#ifndef CARSAVAILABLE_H
#define CARSAVAILABLE_H

#include <QDialog>
#include <QLabel>
#include "adminwindow.h"
#include <map>
#include<algorithm>
#include<vector>
#include<iostream>
#include "carsavailabletest.h"
#include "confirmadmin.h"
using namespace std;


namespace Ui {
class CarsAvailable;
}

class CarsAvailable : public QDialog
{
    Q_OBJECT

public:
    explicit CarsAvailable(QWidget *parent = nullptr);
    ~CarsAvailable();
    void ModelToDisplay();
    int GetNumberOfModel(string modelo);
    int GetImagePath(int key);
    void RemoveCar();
    void DeleteCars(int index,string marca);
    void BackDialog();
    //void SendToDeleteCars(int index);
    void CreateFrames(vector <string> ImagePath, int Num_ModelsAvalibles,string marca);
    void SendADDShoppingChart();


private slots:

    void on_Goback_clicked();

private:
    Ui::CarsAvailable *uiCars;
    vector <int> IdByModels;
    multimap<int, ManageCars> Cars;
    vector<string> ImagePath;
    int Num_ModelsAvalibles;



    QLabel* label_image;
    QVBoxLayout* verticalLayout;
    QSpacerItem* verticalSpacer;
    QVBoxLayout* verticalLayout_3;
    QVBoxLayout* verticalLayout_2;
    QHBoxLayout* horizontalLayout_2;
    QHBoxLayout* horizontalLayout_5;
    QLabel* label_3;
    QLabel* Sellerlabel;
    QLabel* label_2;
    QHBoxLayout* horizontalLayout_4;
    QLabel* label_5;
    QLabel* label_4;
    QHBoxLayout* horizontalLayout_3;
    QHBoxLayout* horizontalLayout_7;
    QHBoxLayout* horizontalLayout_8;
    QLabel* label_7;
    QLabel* label_6;
    QPushButton* Button;
    QSpacerItem* horizontalSpacer_4;
    QSpacerItem* horizontalSpacer_3;
    QSpacerItem* horizontalSpacer_5;
    QSpacerItem* horizontalSpacer_6;
};

#endif // CARSAVAILABLE_H
