/*
 * TwunchControl.hpp
 *
 *  Created on: 17-dec.-2012
 *      Author: Steven
 */

#ifndef TWUNCHCONTROL_HPP_
#define TWUNCHCONTROL_HPP_

#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>

#include <QObject>

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class Label;
        class Font;
        class TextStyle;
        class Color;
    }
}

class TwunchControl: public CustomControl
{

public:

    /**
     * Constructor; sets up the label recipe.
     * @param parent The parent Container, if not specified, 0 is used.
     */
	TwunchControl(Container *parent = 0);

	void setTwunch(QVariantMap *map);

private:
    /**
     * Helper function for setting up a label with a specific system font.
     *
     * @param labelText The text of the Label.
     * @param font The system font of the Label.
     * @param rightAlign If true, align to the right. If false use default alignment (left).
     * @param color Unused in this case, but could be used to specific label text color or background label color.
     * @param isBold If true, the text is bolded. If false, the text is not bolded.
     * @return The created Label based on arguments.
     */
    Label *setUpLabelWithStyle(const QString labelText, const TextStyle &textStyle, bool rightAlign,
            Color color, bool isBold);
    Container *twunchContainer;
    QVariantMap *twunchMap;
};


#endif /* TWUNCHCONTROL_HPP_ */
