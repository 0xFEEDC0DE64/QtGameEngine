#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QAction>
#include <QScrollBar>
#include <QTime>
#include <QModelIndex>
#include <QMetaProperty>
#include <QItemEditorFactory>
#include <QLabel>
#include <QPropertyAnimation>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DInput/QInputAspect>
#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>

#include "houseplant.h"
#include "treemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_view()
{
    ui->setupUi(this);

    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionQuit->setShortcut(QKeySequence::Quit);

    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionCut->setShortcut(QKeySequence::Cut);
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionPaste->setShortcut(QKeySequence::Paste);

    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::start);
    connect(ui->actionPause, &QAction::triggered, this, &MainWindow::pause);
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::stop);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QWidget::customContextMenuRequested, this, &MainWindow::customContextMenuRequested);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::returnPressed);

    m_view.defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    ui->centralWidget->layout()->addWidget(QWidget::createWindowContainer(&m_view, ui->centralWidget));

    auto sceneRoot = new Qt3DCore::QEntity();
    sceneRoot->setObjectName("sceneRoot");

    {
        auto basicCamera = m_view.camera();
        basicCamera->setObjectName("basicCamera");
        basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
        basicCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
        basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
        basicCamera->setPosition(QVector3D(0.0f, 3.5f, 25.0f));

        {
            auto camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
            camController->setObjectName("camController");
            camController->setCamera(basicCamera);
        }
    }

    {
        auto planeEntity = new Qt3DCore::QEntity(sceneRoot);
        planeEntity->setObjectName("planeEntity");

        {
            auto mesh = new Qt3DExtras::QPlaneMesh;
            mesh->setObjectName("mesh");
            mesh->setHeight(100.0f);
            mesh->setWidth(100.0f);
            mesh->setMeshResolution(QSize(20, 20));
            planeEntity->addComponent(mesh);
        }

        {
            auto transform = new Qt3DCore::QTransform();
            transform->setObjectName("transform");
            planeEntity->addComponent(transform);
        }

        {
            auto normalDiffuseSpecularMapMaterial = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial();
            normalDiffuseSpecularMapMaterial->setObjectName("normalDiffuseSpecularMapMaterial");
            normalDiffuseSpecularMapMaterial->setTextureScale(10.0f);
            normalDiffuseSpecularMapMaterial->setShininess(80.0f);
            normalDiffuseSpecularMapMaterial->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));

            {
                auto diffuseImage = new Qt3DRender::QTextureImage();
                diffuseImage->setObjectName("diffuseImage");
                diffuseImage->setSource(QUrl(QStringLiteral("qrc:/assets/textures/pattern_09/diffuse.webp")));
                normalDiffuseSpecularMapMaterial->diffuse()->addTextureImage(diffuseImage);
            }

            {
                auto specularImage = new Qt3DRender::QTextureImage();
                specularImage->setObjectName("specularImage");
                specularImage->setSource(QUrl(QStringLiteral("qrc:/assets/textures/pattern_09/specular.webp")));
                normalDiffuseSpecularMapMaterial->specular()->addTextureImage(specularImage);
            }

            {
                auto normalImage = new Qt3DRender::QTextureImage();
                normalImage->setObjectName("normalImage");
                normalImage->setSource(QUrl((QStringLiteral("qrc:/assets/textures/pattern_09/normal.webp"))));
                normalDiffuseSpecularMapMaterial->normal()->addTextureImage(normalImage);
            }

            planeEntity->addComponent(normalDiffuseSpecularMapMaterial);
        }
    }

    {
        auto chest = new Qt3DCore::QEntity(sceneRoot);
        chest->setObjectName("chest");

        {
            auto mesh = new Qt3DRender::QMesh();
            mesh->setObjectName("mesh");
            mesh->setSource(QUrl(QStringLiteral("qrc:/assets/chest/Chest.obj")));
            chest->addComponent(mesh);
        }

        {
            auto transform = new Qt3DCore::QTransform();
            transform->setObjectName("transform");
            transform->setScale(0.03f);
            chest->addComponent(transform);
        }

        {
            auto diffuseMapMaterial = new Qt3DExtras::QDiffuseMapMaterial();
            diffuseMapMaterial->setObjectName("diffuseMapMaterial");
            diffuseMapMaterial->setSpecular(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));
            diffuseMapMaterial->setShininess(2.0f);

            {
                auto chestDiffuseImage = new Qt3DRender::QTextureImage();
                chestDiffuseImage->setObjectName("chestDiffuseImage");
                chestDiffuseImage->setSource(QUrl(QStringLiteral("qrc:/assets/chest/diffuse.webp")));
                diffuseMapMaterial->diffuse()->addTextureImage(chestDiffuseImage);
            }

            chest->addComponent(diffuseMapMaterial);
        }
    }

    {
        auto trefoil = new Qt3DCore::QEntity(sceneRoot);
        trefoil->setObjectName("trefoil");

        {
            auto mesh = new Qt3DRender::QMesh();
            mesh->setSource(QUrl("qrc:/assets/obj/trefoil.obj"));
            trefoil->addComponent(mesh);
        }

        {
            auto transform = new Qt3DCore::QTransform();
            transform->setTranslation(QVector3D(0.0f, 3.5f, 0.0f));
            transform->setScale(0.5f);

            {
                auto animation = new QPropertyAnimation(transform);
                animation->setObjectName("animation");
                animation->setDuration(2000);
                animation->setStartValue(0.0f);
                animation->setEndValue(360.0f);
                animation->setLoopCount(-1);
                animation->setTargetObject(transform);
                animation->setPropertyName("rotationY");
                m_animations << animation;
            }

            trefoil->addComponent(transform);
        }

        {
            auto phongMaterial = new Qt3DExtras::QPhongMaterial();
            phongMaterial->setObjectName("phongMaterial");
            phongMaterial->setDiffuse(QColor(204, 205, 75)); // Safari Yellow #cccd4b
            phongMaterial->setSpecular(Qt::white);
            trefoil->addComponent(phongMaterial);
        }
    }

    auto createBarrel = [=](const QString &name, const QVector3D &translation, float shininess, const QString &meshPath, const QString &diffuseTexturePath, const QString &normaleTexturePath, const QString &specularTexturePath){
        auto barrel = new Qt3DCore::QEntity(sceneRoot);
        barrel->setObjectName(name);

        {
            auto mesh = new Qt3DRender::QMesh();
            mesh->setObjectName("mesh");
            mesh->setSource(QUrl(meshPath));
            barrel->addComponent(mesh);
        }

        {
            auto transform = new Qt3DCore::QTransform();
            transform->setObjectName("transform");
            transform->setScale(0.03f);
            transform->setTranslation(translation);
            barrel->addComponent(transform);
        }

        {
            auto material = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial();
            material->setObjectName("material");
            material->setShininess(shininess);

            material->diffuse()->setObjectName("diffuseTexture");

            {
                auto diffuseTextureImage = new Qt3DRender::QTextureImage();
                diffuseTextureImage->setObjectName("diffuseTextureImage");
                diffuseTextureImage->setSource(QUrl(diffuseTexturePath));

                material->diffuse()->addTextureImage(diffuseTextureImage);
            }

            material->normal()->setObjectName("normalTexture");

            {
                auto normalTextureImage = new Qt3DRender::QTextureImage();
                normalTextureImage->setObjectName("normalTextureImage");
                normalTextureImage->setSource(QUrl(normaleTexturePath));

                material->normal()->addTextureImage(normalTextureImage);
            }

            material->specular()->setObjectName("specularTexture");

            {
                auto specularTextureImage = new Qt3DRender::QTextureImage();
                specularTextureImage->setObjectName("specularTextureImage");
                specularTextureImage->setSource(QUrl(specularTexturePath));

                material->specular()->addTextureImage(specularTextureImage);
            }

            barrel->addComponent(material);
        }
    };

    createBarrel("basicBarrel", QVector3D(8.0f, 0.0f, 0.0f), 10.0f,
                 QStringLiteral("qrc:/assets/metalbarrel/metal_barrel.obj"),
                 QStringLiteral("qrc:/assets/metalbarrel/diffus_red.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/normal_no_bumps.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/specular.webp"));

    createBarrel("rustyBarrel", QVector3D(10.0f, 0.0f, 0.0f), 10.0f,
                 QStringLiteral("qrc:/assets/metalbarrel/metal_barrel.obj"),
                 QStringLiteral("qrc:/assets/metalbarrel/diffus_rust.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/normal_hard_bumps.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/specular_rust.webp"));

    createBarrel("blueBarrel", QVector3D(12.0f, 0.0f, 0.0f), 10.0f,
                 QStringLiteral("qrc:/assets/metalbarrel/metal_barrel.obj"),
                 QStringLiteral("qrc:/assets/metalbarrel/diffus_blue.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/normal_middle_bumps.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/specular_rust.webp"));

    createBarrel("greenBarrel", QVector3D(14.0f, 0.0f, 0.0f), 10.0f,
                 QStringLiteral("qrc:/assets/metalbarrel/metal_barrel.obj"),
                 QStringLiteral("qrc:/assets/metalbarrel/diffus_green.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/normal_soft_bumps.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/specular_rust.webp"));

    createBarrel("stainlessBarrel", QVector3D(16.0f, 0.0f, 0.0f), 150.0f,
                 QStringLiteral("qrc:/assets/metalbarrel/metal_barrel.obj"),
                 QStringLiteral("qrc:/assets/metalbarrel/diffus_stainless_steel.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/normal_no_bumps.webp"),
                 QStringLiteral("qrc:/assets/metalbarrel/specular_stainless_steel.webp"));

    {
        auto squareBamboo = new HousePlant(sceneRoot);
        squareBamboo->setObjectName("squareBamboo");
        squareBamboo->setPotShape(HousePlant::Square);
        squareBamboo->setPosition(QVector3D(4.0f, 0.0f, 0.0f));
    }

    {
        auto trianglePalm = new HousePlant(sceneRoot);
        trianglePalm->setObjectName("trianglePalm");
        trianglePalm->setPlantType(HousePlant::Palm);
        trianglePalm->setPotShape(HousePlant::Triangle);
        trianglePalm->setPosition(QVector3D(0.0f, 0.0f, 4.0f));
    }

    {
        auto spherePine = new HousePlant(sceneRoot);
        spherePine->setObjectName("spherePine");
        spherePine->setPlantType(HousePlant::Pine);
        spherePine->setPotShape(HousePlant::Sphere);
        spherePine->setPosition(QVector3D(-4.0f, 0.0f, 0.0f));
    }

    {
        auto crossSpikes = new HousePlant(sceneRoot);
        crossSpikes->setObjectName("crossSpikes");
        crossSpikes->setPlantType(HousePlant::Spikes);
        crossSpikes->setPosition(QVector3D(0.0f, 0.0f, -4.0f));
    }

    {
        auto crossPalm = new HousePlant(sceneRoot);
        crossPalm->setObjectName("crossPalm");
        crossPalm->setPlantType(HousePlant::Palm);
        crossPalm->setPosition(QVector3D(0.0f, 0.0f, -8.0f));
        crossPalm->setScale(0.05f);
    }

    {
        auto crossShrub = new HousePlant(sceneRoot);
        crossShrub->setObjectName("crossShrub");
        crossShrub->setPlantType(HousePlant::Shrub);
        crossShrub->setPosition(QVector3D(0.0f, 0.0f, 8.0f));
        crossShrub->setScale(0.05f);
    }

    {
        auto airplane = new Qt3DCore::QEntity(sceneRoot);
        airplane->setObjectName("airplane");

        {
            auto mesh = new Qt3DRender::QMesh();
            mesh->setObjectName("mesh");
            mesh->setSource(QUrl(QStringLiteral("qrc:/assets/obj/toyplane.obj")));
            airplane->addComponent(mesh);
        }

        {
            auto transform = new Qt3DCore::QTransform();
            transform->setObjectName("transform");
            transform->setTranslation(QVector3D(0.0f, 5.0f, -20.0f));
            transform->setScale(0.1f);
            airplane->addComponent(transform);

            {
                auto animation = new QPropertyAnimation(transform);
                animation->setObjectName("animation");
                animation->setDuration(3000);
                animation->setStartValue(0.0f);
                animation->setEndValue(360.0f);
                animation->setLoopCount(-1);
                animation->setTargetObject(transform);
                animation->setPropertyName("rotationX");
                m_animations << animation;
            }
        }

        {
            auto phongMaterial = new Qt3DExtras::QPhongMaterial();
            phongMaterial->setObjectName("phongMaterial");
            phongMaterial->setDiffuse(QColor(150, 150, 150));
            phongMaterial->setSpecular(Qt::white);
            airplane->addComponent(phongMaterial);
        }
    }

    m_view.setRootEntity(sceneRoot);

    ui->treeView->setModel(new TreeModel(sceneRoot));
    ui->treeView->expandAll();
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::currentRowChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::customContextMenuRequested(const QPoint &pos)
{
    auto index = ui->treeView->indexAt(pos);
    if(!index.isValid())
        return;

    auto entity = static_cast<Qt3DCore::QEntity *>(index.internalPointer());

    QMenu menu;
    auto switchEnabled = menu.addAction(entity->isEnabled() ? tr("Disable") : tr("Enable"));
    auto selectedAction = menu.exec(ui->treeView->mapToGlobal(pos));

    if(selectedAction == switchEnabled)
        entity->setEnabled(!entity->isEnabled());
}

void MainWindow::currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << "currentRowChanged";

    if(!current.isValid())
        return;

    while(ui->formLayout->rowCount() > 0)
        ui->formLayout->removeRow(0);

    auto entity = static_cast<Qt3DCore::QEntity *>(current.internalPointer());

    for(int i = 0; i < entity->metaObject()->propertyCount(); i++)
    {
        auto property = entity->metaObject()->property(i);

        auto type = property.type();

        auto widget = QItemEditorFactory::defaultFactory()->createEditor(type, ui->scrollAreaWidgetContents);
        if(widget)
            widget->setProperty(QItemEditorFactory::defaultFactory()->valuePropertyName(type), entity->property(property.name()));
        else
        {
            qWarning() << "no widget for" << property.name() << "(" << property.type() << ")";
            widget = new QLabel(QString("<span style=\"color:#F00;\">%0</span>").arg(tr("No widget for %0").arg(QString(QVariant::typeToName(type)).toHtmlEscaped())), ui->scrollAreaWidgetContents);
        }

        ui->formLayout->addRow(property.name(), widget);
    }
}

void MainWindow::returnPressed()
{
    ui->textBrowser->append(QString("<b>%0 [DEBUG]:</b> Tried to execute \"%1\"").arg(QTime::currentTime().toString()).arg(ui->lineEdit->text()));
    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());

    ui->lineEdit->setText(QString());
    ui->lineEdit->focusWidget();
}

void MainWindow::start()
{
    for(auto animation : m_animations)
        animation->start();

    ui->actionStart->setEnabled(false);
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);
}

void MainWindow::pause()
{
    for(auto animation : m_animations)
        animation->pause();

    ui->actionStart->setEnabled(true);
    ui->actionPause->setEnabled(false);
}

void MainWindow::stop()
{
    for(auto animation : m_animations)
    {
        animation->setCurrentTime(0);
        animation->stop();
    }

    ui->actionStart->setEnabled(true);
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);
}
