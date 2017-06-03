#include "houseplant.h"

#include <Qt3DRender/qtexture.h>

const char *potNames[] = {
    "cross",
    "square",
    "triangle",
    "sphere"
};

const char *plantNames[] = {
    "bamboo",
    "palm",
    "pine",
    "spikes",
    "shrub"
};


HousePlant::HousePlant(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_pot(new RenderableEntity(this))
    , m_plant(new RenderableEntity(m_pot))
    , m_cover(new RenderableEntity(m_pot))
    , m_potMaterial(new Qt3DExtras::QNormalDiffuseMapMaterial())
    , m_plantMaterial(new Qt3DExtras::QNormalDiffuseMapAlphaMaterial())
    , m_coverMaterial(new Qt3DExtras::QNormalDiffuseMapMaterial())
    , m_potImage(new Qt3DRender::QTextureImage())
    , m_potNormalImage(new Qt3DRender::QTextureImage())
    , m_plantImage(new Qt3DRender::QTextureImage())
    , m_plantNormalImage(new Qt3DRender::QTextureImage())
    , m_coverImage(new Qt3DRender::QTextureImage())
    , m_coverNormalImage(new Qt3DRender::QTextureImage())
    , m_plantType(Bamboo)
    , m_potShape(Cross)
{
    m_potMaterial->setObjectName("potMaterial");
    m_plantMaterial->setObjectName("plantMaterial");
    m_coverMaterial->setObjectName("coverMaterial");
    m_potImage->setObjectName("potImage");
    m_potNormalImage->setObjectName("potNormalImage");
    m_plantImage->setObjectName("plantImage");
    m_plantNormalImage->setObjectName("plantNormalImage");
    m_coverImage->setObjectName("coverImage");
    m_coverNormalImage->setObjectName("coverNormalImage");

    m_pot->setObjectName("pot");
    m_pot->transform()->setScale(0.03f);
    m_pot->addComponent(m_potMaterial);

    m_plant->setObjectName("plant");
    m_plant->addComponent(m_plantMaterial);

    m_cover->setObjectName("cover");
    m_cover->addComponent(m_coverMaterial);

    m_potMaterial->diffuse()->addTextureImage(m_potImage);
    m_potMaterial->normal()->addTextureImage(m_potNormalImage);
    m_plantMaterial->diffuse()->addTextureImage(m_plantImage);
    m_plantMaterial->normal()->addTextureImage(m_plantNormalImage);
    m_coverMaterial->diffuse()->addTextureImage(m_coverImage);
    m_coverMaterial->normal()->addTextureImage(m_coverNormalImage);

    updatePlantType();
    updatePotShape();

    m_coverImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/cover.webp")));
    m_coverNormalImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/cover_normal.webp")));
    m_potImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/pot.webp")));
    m_potNormalImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/pot_normal.webp")));

    m_potMaterial->setShininess(10.0f);
    m_potMaterial->setSpecular(QColor::fromRgbF(0.75f, 0.75f, 0.75f, 1.0f));

    m_plantMaterial->setShininess(10.0f);

    m_coverMaterial->setSpecular(QColor::fromRgbF(0.05f, 0.05f, 0.05f, 1.0f));
    m_coverMaterial->setShininess(5.0f);
}

HousePlant::~HousePlant()
{
}

void HousePlant::setPotShape(HousePlant::PotShape shape)
{
    if (shape != m_potShape) {
        m_potShape = shape;
        updatePotShape();
    }
}

void HousePlant::setPlantType(HousePlant::Plant plant)
{
    if (plant != m_plantType) {
        m_plantType = plant;
        updatePlantType();
    }
}

HousePlant::PotShape HousePlant::potShape() const
{
    return m_potShape;
}

HousePlant::Plant HousePlant::plantType() const
{
    return m_plantType;
}

void HousePlant::setPosition(const QVector3D &pos)
{
    m_pot->transform()->setTranslation(pos);
}

void HousePlant::setScale(float scale)
{
    m_pot->transform()->setScale(scale);
}

QVector3D HousePlant::position() const
{
    return m_pot->transform()->translation();
}

float HousePlant::scale() const
{
    return m_pot->transform()->scale();
}

void HousePlant::updatePotShape()
{
    m_pot->mesh()->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/") + potNames[m_potShape] + QStringLiteral("-pot.obj")));
    m_plant->mesh()->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/") + potNames[m_potShape] + QStringLiteral("-") + plantNames[m_plantType] + QStringLiteral(".obj")));
}

void HousePlant::updatePlantType()
{
    m_plant->mesh()->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/") + potNames[m_potShape] + QStringLiteral("-") + plantNames[m_plantType] + QStringLiteral(".obj")));

    m_plantImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/") + plantNames[m_plantType] + QStringLiteral(".webp")));
    m_plantNormalImage->setSource(QUrl(QStringLiteral("qrc:/assets/houseplants/") + plantNames[m_plantType] + QStringLiteral("_normal.webp")));
}
