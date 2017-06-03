#ifndef WIDGETS_H
#define WIDGETS_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QUrl>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include <QMatrix4x4>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QItemEditorCreatorBase>

class UrlWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QUrl value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline UrlWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_lineEdit = new QLineEdit(this));
        {
            auto toolButton = new QToolButton(this);
            connect(toolButton, &QAbstractButton::pressed, this, &UrlWidget::pressed);
            layout->addWidget(toolButton);
        }
        setLayout(layout);
    }

    inline QUrl value() const
    {
        return QUrl(m_lineEdit->text());
    }

    inline void setValue(const QUrl &value)
    {
        m_lineEdit->setText(value.toString());
    }

Q_SIGNALS:
    void valueChanged(const QUrl &value);

private Q_SLOTS:
    inline void pressed()
    {
        auto path = QFileDialog::getOpenFileName(this);
        if(!path.isEmpty())
            m_lineEdit->setText(path);
    }

private:
    QLineEdit *m_lineEdit;
};

class UrlCreator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new UrlWidget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

class Matrix4x4Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline Matrix4x4Widget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QGridLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_doubleSpinBox11 = new QDoubleSpinBox(this), 0, 0);
        layout->addWidget(m_doubleSpinBox12 = new QDoubleSpinBox(this), 0, 1);
        layout->addWidget(m_doubleSpinBox13 = new QDoubleSpinBox(this), 0, 2);
        layout->addWidget(m_doubleSpinBox14 = new QDoubleSpinBox(this), 0, 3);
        layout->addWidget(m_doubleSpinBox21 = new QDoubleSpinBox(this), 1, 0);
        layout->addWidget(m_doubleSpinBox22 = new QDoubleSpinBox(this), 1, 1);
        layout->addWidget(m_doubleSpinBox23 = new QDoubleSpinBox(this), 1, 2);
        layout->addWidget(m_doubleSpinBox24 = new QDoubleSpinBox(this), 1, 3);
        layout->addWidget(m_doubleSpinBox31 = new QDoubleSpinBox(this), 2, 0);
        layout->addWidget(m_doubleSpinBox32 = new QDoubleSpinBox(this), 2, 1);
        layout->addWidget(m_doubleSpinBox33 = new QDoubleSpinBox(this), 2, 2);
        layout->addWidget(m_doubleSpinBox34 = new QDoubleSpinBox(this), 2, 3);
        layout->addWidget(m_doubleSpinBox41 = new QDoubleSpinBox(this), 3, 0);
        layout->addWidget(m_doubleSpinBox42 = new QDoubleSpinBox(this), 3, 1);
        layout->addWidget(m_doubleSpinBox43 = new QDoubleSpinBox(this), 3, 2);
        layout->addWidget(m_doubleSpinBox44 = new QDoubleSpinBox(this), 3, 3);
        setLayout(layout);
    }

    inline QMatrix4x4 value() const
    {
        return QMatrix4x4(m_doubleSpinBox11->value(), m_doubleSpinBox12->value(), m_doubleSpinBox13->value(), m_doubleSpinBox14->value(),
                          m_doubleSpinBox21->value(), m_doubleSpinBox22->value(), m_doubleSpinBox23->value(), m_doubleSpinBox24->value(),
                          m_doubleSpinBox31->value(), m_doubleSpinBox32->value(), m_doubleSpinBox33->value(), m_doubleSpinBox34->value(),
                          m_doubleSpinBox41->value(), m_doubleSpinBox42->value(), m_doubleSpinBox43->value(), m_doubleSpinBox44->value());
    }

    inline void setValue(const QMatrix4x4 &value)
    {
        {
            auto row = value.row(0);
            m_doubleSpinBox11->setValue(row.x());
            m_doubleSpinBox12->setValue(row.y());
            m_doubleSpinBox13->setValue(row.z());
            m_doubleSpinBox14->setValue(row.w());
        }
        {
            auto row = value.row(1);
            m_doubleSpinBox21->setValue(row.x());
            m_doubleSpinBox22->setValue(row.y());
            m_doubleSpinBox23->setValue(row.z());
            m_doubleSpinBox24->setValue(row.w());
        }
        {
            auto row = value.row(2);
            m_doubleSpinBox31->setValue(row.x());
            m_doubleSpinBox32->setValue(row.y());
            m_doubleSpinBox33->setValue(row.z());
            m_doubleSpinBox34->setValue(row.w());
        }
        {
            auto row = value.row(3);
            m_doubleSpinBox41->setValue(row.x());
            m_doubleSpinBox42->setValue(row.y());
            m_doubleSpinBox43->setValue(row.z());
            m_doubleSpinBox44->setValue(row.w());
        }
    }

Q_SIGNALS:
    void valueChanged(const QMatrix4x4 &value);

private:
    QDoubleSpinBox *m_doubleSpinBox11, *m_doubleSpinBox12, *m_doubleSpinBox13, *m_doubleSpinBox14;
    QDoubleSpinBox *m_doubleSpinBox21, *m_doubleSpinBox22, *m_doubleSpinBox23, *m_doubleSpinBox24;
    QDoubleSpinBox *m_doubleSpinBox31, *m_doubleSpinBox32, *m_doubleSpinBox33, *m_doubleSpinBox34;
    QDoubleSpinBox *m_doubleSpinBox41, *m_doubleSpinBox42, *m_doubleSpinBox43, *m_doubleSpinBox44;
};

class Matrix4x4Creator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new Matrix4x4Widget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

class Vector2DWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVector2D value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline Vector2DWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_doubleSpinBoxX = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxY = new QDoubleSpinBox(this));
        setLayout(layout);
    }

    inline QVector2D value() const
    {
        return QVector2D(m_doubleSpinBoxX->value(), m_doubleSpinBoxY->value());
    }

    inline void setValue(const QVector2D &value)
    {
        m_doubleSpinBoxX->setValue(value.x());
        m_doubleSpinBoxY->setValue(value.y());
    }

Q_SIGNALS:
    void valueChanged(const QVector2D &value);

private:
    QDoubleSpinBox *m_doubleSpinBoxX;
    QDoubleSpinBox *m_doubleSpinBoxY;
};

class Vector2DCreator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new Vector2DWidget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

class Vector3DWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVector3D value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline Vector3DWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_doubleSpinBoxX = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxY = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxZ = new QDoubleSpinBox(this));
        setLayout(layout);
    }

    inline QVector3D value() const
    {
        return QVector3D(m_doubleSpinBoxX->value(),  m_doubleSpinBoxY->value(), m_doubleSpinBoxZ->value());
    }

    inline void setValue(const QVector3D &value)
    {
        m_doubleSpinBoxX->setValue(value.x());
        m_doubleSpinBoxY->setValue(value.y());
        m_doubleSpinBoxZ->setValue(value.z());
    }

Q_SIGNALS:
    void valueChanged(const QVector3D &value);

private:
    QDoubleSpinBox *m_doubleSpinBoxX;
    QDoubleSpinBox *m_doubleSpinBoxY;
    QDoubleSpinBox *m_doubleSpinBoxZ;
};

class Vector3DCreator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new Vector3DWidget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

class Vector4DWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVector4D value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline Vector4DWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_doubleSpinBoxX = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxY = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxZ = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxW = new QDoubleSpinBox(this));
        setLayout(layout);
    }

    inline QVector4D value() const
    {
        return QVector4D(m_doubleSpinBoxX->value(), m_doubleSpinBoxY->value(), m_doubleSpinBoxZ->value(), m_doubleSpinBoxW->value());
    }

    inline void setValue(const QVector4D &value)
    {
        m_doubleSpinBoxX->setValue(value.x());
        m_doubleSpinBoxY->setValue(value.y());
        m_doubleSpinBoxZ->setValue(value.z());
        m_doubleSpinBoxW->setValue(value.w());
    }

Q_SIGNALS:
    void valueChanged(const QVector4D &value);

private:
    QDoubleSpinBox *m_doubleSpinBoxX;
    QDoubleSpinBox *m_doubleSpinBoxY;
    QDoubleSpinBox *m_doubleSpinBoxZ;
    QDoubleSpinBox *m_doubleSpinBoxW;
};

class Vector4DCreator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new Vector4DWidget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

class QuaternionWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QQuaternion value READ value WRITE setValue NOTIFY valueChanged)

public:
    inline QuaternionWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        auto layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(m_doubleSpinBoxX = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxY = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxZ = new QDoubleSpinBox(this));
        layout->addWidget(m_doubleSpinBoxScalar = new QDoubleSpinBox(this));
        setLayout(layout);
    }

    inline QQuaternion value() const
    {
        return QQuaternion(m_doubleSpinBoxX->value(), m_doubleSpinBoxY->value(), m_doubleSpinBoxZ->value(), m_doubleSpinBoxScalar->value());
    }

    inline void setValue(const QQuaternion &value)
    {
        m_doubleSpinBoxX->setValue(value.x());
        m_doubleSpinBoxY->setValue(value.y());
        m_doubleSpinBoxZ->setValue(value.z());
        m_doubleSpinBoxScalar->setValue(value.scalar());
    }

Q_SIGNALS:
    void valueChanged(const QQuaternion &value);

private:
    QDoubleSpinBox *m_doubleSpinBoxX;
    QDoubleSpinBox *m_doubleSpinBoxY;
    QDoubleSpinBox *m_doubleSpinBoxZ;
    QDoubleSpinBox *m_doubleSpinBoxScalar;
};

class QuaternionCreator : public QItemEditorCreatorBase
{
public:
    QWidget *createWidget(QWidget *parent) const Q_DECL_OVERRIDE
    {
        return new QuaternionWidget(parent);
    }

    QByteArray valuePropertyName() const Q_DECL_OVERRIDE
    {
        return "value";
    }
};

template<int Tmin, int Tmax>
class LimitedQSpinBox : public QSpinBox
{
public:
    inline LimitedQSpinBox(QWidget *parent = Q_NULLPTR) : QSpinBox(parent)
    {
        setRange(Tmin, Tmax);
    }
};

#endif // WIDGETS_H
