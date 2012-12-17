/*
 * TwunchItemFactory.cpp
 *
 *  Created on: 15-dec.-2012
 *      Author: Steven
 */

#include "TwunchItemFactory.hpp"
#include "TwunchItem.hpp"

using namespace bb::cascades;

TwunchItemFactory::TwunchItemFactory()
{
}

VisualNode * TwunchItemFactory::createItem(ListView* list, const QString &type)
{
  // We only have one item type so we do not need to check the type variable
  Q_UNUSED(type);
  Q_UNUSED(list);
  qDebug() << "\n TwunchItemFactory::createItem()";
  qDebug() << "\nlist: " << list;
  qDebug() << "\ntype: " << type;
  TwunchItem *twunchItem = new TwunchItem();
  return twunchItem;
}

void TwunchItemFactory::updateItem(ListView* list, bb::cascades::VisualNode *listItem,
    const QString &type, const QVariantList &indexPath, const QVariant &data)
{
  Q_UNUSED(list);
  Q_UNUSED(indexPath);
  Q_UNUSED(type);

  // Update the control with correct data
  QVariantMap map = data.value<QVariantMap>();
  qDebug() << "\nTwunchItemFactory::updateItem()";
  qDebug() << "\nmap: " << map;
  qDebug() << "\nTwunch title: " << map["title"];
  qDebug() << "\nTwunch date: " << map["date"];
  qDebug() << "\ndata: " << data;
  TwunchItem *twunchItem = static_cast<TwunchItem *>(listItem);
  //twunchItem->updateItem(map["title"].toString(), map["image"].toString());
  QString date(map["date"].toString());
  QString argDate = date.mid(4,4);
  QDate d = QDate::fromString(argDate, "MMdd");
  argDate = d.toString("d MMM");
  twunchItem->updateItem(map["title"].toString(), map["address"].toString(), argDate, "app/native/assets/images/burger.png");
}



