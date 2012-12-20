/*
 * TwunchControl.cpp
 *
 *  Created on: 17-dec.-2012
 *      Author: Steven
 */
#include "TwunchControl.hpp"

#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/StackLayout>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/TextStyle>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>

using namespace bb::cascades;

TwunchControl::TwunchControl(Container *parent) :
        CustomControl(parent)
{
	twunchContainer = new Container();
	StackLayout *twunchLayout = new StackLayout();
	twunchLayout->setOrientation(LayoutOrientation::TopToBottom);
	twunchContainer->setLayout(twunchLayout);

	setRoot(twunchContainer);

}

void TwunchControl::setTwunch(QVariantMap *map){
	twunchMap = map;
	qDebug() << "\nTwunchControl::setTwunch() " << map;
	qDebug() << "\nTwunchControl::setTwunch() " << twunchMap;
	qDebug() << "\nTwunchControl::setTwunch() " << twunchMap->value("address");
	qDebug() << "\nTwunchControl::setTwunch() " << twunchMap->value("date");
	twunchContainer->add(setUpLabelWithStyle(twunchMap->value("date").toString(), SystemDefaults::TextStyles::bodyText(), false, Color::Gray, true));
	twunchContainer->add(setUpLabelWithStyle(twunchMap->value("address").toString(), SystemDefaults::TextStyles::bodyText(), false, Color::Gray, true));
	twunchContainer->add(setUpLabelWithStyle(twunchMap->value("closed").toString(), SystemDefaults::TextStyles::primaryText(), false, Color::White, true));
	twunchContainer->add(setUpLabelWithStyle(twunchMap->value("note").toString(), SystemDefaults::TextStyles::primaryText(), false, Color::White, true));
	twunchContainer->add(setUpLabelWithStyle(twunchMap->value("sponsored").toString(), SystemDefaults::TextStyles::primaryText(), false, Color::White, true));

	QMap<QString, QVariant> participantsMap = (QMap<QString, QVariant>) twunchMap->value("participants").toMap();
	QList<QVariant> participants = participantsMap.value("participant").toList();
	twunchContainer->add(setUpLabelWithStyle(QString::number(participants.length()).append(" participants:"), SystemDefaults::TextStyles::primaryText(), false, Color::White, true));
	ListView *participantsListView = new ListView();
	participantsListView->setDataModel(new ArrayDataModel(participants));
	twunchContainer->add(participantsListView);
}

Label *TwunchControl::setUpLabelWithStyle(const QString labelText, const TextStyle &textStyle,
        bool rightAlign, Color color, bool isBold)
{
    Q_UNUSED(color);
    Label *label = new Label();
    label->setText(labelText);
    label->textStyle()->setBase(textStyle);

    // Add some space below the Label.
    label->setBottomMargin(50.0f);

    if (isBold)
        label->textStyle()->setFontWeight(FontWeight::Bold);
    // We have the option of setting the alignment to the right since
    // we'd like one of the Containers to contain right-aligned Labels.
    if (rightAlign == true) {
        label->setHorizontalAlignment(HorizontalAlignment::Right);
    }

    return label;
}
