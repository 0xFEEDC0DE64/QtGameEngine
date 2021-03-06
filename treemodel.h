#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>

namespace Qt3DCore { class QEntity; }

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(Qt3DCore::QEntity *root, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    //Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    Qt3DCore::QEntity *root() const;

private:
    Qt3DCore::QEntity *m_root;
};

#endif // TREEMODEL_H
