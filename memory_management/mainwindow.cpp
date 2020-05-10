#include "mainwindow.h"
#include "alg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    /******************** Creating Testcase ***************************/
    Segments* Temp_Segment= new Segments;
    Segments* Temp_Segment1= new Segments;
    Temp_Segment->size=700;
    Temp_Segment1->size=400;
    Temp_Segment1->segmentName="p1";
    segmQueue.append(Temp_Segment);
    segmQueue.append(Temp_Segment1);
    Holes* Temp_Hole = new Holes;
    Temp_Hole->startingAddress = 0;
    Temp_Hole->size = 500;
    holeQueue.append(Temp_Hole);
    Holes* Temp_Hole1 = new Holes;
    Temp_Hole1->startingAddress = 2400;
    Temp_Hole1->size = 1000;
    holeQueue.append(Temp_Hole1);
    Holes* Temp_Hole2 = new Holes;
    Temp_Hole2->startingAddress = 5700;
    Temp_Hole2->size = 1400;
    holeQueue.append(Temp_Hole2);


    /**************GUI Design*******************/
    Horizontal_layout = new QHBoxLayout();

    sideButtonsScene = new QGraphicsScene();
    sideButtonsView = new QGraphicsView(sideButtonsScene);
    sideButtonsScene->setBackgroundBrush(QColor(3,90,166));
    sideButtonsView->setMinimumWidth(30);
    sideButtonsView->setMaximumWidth(70);
    sideButtonsView->setMinimumHeight(600);
    sideButtonsView->setAlignment(Qt::AlignTop);

    /*****************************Adding buttons to sideButtonsView******************************/

    addHoles = new QToolButton();
    addHoles->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    addHoles->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addHoles->setGeometry(0,15,75,80);
    addHoles->setIcon(QIcon("C:/Users/Dina/Desktop/hole.png"));
    addHoles->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    addHoles->setText("Holes");
    sideButtonsScene->addWidget(addHoles);

    connect(addHoles,SIGNAL(clicked()),this,SLOT(lineEdits())) ;




    processButton = new QToolButton();
    processButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    processButton->setGeometry(0,100,75,75);
    processButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    processIcon.addPixmap(QPixmap("C:/Users/Dina/Desktop/planning.png"), QIcon::Normal);
    //processIcon.addPixmap(QPixmap("C:/Users/Dina/Desktop/process-disabled.png"), QIcon::Disabled);
    processButton->setIcon(processIcon);
    processButton->setIconSize(QSize(50,50));
    processButton->setText("Process");
    processButton->setEnabled(false);
    sideButtonsScene->addWidget(processButton);
    connect(processButton,SIGNAL(clicked()),this,SLOT(segmentsLayout())) ;







    drawButton = new QToolButton();
    drawButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    drawButton->setGeometry(0,190,75,75);
    drawButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    drawButton->setIcon(QIcon("C:/Users/Dina/Desktop/right.png"));
    drawButton->setIconSize(QSize(50,50));
    drawButton->setText("Draw");
    sideButtonsScene->addWidget(drawButton);
    connect(drawButton,SIGNAL(clicked()),this,SLOT(drawProcess())) ;

    tableButton = new QToolButton();
    tableButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    tableButton->setGeometry(0,275,75,75);
    tableButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tableButton->setIcon(QIcon("C:/Users/Dina/Desktop/edit-table.png"));
    tableButton->setIconSize(QSize(50,50));
    tableButton->setText("Table");
    sideButtonsScene->addWidget(tableButton);
    connect(tableButton,SIGNAL(clicked()),this,SLOT(show_seg_table())) ;

    restartButton = new QToolButton();
    restartButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    restartButton->setGeometry(0,350,75,75);
    restartButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    restartButton->setIcon(QIcon("C:/Users/Dina/Desktop/updated2.png"));
    restartButton->setIconSize(QSize(50,50));
    restartButton->setText("Restart");
    sideButtonsScene->addWidget(restartButton);


    /***********************************************************************/

    sideOptionsScene = new QGraphicsScene();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);



    segmentTableScene = new QGraphicsScene();
    segmentTableView = new QGraphicsView(segmentTableScene);
    segmentTableScene->setBackgroundBrush(Qt::white);
    segmentTableView->setMinimumWidth(150);


    memDrawingScene = new QGraphicsScene();
    memDrawingView = new QGraphicsView(memDrawingScene);
    memDrawingScene->setBackgroundBrush(Qt::white);
    memDrawingView->setMinimumWidth(250);


    Horizontal_layout->addWidget(sideButtonsView);
    Horizontal_layout->addWidget(sideOptionsView);
    Horizontal_layout->addWidget(segmentTableView);
    Horizontal_layout->addWidget(memDrawingView);


    placeholder= new  QWidget();
    placeholder->setLayout(Horizontal_layout);
    //placeholder->setStyleSheet("QWidget{background-color : #035aa6;}");
    this->setCentralWidget(placeholder);


}


MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::lineEdits()
{
    memorySizeLabel= new QLabel ();
    memorySizeLabel->setText("Memory Size");
    memorySizeLabel->setStyleSheet("background-color :#035aa6; color:black;font-size: 15px; font-family: Arial;");
    memorySizeLabel->setGeometry(50,10,90,30);
    sideOptionsScene->addWidget(memorySizeLabel);

    memorySize= new   QLineEdit();
    memorySize->setGeometry(30,50,120,30);
    memorySize->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(memorySize);


    noHolesLabel = new QLabel ();
    noHolesLabel->setText("Number of Holes");
    noHolesLabel->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    noHolesLabel->setGeometry(35,100, 110, 30);
    sideOptionsScene->addWidget(noHolesLabel);

    noHoles = new   QLineEdit();
    noHoles->setGeometry(30,140,120,30);
    noHoles->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(noHoles);



    addHolesNo = new QToolButton();
    addHolesNo->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    //addHolesNo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addHolesNo->setGeometry(50,180,75,80);
    addHolesNo->setIcon(QIcon("C:/Users/Dina/Desktop/add.png"));
    addHolesNo->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    //addHolesNo->setText("Holes");
    sideOptionsScene->addWidget(addHolesNo);
    connect(addHolesNo,SIGNAL(clicked()),this,SLOT(memSizeAndAdd())) ;

}

void MainWindow::memSizeAndAdd()
{
    memSize= memorySize->text();
    holes_num = noHoles->text();
    qDebug()<<"hey1: "<<holes_num;
    hSizeLabel = new QLabel("Hole Size");
    hAddressLabel = new QLabel("Starting Address");

    hSizeLabel ->setGeometry(5,245,65,30);
    hAddressLabel->setGeometry(90,245,120,30);

    hSizeLabel ->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");
    hAddressLabel->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");

    sideOptionsScene->addWidget(hSizeLabel);
    sideOptionsScene->addWidget(hAddressLabel);



    int height=245;
    qDebug()<<"hey2: "<<holes_num;
    for (int i = 0; i<holes_num.split(" ")[0].toInt(); i++)
    {
        hSize = new QLineEdit();
        hAddress = new QLineEdit();

        qDebug()<<hAddress;

        Holes *h = new Holes;

        hSize->setGeometry(0,50+height,80,30);
        hAddress->setGeometry(100,50+height,80,30);

        h->startingAddress=(hAddress->text()).split(" ")[0].toInt();
        h->size=(hSize->text()).split(" ")[0].toInt();

        sideOptionsScene->addWidget(hSize);
        sideOptionsScene->addWidget(hAddress);

        height+=50;
        holesQueue.append(h);
    }

    drawMyHoles = new QToolButton();
    drawMyHoles->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    drawMyHoles->setGeometry(50,height+50,75,80);
    drawMyHoles->setIcon(QIcon("C:/Users/Dina/Desktop/check.png"));
    drawMyHoles->setIconSize(QSize(50,50));
    sideOptionsScene->addWidget(drawMyHoles);
    connect(drawMyHoles,SIGNAL(clicked()),this,SLOT(drawHoles())) ;
}

void MainWindow::drawHoles()
{

    processButton->setEnabled(true);
}

void MainWindow::segmentsLayout()
{
    sideOptionsScene->clear();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);



}

void MainWindow::drawProcess(){

    Best_fit(segmQueue,large_segments,holeQueue);

    for(int i=0; i<large_segments.size();i++){
        qDebug()<<large_segments[i]->startingAddress<<endl;
    }

    /*insert memory drawing here*/
}

void MainWindow::show_seg_table(){
    get_segment_table(table,large_segments,"p1");

    int height=0;
    for(int i=0;i<table.size();i++){
        QLabel *address1 = new QLabel;
        QLabel *size1 = new QLabel;
        address1->setText(tr(" %1").arg(table[i]->startingAddress));
        size1->setText(tr(" %1").arg(table[i]->size));
        address1->setGeometry(300,100+height,100,100);
        size1->setGeometry(500,100+height,100,100);
        this->layout()->addWidget(address1);
        this->layout()->addWidget(size1);
        height+=70;
    }

}
