/*
 * MashStepTableModel.h is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009-2012.
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MASHSTEPTABLEMODEL_H
#define   _MASHSTEPTABLEMODEL_H

class MashStepTableModel;
class MashStepItemDelegate;

#include <QAbstractTableModel>
#include <QWidget>
#include <QModelIndex>
#include <QVariant>
#include <QMetaProperty>
#include <QVariant>
#include <QItemDelegate>
#include <QVector>
#include <QTableView>

#include "mashstep.h"
#include "mash.h"
#include "unit.h"

enum{ MASHSTEPNAMECOL, MASHSTEPTYPECOL, MASHSTEPAMOUNTCOL, MASHSTEPTEMPCOL, MASHSTEPTARGETTEMPCOL, MASHSTEPTIMECOL, MASHSTEPNUMCOLS /*This one MUST be last*/};

/*!
 * \class MashStepTableModel
 * \author Philip G. Lee
 *
 * \brief Model for the list of mash steps in a mash.
 */
class MashStepTableModel : public QAbstractTableModel
{
   Q_OBJECT

public:
   MashStepTableModel(QTableView* parent=0);
   virtual ~MashStepTableModel() {}
   //! Set the mash whose mash steps we want to model.
   void setMash( Mash* m );
   //! \returns the mash step at model index \b i.
   MashStep* getMashStep(unsigned int i);

   //! Reimplemented from QAbstractTableModel.
   virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
   //! Reimplemented from QAbstractTableModel.
   virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
   //! Reimplemented from QAbstractTableModel.
   virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
   //! Reimplemented from QAbstractTableModel.
   virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
   //! Reimplemented from QAbstractTableModel.
   virtual Qt::ItemFlags flags(const QModelIndex& index ) const;
   //! Reimplemented from QAbstractTableModel.
   virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );

   unitDisplay displayUnit(int column) const;
   unitScale displayScale(int column) const;
   void setDisplayUnit(int column, unitDisplay displayUnit);
   void setDisplayScale(int column, unitScale displayScale);
   QString generateName(int column) const;

public slots:
   void moveStepUp(int i);
   void moveStepDown(int i);
   void mashChanged(QMetaProperty,QVariant);
   //void mashStepChanged(QMetaProperty,QVariant);
   
private:
   Mash* mashObs;
   QTableView* parentTableWidget;
   QList<MashStep*> steps;
};

/*!
 * \class MashStepItemDelegate
 * \author Philip G. Lee
 *
 * An item delegate for mash step tables.
 */
class MashStepItemDelegate : public QItemDelegate
{
   Q_OBJECT

public:
   MashStepItemDelegate(QObject* parent = 0);

   // Inherited functions.
   virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
   virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
   virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
};

#endif   /* _MASHSTEPTABLEMODEL_H */

