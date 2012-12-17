/*
 * TwunchItem.cpp
 *
 *  Created on: 16-dec.-2012
 *      Author: Steven
 */

#include "TwunchItem.hpp"

#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/StackLayout>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/TextStyle>

using namespace bb::cascades;

TwunchItem::TwunchItem(Container *parent) :
    CustomControl(parent)
{
	qDebug() << "\nTwunchItem::TwunchItem()";
  // A background Container that will hold a background image and an item content Container
  Container *itemContainer = new Container();
  DockLayout *itemLayout = new DockLayout();
  itemContainer->setLayout(itemLayout);
  itemContainer->setPreferredWidth(768.0f);

  // The white background image for an item
  ImageView *bkgImage = ImageView::create("asset:///images/burger.png")
                          .preferredSize(114.0f, 114.0f);

  // A Colored Container will be used to show if an item is highlighted
  mHighlighContainer = new Container();
  mHighlighContainer->setBackground(Color::fromARGB(0xff75b5d3));
  mHighlighContainer->setHorizontalAlignment(HorizontalAlignment::Center);
  mHighlighContainer->setOpacity(0.0);
  mHighlighContainer->setPreferredWidth(760.0f);
  mHighlighContainer->setPreferredHeight(120.0f);

  // Content Container containing an image and label with padding for the alignment on background image
  Container *contentContainer = new Container();
  StackLayout *contentLayout = new StackLayout();
  contentLayout->setOrientation(LayoutOrientation::LeftToRight);
  contentContainer->setLeftPadding(3.0f);
  contentContainer->setLayout(contentLayout);

  // The list item image which is docked to the top, the actual image is set in updateItem
  mItemImage = ImageView::create("asset:///images/burger.png");
  mItemImage->setVerticalAlignment(VerticalAlignment::Top);

  Container *infoContainer = new Container();
  StackLayout *infoLayout = new StackLayout();
  infoLayout->setOrientation(LayoutOrientation::TopToBottom);
  infoContainer->setLeftMargin(120.0f);
  infoContainer->setTopPadding(3.0f);
  infoContainer->setBottomPadding(3.0f);
  infoContainer->setLayout(infoLayout);

  Container *titleContainer = new Container();
  StackLayout *titleLayout = new StackLayout();
  titleLayout->setOrientation(LayoutOrientation::LeftToRight);
  titleContainer->setLayout(titleLayout);

  // A list item label, docked to the center, the text is set in updateItem.
  mItemLabel = Label::create().text(" ");
  //mItemLabel->setVerticalAlignment(VerticalAlignment::Top);
  mItemLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
  mItemLabel->textStyle()->setColor(Color::White);

  mItemAddress = Label::create().text(" ");
  //mItemAddress->setVerticalAlignment(VerticalAlignment::Bottom);
  mItemAddress->textStyle()->setBase(SystemDefaults::TextStyles::subtitleText());
  mItemAddress->textStyle()->setColor(Color::White);

  mItemDateTime = Label::create().text(" ");
  //mItemDateTime->setVerticalAlignment(VerticalAlignment::Bottom);
  mItemDateTime->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
  mItemDateTime->textStyle()->setColor(Color::White);
  mItemDateTime->setPreferredWidth(170.0f);

  titleContainer->add(mItemDateTime);
  titleContainer->add(mItemLabel);
  infoContainer->add(titleContainer);
  infoContainer->add(mItemAddress);

  // Add the Image and Label to the content Container
  contentContainer->add(mItemImage);
  contentContainer->add(infoContainer);

  // Add the background image and the content to the full item container.
  itemContainer->add(bkgImage);
  itemContainer->add(mHighlighContainer);
  itemContainer->add(contentContainer);

  setRoot(itemContainer);
}

void TwunchItem::updateItem(const QString text, const QString address, const QString dateTime, const QString imagePath)
{
	qDebug() << "\nTwunchItem::updateItem(): " << text << " " << imagePath;
  // Update image and text for the current item
  mItemImage->setImage(Image(imagePath));
  mItemLabel->setText(text);
  mItemAddress->setText(address);
  mItemDateTime->setText(dateTime);
}

void TwunchItem::select(bool select)
{
  // When an item is selected, show the colored highlight Container
  if (select) {
    mHighlighContainer->setOpacity(0.9f);
  } else {
    mHighlighContainer->setOpacity(0.0f);
  }
}

void TwunchItem::reset(bool selected, bool activated)
{
  Q_UNUSED(activated);

  // Since items are recycled, the reset function is where we have
  // to make sure that item state (defined by the arguments) is correct.
  select(selected);
}

void TwunchItem::activate(bool activate)
{
  // There is no special activate state; selected and activated look the same.
  select(activate);
}
