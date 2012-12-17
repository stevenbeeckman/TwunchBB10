// based on https://developer.blackberry.com/cascades/documentation/device_comm/networking/tutorial_http_comm.html
#include "Twunch.hpp"
#include "TwunchItemFactory.hpp"
#include "TwunchItem.hpp"

#include "TwunchControl.hpp"

#include <QObject>
#include <QIODevice>
#include <QDir>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/XmlDataModel>
#include <bb/cascades/GroupDataModel>
#include <bb/data/XmlDataAccess>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Container>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/StackLayout>
#include <bb/cascades/ActionItem>
#include <bb/cascades/TitleBar>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/UIOrientation>
#include <bb/cascades/SupportedDisplayOrientation>
#include <bb/cascades/Label>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/TextStyle>

using namespace bb::cascades;
using namespace bb::data;

Twunch::Twunch(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Expose this class to QML so that we can call its functions from there
    qml->setContextProperty("app", this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    mActivityIndicator = root->findChild<ActivityIndicator*>("indicator");
    mListView = root->findChild<ListView*>("twunches");
    mNavPane = root->findChild<NavigationPane*>("navigationPane");
    mNetworkAccessManager = new QNetworkAccessManager(this);
    mContentPage = createContentPage();

    bool result = connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(result);
    Q_UNUSED(result);

    mFile = new QFile("app/native/assets/twunches.xml");

    // set created root object as a scene
    app->setScene(root);
    initiateRequest();
}

void Twunch::initiateRequest(){
	mActivityIndicator->start();

	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl("http://twunch.be/events.xml?when=future"));
	mNetworkAccessManager->get(request);
}

void Twunch::requestFinished(QNetworkReply* reply){
	if(reply->error() == QNetworkReply::NoError) {
		if(!mFile->open(QIODevice::ReadWrite)){
			qDebug() << "\n Failed to open file";
			return;
		}

		mFile->write(reply->readAll());
		mFile->flush();
		mFile->close();

		//XmlDataModel *dataModel = new XmlDataModel();
		//dataModel->setSource(QUrl("file://" + QDir::homePath() + "/twunches.xml"));

		model = new GroupDataModel(QStringList() << "date" << "title");
		XmlDataAccess xda;
		QVariant list = xda.load("app/native/assets/twunches.xml", "/twunches/twunch");
		/*QValueList<QVariant> listToPrint = list.asList();
		QValueList<QVariant>::Iterator it = listToPrint.begin();
		while( it != listToPrint.end() ) {
		    qDebug() << "\nTwunch: " << *it;
		    ++it;
		}*/
		qDebug() << "\nList: " << list;

		TwunchItemFactory *twunchItemFactory = new TwunchItemFactory();
		//QVariantMap map = QVariantMap();
		//map["title"] = QString("Twunches");
		//map["image"] = QString("app/native/assets/images/burger.png");
		//qDebug() << "\nMap: " << map;
		//mTwunchModel << map;

		model->insertList(list.value<QVariantList>());

		//mListView->setDataModel(dataModel);
		mListView->setDataModel(model);
		//mListView->setDataModel(&mTwunchModel);
		mListView->setListItemProvider(twunchItemFactory);
		connect(mListView, SIGNAL(triggered(const QVariantList)), this,
		            SLOT(onTriggered(const QVariantList)));
		mActivityIndicator->stop();
	}else{
		qDebug() << "\n Problem with the network";
		qDebug() << "\n" << reply->errorString();
	}
}

void Twunch::onTopChanged(bb::cascades::Page* page)
{
    if (page != mContentPage) {
        // Reset list selection when the main container Page is not the Content Page
        mListView->clearSelection();
    }

    // We only want the app to be in Portrait mode when viewing ListView
    OrientationSupport *support = OrientationSupport::instance();
    if (support->orientation() == UIOrientation::Landscape) {
        support->setSupportedDisplayOrientation(SupportedDisplayOrientation::DisplayPortrait);
    }
}

Page *Twunch::createContentPage()
{
    // Create a second page where the recipes (CustomControls) will be added in
    Page *page = new Page();

    // We need an action on the ContentPage, so we can navigate back.
    ActionItem* backAction = ActionItem::create();
    connect(backAction, SIGNAL(triggered()), mNavPane, SLOT(pop()));
    page->setPaneProperties(NavigationPaneProperties::create().backButton(backAction));

    // Set the title bar
    TitleBar* titleBar = TitleBar::create().visibility(ChromeVisibility::Visible).title("Twunch");
    page->setTitleBar(titleBar);

    // Create the content Container which is where the CustomControl recipes are added in onSelectionChanged
    Container *content = new Container();

    // Set the background and layout
    content->setLayout(StackLayout::create());

    // Add the ContentContainer to the content Page
    page->setContent(content);

    return page;
}

void Twunch::onTriggered(const QVariantList indexPath)
{
	CustomControl *twunchControl = NULL;

	QVariantMap twunchMap = model->data(indexPath).toMap();
	qDebug() << "\nTwunch::onTriggered(): " << twunchMap;
	//Container *twunchContainer = new Container();
	//qDebug() << "\nCreated twunchContainer";
	QString title = twunchMap.value("title").toString();
	qDebug() << "\nTitle: " << title;
    Label *twunchTitle = Label::create().text(title);
    qDebug() << "\nCreated twunchTitle";
    //twunchContainer->add(twunchTitle);
    //qDebug() << "\nAdded twunchTitle to twunchContainer";

    twunchControl = new TwunchControl();

    Container *content = qobject_cast<Container *>(mContentPage->content());
    qDebug() << "\nGot the content of mContentPage";
    if(twunchControl){
    	if(content && mContentPage){
			content->add(twunchTitle);
			qDebug() << "\nAdded twunchContainer to content. Pushing mContentPage now...";
			mContentPage->titleBar()->setTitle(title);
			mNavPane->push(mContentPage);
			qDebug() << "\nPushed mContentPage";
		}
    }


    /*if (recipe) {
        // Get the content Container of the ContentPage, add the new recipe, it will be removed when
        // the popTransitionEnded signal is received in the onPopTransitionEnded function.
        Container *content = qobject_cast<Container *>(mContentPage->content());

        if (content) {
            recipe->setHorizontalAlignment(HorizontalAlignment::Center);
            recipe->setVerticalAlignment(VerticalAlignment::Center);
            content->add(recipe);
            mContentPage->titleBar()->setTitle(title);
            mNavPane->push(mContentPage);
        } else {
            delete recipe;
        }

    } else {
        qDebug("No Twunch found for this selection. Here be dragons.");
    }*/

}

void Twunch::onPopTransitionEnded(bb::cascades::Page *page)
{
    if (page == mContentPage) {
    	qDebug() << "in Twunch::onPopTransitionEnded()";

        // When the transition from the content page is complete, the recipe is removed.
        Container *content = qobject_cast<Container *>(mContentPage->content());

        if (content) {
            Control *recipeControl = content->at(0);

            // Remove the current recipe once we return to the ListView
            if (recipeControl && content->remove(recipeControl)) {
                delete recipeControl;
            }
        }
    }
}
