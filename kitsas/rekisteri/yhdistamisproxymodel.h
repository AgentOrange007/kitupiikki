/*
   Copyright (C) 2019 Arto Hyvättinen

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef YHDISTAMISPROXYMODEL_H
#define YHDISTAMISPROXYMODEL_H

#include <QSortFilterProxyModel>

class YhdistamisProxyModel : public QSortFilterProxyModel
{
public:
    YhdistamisProxyModel(QObject* parent = nullptr);

    void asetaId(int id);
    void suodataNimella(const QString& nimi = QString());

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    int id_ = 0;
    QStringList nimiPalat_;
};

#endif // YHDISTAMISPROXYMODEL_H
