/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created: Tue Feb 21 17:58:55 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QListWidget *presets;
    QLabel *label;
    QLineEdit *wmClasses;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QComboBox *actGrad;
    KColorButton *actColor;
    QLabel *label_7;
    QComboBox *actGrad2;
    KColorButton *actColor2;
    QLabel *label_15;
    KColorButton *actText;
    QLabel *label_16;
    KColorButton *actButtons;
    QWidget *tab_4;
    QGridLayout *gridLayout_5;
    QLabel *label_6;
    QComboBox *inactGrad;
    KColorButton *inactColor;
    QLabel *label_9;
    QComboBox *inactGrad2;
    KColorButton *inactColor2;
    QLabel *label_13;
    KColorButton *inactText;
    QLabel *label_14;
    KColorButton *inactButtons;
    QSpacerItem *verticalSpacer;
    QPushButton *newPreset;
    QPushButton *deletePreset;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *wmTypes;
    QLabel *label_2;
    QWidget *Seite_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *label_11;
    QComboBox *iconVariant;
    QLabel *label_4;
    QComboBox *slickButtons;
    QLabel *label_3;
    QLineEdit *multibutton;
    QComboBox *buttonGradient;
    QLabel *label_17;
    QCheckBox *inactiveButtons;
    QSpacerItem *verticalSpacer_2;
    QWidget *Seite;
    QGridLayout *gridLayout_4;
    QCheckBox *roundCorners;
    QCheckBox *verticalTitlebar;
    QSpacerItem *verticalSpacer_4;
    QFormLayout *formLayout;
    QLabel *label_10;
    QWidget *widget;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer;
    QRadioButton *titleLeft;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *titleCenter;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *titleRight;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QSpinBox *titlePadding;
    QLabel *label_20;
    QGridLayout *gridLayout_6;
    QLabel *label_21;
    QSpinBox *baseSize;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *edgeSize;
    QLabel *label_22;
    QLabel *label_12;
    QLineEdit *smallTitleClasses;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QCheckBox *trimmTitle;
    QCheckBox *resizeCorner;
    QCheckBox *forceUserColors;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_5;
    QFormLayout *formLayout_3;
    QLabel *label_18;
    QSlider *inactiveShadowSize;
    QLabel *label_19;
    QSlider *activeShadowSize;
    KColorButton *shadowColor;
    QCheckBox *halo;
    QTextBrowser *onlinehelp;

    void setupUi(QWidget *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QString::fromUtf8("Config"));
        Config->resize(564, 348);
        horizontalLayout = new QHBoxLayout(Config);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(Config);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        presets = new QListWidget(tab);
        presets->setObjectName(QString::fromUtf8("presets"));

        gridLayout->addWidget(presets, 0, 0, 5, 2);

        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 2, 1, 1);

        wmClasses = new QLineEdit(tab);
        wmClasses->setObjectName(QString::fromUtf8("wmClasses"));
        wmClasses->setEnabled(false);

        gridLayout->addWidget(wmClasses, 1, 3, 1, 1);

        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setDocumentMode(false);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        actGrad = new QComboBox(tab_3);
        actGrad->setObjectName(QString::fromUtf8("actGrad"));

        gridLayout_2->addWidget(actGrad, 0, 1, 1, 1);

        actColor = new KColorButton(tab_3);
        actColor->setObjectName(QString::fromUtf8("actColor"));
        actColor->setEnabled(true);

        gridLayout_2->addWidget(actColor, 0, 2, 1, 1);

        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        actGrad2 = new QComboBox(tab_3);
        actGrad2->setObjectName(QString::fromUtf8("actGrad2"));

        gridLayout_2->addWidget(actGrad2, 1, 1, 1, 1);

        actColor2 = new KColorButton(tab_3);
        actColor2->setObjectName(QString::fromUtf8("actColor2"));
        actColor2->setEnabled(true);

        gridLayout_2->addWidget(actColor2, 1, 2, 1, 1);

        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 2, 1, 1, 1);

        actText = new KColorButton(tab_3);
        actText->setObjectName(QString::fromUtf8("actText"));
        actText->setEnabled(true);

        gridLayout_2->addWidget(actText, 2, 2, 1, 1);

        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 3, 1, 1, 1);

        actButtons = new KColorButton(tab_3);
        actButtons->setObjectName(QString::fromUtf8("actButtons"));
        actButtons->setEnabled(true);

        gridLayout_2->addWidget(actButtons, 3, 2, 1, 1);

        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_5 = new QGridLayout(tab_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        inactGrad = new QComboBox(tab_4);
        inactGrad->setObjectName(QString::fromUtf8("inactGrad"));

        gridLayout_5->addWidget(inactGrad, 0, 1, 1, 1);

        inactColor = new KColorButton(tab_4);
        inactColor->setObjectName(QString::fromUtf8("inactColor"));
        inactColor->setEnabled(true);

        gridLayout_5->addWidget(inactColor, 0, 2, 1, 1);

        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 1, 0, 1, 1);

        inactGrad2 = new QComboBox(tab_4);
        inactGrad2->setObjectName(QString::fromUtf8("inactGrad2"));

        gridLayout_5->addWidget(inactGrad2, 1, 1, 1, 1);

        inactColor2 = new KColorButton(tab_4);
        inactColor2->setObjectName(QString::fromUtf8("inactColor2"));
        inactColor2->setEnabled(true);

        gridLayout_5->addWidget(inactColor2, 1, 2, 1, 1);

        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_13, 2, 1, 1, 1);

        inactText = new KColorButton(tab_4);
        inactText->setObjectName(QString::fromUtf8("inactText"));
        inactText->setEnabled(true);

        gridLayout_5->addWidget(inactText, 2, 2, 1, 1);

        label_14 = new QLabel(tab_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_14, 3, 1, 1, 1);

        inactButtons = new KColorButton(tab_4);
        inactButtons->setObjectName(QString::fromUtf8("inactButtons"));
        inactButtons->setEnabled(true);

        gridLayout_5->addWidget(inactButtons, 3, 2, 1, 1);

        tabWidget_2->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget_2, 3, 2, 1, 2);

        verticalSpacer = new QSpacerItem(39, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 3, 1, 1);

        newPreset = new QPushButton(tab);
        newPreset->setObjectName(QString::fromUtf8("newPreset"));

        gridLayout->addWidget(newPreset, 5, 0, 1, 1);

        deletePreset = new QPushButton(tab);
        deletePreset->setObjectName(QString::fromUtf8("deletePreset"));
        deletePreset->setEnabled(false);
        QPalette palette;
        QBrush brush(QColor(156, 14, 14, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush2(QColor(157, 156, 156, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        deletePreset->setPalette(palette);

        gridLayout->addWidget(deletePreset, 5, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(180, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 5, 2, 1, 2);

        wmTypes = new QLineEdit(tab);
        wmTypes->setObjectName(QString::fromUtf8("wmTypes"));
        wmTypes->setEnabled(false);

        gridLayout->addWidget(wmTypes, 2, 3, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        tabWidget->addTab(tab, QString());
        Seite_2 = new QWidget();
        Seite_2->setObjectName(QString::fromUtf8("Seite_2"));
        verticalLayout = new QVBoxLayout(Seite_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_11 = new QLabel(Seite_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_11);

        iconVariant = new QComboBox(Seite_2);
        iconVariant->setObjectName(QString::fromUtf8("iconVariant"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconVariant->sizePolicy().hasHeightForWidth());
        iconVariant->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, iconVariant);

        label_4 = new QLabel(Seite_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        slickButtons = new QComboBox(Seite_2);
        slickButtons->setObjectName(QString::fromUtf8("slickButtons"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, slickButtons);

        label_3 = new QLabel(Seite_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_3->setFont(font);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_3);

        multibutton = new QLineEdit(Seite_2);
        multibutton->setObjectName(QString::fromUtf8("multibutton"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, multibutton);

        buttonGradient = new QComboBox(Seite_2);
        buttonGradient->setObjectName(QString::fromUtf8("buttonGradient"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, buttonGradient);

        label_17 = new QLabel(Seite_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_17);


        verticalLayout->addLayout(formLayout_2);

        inactiveButtons = new QCheckBox(Seite_2);
        inactiveButtons->setObjectName(QString::fromUtf8("inactiveButtons"));

        verticalLayout->addWidget(inactiveButtons);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        tabWidget->addTab(Seite_2, QString());
        Seite = new QWidget();
        Seite->setObjectName(QString::fromUtf8("Seite"));
        gridLayout_4 = new QGridLayout(Seite);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        roundCorners = new QCheckBox(Seite);
        roundCorners->setObjectName(QString::fromUtf8("roundCorners"));

        gridLayout_4->addWidget(roundCorners, 1, 0, 1, 1);

        verticalTitlebar = new QCheckBox(Seite);
        verticalTitlebar->setObjectName(QString::fromUtf8("verticalTitlebar"));

        gridLayout_4->addWidget(verticalTitlebar, 4, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 5, 0, 1, 2);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout->setHorizontalSpacing(8);
        formLayout->setVerticalSpacing(10);
        label_10 = new QLabel(Seite);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_10->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        widget = new QWidget(Seite);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        gridLayout_10 = new QGridLayout(widget);
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalSpacer = new QSpacerItem(1, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer, 0, 0, 1, 1);

        titleLeft = new QRadioButton(widget);
        titleLeft->setObjectName(QString::fromUtf8("titleLeft"));

        gridLayout_10->addWidget(titleLeft, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        titleCenter = new QRadioButton(widget);
        titleCenter->setObjectName(QString::fromUtf8("titleCenter"));

        gridLayout_10->addWidget(titleCenter, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_4, 0, 4, 1, 1);

        titleRight = new QRadioButton(widget);
        titleRight->setObjectName(QString::fromUtf8("titleRight"));

        gridLayout_10->addWidget(titleRight, 0, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_2, 0, 6, 1, 1);


        formLayout->setWidget(2, QFormLayout::FieldRole, widget);

        label_5 = new QLabel(Seite);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        titlePadding = new QSpinBox(Seite);
        titlePadding->setObjectName(QString::fromUtf8("titlePadding"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titlePadding->sizePolicy().hasHeightForWidth());
        titlePadding->setSizePolicy(sizePolicy1);
        titlePadding->setMaximum(10);

        formLayout->setWidget(3, QFormLayout::FieldRole, titlePadding);

        label_20 = new QLabel(Seite);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_20);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_21 = new QLabel(Seite);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_21, 0, 2, 1, 2);

        baseSize = new QSpinBox(Seite);
        baseSize->setObjectName(QString::fromUtf8("baseSize"));
        baseSize->setMaximum(32);

        gridLayout_6->addWidget(baseSize, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_5, 1, 1, 1, 1);

        edgeSize = new QSpinBox(Seite);
        edgeSize->setObjectName(QString::fromUtf8("edgeSize"));
        edgeSize->setMaximum(32);

        gridLayout_6->addWidget(edgeSize, 1, 2, 1, 2);

        label_22 = new QLabel(Seite);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_22, 0, 0, 1, 1);


        formLayout->setLayout(4, QFormLayout::FieldRole, gridLayout_6);

        label_12 = new QLabel(Seite);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_12);

        smallTitleClasses = new QLineEdit(Seite);
        smallTitleClasses->setObjectName(QString::fromUtf8("smallTitleClasses"));

        formLayout->setWidget(5, QFormLayout::FieldRole, smallTitleClasses);


        gridLayout_4->addLayout(formLayout, 0, 0, 1, 2);

        tabWidget->addTab(Seite, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        trimmTitle = new QCheckBox(tab_2);
        trimmTitle->setObjectName(QString::fromUtf8("trimmTitle"));

        gridLayout_3->addWidget(trimmTitle, 0, 0, 1, 1);

        resizeCorner = new QCheckBox(tab_2);
        resizeCorner->setObjectName(QString::fromUtf8("resizeCorner"));

        gridLayout_3->addWidget(resizeCorner, 1, 0, 1, 1);

        forceUserColors = new QCheckBox(tab_2);
        forceUserColors->setObjectName(QString::fromUtf8("forceUserColors"));

        gridLayout_3->addWidget(forceUserColors, 3, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 4, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        formLayout_3 = new QFormLayout(tab_5);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_18 = new QLabel(tab_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_18);

        inactiveShadowSize = new QSlider(tab_5);
        inactiveShadowSize->setObjectName(QString::fromUtf8("inactiveShadowSize"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(inactiveShadowSize->sizePolicy().hasHeightForWidth());
        inactiveShadowSize->setSizePolicy(sizePolicy2);
        inactiveShadowSize->setMinimumSize(QSize(128, 0));
        inactiveShadowSize->setMinimum(8);
        inactiveShadowSize->setMaximum(72);
        inactiveShadowSize->setPageStep(8);
        inactiveShadowSize->setValue(12);
        inactiveShadowSize->setOrientation(Qt::Horizontal);
        inactiveShadowSize->setTickPosition(QSlider::TicksBelow);
        inactiveShadowSize->setTickInterval(8);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, inactiveShadowSize);

        label_19 = new QLabel(tab_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_19);

        activeShadowSize = new QSlider(tab_5);
        activeShadowSize->setObjectName(QString::fromUtf8("activeShadowSize"));
        sizePolicy2.setHeightForWidth(activeShadowSize->sizePolicy().hasHeightForWidth());
        activeShadowSize->setSizePolicy(sizePolicy2);
        activeShadowSize->setMinimumSize(QSize(128, 0));
        activeShadowSize->setMinimum(8);
        activeShadowSize->setMaximum(72);
        activeShadowSize->setPageStep(8);
        activeShadowSize->setValue(48);
        activeShadowSize->setOrientation(Qt::Horizontal);
        activeShadowSize->setTickPosition(QSlider::TicksAbove);
        activeShadowSize->setTickInterval(8);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, activeShadowSize);

        shadowColor = new KColorButton(tab_5);
        shadowColor->setObjectName(QString::fromUtf8("shadowColor"));
        shadowColor->setEnabled(false);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, shadowColor);

        halo = new QCheckBox(tab_5);
        halo->setObjectName(QString::fromUtf8("halo"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, halo);

        tabWidget->addTab(tab_5, QString());

        horizontalLayout->addWidget(tabWidget);

        onlinehelp = new QTextBrowser(Config);
        onlinehelp->setObjectName(QString::fromUtf8("onlinehelp"));
        onlinehelp->setFocusPolicy(Qt::NoFocus);
        onlinehelp->setFrameShape(QFrame::StyledPanel);
        onlinehelp->setFrameShadow(QFrame::Plain);
        onlinehelp->setLineWidth(0);

        horizontalLayout->addWidget(onlinehelp);


        retranslateUi(Config);
        QObject::connect(halo, SIGNAL(toggled(bool)), shadowColor, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(4);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QWidget *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "Bespin KWin Client Config", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Config", "Classes", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Config", "Base", 0, QApplication::UnicodeUTF8));
        actGrad->clear();
        actGrad->insertItems(0, QStringList()
         << QApplication::translate("Config", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Button", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Sunken", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Gloss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Glass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Cloudy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Shiny", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Flat", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Vertical gradient", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Horizontal gradient", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("Config", "Deco", 0, QApplication::UnicodeUTF8));
        actGrad2->clear();
        actGrad2->insertItems(0, QStringList()
         << QApplication::translate("Config", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Button", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Sunken", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Gloss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Glass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Cloudy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Shiny", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("Config", "Label", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Config", "Buttons", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("Config", "Active", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Config", "Base", 0, QApplication::UnicodeUTF8));
        inactGrad->clear();
        inactGrad->insertItems(0, QStringList()
         << QApplication::translate("Config", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Button", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Sunken", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Gloss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Glass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Cloudy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Shiny", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Flat", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Vertical gradient", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Horizontal gradient", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("Config", "Deco", 0, QApplication::UnicodeUTF8));
        inactGrad2->clear();
        inactGrad2->insertItems(0, QStringList()
         << QApplication::translate("Config", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Button", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Sunken", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Gloss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Glass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Cloudy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Shiny", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("Config", "Label", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Config", "Buttons", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("Config", "Inactive", 0, QApplication::UnicodeUTF8));
        newPreset->setText(QApplication::translate("Config", "New", 0, QApplication::UnicodeUTF8));
        deletePreset->setText(QApplication::translate("Config", "Delete", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Config", "Types", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Config", "Style", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Config", "Icons", 0, QApplication::UnicodeUTF8));
        iconVariant->clear();
        iconVariant->insertItems(0, QStringList()
         << QApplication::translate("Config", "Square (1st gen)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Round (2nd gen)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "TheRob (3rd gen)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "LasseKongo (nogen)", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("Config", "Unhovered button", 0, QApplication::UnicodeUTF8));
        slickButtons->clear();
        slickButtons->insertItems(0, QStringList()
         << QApplication::translate("Config", "Scaled icons", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Dots", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Bricks", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("Config", "Multibutton order", 0, QApplication::UnicodeUTF8));
        buttonGradient->clear();
        buttonGradient->insertItems(0, QStringList()
         << QApplication::translate("Config", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Button", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Sunken", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Gloss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Glass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Cloudy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Config", "Shiny", 0, QApplication::UnicodeUTF8)
        );
        label_17->setText(QApplication::translate("Config", "Gradient", 0, QApplication::UnicodeUTF8));
        inactiveButtons->setText(QApplication::translate("Config", "Show Icons on inactive windows", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Seite_2), QApplication::translate("Config", "Buttons", 0, QApplication::UnicodeUTF8));
        roundCorners->setText(QApplication::translate("Config", "Round window corners", 0, QApplication::UnicodeUTF8));
        verticalTitlebar->setText(QApplication::translate("Config", "Netbook compatible titlebar orientation ;-)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Config", "Title alignment", 0, QApplication::UnicodeUTF8));
        titleLeft->setText(QString());
        titleCenter->setText(QString());
        titleRight->setText(QString());
        label_5->setText(QApplication::translate("Config", "Titlebar padding", 0, QApplication::UnicodeUTF8));
        titlePadding->setSuffix(QApplication::translate("Config", "px", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("Config", "Border widths", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("Config", "Edges", 0, QApplication::UnicodeUTF8));
        baseSize->setSuffix(QApplication::translate("Config", "px", 0, QApplication::UnicodeUTF8));
        edgeSize->setSuffix(QApplication::translate("Config", "px", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("Config", "Base", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Config", "Force small titlebar for", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Seite), QApplication::translate("Config", "Layout", 0, QApplication::UnicodeUTF8));
        trimmTitle->setText(QApplication::translate("Config", "Trimm title", 0, QApplication::UnicodeUTF8));
        resizeCorner->setText(QApplication::translate("Config", "Show resize grip", 0, QApplication::UnicodeUTF8));
        forceUserColors->setText(QApplication::translate("Config", "Ignore style hints from the (Bespin) widget style", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Config", "Tricks", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("Config", "Inactive windows", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("Config", "Active windows", 0, QApplication::UnicodeUTF8));
        halo->setText(QApplication::translate("Config", "Halo", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Config", "Shadows", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
