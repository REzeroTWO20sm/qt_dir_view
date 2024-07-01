#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "dir_view_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QSplitter spl(Qt::Horizontal);
    QFileSystemModel model;

    model.setRootPath(QDir::rootPath());

    QTreeView* pTreeView = new QTreeView;
    pTreeView->setModel(&model);

    QTableView* pTableView = new QTableView;
    pTableView->setModel(&model);

    QObject::connect(pTreeView,SIGNAL(clicked(const QModelIndex&)),pTableView,SLOT(setRootIndex(const QModelIndex&)));
    QObject::connect(pTableView,SIGNAL(activated(const QModelIndex&)),pTreeView,SLOT(setCurrentIndex(const QModelIndex&)));
    QObject::connect(pTableView,SIGNAL(activated(const QModelIndex&)),pTableView,SLOT(setRootIndex(const QModelIndex&)));

    spl.addWidget(pTreeView);
    spl.addWidget(pTableView);
    spl.show();

    return a.exec();
}
