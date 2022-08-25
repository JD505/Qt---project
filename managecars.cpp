#include "managecars.h"

multimap<int, ManageCars> ManageCars::CarsRead;
multimap<int, ManageCars> ManageCars::ShoppingCart;
ManageCars::ManageCars()
{
    this->intialpath = "BD.dat";
    if (CarsRead.size() == 0) {

        ExistentsCars(intialpath);
    }
}

ManageCars::ManageCars(bool reload)
{
    if (reload == true) {
        CarsRead.clear();
        CarsRead = ExistentsCars(intialpath);
    }

    this->imagepath = "";
    this->Admin = "";
    this->intialpath = "BD.dat";
    this->Marca = "";
    this->km = 0;
    this->ano = 0;
    this->Model = "";
    this->Price = 0;

}

ManageCars::ManageCars(multimap<int, ManageCars> NewMap) {

    this->intialpath = "BD.dat";
    ifstream fileToRead(intialpath);
    string line;
    getline(fileToRead, line);
    fileToRead.close();

    fstream fileBD;
    fileBD.open(intialpath, ios::app);


    string StdAdmin, StdBrand, StdModel, StdKm, StdPrice, StdYear, StdImagePath;
    double km, Price;
    int year;

    for (std::multimap<int, ManageCars>::iterator it = NewMap.begin(); it != NewMap.end(); ++it) {
        StdAdmin = it->second.Admin;
        StdBrand = it->second.Marca;
        StdModel = it->second.Model;
        year = it->second.ano;
        km = it->second.km;
        Price = it->second.Price;
        StdImagePath = it->second.imagepath;

    }
    StdKm = to_string(km);
    StdPrice = to_string(Price);
    StdYear = to_string(year);

    if (fileBD.is_open() && line != "") {
        fileBD << "\n" << StdAdmin << " " << StdBrand << " " << StdModel << " " << StdYear << " " << StdKm << " " << StdPrice << " " << StdImagePath;

    }
    else {
        fileBD << StdAdmin << " " << StdBrand << " " << StdModel << " " << StdYear << " " << StdKm << " " << StdPrice << " " << StdImagePath;

    }


    //tem de dar refresh ao multimap logo tem de apagar o que lá tem e reecresver (função ExistentCar)
    CarsRead.clear();
    CarsRead = ExistentsCars(intialpath);



}


ManageCars::ManageCars(string admin ,string marca, string model, int ano, double km, double Price,string imagepath)
{
    this->imagepath = imagepath;
    this->Admin = admin;
    this->Marca = marca;
    this->km = km;
    this->ano = ano;
    this->Model = model;
    this->Price = Price;
 
    this->intialpath = "BD.dat";

}


void ManageCars::AddFilesToList()
{


    multimap<int, ManageCars> CarsBD_ = CarsRead;


    for (std::multimap<int, ManageCars>::iterator it = CarsBD_.begin(); it != CarsBD_.end(); ++it) {

        Marcas_Disponiveis.push_back(it->second.Marca);
        Models_Disponiveis.push_back(it->second.Model);
        IDS.push_back(it->first);
    } 

}

string ManageCars::getCarsAvailable(int index)
{
    // retorna as marcas dos carros disponiveis

    for (int i = 0; i < Marcas_Disponiveis.size(); i++) {
        return Marcas_Disponiveis[index];
    }

}

string ManageCars::getModelsAvailable(int index)
{
    //função retorna todos os modelos disponiveis independemente se está asssociado á amrca
    for (int i = 0; i < Models_Disponiveis.size(); i++) {
        return Models_Disponiveis[index];
    }
}

vector<string> ManageCars::getModelsAvailableFromID(vector<int> index)
{
    //função retorna todos os modelos disponiveis independemente se está asssociado á marca
    vector<string>  ModelFromId;
    //multimap<int, ManageCars> CarsBD_ = ExistentsCars("BD.dat");

    //percorre todo o multimap e procura no vector o numero que vem do outro lado que ja tinhamos visto que tinha os ids
    for (std::multimap<int, ManageCars>::iterator it = CarsRead.begin(); it != CarsRead.end()/*it != CarsRead.end()*/; ++it) {

        if (find(index.begin(), index.end(), it->first) != index.end()) {
            ModelFromId.push_back(it->second.Model);

        }
        else {

        }
    }
    return ModelFromId;

}

multimap<int, ManageCars> ManageCars::ExistentsCars(string path)
{
    //função para inicialmente ler o ficheiro base de dados com os carros anteriormente configurados


    ifstream fileBD;

    //open file in read mode
    fileBD.open(path, ios::in);
    if (fileBD.is_open()) {
        //read data from file to other map


        string line, str_Marca, str_Model, str_ano, str_km, str_Price, str_ImagePath, std_Admin;
        //loop to serch for each Car
        int i = 0;
        while (fileBD.eof() == 0) {

            getline(fileBD, line);
            stringstream(line) >> std_Admin >> str_Marca >> str_Model >> str_ano >> str_km >> str_Price  >> str_ImagePath;
            stringstream(str_ano) >> ano;
            stringstream(str_km) >> km;
            stringstream(str_Price) >> Price;
            stringstream(str_ImagePath) >> imagepath;
            stringstream(std_Admin) >> Admin;
            Marca = str_Marca;
            //stringstream(str_Model) >> Model;
            Model = str_Model;
            CarsRead.insert(make_pair(i, ManageCars(Admin,Marca, Model, ano, km, Price, imagepath)));
            i++;
        }

        //close the file

        fileBD.close();
        return CarsRead;
    }

    else {

        //QMessageBox::information(0,"ERROR","No file detected to add cars to the list");
        return multimap<int, ManageCars>();
    }

}

int ManageCars::FindID()
{
    // função para sabermos a que id , cada marca tem um id , está descontinuada

    //convert a string to a qstring to facilitate to convert to a lower case
    QString Marca_ = Marca.c_str();
    Marca_.toLower();

    if (Marca_ == "audi") {
        id = 0;
    }
    else if (Marca_ == "mercedes") {
        id = 2;
    }
    else if (Marca_ == "bmw") {
        id = 1;
    }
    else if (Marca_ == "kia") {
        id = 3;
    }
    return id;
}

vector<int> ManageCars::GetID(string marca)
{
    vector<int> ToSaveId;


    for (std::multimap<int, ManageCars>::iterator it = CarsRead.begin(); it != CarsRead.end(); ++it) {
        if (it->second.Marca == marca) {
            ToSaveId.push_back(it->first);
        }
    }
    return ToSaveId;
}

int ManageCars::GetSizeCarros(string tipo) {

    if (tipo == "marca") {
        return Marcas_Disponiveis.size();
    }
    else {
        return Models_Disponiveis.size();
    }
}

vector<int> ManageCars::IDModels_ToBuy(string model) {

    //função retorna todos os modelos disponiveis independemente se está asssociado á marca
    vector<int>  IDModels_ToBuy;


    //percorre todo o multimap para procurar os ids que têm o modelos correspondente
    for (std::multimap<int, ManageCars>::iterator it = CarsRead.begin(); it != CarsRead.end(); it++) {
        string check = it->second.Model;
        if (model == check) {
            IDModels_ToBuy.push_back(it->first);

        }
        else {

        }
    }

    return IDModels_ToBuy;


}

void ManageCars::DeleteOnDataBase(int index,string marca) {
    ifstream fileBD;

    //open file in read mode
    fileBD.open(intialpath, ios::in);
    string vazio = " ", line;
    vector<string> vecline;
    string str_Admin, str_Marca, str_Model, str_ano, str_km, str_Price, str_Image, Image;
    int ano, km, Price;
    int indexToDelete = 0;
    int aux = 0;
    if (fileBD.is_open()) {
        for (int i = 0; fileBD.eof() == 0; i++) {
            getline(fileBD, line);



            stringstream(line) >> str_Admin >> str_Marca >> vazio >> str_Model >> vazio >> str_ano >> vazio >> str_km >> vazio >> str_Price >> vazio >> str_Image;
            vecline.push_back(line);
            stringstream(str_ano) >> ano;
            stringstream(str_km) >> km;
            stringstream(str_Price) >> Price;
            stringstream(str_Image) >> Image;

            aux++;
            if (str_Marca == marca) {

                if (aux == index + 1) {
                    indexToDelete = i;
                }
            }

        }
        //Reescrever ficheiro , sem a linha do carro que foi comprado
        vecline.erase(vecline.begin() + (indexToDelete));
        //
        fstream fileBD_Clear;
        fileBD_Clear.open(intialpath, ios::trunc | ios::out);
        fileBD_Clear.close();
        fstream fileBD_Out;
        fileBD_Out.open(intialpath, ios::app);

        int lastline = CarsRead.size();
        int i = 0;
        for (auto range : vecline) {
            i++;
            fileBD_Out << range;

            if (i != lastline - 1) {
                fileBD_Out << "\n";
            }
        }
    }
}

string ManageCars::GetImagePath(int key)
{
    //percorre todo o multimap para enviar o path do carro correspondente
    for (multimap<int, ManageCars>::iterator it = CarsRead.begin(); it != CarsRead.end(); it++) {

        if (key == it->first) {

            return it->second.imagepath;
        }
    }

}

int ManageCars::GetAno(int id)
{
    auto it = CarsRead.find(id);
    
    return it->second.ano;
}

int ManageCars::GetKm(int id)
{
    auto it = CarsRead.find(id);

    return it->second.km;
}

double ManageCars::GetPrice(int id)
{
    auto it = CarsRead.find(id);

    return it->second.Price;
}

string ManageCars::GetMarca(int id)
{
    auto it = CarsRead.find(id);

    return it->second.Marca;
}
string ManageCars::GetModel(int id)
{
    auto it = CarsRead.find(id);

    return it->second.Model;
}

string ManageCars::GetAdmin(int id)
{
    auto it = CarsRead.find(id);

    return it->second.Admin;
}

vector<string> ManageCars::ModelFromBrands(string marca)
{


    auto it = CarsRead.begin();
    vector<string> models;

    for (int i = 0; i < CarsRead.size(); i++){

        if ( it->second.Marca == marca)
        {
            models.push_back(it->second.Model);
        }
        it++;
    }
    return models;
}

multimap<int, ManageCars> ManageCars::CompleteTheShoppingCart(int index, string model)
{
    ifstream fileBD;

    //open file in read mode
    fileBD.open(intialpath, ios::in);

    //Create Variables
    string line;
    string std_Admin, str_Marca, str_Model, str_ano, str_km, str_Price, str_ImagePath;
    int indexToDelete = 0;
    int aux = 0;
    if (fileBD.is_open()) {

        for (int i = 0; fileBD.eof() == 0; i++) {
            getline(fileBD, line);
            stringstream(line) >> std_Admin >> str_Marca >> str_Model >> str_ano >> str_km >> str_Price >> str_ImagePath;
            stringstream(str_ano) >> ano;
            stringstream(str_km) >> km;
            stringstream(str_Price) >> Price;
            stringstream(str_ImagePath) >> imagepath;
            stringstream(std_Admin) >> Admin;
            Marca = str_Marca;
            //stringstream(str_Model) >> Model;
            Model = str_Model;

            if (str_Model == model) {
                aux++;
                if (aux == index) {
                    ShoppingCart.insert(make_pair(i, ManageCars(Admin, Marca, Model, ano, km, Price, imagepath)));
                }
            }
        }

    }

    return ShoppingCart;
}



