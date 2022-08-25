#ifndef MANAGECARS_H
#define MANAGECARS_H
#include "iostream"
#include "string.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include <QTextStream>
#include <QMessageBox>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QPushButton>
#include <QListWidgetItem>
#include <QtCore>
#include <QtGui>


using namespace std;
class ManageCars
{

public:


    ManageCars();
    ManageCars(bool reload);
    ManageCars(multimap<int, ManageCars> NewMap);
    ManageCars(string admin, string marca, string model, int ano, double km, double Price, string imagepath);

    void AddFilesToList();
    string getCarsAvailable(int index);
    string getModelsAvailable(int index);
    vector<string> getModelsAvailableFromID(vector<int> Ids);
    multimap<int, ManageCars> ExistentsCars(string path);
    int FindID();
    vector<int> GetID(string marca);
    int GetSizeCarros(string tipo);
    vector<int> IDModels_ToBuy(string model);
    void DeleteOnDataBase(int index, string marca);
    string GetImagePath(int key);
    static multimap<int, ManageCars> CarsRead, ShoppingCart;
    int GetAno(int id);
    int GetKm(int id);
    double GetPrice(int id);
    string GetMarca(int id);
    string GetModel(int id);
    string GetAdmin(int id);
    vector<string> ModelFromBrands(string);
    multimap<int, ManageCars> CompleteTheShoppingCart(int, string);



private:
    string Marca,Admin,Model;
    int ano;
    int id;
    double km;
    double Price;
    //bool negociavel;
    string intialpath,imagepath = "";

    vector<string> Marcas_Disponiveis;
    vector<string> Models_Disponiveis;
    vector<int> IDS;

};

#endif // MANAGECARS_H
