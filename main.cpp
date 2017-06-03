#include <QApplication>
#include <QItemEditorFactory>
#include <QStandardItemEditorCreator>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QKeySequenceEdit>

#include "widgets.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        auto factory = new QItemEditorFactory;

        factory->registerEditor(QVariant::Bool, new QStandardItemEditorCreator<QCheckBox>());
        factory->registerEditor(QVariant::Int, new QStandardItemEditorCreator<LimitedQSpinBox<std::numeric_limits<qint32>::min(), std::numeric_limits<qint32>::max()> >());
        factory->registerEditor(QVariant::UInt, new QStandardItemEditorCreator<LimitedQSpinBox<std::numeric_limits<quint32>::min(), std::numeric_limits<quint32>::max()> >());
        factory->registerEditor(QVariant::LongLong, new QStandardItemEditorCreator<LimitedQSpinBox<std::numeric_limits<qint64>::min(), std::numeric_limits<qint64>::max()> >());
        factory->registerEditor(QVariant::ULongLong, new QStandardItemEditorCreator<LimitedQSpinBox<std::numeric_limits<quint64>::min(), std::numeric_limits<quint64>::max()> >());
        factory->registerEditor(QVariant::Double, new QStandardItemEditorCreator<QDoubleSpinBox>());
        factory->registerEditor(QMetaType::Float, new QStandardItemEditorCreator<QDoubleSpinBox>());
        factory->registerEditor(QVariant::ULongLong, new QStandardItemEditorCreator<LimitedQSpinBox<std::numeric_limits<char>::min(), std::numeric_limits<char>::max()> >());
        //factory->registerEditor(QVariant::Map, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::List, Q_NULLPTR); //TODO
        factory->registerEditor(QVariant::String, new QStandardItemEditorCreator<QLineEdit>());
        //factory->registerEditor(QVariant::StringList, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::ByteArray, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::BitArray, Q_NULLPTR); //TODO
        factory->registerEditor(QVariant::Date, new QStandardItemEditorCreator<QDateEdit>());
        factory->registerEditor(QVariant::Time, new QStandardItemEditorCreator<QTimeEdit>());
        factory->registerEditor(QVariant::DateTime, new QStandardItemEditorCreator<QDateTimeEdit>());
        factory->registerEditor(QVariant::Url, new UrlCreator); //TODO
        //factory->registerEditor(QVariant::Locale, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Rect, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::RectF, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Size, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::SizeF, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Line, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::LineF, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Point, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::PointF, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::RegExp, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::RegularExpression, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Hash, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::EasingCurve, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Uuid, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::ModelIndex, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::PersistentModelIndex, Q_NULLPTR); //TODO

        //factory->registerEditor(QVariant::Font, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Pixmap, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Brush, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Color, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Palette, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Image, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Polygon, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Region, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Bitmap, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Cursor, Q_NULLPTR); //TODO
        factory->registerEditor(QVariant::KeySequence, new QStandardItemEditorCreator<QKeySequenceEdit>()); //TODO
        //factory->registerEditor(QVariant::Pen, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::TextLength, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::TextFormat, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Matrix, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Transform, Q_NULLPTR); //TODO
        factory->registerEditor(QVariant::Matrix4x4, new Matrix4x4Creator);
        factory->registerEditor(QVariant::Vector2D, new Vector2DCreator);
        factory->registerEditor(QVariant::Vector3D, new Vector3DCreator);
        factory->registerEditor(QVariant::Vector4D, new Vector4DCreator);
        factory->registerEditor(QVariant::Quaternion, new QuaternionCreator);
        //factory->registerEditor(QVariant::PolygonF, Q_NULLPTR); //TODO
        //factory->registerEditor(QVariant::Icon, Q_NULLPTR); //TODO

        //factory->registerEditor(QVariant::SizePolicy, Q_NULLPTR); //TODO

        QItemEditorFactory::setDefaultFactory(factory);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
