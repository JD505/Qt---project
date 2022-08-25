#include "carsavailable.h"
#include "ui_carsavailable.h"

CarsAvailable::CarsAvailable(QWidget *parent) :
    QDialog(parent),
    uiCars(new Ui::CarsAvailable)
{   
    //set page icon
    setWindowIcon(QIcon(":/R/Resources/icon.png"));
    
    uiCars->setupUi(this);
    CarsAvailable::ModelToDisplay();
}

CarsAvailable::~CarsAvailable()
{
    delete uiCars;
}

//vector <string> CarsAvailable::ImagePath;
//int CarsAvailable::Num_ModelsAvalibles;


void CarsAvailable::ModelToDisplay(){
    AdminWindow *obj = new AdminWindow;
    string model = obj->ModelonList();
    string marca  = obj->MarcaOnList();
    CarsAvailable::GetNumberOfModel(model); // Reiniciar  IdByModels 
    ManageCars* cars = new ManageCars;
    Cars = cars->CarsRead;
    int i;

    if (marca== "Mercedes"){
                 //Ir buscar o multimap ao ficheiro managecars

                

                //percorre todo o multimap para procurar os Paths das imagens em compara��o com o Ids com o modelo que se carregou
              for (multimap<int, ManageCars>::iterator it = Cars.begin(); it != Cars.end(); it++) {
                 
                 if (cars->GetMarca(it->first) == marca){
                    int KeyComparation = it->first;
             
                    if (std::find(IdByModels.begin(), IdByModels.end(), KeyComparation) != IdByModels.end()) {
                        
                        ImagePath.push_back(cars->GetImagePath(KeyComparation));
                    }
                    }
                 else {

                    }
               }

              Num_ModelsAvalibles = ImagePath.size();
              CreateFrames(ImagePath, Num_ModelsAvalibles,marca);

    }
    else if (marca == "BMW") {
        //Ir buscar o multimap ao ficheiro managecars



       //percorre todo o multimap para procurar os Paths das imagens em compara��o com o Ids com o modelo que se carregou
        for (multimap<int, ManageCars>::iterator it = Cars.begin(); it != Cars.end(); it++) {

            if (cars->GetMarca(it->first) == marca) {
                int KeyComparation = it->first;

                if (std::find(IdByModels.begin(), IdByModels.end(), KeyComparation) != IdByModels.end()) {

                    ImagePath.push_back(cars->GetImagePath(KeyComparation));
                }
            }
            else {

            }
        }

        Num_ModelsAvalibles = ImagePath.size();
        CreateFrames(ImagePath, Num_ModelsAvalibles, marca);

    }
    else if (marca == "Audi") {
        //Ir buscar o multimap ao ficheiro managecars



       //percorre todo o multimap para procurar os Paths das imagens em compara��o com o Ids com o modelo que se carregou
        for (multimap<int, ManageCars>::iterator it = Cars.begin(); it != Cars.end(); it++) {

            if (cars->GetMarca(it->first) == marca) {
                int KeyComparation = it->first;

                if (std::find(IdByModels.begin(), IdByModels.end(), KeyComparation) != IdByModels.end()) {

                    ImagePath.push_back(cars->GetImagePath(KeyComparation));
                }
            }
            else {

            }
        }

        Num_ModelsAvalibles = ImagePath.size();
        CreateFrames(ImagePath, Num_ModelsAvalibles, marca);

    }
    else if (marca == "Kia") {
        //Ir buscar o multimap ao ficheiro managecars



       //percorre todo o multimap para procurar os Paths das imagens em compara��o com o Ids com o modelo que se carregou
        for (multimap<int, ManageCars>::iterator it = Cars.begin(); it != Cars.end(); it++) {

            if (cars->GetMarca(it->first) == marca) {
                int KeyComparation = it->first;

                if (std::find(IdByModels.begin(), IdByModels.end(), KeyComparation) != IdByModels.end()) {

                    ImagePath.push_back(cars->GetImagePath(KeyComparation));
                }
            }
            else {

            }
        }

        Num_ModelsAvalibles = ImagePath.size();
        CreateFrames(ImagePath, Num_ModelsAvalibles,marca);

    }
    else {}
    delete cars;
    delete obj;
}

int CarsAvailable::GetNumberOfModel(string model)
{


    //Criar objeto para ir ao ficheiro do manage criar novamente o Multimap pelo ficheiro
    ManageCars * cars = new ManageCars;
    cars->AddFilesToList();
    IdByModels = cars->IDModels_ToBuy(model);
    delete cars;
    return IdByModels.size(); // Envia para a outra func quantos carros disponiveis daquele modelo
}

int CarsAvailable::GetImagePath(int key){

    return 0;
}

void CarsAvailable::CreateFrames(vector <string> ImagePath, int NumberToShow,string marca){

    int divider;


        for (int i = 0; i < NumberToShow; i++) {
            ManageCars cartoshow;

            int ano = cartoshow.GetAno(IdByModels[i]);
            QString AnoQs = QString::number(ano);

            QString Image = QDir::currentPath() + QString::fromStdString(ImagePath[i]);
            QPixmap pix(Image);
            string SellerToshow = cartoshow.GetAdmin(IdByModels[i]);
            QString SellerToshowQs = QString::fromStdString(SellerToshow);
            

            verticalLayout = new QVBoxLayout();
            verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
            label_image = new QLabel(uiCars->horizontalLayoutWidget);
            label_image->setObjectName(QString::fromUtf8("label"));
            QRect geometry = uiCars->horizontalLayoutWidget->geometry();
            int width = geometry.width();
            int height = geometry.height();
            QSize VerticalParameter = verticalLayout->maximumSize();
            int y = (VerticalParameter.width() / 20) / 100 ;
            //Determinar quanto temos de dar em resize
            switch (NumberToShow)
            {
            case 1:
                divider = 1;
                break;
            case 2:
                divider = 1.5;
                break;
            case 3:
                divider = 2.05;
                break;
            case 4:
                divider = 2.20;
                break;
            case 5:
                divider = 2.75;
                break;
            case 6:
                divider =3.25;
                break;
            case 7:
                divider = 3.75;
                break;
            default:
                divider = 3.25;
                break;
            }
            int x = (height/ divider);
            label_image->setPixmap(pix.scaled(x, y, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));   
            verticalLayout->addWidget(label_image,  0,  Qt::AlignCenter);
           
            // seller label layout
            Sellerlabel = new QLabel(uiCars->horizontalLayoutWidget);     
            Sellerlabel->setObjectName(QString::fromUtf8("Sellerlabel"));
            Sellerlabel->setLayoutDirection(Qt::RightToLeft);
            Sellerlabel->setAutoFillBackground(true);                             
            Sellerlabel->setToolTip("Seller");                        
            Sellerlabel->setText(SellerToshowQs);
            Sellerlabel->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            verticalLayout->addWidget(Sellerlabel, 0, Qt::AlignCenter);

            // vertical spacer layout
            verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
            verticalLayout->addItem(verticalSpacer);
            verticalLayout_3 = new QVBoxLayout();
            verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
            
            // year label layout
            label_3 = new QLabel(uiCars->horizontalLayoutWidget);
            label_3->setObjectName(QString::fromUtf8("label_3"));
           // label_3->setLayoutDirection(Qt::RightToLeft);           
            label_3->setText("Year");                                            
            label_3->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");           
            label_3->setFixedSize(QSize(80, 20));
            horizontalLayout_3->addWidget(label_3, 0, Qt::AlignRight);

            
            // year layout - data
            label_2 = new QLabel(uiCars->horizontalLayoutWidget);
            label_2->setObjectName(QString::fromUtf8("label_2"));         
            label_2->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            label_2->setText(AnoQs);
            label_2->setFixedSize(QSize(80, 20));
            horizontalLayout_3->addWidget(label_2, 0, Qt::AlignLeft);

            verticalLayout_3->addLayout(horizontalLayout_3);

            horizontalLayout_5 = new QHBoxLayout();
            horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
            
            // kilometers label layout
            label_5 = new QLabel(uiCars->horizontalLayoutWidget);
            label_5->setObjectName(QString::fromUtf8("label_5"));                     
            label_5->setText("kilometers");
            label_5->setFixedSize(QSize(80, 20));
            label_5->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            horizontalLayout_5->addWidget(label_5, 0, Qt::AlignRight);

            int km = cartoshow.GetKm(IdByModels[i]);
            QString kmQs = QString::number(km);
            
            // kilometers layout - data
            label_4 = new QLabel(uiCars->horizontalLayoutWidget);
            label_4->setObjectName(QString::fromUtf8("label_4"));       
            label_4->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            label_4->setText(kmQs);
            label_4->setFixedSize(QSize(80, 20));
            horizontalLayout_5->addWidget(label_4, 0, Qt::AlignLeft);

            verticalLayout_3->addLayout(horizontalLayout_5);

            horizontalLayout_4 = new QHBoxLayout();
            horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

            // Price label layout
            label_7 = new QLabel(uiCars->horizontalLayoutWidget);
            label_7->setObjectName(QString::fromUtf8("label_7"));                       
            string pricelabel = "Price";
            QString qpricelabel = QString::fromUtf8(pricelabel.c_str()); //para dar com caracteres especiais       
            label_7->setText(qpricelabel);
            label_7->setFixedSize(QSize(80, 20));
            label_7->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            horizontalLayout_4->addWidget(label_7, 0, Qt::AlignRight);

            double price = cartoshow.GetPrice(IdByModels[i]);
            QString priceQs = QString::number(price);
         
            // price layout - data
            label_6 = new QLabel(uiCars->horizontalLayoutWidget);
            label_6->setObjectName(QString::fromUtf8("label_6"));         ;                   
            label_6->setStyleSheet("QLabel {border-style:outset; border-width: 1px; border-radius: 4px; border-color: white;}");
            label_6->setFixedSize(QSize(80, 20));
            label_6->setText(priceQs);
            horizontalLayout_4->addWidget(label_6, 0, Qt::AlignLeft);


            verticalLayout_3->addLayout(horizontalLayout_4);
            verticalLayout->addLayout(verticalLayout_3);
            uiCars->horizontalLayout->addLayout(verticalLayout);

            verticalLayout_2 = new QVBoxLayout();
            verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

            uiCars->horizontalLayout->addLayout(verticalLayout_2);

            horizontalLayout_7 = new QHBoxLayout();
            horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
            horizontalSpacer_3 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);

            horizontalLayout_7->addItem(horizontalSpacer_3);

            horizontalLayout_8 = new QHBoxLayout();
            horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
            Button = new QPushButton(uiCars->horizontalLayoutWidget);
            string StdButtonNum = to_string(i);
            string stdButtonNum_ = "Button_" + StdButtonNum;
            QString ButtonNumber = QString::fromStdString(stdButtonNum_);
            Button->setObjectName(ButtonNumber);
            Button->setMaximumSize(QSize(90, 50));
            Button->setToolTip("Click to buy this car");
            Button->setText("Add to Cart");

            horizontalLayout_8->addWidget(Button);
            verticalLayout->addLayout(horizontalLayout_8);

            horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
            horizontalLayout_7->addItem(horizontalSpacer_4);
            verticalLayout->addLayout(horizontalLayout_7);
            uiCars->horizontalLayout->addLayout(verticalLayout);

            QObject::connect(Button, &QPushButton::clicked, this, &CarsAvailable::SendADDShoppingChart);
        }
    }

void CarsAvailable::SendADDShoppingChart()
    
{

        AdminWindow* obj = new AdminWindow;
        string marca = obj->MarcaOnList();

        ManageCars* carsToDelete = new ManageCars;;


        QObject* metaObj = sender();
        QString nameObj = metaObj->objectName();
        string stdnameObj = nameObj.toStdString();

        string number = stdnameObj.substr(7, stdnameObj.find('_'));// parse para o nr do botao
        int index = stoi(number) + 1;


        carsToDelete->AddFilesToList();

        string model = obj->ModelonList();
        IdByModels = carsToDelete->IDModels_ToBuy(model);
        carsToDelete->CompleteTheShoppingCart(index, model);
        //carsToDelete->DeleteOnDataBase(IdByModels[index - 1], marca);
         //função que elimina do txt e depois vai dar refresh no multimap

        delete carsToDelete;
        delete obj;

        BackDialog();
}
 
void CarsAvailable::on_Goback_clicked()
{
        ManageCars* c = new ManageCars{ true };
        CarsAvailable::close();
        AdminWindow* admin = new AdminWindow;
        ConfirmAdmin* confirm = new ConfirmAdmin;

        admin->confirm(admin->isAClient, confirm->userConf);
        admin->exec();

        delete admin;
        delete confirm;
        delete c;
}

void CarsAvailable::RemoveCar()
{
    AdminWindow* obj = new AdminWindow;
    string marca = obj->MarcaOnList();
    delete obj;
    QObject* metaObj = sender();
    QString nameObj = metaObj->objectName();
    string stdnameObj = nameObj.toStdString();

    string number = stdnameObj.substr(7, stdnameObj.find('_'));// parse para o nr do botao
    int index = stoi(number) + 1;

    DeleteCars(index, marca);

    BackDialog();


}


