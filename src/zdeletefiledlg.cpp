#include <QStandardItemModel>
#include <QFileDialog>
#include <QSettings>
#include "zdeletefiledlg.h"
#include "zfiletool.h"

ZDeleteFileDlg::ZDeleteFileDlg(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent,f)
{
    ui.setupUi(this);
    m_model = new QStandardItemModel(this);
    initSetting();
}

ZDeleteFileDlg::~ZDeleteFileDlg()
{
    QSettings settings("ZTOOLKIT", "ZDeleteFileDlg");
    settings.beginGroup("ZDeleteFileDlg");

    settings.setValue("lineEdit_path",ui.lineEdit_path->text());
    settings.setValue("lineEdit_del_filters",ui.lineEdit_del_filters->text());
    settings.endGroup();
}

void ZDeleteFileDlg::initSetting()
{
    QSettings settings("ZTOOLKIT", "ZDeleteFileDlg");
    settings.beginGroup("ZDeleteFileDlg");

    QString lineEdit_path = settings.value("lineEdit_path").toString();
    ui.lineEdit_path->setText(lineEdit_path);

    QString lineEdit_del_filters = settings.value("lineEdit_del_filters").toString();
    ui.lineEdit_del_filters->setText(lineEdit_del_filters);
    settings.endGroup();
}

void ZDeleteFileDlg::on_btn_update_clicked()
{
    DEBUG_CURRENT_LINE;
    ui.tableView->setModel(NULL);
    m_model->clear();
    QStringList filters = ui.lineEdit_del_filters->text().trimmed().split(";",QString::SkipEmptyParts);
    QList<QFileInfo> allNames;
    ZFileTool::findFile(allNames,ui.lineEdit_path->text(),QStringList());
    qDebug()<<filters.join("-");
    QList<QFileInfo> delNames;
    foreach (QFileInfo fileInfo, allNames)
    {
        QString fileName = fileInfo.fileName();
        bool isFound =false;
        foreach (QString filter , filters)
        {
            if(/*fileName.contains(QRegExp(filter,Qt::CaseInsensitive)) ||*/ fileName.endsWith(filter,Qt::CaseInsensitive) || fileName.toUpper() == filter.toUpper())
            {
                isFound = true;
                break;
            }
        }
        if(isFound)
        {
            delNames.append(fileInfo);
        }
    }
    QStringList labels;
    labels<<"文件"<<"类型"<<"状态";
    m_model->setHorizontalHeaderLabels(labels);
    m_model->setRowCount(delNames.count());
    m_model->setColumnCount(labels.count());
    int row = 0;
    QHash<QString,QColor> typeColor;
    QColor emptyColor("#12a813");
    foreach (QFileInfo fileInfo, delNames)
    {
        QString name = fileInfo.absoluteFilePath();
        {
            QModelIndex index = m_model->index(row,0);
            m_model->setData(index,name);
            QStandardItem* item = m_model->item(row,0);
            item->setCheckable(true);
            item->setCheckState(Qt::Checked);
        }
        {
            QString suffix = fileInfo.completeSuffix();
            QModelIndex index = m_model->index(row,1);
            m_model->setData(index,suffix);
            QStandardItem* item = m_model->item(row,1);
            QColor color(emptyColor);
            if(!suffix.isEmpty())
            {
                if(typeColor.contains(suffix))
                {
                    color = typeColor.value(suffix);
                }
                else
                {
                    color = QColor(qrand()%256,qrand()%256,qrand()%256);
                    typeColor.insert(suffix,color);
                }
            }
            QBrush brush(color);
            item->setBackground(brush);
        }
        {
            QModelIndex index = m_model->index(row,2);
            m_model->setData(index,"未删除");
        }
       row++;
    }

    m_model->setSortRole(Qt::EditRole);
    ui.tableView->setModel(m_model);
    ui.tableView->setSortingEnabled(true);
    ui.tableView->resizeColumnsToContents();
}

void ZDeleteFileDlg::on_btn_path_clicked()
{
    DEBUG_CURRENT_LINE;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    ui.lineEdit_path->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        ui.lineEdit_path->setText(dir);
    }
}

void ZDeleteFileDlg::on_btn_delete_clicked()
{
    DEBUG_CURRENT_LINE;
    for(int row = 0; row < m_model->rowCount(); ++row)
    {
        if(m_model->item(row,0)->checkState()  == Qt::Checked)
        {
            QModelIndex index = m_model->index(row,0);
            QString fileName = m_model->data(index).toString();
            bool isOk = QFile::remove(fileName);
            qDebug()<<QString("删除文件<%1>%2").arg(fileName).arg(isOk ?"成功":"失败");
            {//修改状态
                QModelIndex index = m_model->index(row,2);
                m_model->setData(index,QString("删除<%1>").arg(isOk ?"成功":"失败"));
                QColor color = isOk ? QColor(56,120,0) : QColor(255,111,0);
                QBrush brush(color);
                QStandardItem* item = m_model->item(row,2);
                item->setBackground(brush);
            }
        }
    }
}
