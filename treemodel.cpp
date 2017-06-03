#include "treemodel.h"

#include <QEntity>
#include <QFont>

TreeModel::TreeModel(Qt3DCore::QEntity *root, QObject *parent) :
    QAbstractItemModel(parent),
    m_root(root)
{

}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, (parent.isValid() ? static_cast<Qt3DCore::QEntity *>(parent.internalPointer()) : root())->childNodes().at(row));
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto parent = static_cast<Qt3DCore::QEntity *>(index.internalPointer())->parentNode();

    if (parent == root())
        return QModelIndex();

    int parentRow = 0;

    if(parent->parentNode())
        parentRow = parent->parentNode()->childNodes().indexOf(parent);

    return createIndex(parentRow, 0, parent);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    return (parent.isValid() ? static_cast<Qt3DCore::QEntity *>(parent.internalPointer()) : root())->childNodes().count();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    return 3; //(parent.isValid() ? static_cast<Qt3DCore::QEntity *>(parent.internalPointer()) : root())->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(index.column())
    {
    case 0:
    {
        auto name = static_cast<Qt3DCore::QEntity *>(index.internalPointer())->objectName();
        switch(role)
        {
        case Qt::DisplayRole:
            if(name.isNull())
                return tr("NULL");
            else
                return name;
        case Qt::EditRole:
            return name;
        case Qt::FontRole:
            if(name.isNull())
            {
                QFont font;
                font.setItalic(true);
                return font;
            }
        default:
            return QVariant();
        }
    }
    case 1:
    {
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return static_cast<Qt3DCore::QEntity *>(index.internalPointer())->metaObject()->className();
        default:
            return QVariant();
        }
    }
    case 2:
    {
        auto enabled = static_cast<Qt3DCore::QEntity *>(index.internalPointer())->isEnabled();
        switch(role)
        {
        case Qt::DisplayRole:
            return enabled ? tr("true") : tr("false");
        case Qt::EditRole:
            return enabled;
        default:
            return QVariant();
        }
    }
    }

    return QVariant();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation)
    {
    case Qt::Horizontal:
        switch(section) {
        case 0:
        {
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return tr("Name");
            default: return QVariant();
            }
        }
        case 1:
        {
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return tr("Typ");
            default: return QVariant();
            }
        }
        case 2:
        {
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return tr("Enabled");
            default: return QVariant();
            }
        }
        default: return QVariant();
        }
    default: return QVariant();
    }

    return QVariant();
}

//Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::ItemFlags();

//    return static_cast<Qt3DCore::QEntity *>(index.internalPointer())->flags();
//}

Qt3DCore::QEntity *TreeModel::root() const
{
    return m_root;
}
