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

using namespace bb::cascades;

Twunch::Twunch(Container *parent) :
        CustomControl(parent)
{
	twunchContainer = new Container();
	StackLayout *twunchLayout = new StackLayout();
	twunchLayout->setOrientation(LayoutOrientation::TopToBottom);
	twunchContainer->setLayout(twunchLayout);

	twunchContainer->add(
            setUpLabelWithStyle((const QString) "Twunch", SystemDefaults::TextStyles::bigText(),
                    true, Color::Gray, true));

	setRoot(twunchContainer);

}

Label *Twunch::setUpLabelWithStyle(const QString labelText, const TextStyle &textStyle,
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
