// Navigation pane project template
#ifndef Twunch_HPP_
#define Twunch_HPP_

#include <QObject>
#include <QFile>

#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ListView>
#include <bb/data/XmlDataAccess>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/NavigationPane>

using namespace bb::cascades;
using namespace bb::data;

namespace bb { namespace cascades { class Application;
class Page;}}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class Twunch : public QObject
{
    Q_OBJECT
public:
    Twunch(bb::cascades::Application *app);
    virtual ~Twunch() {}
    Q_INVOKABLE void initiateRequest();

private slots:
	void requestFinished(QNetworkReply* reply);

    /**
     * This Slot function for selection in list.
     *
     * @param indexPath Index path to the item
     */
    void onTriggered(const QVariantList indexPath);

    /**
     * This Slot function receives signals when the top Control has changed in the
     * NavigationPane.
     *
     * @param page Top Container to be changed to
     */
    void onTopChanged(bb::cascades::Page* page);

    /**
     * This Signal handler function for when navigation ends in the NavigationPane.
     *
     * @param page The main content Container we are transitioning away from
     */
    void onPopTransitionEnded(bb::cascades::Page *page);

private:
    /**
	 * This function initializes the content page
	 *
	 * @return The created content Page
	 */
	Page *createContentPage();

	ActivityIndicator *mActivityIndicator;
	ListView *mListView;
	QNetworkAccessManager *mNetworkAccessManager;
	QFile *mFile;
	XmlDataAccess xda;
	QVariant list;
	bb::cascades::QVariantListDataModel mTwunchModel;
	NavigationPane *mNavPane;
	Page *mContentPage;
	GroupDataModel *model;

};

#endif /* Twunch_HPP_ */
