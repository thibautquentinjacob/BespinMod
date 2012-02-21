/* Bespin widget style for Qt4
Copyright (C) 2007 Thomas Luebking <thomas.luebking@web.de>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License version 2 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QDir>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QSettings>
#include <QStyleFactory>
#include <QTimer>
// #include <QDialogButtonBox>
// #include <QInputDialog>
// #include <QMessageBox>
#include <QPainter>
#include <QProcess>
#include <QValidator>

#include "kdeini.h"
#include "../config.defaults"
#include "config.h"

typedef QMap<QString,QString> StringMap;

/** This function declares the kstyle config plugin, you may need to adjust it
for other plugins or won't need it at all, if you're not interested in a plugin */
extern "C"
{
    Q_DECL_EXPORT QWidget* allocate_kstyle_config(QWidget* parent)
    {
        /**Create our config dialog and reply it as plugin
        This is slightly different from the setup in a standalone dialog at the
        bottom of this file*/
        return new Config(parent);
    }
}

/** Gradient enumeration for the comboboxes, so that i don't have to handle the
integers - not of interest for you*/
namespace Gradients {
    enum Type {
        None = 0, Simple, Button, Sunken, Gloss, Glass, Metal, Cloudy, Shiny, //RadialGloss,
        TypeAmount
    };
    enum BgMode { BevelV = 2, BevelH };
}

static const char* defInfo1 =
"<b>Bespin Style</b><hr>\
<p>\
&copy;&nbsp;2006-2009 by Thomas L&uuml;bking<br>\
Includes Design Ideas by\
<ul type=\"disc\">\
<li>Nuno Pinheiro</li>\
<li>David Vignoni</li>\
<li>Kenneth Wimer</li>\
</ul>\
</p>\
<hr>\
Visit <a href=\"http://cloudcity.sourceforge.net\">CloudCity.SourceForge.Net</a>";

#if 0
static const char* defInfo2 =
"<div align=\"center\">\
<img src=\":/bespin.png\"/><br>\
<a href=\"http://cloudcity.sourceforge.net\">CloudCity.SourceForge.Net</a>\
</div>";


static const char* defInfo3 =
"<div align=\"center\">\
<img src=\":/bespin.png\"/><br>\
<a href=\"http://cloudcity.sourceforge.net\">CloudCity.SourceForge.Net</a>\
</div>\
<h2>Warning!</h2>\
<p>\
Activating these hacks...\
</p>\
";
#endif

/** Intenal class for the PW Char entry - not of interest */

static ushort unicode(const QString &string)
{
    if (string.length() == 1)
        return string.at(0).unicode();
    uint n = string.toUShort();
    if (!n)
        n = string.toUShort(0,16);
    if (!n)
        n = string.toUShort(0,8);
    return n;
}

class UniCharValidator : public QValidator {
public:
    UniCharValidator( QObject * parent ) : QValidator(parent){}
    virtual State validate ( QString & input, int & ) const
    {
        if (input.length() == 0)
            return Intermediate;
        if (input.length() == 1)
            return Acceptable;
        if (input.length() == 2 && input.at(0) == '0' && input.at(1).toLower() == 'x')
            return Intermediate;
        if (unicode(input))
            return Acceptable;
        return Invalid;
    }
};

/** The Constructor - your first job! */
Config::Config(QWidget *parent) : BConfig(parent), loadedPal(0), infoIsManage(false)
{
    /** Setup the UI and geometry */
    ui.setupUi(this);

    /** Some special stuff */
    QEvent event(QEvent::PaletteChange);
    changeEvent(&event);
    ui.info->setOpenExternalLinks( true ); /** i've an internet link here */

    const QPalette::ColorGroup groups[3] = { QPalette::Active, QPalette::Inactive, QPalette::Disabled };
    ui.info->viewport()->setAutoFillBackground(false);
    QPalette pal = ui.info->palette();
    for (int i = 0; i < 3; ++i)
    {
        pal.setColor(groups[i], QPalette::Base, pal.color(groups[i], QPalette::Window));
        pal.setColor(groups[i], QPalette::Text, pal.color(groups[i], QPalette::WindowText));
    }
    ui.info->setPalette(pal);

    ui.logo->setMargin(9);

    ui.sectionSelect->viewport()->setAutoFillBackground(false);
    pal = ui.sectionSelect->palette();
    for (int i = 0; i < 3; ++i)
    {
        pal.setColor(groups[i], QPalette::Base, pal.color(groups[i], QPalette::Window));
        pal.setColor(groups[i], QPalette::Text, pal.color(groups[i], QPalette::WindowText));
    }
    ui.sectionSelect->setPalette(pal);

    connect (ui.sectionSelect, SIGNAL(currentRowChanged(int)),
                ui.sections, SLOT(setCurrentIndex(int)));
    connect (ui.sectionSelect, SIGNAL(currentTextChanged(const QString &)),
                this, SLOT(setHeader(const QString &)));
    connect (ui.sections, SIGNAL(currentChanged(int)), this, SLOT(reloadColorRoles()));

    /** Prepare the settings store, not of interest */
    StringMap presetMap;
    QSettings settings("Bespin", "Store");
    QString preset;
    foreach (preset, settings.childGroups())
        if ( !preset.startsWith("__") )
            presetMap.insert(preset, "");
    QSettings settings2("Bespin", "Style");
    settings2.beginGroup("PresetApps");
    StringMap::iterator entry;
    foreach (QString appName, settings2.childKeys())
    {
        preset = settings2.value(appName, QString()).toString();
        entry = presetMap.find(preset);
        if (entry != presetMap.end())
        {
            if (!entry.value().isEmpty())
                entry.value() += ", ";
            entry.value() += appName;
        }
    }
    QTreeWidgetItem *item;
    for (entry = presetMap.begin(); entry != presetMap.end(); ++entry)
    {
        item = new QTreeWidgetItem(QStringList() << entry.key() << entry.value());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        ui.store->addTopLevelItem(item);
    }
//    ui.store->addItems( settings.childGroups() );
    ui.store->sortItems(0, Qt::AscendingOrder);
    ui.btnStore->setAutoDefault ( false );
    ui.btnRestore->setAutoDefault ( false );
    ui.btnImport->setAutoDefault ( false );
    ui.btnExport->setAutoDefault ( false );
    ui.btnDelete->setAutoDefault ( false );
    connect (ui.store, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(presetAppsChanged(QTreeWidgetItem *, int)));
    connect (ui.btnStore, SIGNAL(clicked()), this, SLOT(store()));
    connect (ui.btnRestore, SIGNAL(clicked()), this, SLOT(restore()));
    connect (ui.store, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
                this, SLOT(restore(QTreeWidgetItem*, int)));
    connect (ui.btnImport, SIGNAL(clicked()), this, SLOT(import()));
    connect (ui.btnExport, SIGNAL(clicked()), this, SLOT(saveAs()));
    connect (ui.store, SIGNAL(currentItemChanged( QTreeWidgetItem *, QTreeWidgetItem *)),
                this, SLOT(storedSettigSelected(QTreeWidgetItem *)));
    connect (ui.btnDelete, SIGNAL(clicked()), this, SLOT(remove()));
    connect (ui.presetFilter, SIGNAL(textChanged (const QString &)), this, SLOT(filterPresets(const QString &)));
    ui.btnRestore->setEnabled(false);
    ui.btnExport->setEnabled(false);
    ui.btnDelete->setEnabled(false);
    ui.storeLine->hide();

    /** set up color page, not of interest */
    QColorDialog *cd = new QColorDialog(this);
    cd->hide();
    connect ( ui.colorButton, SIGNAL(clicked()), cd, SLOT(show()) );
    connect ( ui.colorButton, SIGNAL(clicked()), cd, SLOT(raise()) );
    ui.role_window->installEventFilter(this);
    ui.role_windowText->installEventFilter(this);
    ui.role_button->installEventFilter(this);
    ui.role_buttonText->installEventFilter(this);
    ui.role_base->installEventFilter(this);
    ui.role_text->installEventFilter(this);
    ui.role_highlight->installEventFilter(this);
    ui.role_highlightedText->installEventFilter(this);
    QTimer::singleShot( 50, this, SLOT(initColors()) );

    /** fill some comboboxes, not of interest */

    generateGradientTypes(ui.uno_gradient);
    generateGradientTypes(ui.gradButton);
    generateGradientTypes(ui.toolbuttonGradient);
    generateGradientTypes(ui.gradChoose);
    generateGradientTypes(ui.gradMenuItem);
    generateGradientTypes(ui.gradProgress);
    generateGradientTypes(ui.gradTab);
    generateGradientTypes(ui.gradScroll);
    generateGradientTypes(ui.headerGradient);
    generateGradientTypes(ui.headerSortingGradient);
    generateGradientTypes(ui.kwinInactiveGrad);
    generateGradientTypes(ui.kwinActiveGrad);

    QSettings csettings("Bespin", "Config");
    QStringList strList = csettings.value ( "UserPwChars", QStringList() ).toStringList();
    ushort n;
    foreach (QString str, strList)
    {
        n = str.toUShort(0,16);
        if (n)
            ui.pwEchoChar->addItem(QChar(n), n);
    }
    strList.clear();
    ui.pwEchoChar->addItem(QChar(0x26AB), 0x26AB);
    ui.pwEchoChar->addItem(QChar(0x2022), 0x2022);
    ui.pwEchoChar->addItem(QChar(0x2055), 0x2055);
    ui.pwEchoChar->addItem(QChar(0x220E), 0x220E);
    ui.pwEchoChar->addItem(QChar(0x224E), 0x224E);
    ui.pwEchoChar->addItem(QChar(0x25AA), 0x25AA);
    ui.pwEchoChar->addItem(QChar(0x25AC), 0x25AC);
    ui.pwEchoChar->addItem(QChar(0x25AC), 0x25AC);
    ui.pwEchoChar->addItem(QChar(0x25A0), 0x25A0);
    ui.pwEchoChar->addItem(QChar(0x25CF), 0x25CF);
    ui.pwEchoChar->addItem(QChar(0x2605), 0x2605);
    ui.pwEchoChar->addItem(QChar(0x2613), 0x2613);
    ui.pwEchoChar->addItem(QChar(0x26A1), 0x26A1);
    ui.pwEchoChar->addItem(QChar(0x2717), 0x2717);
    ui.pwEchoChar->addItem(QChar(0x2726), 0x2726);
    ui.pwEchoChar->addItem(QChar(0x2756), 0x2756);
    ui.pwEchoChar->addItem(QChar(0x2756), 0x2756);
    ui.pwEchoChar->addItem(QChar(0x27A4), 0x27A4);
    ui.pwEchoChar->addItem(QChar(0xa4), 0xa4);
    ui.pwEchoChar->addItem("|", '|');
    ui.pwEchoChar->addItem(":", ':');
    ui.pwEchoChar->addItem("*", '*');
    ui.pwEchoChar->addItem("#", '#');
    ui.pwEchoChar->lineEdit()-> setValidator(new UniCharValidator(ui.pwEchoChar->lineEdit()));
    connect (ui.pwEchoChar->lineEdit(), SIGNAL(returnPressed()), this, SLOT (learnPwChar()));
    ui.pwEchoChar->setInsertPolicy(QComboBox::NoInsert);

    /** connection between the bgmode and the structure combo - not of interest*/
    connect(ui.bgMode, SIGNAL(currentIndexChanged(int)), this, SLOT(handleBgMode(int)));
    connect(ui.sliderGroove, SIGNAL(valueChanged(int)), this, SLOT(handleGrooveMode(int)));

    /** 1. name the info browser, you'll need it to show up context help
    Can be any QTextBrowser on your UI form */
    setInfoBrowser(ui.info);
    /** 2. Define a context info that is displayed when no other context help is demanded */
    setDefaultContextInfo(defInfo1);

    /** handleSettings(.) tells BConfig to take care (save/load) of a widget
    In this case "ui.bgMode" is the widget on the form,
    "BackgroundMode" specifies the entry in the ini style config file and
    "3" is the default value for this entry*/
    handleSettings(ui.bgMode, BG_MODE);
    handleSettings(ui.bgIntensity, BG_INTENSITY);
    handleSettings(ui.ringOverlay, BG_RING_OVERLAY);
#if BESPIN_ARGB_WINDOWS
    handleSettings(ui.argbOpacity, BG_OPACITY);
    setContextHelp(ui.argbSupport, "<b>Window Opacity</b><hr>\
    Yes, it means you can have translucent windows, BUT:<br>\
    - It's highly experimental<br>\
    - Setting opacity < 255 will likely impact performance<br>\
    - You need a running COMPOSITE manager<br>\
    - And that's currently not tested at runtime");
    handleSettings(ui.argbBlacklist, ARGB_BLACKLIST);
    setContextHelp(ui.argbBlacklist, "<b>Blacklist</b><hr>\
    Some apps just don't work too god with this. Add them to a comma separated list here.");
    handleSettings(ui.argbGlassy, ARGB_GLASSY);
    handleSettings(ui.argbBlur, ARGB_BLUR);
#else
    ui.windowSettings->removeItem( ui.windowSettings->indexOf( ui.argbSupport ) );
    ui.argbSupport->hide();
    ui.popup_ARGB->hide();
#endif
    handleSettings(ui.fadeInactive, FADE_INACTIVE);
    handleSettings(ui.structure, BG_STRUCTURE);
    handleSettings(ui.modalGlas, BG_MODAL_GLASSY);
    handleSettings(ui.modalOpacity, BG_MODAL_OPACITY);
    handleSettings(ui.modalInvert, BG_MODAL_INVERT);
    handleSettings(ui.tooltipRole, BG_TOOLTIP_ROLE);
    handleSettings(ui.groupBoxMode, GROUP_BOX_MODE);
    handleSettings(ui.titleShadow, SHADOW_TITLEBAR);

    handleSettings(ui.uno, UNO_UNO);
    handleSettings(ui.uno_toolbars, UNO_TOOLBAR);
    handleSettings(ui.uno_title, UNO_TITLE);
    handleSettings(ui.uno_gradient, UNO_GRADIENT);
    handleSettings(ui.uno_role, UNO_ROLE);
    handleSettings(ui.uno_sunken, UNO_SUNKEN);

    handleSettings(ui.sunkenButtons, BTN_LAYER);
    handleSettings(ui.checkMark, BTN_CHECKTYPE);
    handleSettings(ui.cushion, BTN_CUSHION);
    handleSettings(ui.fullButtonHover, BTN_FULLHOVER);
    handleSettings(ui.gradButton, BTN_GRADIENT);
    handleSettings(ui.btnRole, BTN_ROLE);
    handleSettings(ui.btnActiveRole, BTN_ACTIVEROLE);
    handleSettings(ui.ambientLight, BTN_AMBIENTLIGHT);
    handleSettings(ui.backlightHover, BTN_BACKLIGHTHOVER);
    handleSettings(ui.btnRound, BTN_ROUND);
    handleSettings(ui.btnBevelEnds, BTN_BEVEL_ENDS);
    handleSettings(ui.btnMinHeight, BTN_MIN_HEIGHT);

    handleSettings(ui.connectedToolbuttons, BTN_CONNECTED_TOOLS);
    handleSettings(ui.toolbuttonLayer, BTN_SUNKEN_TOOLS);
    handleSettings(ui.toolbuttonRole, BTN_TOOL_ROLE);
    handleSettings(ui.toolbuttonActiveRole, BTN_TOOL_ACTIVEROLE);
    handleSettings(ui.toolbuttonGradient, BTN_TOOL_GRADIENT);
    handleSettings(ui.toolbuttonSeparator, BTN_TOOL_SEPARATOR);
    handleSettings(ui.disabledToolbuttonStyle, BTN_DISABLED_TOOLS);
    setContextHelp(ui.disabledToolbuttonStyle, "<b>Disabled Toolbuttons</b><hr>\
    Qt has a \"standard\" way to gray out disabled toolbuttons, which can be altered by the style.\
    KDE provides several FX on icons to indicate disabled (tool)buttons but those won't apply to\
    Qt-only applications.<br>\
    As KDE for a while ignored it's own settings as well, i started to override the disabled\
    appereance and while at it introduced blurring ;-P<br>\
    Now that KDE actually allows me again to choose an effect, you can select to leave the icon FX\
    untouched (what will result in different disabled looks for Qt and KDE applications), force the\
    Qt desaturation or the former Bespin (forced - sorry everyone) blurring.");

    handleSettings(ui.chooserLayer, CHOOSER_LAYER);
    setContextHelp(ui.chooserLayer, "<b>Combobox layers</b><hr>\
    I guess it's been enough time. Whoever really <b>must</b> make comboboxes look like pushbuttons\
    may now do so.<br>;-)<br>\
    The main reason for this is that you likely want to use inlay combos with inlay buttons since\
    the latter currently enforce a frameless hover animation.");
    handleSettings(ui.gradChoose, CHOOSER_GRADIENT);

    handleSettings(ui.pwEchoChar, INPUT_PWECHOCHAR);

    handleSettings(ui.showMnemonics, SHOW_MNEMONIC);
    handleSettings(ui.leftHanded, LEFTHANDED);
    handleSettings(ui.macStyle, MACSTYLE);
    handleSettings(ui.dialogBtnLayout, DIALOG_BTN_LAYOUT);
    setContextHelp(ui.dialogBtnLayout, "<b>Dialog button layout</b><hr>\
    This controls the order of the Yes/No/Cancel buttons, use with care, you might accidently\
    misclick if you revert it from e.g. KDE to OS X");

    handleSettings(ui.drawSplitters, DRAW_SPLITTERS);
    setContextHelp(ui.drawSplitters, "<b>Draw Splitters</b><hr>\
    The things that allow you to adjust the layout in some windows (dolphin, amarok, many ... :)<br>\
    Warning: Unchecking this will result in VERY thin splitters (2px) - while they look slick, they're also\
    harder to hit. Test yoursef...");

    handleSettings(ui.crMenuActive, MENU_ACTIVEROLE);
    handleSettings(ui.menuRound, MENU_ROUND);
    handleSettings(ui.menuRoundSelect, "Menu.RoundSelect", true);
    handleSettings(ui.menuGlas, MENU_GLASSY);
    handleSettings(ui.gradMenuItem, MENU_ITEMGRADIENT);
    handleSettings(ui.showMenuIcons, MENU_SHOWICONS);
    handleSettings(ui.menuShadow, MENU_SHADOW); // false, i have a compmgr running :P
    handleSettings(ui.menuOpacity, MENU_OPACITY);
    handleSettings(ui.crPopup, MENU_ROLE);
    handleSettings(ui.menuBoldText, MENU_BOLDTEXT);
    handleSettings(ui.menuActiveItemSunken, MENU_ACTIVEITEMSUNKEN);

    handleSettings(ui.gradProgress, PROGRESS_GRADIENT);
    handleSettings(ui.crProgressBg, PROGRESS_ROLE_BG);
    handleSettings(ui.crProgressFg, PROGRESS_ROLE_FG);

    handleSettings(ui.showScrollButtons, SCROLL_SHOWBUTTONS);
    handleSettings(ui.fullScrollHover, SCROLL_FULLHOVER);
    setContextHelp(ui.fullScrollHover, "<b>Frameless hovering</b><hr>\
    This used to be bound to the corresponding setting for Pushbuttons, but i figured that i wanted them framed\
    regardless of the pushbutton behaviour, just looks much better ...");
    handleSettings(ui.sliderGroove, SCROLL_GROOVE);
    handleSettings(ui.showOff, SHOW_OFF);
    setContextHelp(ui.showOff, "<b>Show Off</b><hr>\
    This used to be a hidden setting i used for showing off only. It will allocate vertical gradients\
    for vertical sliders.<br>\
    Be warned that there can end up being many (since the slider lenths tend to vary). The cache is\
    a limited FIFO and the gradients are handled sloppy (The bigger they become the bigger grows the\
    cluster) but this is still no cheap setting. <br>\
    However in times where 8GB RAM and 1GB VRAM become common - who cares ;-)<br>\
    (It's by far not that much, every Web 2.0 page is worse by the order of *some* magnitutes)");
    handleSettings(ui.gradScroll, SCROLL_GRADIENT);
    handleSettings(ui.invertGroove, SCROLL_INVERT_BG);
    handleSettings(ui.sliderWidth, SCROLL_SLIDER_WIDTH);
    // THIS MUST! happen after the buttons are loaded!
    handleSettings(ui.scrollRole, "Scroll.Role", QPalette::Button);
    handleSettings(ui.scrollActiveRole, "Scroll.ActiveRole", QPalette::Highlight);

    handleSettings(ui.shadowIntensity, SHADOW_INTENSITY);

    handleSettings(ui.crTabBarActive, TAB_ACTIVEROLE);
    handleSettings(ui.tabAnimDuration, TAB_DURATION);
    handleSettings(ui.gradTab, TAB_GRADIENT);
    handleSettings(ui.crTabBar, TAB_ROLE);
    handleSettings(ui.tabTransition, TAB_TRANSITION);
    handleSettings(ui.activeTabSunken, TAB_ACTIVETABSUNKEN);

    handleSettings(ui.headerRole, VIEW_HEADERROLE);
    handleSettings(ui.headerSortingRole, VIEW_SORTINGHEADERROLE);
    handleSettings(ui.headerGradient, VIEW_HEADERGRADIENT);
    handleSettings(ui.headerSortingGradient, VIEW_SORTINGHEADERGRADIENT);
    handleSettings(ui.viewShadingRole, VIEW_SHADE_ROLE);
    handleSettings(ui.viewShadeLevel, VIEW_SHADE_LEVEL);

    handleSettings(ui.kwinActiveGrad, KWIN_ACTIVE_GRADIENT);
    handleSettings(ui.kwinInactiveGrad, KWIN_INACTIVE_GRADIENT);
    handleSettings(ui.kwinActiveRole, KWIN_ACTIVE_ROLE);
    handleSettings(ui.kwinInactiveRole, KWIN_INACTIVE_ROLE);
    handleSettings(ui.kwinActiveText, KWIN_ACTIVE_TEXT_ROLE);
    handleSettings(ui.kwinInactiveText, KWIN_INACTIVE_TEXT_ROLE);

    handleSettings(ui.amarokViews, HACK_AMAROK_VIEWS);
    setContextHelp(ui.amarokViews, "<b>Amarok... again ;-)</b><hr>\
    Amarok has a \"nice\" attitude to <u>force</u> it's playlist and other views in the window background color.<br>\
    Not only does this maybe look strange, but it's also badly implemented, breaking certain color combinations.<br>\
    (To be fair: it's by far not the only program with this broken approach...)<br>\
    This setting allows to \"normalize\" the views (including a sunken frame) ...<br>\
    PS: there <u>is</u> a pending merge request to at least fix the bad implementation and\
    i've actually noted this for the first time in 2007 or 2008... ;-P");

    handleSettings(ui.hackFixGwenview, HACK_FIX_GWENVIEW);
    setContextHelp(ui.hackFixGwenview, "<b>Gwenview's Thumbview</b><hr>\
    There are two major issues with the thumbnail browsing in Gwenview.\
    <ol><li>It scrolls 3 lines on one wheel event and you waste time on redetecting context</li>\
    <li>It moves to another (upper) position when you leave the image view</li></ol>\
    If those were bugs, one could easily fix them, but they exists ever since...<br>\
    So you can fix them here >-)");

    handleSettings(ui.hackDolphinUrl, HACK_DOLPHIN_URLBAR);
    setContextHelp(ui.hackDolphinUrl, "<b>Dolphin's URL Navigator</b><hr>\
    Invert colors, paint a TabBar-a-like frame and remove the location icon...");

    handleSettings(ui.hackDolphinIconViews, HACK_DOLPHIN_ICONVIEWS);
    setContextHelp(ui.hackDolphinIconViews, "<b>Dolphin Iconviews</b><hr>\
    The three items for a unity when eg. splitting the view, but this is not reflected visually what\
    leads to \"disalignment\"");

    handleSettings(ui.dolphinViews, HACK_DOLPHIN_VIEWS);
    setContextHelp(ui.dolphinViews, "<b>Dolphin sidebar</b><hr>\
    Dolphin sets some views in the sidebars to look like the window - check this to force a\
    \"traditional\" appearance.<br>(Sunken frame, Base colored background)");

    handleSettings(ui.placesViews, HACK_PLACES_VIEWS);
    setContextHelp(ui.placesViews, "<b>Places selectors</b><hr>\
    The PlacesView also used in Dolphin appears in virtually all filedialogs and probably\
    some other places...<br>\
    Check this to hit them all");

    handleSettings(ui.kmailFolderList, HACK_KMAIL_FOLDERS);
    setContextHelp(ui.kmailFolderList, "<b>KMail's Folder list</b><hr>\
    A bit more like Apple mail - the reasons:<br>\
    * There's usually only one column (did you know you can have more?) so the alternating\
    row style is way too much.<br>\
    * For the same reason the header is superflous<br>\
    * Did you know you can have bigger icons?<br>\
    * For this usecase one can drop the decoration (arrows) of the root element (un/collapsing \
    still works by double clicking the item)<br>\
    * as a minor fix the column autoexpands (would stretch the header, now affects the section)");

    setContextHelp(ui.konsoleScanlines, "<b>Konsole scanlines</b><hr>Since konsole support wallpapers again, use that. It's more flexible, efficient and nicer that plaing with the paint mode and drawing lines by line.");

    handleSettings(ui.kTitleWidgets, HACK_TITLE_WIDGET);
    setContextHelp(ui.kTitleWidgets, "<b>KTitleWidget</b><hr>I'd' like my headers inverted and center aligned...");

    handleSettings(ui.hackMessages, HACK_MESSAGES);
    setContextHelp(ui.hackMessages, "<b>Messageboxes</b><hr>\
    Overwrites the painting routines of QMessageBoxes for a custom appereance.<br>\
    Also removes the Window decoration but allows you to drag around the window by\
    clicking anywhere.");

    handleSettings(ui.hackKHtml, HACK_KHTMLVIEW);
    setContextHelp(ui.hackKHtml, "<b>Konqueror HTML window</b><hr>\
    By default, Konquerors HTML view has no frame around, but you may force a sunken\
    frame here.<br>\
    Notice that this may have a bad impact on scroll performance, especially if you\
    lack HW alpha blending.");

    handleSettings(ui.hackWindowMove, HACK_WINDOWMOVE);
    setContextHelp(ui.hackWindowMove, "<b>Easy Window Draging</b><hr>\
    Usually you'll have to hit the titlebar in order to drag around a window.<br>\
    This one allows you to drag the window by clicking many empty spaces.<br>\
    Currently supported items:<br>\
    - Dialogs<br>\
    - Menubars<br>\
    - Toolbars (including disabled buttons)<br>\
    - Docks<br>\
    - Groupboxers<br>\
    - Mainwindows<br>\
    - Statusbars<br>\
    - SMPlayer/DragonPlayer Video areas<br>");

    handleSettings(ui.suspendFsVideoCompositing, HACK_SUSPEND_FULLSCREEN_PLAYERS);
    setContextHelp(ui.suspendFsVideoCompositing, "<b>Suspend Fullscreen Video Compositing</b><hr>\
    Compositing, esp. the OpenGL variant, can have a significant conversion overhead, depending\
    on the window size and the update frequency - unfortunately that especially holds for fullscreen\
    video playback, when often the CPU is worried with decoding an 1080p x264 video as well.<br>\
    This will catch some video clients when entering the fullscreen mode and disable compositing until\
    fullscreen mode exits.<br>\
    Will likely cause some temporarily flicker when entering/leaving the fullscreen mode but can safe a lot\
    of cpu when it really matters.");

    handleSettings(ui.killThrobber, HACK_THROBBER);
    setContextHelp(ui.killThrobber, "<b>Kill JarJar, err... Throbber</b><hr>\
    You see the nasty rotating thing in the top right of konqueror, now even oversizing the menubar?\
    Click here and you won't anymore >-P" );

    handleSettings(ui.hackTreeViews, HACK_TREEVIEWS);
    setContextHelp(ui.hackTreeViews, "<b>Animate TreeViwes</b><hr>\
    This is a plain vanilla Qt feature, but must be activated by developers for each\
    treeview in order to be used - can be cute, can be annoying: choose by yourself<br>\
    This way it's activated globally." );

    handleSettings(ui.lockToolbars, HACK_TOOLBAR_LOCKING);
    setContextHelp(ui.lockToolbars, "<b>Lock Toolbars</b><hr>\
    KDE toolbars allow you (among other) to lock their position, plain Qt Toolbars\
    (like in eg. arora) don't.<br>\
    This locks all Qt Toolbars and adds a config item, accessible by pressing CTRL\
    and rightclicking the Toolbar.");

    handleSettings(ui.lockDocks, HACK_DOCK_LOCKING);
    setContextHelp(ui.lockDocks, "<b>Lock Dockwidgets</b><hr>\
    Qt mainwindows provide a (quite ;-) powerfull way to arrange parts of the application\
    (like the sidebars in Dolphin or K3b) but while you can lock them in eg. Amarok or K3b,\
    they'll remain always movable in most other applications.<br>\
    Checking this will initially lock those docks and allow you to toggle them unlocked\
    by pressing CRTL+ALT+D.");

    /** setContextHelp(.) attaches a context help string to a widget on your form */
    setContextHelp(ui.btnRole, "<b>Button Colors</b><hr>\
    The default and the hovered color of a button.<br>\
    <b>Notice:</b> It's strongly suggested to select \"Button\" to\
    (at least and best excatly) one of the states!");

    setContextHelp(ui.btnActiveRole, "<b>Button Colors</b><hr>\
    The default and the hovered color of a button.<br>\
    <b>Notice:</b> It's strongly suggested to select \"Button\" to\
    (at least and best excatly) one of the states!");

    strList <<
        "<b>Plain (color)</b><hr>Select if you have a really lousy \
        machine or just hate structured backgrounds." <<

        "<b>Scanlines</b><hr>Wanna Aqua feeling?" <<

        "<b>Vertical Top/Bottom Gradient</b><hr>Simple gradient that brightens \
        on the upper and darkens on the lower end<br>(cheap, fallback suggestion 1)" <<

        "<b>Horizontal Left/Right Gradient</b><hr>Simple gradient that darkens \
        on left and right side." <<

        "<b>Vertical Center Gradient</b><hr>The window vertically brightens \
        to the center" <<

        "<b>Horizontal Center Gradient</b><hr>The window horizontally brightens \
        to the center (similar to Apples Brushed Metal, less cheap, \
        fallback suggestion 2)";

    /** if you call setContextHelp(.) with a combobox and pass a stringlist,
    the strings are attached to the combo entries and shown on select/hover */
    setContextHelp(ui.bgMode, strList);
    strList.clear();

    strList <<
        "<b>Jump</b><hr>No transition at all - fastest but looks stupid" <<
        "<b>ScanlineBlend</b><hr>Similar to CrossFade, but won't require Hardware acceleration." <<
        "<b>SlideIn</b><hr>The new tab falls down from top" <<
        "<b>SlideOut</b><hr>The new tab rises from bottom" <<
        "<b>RollIn</b><hr>The new tab appears from Top/Bottom to center" <<
        "<b>RollOut</b><hr>The new tab appears from Center to Top/Bottom" <<
        "<b>OpenVertically</b><hr>The <b>old</b> Tab slides <b>out</b> to Top and Bottom" <<
        "<b>CloseVertically</b><hr>The <b>new</b> Tab slides <b>in</b> from Top and Bottom" <<
        "<b>OpenHorizontally</b><hr>The <b>old</b> Tab slides <b>out</b> to Left and Right" <<
        "<b>CloseHorizontally</b><hr>The <b>new</b> Tab slides <b>in</b> from Left and Right" <<
        "<b>CrossFade</b><hr>What you would expect - one fades out while the other fades in.<br>\
        This is CPU hungry - better have GPU Hardware acceleration.";

    setContextHelp(ui.tabTransition, strList);

    setContextHelp(ui.store, "<b>Settings management</b><hr>\
                    <p>\
                    You can save your current settings (including colors from qconfig!) and\
                    restore them later here.\
                    </p><p>\
                    It's also possible to im and export settings from external files and share\
                    them with others.\
                    </p><p>\
                    You can also call the config dialog with the paramater \"demo\"\
                    <p><b>\
                    bespin demo [some style]\
                    </b></p>\
                    to test your settings on various widgets.\
                    </p><p>\
                    If you want to test settings before importing them, call\
                    <p><b>\
                    bespin try &lt;some_settings.conf&gt;\
                    </b></p>\
                    Installed presets can be referred by the BESPIN_PRESET environment variable\
                    <p><b>\
                    BESPIN_PRESET=\"Bos Taurus\" bespin demo\
                    </b></p>\
                    will run the Bespin demo widget with the \"Bos Taurus\" preset\
                    (this works - of course - with every Qt4 application,\
                    not only the bespin executable)\
                    </p>");

    setContextHelp(ui.pwEchoChar, "<b>Pasword Echo Character</b><hr>\
                    The character that is displayed instead of the real text when\
                    you enter e.g. a password.<br>\
                    You can enter any char or unicode number here.\
                    <b>Notice:</b> That not all fontsets may provide all unicode characters!");

    setContextHelp(ui.tabAnimDuration, "<b>Tab Transition Duration</b><hr>\
                    How long the transition lasts.");


    setContextHelp(ui.cushion, "<b>Cushion Mode</b><hr>\
                    By default, the buttons are kinda solid and will move towards\
                    the background when pressed.<br>\
                    If you check this, you'll get a more cushion kind look, i.e.\
                    the Button will be \"pressed in\"");

    setContextHelp(ui.ambientLight, "<b>Ambient Lightning</b><hr>\
                    Whether to paint a light reflex on the bottom right corner of\
                    Pushbuttons.<br>\
                    You can turn this off for artistic reasons or on bright color\
                    settings (to save some CPU cycles)");

    setContextHelp(ui.showScrollButtons, "<b>Show Scrollbar buttons</b><hr>\
                    Seriously, honestly: when do you ever use the buttons to move\
                    a scrollbar slider? (ok, notebooks don't have a mousewheel...)");

    setContextHelp(ui.crPopup, "<b>Popup Menu Role</b><hr>\
                    Choose anything you like (hint: saturated colors annoy me :)<br>\
                    The Text color is chosen automatically<br>\
                    Selected items are like selected menubar items if you choose \"Window\" here,\
                    otherwise they appear inverted");

    setContextHelp(ui.crMenuActive, "<b>Selected Menubar Item Role</b><hr>\
                    You may choose any role here<br>\
                    Select \"WindowText\" if you want inversion.<br>\
                    <b>Warning!</b><br>If you select \"Window\" here and \"None\" \
                    below, the hovering is hardly indicated!");

    setContextHelp(ui.menuBoldText, "<b>Rounded popup corners</b><hr>\
                    Round popup corners are nifty, but lame (Buhhh ;-P) compiz won't draw shadows\
                    then. So you can check them off here. (The proper solution to your problem was\
                    of course to use KWin... You GNOME guy! We hates thy GNOME guys. Really much =D");

    setContextHelp(ui.menuBoldText, "<b>Bold Menu Text</b><hr>\
                    Depending on your font this can be a good choice especially \
                    for bright text on dark backgrounds.");

    setContextHelp(ui.crTabBar, "<b>Tabbar Role</b><hr>\
                    The color of the tabbar background<br>\
                    The Text color is chosen automatically");

    setContextHelp(ui.crTabBarActive, "<b>Tabbar Active Item Role</b><hr>\
                    The color of the hovered or selected tab<br>\
                    The Text color is chosen automatically");

    setContextHelp(ui.fullButtonHover, "<b>Fully filled hovered buttons</b><hr>\
                    This is especially a good idea if the contrast between the\
                    button and Window color is low and also looks ok with Glass/Gloss\
                    gradient settings - but may be toggled whenever you want");

    setContextHelp(ui.leftHanded, "<b>Are you a Flanders?</b><hr>\
                    Some people (\"Lefties\") prefer a reverse orientation of eg.\
                    Comboboxes or Spinboxes.<br>\
                    If you are a Flanders, check this - maybe you like it.<br>\
                    (Not exported from presets)");

    setContextHelp(ui.macStyle, "<b>Mac Style Behaviour</b><hr>\
                    This currently affects the appereance of Wizzards and allows\
                    you to activate items with a SINGLE mouseclick, rather than\
                    the M$ DOUBLEclick thing ;)<br>\
                    (Not exported from presets)");


    /** setQSetting(.) tells BConfig to store values at
    "Company, Application, Group" - these strings are passed to QSettings */
    setQSetting("Bespin", "Style", "Style");

    /** you can call loadSettings() whenever you want, but (obviously)
    only items that have been propagated with handleSettings(.) are handled !!*/
    loadSettings();

    ui.sections->setCurrentIndex(0);

    /** ===========================================
    You're pretty much done here - simple eh? ;)
        The following code reimplemets some BConfig functions
    (mainly to manage Qt color setttings)

    if you want a standalone app you may want to check the main() funtion
    at the end of this file as well - but there's nothing special about it...
        =========================================== */
}

void
Config::initColors()
{
    setColorsFromPalette( QApplication::palette() );
}

void
Config::changeEvent(QEvent *event)
{
    if (event->type() != QEvent::PaletteChange)
        return;

    myColorsHaveChanged = true;
    reloadColorRoles();

    const int s = 32;
    QPixmap logo(s*4,s*4);
    QPainterPath path;
    path.moveTo(logo.rect().center());
    path.arcTo(logo.rect(), 90, 270);
    path.lineTo(logo.rect().right(), logo.rect().y()+4*s/3);
    path.lineTo(logo.rect().right()-s, logo.rect().y()+4*s/3);
    path.lineTo(logo.rect().center().x() + s/2, logo.rect().center().y());
    path.lineTo(logo.rect().center());
    path.closeSubpath();
    path.addEllipse(logo.rect().right()-3*s/2, logo.rect().y(), s, s);
    logo.fill(Qt::transparent);
    QColor c = palette().color(foregroundRole());
    c.setAlpha(180);
    QPainter p(&logo);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(c);
    p.setPen(Qt::NoPen);
    p.drawPath(path);
    p.end();
    ui.logo->setPixmap(logo);
}

bool
Config::eventFilter( QObject *o, QEvent *e )
{
    if ( e->type() == QEvent::DragEnter )
    {
        QDropEvent *de = static_cast<QDragMoveEvent*>(e);
        if (de->mimeData()->hasColor())
            de->accept();
        else
            de->ignore();
        return false;
    }
    if ( e->type() == QEvent::Drop )
    {
        QDropEvent *de = static_cast<QDropEvent*>(e);
        if (de->mimeData()->hasColor())
        {
            QColor c = qvariant_cast<QColor>(de->mimeData()->colorData());
            QWidget *w = static_cast<QWidget*>(o);
            QPalette pal = w->palette();
            bool fg = false;
            QWidget *counter = 0L;
            if ( w == ui.role_window ) counter = ui.role_windowText;
            else if ( w == ui.role_button ) counter = ui.role_buttonText;
            else if ( w == ui.role_base ) counter = ui.role_text;
            else if ( w == ui.role_highlight ) counter = ui.role_highlightedText;
            else if ( (fg = (w == ui.role_windowText)) ) counter = ui.role_window;
            else if ( (fg = (w == ui.role_buttonText)) ) counter = ui.role_button;
            else if ( (fg = (w == ui.role_text)) ) counter = ui.role_base;
            else if ( (fg = (w == ui.role_highlightedText)) ) counter = ui.role_highlight;
            else return false; // whatever this might be...

            pal.setColor( fg ? w->foregroundRole() : w->backgroundRole(), c );
            w->setPalette(pal);
            counter->setPalette(pal);
            // TODO this doesn't work (the app palette didn't change) - need to figure whether i want it to...
            // requires a palette in sync with the color dialog
//             myColorsHaveChanged = true;
            emit changed(true);
            emit changed();
        }
        return false;
    }
    return BConfig::eventFilter(o, e);
}


QStringList
Config::colors(const QPalette &pal, QPalette::ColorGroup group)
{
    QStringList list;
    for (int i = 0; i < QPalette::NColorRoles; i++)
        list << pal.color(group, (QPalette::ColorRole) i).name();
    return list;
}

void
Config::updatePalette(QPalette &pal, QPalette::ColorGroup group, const QStringList &list)
{
    int max = QPalette::NColorRoles;
    if (max > list.count())
    {
        qWarning("The demanded palette seems to be incomplete!");
        max = list.count();
    }
    for (int i = 0; i < max; i++)
        pal.setColor(group, (QPalette::ColorRole) i, list.at(i));
}

bool
Config::load(const QString &preset)
{
    QSettings store("Bespin", "Store");
    if (!store.childGroups().contains(preset))
        return false;
    store.beginGroup(preset);

    QSettings system("Bespin", "Style");
    system.beginGroup("Style");
    foreach (QString key, store.allKeys())
        if (key != "QPalette")
            system.setValue(key, store.value(key));
    system.endGroup();

    //NOTICE: we pass the loaded palette through ::updatePalette() to ensure
    // we'll get a complete palette for this Qt version as otherwise Qt will
    // fallback to the default palette... ===================================
    QPalette pal;
    store.beginGroup("QPalette");
    updatePalette(pal, QPalette::Active, store.value("active").toStringList());
    updatePalette(pal, QPalette::Inactive, store.value("inactive").toStringList());
    updatePalette(pal, QPalette::Disabled, store.value("disabled").toStringList());
    store.endGroup(); store.endGroup();
    savePalette(pal);
    return true;
}

static bool
blackListed(QString &key)
{
    return
        key.startsWith("Hack.") || // don't im/export hacks
//         key.startsWith("ARGB.") || // don't im/export ARGB stuff
        key.startsWith("App.") || // don't im/export app specific stuff
        key == "Bg.Opacity" || // or dimmed inactive wins
        key == "DialogButtonLayout" || // or OS conventions
        key == "FadeInactive" || // or dimmed inactive wins
        key == "Tab.Duration" || key == "Tab.Transition" || // or tab trans settings
        key == "MacStyle" || // or macfeeling
        key == "ShowMnemonic" || // or macfeeling
        key == "Menu.Opacity" || // or menu opacity (interferes with e.g. kwin/compiz)
        key == "LeftHanded" || // or flanders mode
        key == "Scroll.ShowButtons" || // or the scrollbar look
        key == "StoreName"; // finally don't im/export storename, are forcewise written
}

QString
Config::sImport(const QString &filename, bool override)
{
    if (!QFile::exists(filename))
        return QString();

    QSettings file(filename, QSettings::IniFormat);

    if (!file.childGroups().contains("BespinStyle"))
        return QString();

    file.beginGroup("BespinStyle");

    QString demandedName;
    QString storeName = demandedName = file.value("StoreName", "Imported").toString();

    QSettings store("Bespin", "Store");

    if (!override)
    {
        int i = 2;
        QStringList entries = store.childGroups();
        while (entries.contains(storeName))
            storeName = demandedName + '#' + QString::number(i++);
    }

    store.beginGroup(storeName);
    foreach (QString key, file.allKeys())
    {
        if (!blackListed(key))
            store.setValue(key, file.value(key));
    }

    store.endGroup();
    file.endGroup();
    return storeName;
}

bool
Config::sExport(const QString &preset, const QString &filename)
{
    QSettings store("Bespin", "Store");
    if (!store.childGroups().contains(preset))
        return false;
    store.beginGroup(preset);

    QSettings file(filename, QSettings::IniFormat);
    file.beginGroup("BespinStyle");

    file.setValue("StoreName", preset);
    foreach (QString key, store.allKeys())
    {
        if (!blackListed(key))
            file.setValue(key, store.value(key));
    }
    store.endGroup();
    file.endGroup();
    return true;
}

/** reimplemented - i just want to extract the data from the store */
static QString lastPath = QDir::home().path();

void
Config::saveAs()
{
    if (!ui.store->currentItem())
        return;

    QString filename = QFileDialog::getSaveFileName(parentWidget(), tr("Save Configuration"),
                                                    lastPath, tr("Config Files (*.bespin *.conf *.ini)"));
    sExport(ui.store->currentItem()->text(0), filename);
}

/** reimplemented - i just want to merge the data into the store */
void
Config::import()
{
    QStringList filenames = QFileDialog::getOpenFileNames(parentWidget(),
        tr("Import Configuration"), lastPath, tr("Config Files (*.bespin *.conf *.ini)"));

    QTreeWidgetItem *item;
    foreach(QString filename, filenames)
    {
        QString storeName = sImport(filename);
        if (!storeName.isNull())
        {
            item = new QTreeWidgetItem(QStringList(storeName));
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
            ui.store->addTopLevelItem(item);
            ui.store->sortItems(0, Qt::AscendingOrder);
        }
    }
}


void
Config::presetAppsChanged(QTreeWidgetItem *changingItem, int idx)
{
    if (!changingItem || idx != 1)
        return;
    QStringList newApps = changingItem->text(1).split(',', QString::SkipEmptyParts);
    for (int i = 0; i < newApps.count(); ++i)
        newApps[i] = newApps[i].simplified();

    QTreeWidgetItem *item;
    const int cnt = ui.store->topLevelItemCount();
    for (int i = 0; i < cnt; ++i)
    {
        item = ui.store->topLevelItem(i);
        if (item == changingItem || item->text(1).isEmpty())
            continue;
        QStringList apps = item->text(1).split(',', QString::SkipEmptyParts);
        for (int i = 0; i < apps.count(); ++i)
            apps[i] = apps[i].simplified();
        foreach (QString newApp, newApps)
            apps.removeAll(newApp);
        item->setText(1, apps.join(", "));
    }
    emit changed(true);
    emit changed();
}

/** addition to the import functionality
1. we won't present a file dialog, but a listview
2. we wanna im/export the current palette as well
*/
void
Config::restore()
{
    restore(ui.store->currentItem(), 0);
}

class BStyle : public QStyle
{
    public:
        BStyle() : QStyle (){}
        virtual void init(const QSettings *settings) = 0;
};

void
Config::restore(QTreeWidgetItem *item, int col)
{
    if (col == 1)
    {
        ui.store->editItem( item, col );
        return;
    }
    setQSetting("Bespin", "Store", item->text(0));
    loadSettings(0, false, true);
    setQSetting("Bespin", "Style", "Style");

    /** import the color settings as well */
    if (!loadedPal)
        loadedPal = new QPalette;
    else
        emit changed(true); // we must update cause we loded probably different colors before

    QStringList list;
    const QPalette &pal = QApplication::palette();
    QSettings settings("Bespin", "Store");
    settings.beginGroup(item->text(0));
    settings.beginGroup("QPalette");

    list = settings.value ( "active", colors(pal, QPalette::Active) ).toStringList();
    updatePalette(*loadedPal, QPalette::Active, list);
    list = settings.value ( "inactive", colors(pal, QPalette::Inactive) ).toStringList();
    updatePalette(*loadedPal, QPalette::Inactive, list);
    list = settings.value ( "disabled", colors(pal, QPalette::Disabled) ).toStringList();
    updatePalette(*loadedPal, QPalette::Disabled, list);

    setColorsFromPalette( *loadedPal );
    applyPalette( loadedPal );

    settings.endGroup();
    if ( QApplication::style()->objectName() == "bespin" || QApplication::setStyle("Bespin") )
        static_cast<BStyle*>(QApplication::style())->init(&settings);

    settings.endGroup();
}

bool
Config::save()
{
    if ( !BConfig::save() )
        return false;
    /** store app presets */
    QSettings settings("Bespin", "Style");
    settings.beginGroup("PresetApps");
    settings.remove("");
    QTreeWidgetItem *item;
    const int cnt = ui.store->topLevelItemCount();
    for (int i = 0; i < cnt; ++i)
    {
        item = ui.store->topLevelItem(i);
        if (item->text(1).isEmpty())
            continue;
        QStringList apps = item->text(1).split(',', QString::SkipEmptyParts);
        foreach (QString app, apps)
            settings.setValue(app.simplified(), item->text(0));
    }
    settings.endGroup();
    /** save the palette loaded from store to qt configuration */
    if (!loadedPal)
        loadedPal = new QPalette;
    applyPalette( loadedPal );
    savePalette(*loadedPal);
    return true;
}

static QColor mid(const QColor &c1, const QColor &c2, int w1 = 1, int w2 = 1)
{
    int sum = (w1+w2);
    return QColor((w1*c1.red() + w2*c2.red())/sum,
                    (w1*c1.green() + w2*c2.green())/sum,
                    (w1*c1.blue() + w2*c2.blue())/sum,
                    (w1*c1.alpha() + w2*c2.alpha())/sum);
}


void
Config::setColorsFromPalette( const QPalette &pal )
{
    QPalette p = ui.role_window->palette();
    p.setColor( ui.role_window->backgroundRole(), pal.color( QPalette::Active, QPalette::Window ) );
    p.setColor( ui.role_windowText->foregroundRole(), pal.color( QPalette::Active, QPalette::WindowText ) );
    ui.role_window->setPalette( p );
    ui.role_windowText->setPalette( p );

    p = ui.role_button->palette();
    p.setColor( ui.role_button->backgroundRole(), pal.color( QPalette::Active, QPalette::Button ) );
    p.setColor( ui.role_buttonText->foregroundRole(), pal.color( QPalette::Active, QPalette::ButtonText ) );
    ui.role_button->setPalette( p );
    ui.role_buttonText->setPalette( p );

    p = ui.role_base->palette();
    p.setColor( ui.role_base->backgroundRole(), pal.color( QPalette::Active, QPalette::Base ) );
    p.setColor( ui.role_text->foregroundRole(), pal.color( QPalette::Active, QPalette::Text ) );
    ui.role_base->setPalette( p );
    ui.role_text->setPalette( p );

    p = ui.role_highlight->palette();
    p.setColor( ui.role_highlight->backgroundRole(), pal.color( QPalette::Active, QPalette::Highlight ) );
    p.setColor( ui.role_highlightedText->foregroundRole(), pal.color( QPalette::Active, QPalette::HighlightedText ) );
    ui.role_highlight->setPalette( p );
    ui.role_highlightedText->setPalette( p );
}

void
Config::applyPalette( QPalette *pal )
{
    if ( !pal )
    {
        if (!loadedPal)
            loadedPal = new QPalette;
        pal = loadedPal;
    }
    pal->setColor( QPalette::Window, ui.role_window->palette().color( ui.role_window->backgroundRole() ) );
    pal->setColor( QPalette::WindowText, ui.role_windowText->palette().color( ui.role_windowText->foregroundRole() ) );
    pal->setColor( QPalette::Button, ui.role_button->palette().color( ui.role_button->backgroundRole() ) );
    pal->setColor( QPalette::ButtonText, ui.role_buttonText->palette().color( ui.role_buttonText->foregroundRole() ) );
    pal->setColor( QPalette::Base, ui.role_base->palette().color( ui.role_base->backgroundRole() ) );
    pal->setColor( QPalette::Text, ui.role_text->palette().color( ui.role_text->foregroundRole() ) );
    pal->setColor( QPalette::Highlight, ui.role_highlight->palette().color( ui.role_highlight->backgroundRole() ) );
    pal->setColor( QPalette::HighlightedText, ui.role_highlightedText->palette().color( ui.role_highlightedText->foregroundRole() ) );
    if ( pal == loadedPal )
    {
        QApplication::setPalette( *loadedPal );
        emit changed(true);
        emit changed();
    }
}

void
Config::savePalette(const QPalette &pal)
{

    // for Qt =====================================
    QSettings settings("Trolltech");
    settings.beginGroup("Qt");
    settings.beginGroup("Palette");

    settings.setValue ( "active", colors(pal, QPalette::Active) );
    settings.setValue ( "inactive", colors(pal, QPalette::Inactive) );
    settings.setValue ( "disabled", colors(pal, QPalette::Disabled) );

    settings.endGroup(); settings.endGroup();

    // and KDE ==== I'm now gonna mourn a bit and not allways be prudent...:
    //
    // yeah - 5000 new extra colors for a style that relies on very restricted
    // color assumptions (kstyle, plastik and thus oxygen...) - sure...
    //
    // [ UPDATE:this is meanwhile fixed... ]
    // and please don't sync the Qt palette, ppl. will certainly be happy to
    // make color setting in KDE first and then in qtconfig for QApplication...
    // [ End update ]
    //
    // Ok, KDE supports extra DecorationFocus and DecorationHover
    //                        --------------      ---------------
    // -- we don't so we won't sync
    //
    // next, there's ForegroundLink and ForegroundVisited in any section
    //               -------------      ----------------
    // -- we just map them to QPalette::Link & QPalette::LinkVisited
    //
    // third, there're alternate backgroundcolors for all sections - sure:
    //                 ------------------------        ---------
    // my alternate button color: 1st button blue, second red, third blue...
    // -- we'll do what we do for normal alternate row colors and slightly shift
    // to the foreground....
    //
    // there's a ForegroundActive color that is by default... PINK???
    //          -----------------
    // what a decent taste for aesthetics... &-}
    // -- we just leave it as it is, cause i've no idea what it shall be good for
    // (active palette text - that's gonna be fun ;-)
    //
    // last there're ForegroundNegative, ForegroundNeutral and ForegroundPositive
    //               ------------------  ----------------      -----------------
    // what basically means: shifted to red, yellow and green...
    //
    // oh, and of course there NEEDS to be support for special chars in the
    // KDE ini files - plenty. who could ever life without keys w/o ':' or '$'
    // so we cannot simply use QSettings on a KDE ini file, thus we'll use our
    // own very... slim... ini parser, ok, we just read the file group it by
    // ^[.* entries, replace the color things and than flush the whole thing back
    // on disk

    KdeIni *kdeglobals = KdeIni::open("kdeglobals");
    if (!kdeglobals)
    {
        qWarning("Warning: kde4-config not found or \"--path config\" flag does not work\nWarning: No KDE support!");
        return;
    }
    const QString prefix("Colors:");
#if QT_VERSION >= 0x040400
    const int numItems = 5;
#else
    const int numItems = 4;
#endif
    static const char *items[numItems] =
    {
        "Button", "Selection", "View", "Window"
#if QT_VERSION >= 0x040400
        , "Tooltip"
#endif
    };
    static const QPalette::ColorRole roles[numItems][2] =
    {
        {QPalette::Button, QPalette::ButtonText},
        {QPalette::Highlight, QPalette::HighlightedText},
        {QPalette::Base, QPalette::Text},
        {QPalette::Window, QPalette::WindowText}
#if QT_VERSION >= 0x040400
        , {QPalette::ToolTipBase, QPalette::ToolTipText}
#endif
    };
    for (int i = 0; i < numItems; ++i)
    {
        kdeglobals->setGroup(prefix + items[i]);
        kdeglobals->setValue("BackgroundAlternate", mid(pal.color(QPalette::Active, roles[i][0]),
                                                        pal.color(QPalette::Active, roles[i][1]), 15, 1));
        kdeglobals->setValue("BackgroundNormal", pal.color(QPalette::Active, roles[i][0]));
        kdeglobals->setValue("ForegroundInactive", pal.color(QPalette::Disabled, roles[i][1]));
        kdeglobals->setValue("ForegroundLink", pal.color(QPalette::Active, QPalette::Link));
        kdeglobals->setValue("ForegroundNegative", mid(pal.color(QPalette::Active, roles[i][1]), Qt::red));
        kdeglobals->setValue("ForegroundNeutral", mid(pal.color(QPalette::Active, roles[i][1]), Qt::yellow));
        kdeglobals->setValue("ForegroundNormal", pal.color(QPalette::Active, roles[i][1]));
        kdeglobals->setValue("ForegroundPositive", mid(pal.color(QPalette::Active, roles[i][1]), Qt::green));
        kdeglobals->setValue("ForegroundVisited", pal.color(QPalette::Active, QPalette::LinkVisited));
    }
    kdeglobals->close();
    delete kdeglobals;

}

void
Config::showDemo()
{
    QPalette pal;
    applyPalette( &pal );
    store3( "__config-tmp", false, pal );
    QProcess *process = new QProcess( this );
    QStringList env = QProcess::systemEnvironment();
    env << "BESPIN_PRESET=__config-tmp";
    process->setEnvironment(env);
    connect ( process, SIGNAL(finished(int, QProcess::ExitStatus)), process, SLOT(deleteLater()) );
    process->start( QCoreApplication::arguments().at(0), QStringList() << "demo" );
}

/** see above, we'll present a name input dialog here */
void
Config::store()
{
    ui.presetLabel->hide();
    ui.presetFilter->hide();
    ui.storeLine->setText("Enter a name or select an item above");
    ui.storeLine->selectAll();
    ui.storeLine->show();
    ui.storeLine->setFocus();
    connect (ui.storeLine, SIGNAL(returnPressed()), this, SLOT(store2a()));
    connect (ui.store, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(store2b(QTreeWidgetItem *)));
}

void
Config::store2a()
{
    if (sender() != ui.storeLine)
        return;
    const QString &string = ui.storeLine->text();
    if (string.isEmpty())
    {
        ui.storeLine->setText("Valid names have some chars...");
        return;
    }
    if (!ui.store->findItems ( string, Qt::MatchExactly ).isEmpty())
    {
        ui.storeLine->setText("Item allready exists, please click it to replace it!");
        return;
    }
    disconnect (ui.storeLine, SIGNAL(returnPressed()), this, SLOT(store2a()));
    disconnect (ui.store, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(store2b(QTreeWidgetItem *)));
    ui.storeLine->hide();
    ui.presetLabel->show();
    ui.presetFilter->show();
    store3( string, true );
}

void
Config::store2b(QTreeWidgetItem* item)
{
    disconnect (ui.storeLine, SIGNAL(returnPressed()), this, SLOT(store2a()));
    disconnect (ui.store, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(store2b(QTreeWidgetItem *)));
    ui.storeLine->hide();
    ui.presetLabel->show();
    ui.presetFilter->show();
    store3( item->text(0), false );
}

/** real action */
void
Config::store3( const QString &string, bool addItem, const QPalette &pal )
{
    if (addItem)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(string));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        ui.store->addTopLevelItem(item);
        ui.store->sortItems(0, Qt::AscendingOrder);
    }
    setQSetting("Bespin", "Store", string);
    BConfig::save();
    setQSetting("Bespin", "Style", "Style");

    QSettings settings("Bespin", "Store");
    settings.beginGroup(string);
    /** Clear unwanted keys*/
    settings.remove("LeftHanded");
    settings.remove("MacStyle");
    settings.remove("ShowMnemonics");
    settings.remove("Scroll.ShowButtons");
    settings.remove("Tab.Duration");
    settings.remove("Tab.Transition");
    /** Now let's save colors as well */
    settings.beginGroup("QPalette");

    settings.setValue ( "active", colors(pal, QPalette::Active) );
    settings.setValue ( "inactive", colors(pal, QPalette::Inactive) );
    settings.setValue ( "disabled", colors(pal, QPalette::Disabled) );

    settings.endGroup();
    settings.endGroup();
}


void
Config::remove()
{
    QTreeWidgetItem *item = ui.store->currentItem();
    if (!item) return;

    QSettings store("Bespin", "Store");
    store.beginGroup(item->text(0));
    store.remove("");
    store.endGroup();
    delete item;
}

void
Config::storedSettigSelected(QTreeWidgetItem *item)
{
    ui.btnRestore->setEnabled(item);
    ui.btnExport->setEnabled(item);
    ui.btnDelete->setEnabled(item);
}

void
Config::handleBgMode(int idx)
{
    ui.structure->setEnabled(idx == 1);
}

static const char *grooveModes[5] = {"Line", "Groove", "Inlay", "Sunken", "None"};

void
Config::handleGrooveMode(int v)
{
    if (v > 4 || v < 0)
        ui.grooveLabel->setText("INVALID");
    else
        ui.grooveLabel->setText(grooveModes[v]);

    ui.showScrollButtons->setDisabled(v == 4);
    ui.fullScrollHover->setDisabled(v == 4);
    ui.invertGroove->setDisabled(v == 4);
    ui.scrollRole->setDisabled(v == 4);
    ui.scrollActiveRole->setDisabled(v == 4);
}

void
Config::learnPwChar()
{
    ushort n = unicode(ui.pwEchoChar->lineEdit()->text());
    if (ui.pwEchoChar->findData(n) != -1)
        return;
    ui.pwEchoChar->insertItem(0, QString(QChar(n)), QVariant(n));
    QSettings settings("Bespin", "Config");
    QStringList list = settings.value ( "UserPwChars", QStringList() ).toStringList();
    list << QString::number( n, 16 );
    settings.setValue("UserPwChars", list);
}

void
Config::filterPresets(const QString & string)
{
    QTreeWidgetItem *item;
    const int cnt = ui.store->topLevelItemCount();
    for (int i = 0; i < cnt; ++i)
    {
        item = ui.store->topLevelItem(i);
        item->setHidden(!item->text(0).contains(string, Qt::CaseInsensitive));
    }
}

static bool haveIcons = false;
static QIcon icons[8];
static const QPalette::ColorRole roles[] =
{
   QPalette::Window, QPalette::WindowText,
   QPalette::Base, QPalette::Text,
   QPalette::Button, QPalette::ButtonText,
   QPalette::Highlight, QPalette::HighlightedText
};
static const char* roleStrings[] =
{
   "Window", "Window Text",
   "Base (text editor)", "Text (text editor)",
   "Button", "Button Text",
   "Highlight", "Highlighted Text",
   "ToolTip", "ToolTip Text"
};

static void ensureIcons()
{
    if (haveIcons)
        return;
    haveIcons = true;
    QPixmap pix(16,16);
    pix.fill(Qt::transparent);
    QPainter p;
    for (int i = 0; i < 8; ++i)
    {
        pix.fill(Qt::transparent);
        p.begin(&pix);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::white);
        p.drawEllipse(pix.rect().adjusted(2,2,-2,-2));
        p.setBrush(qApp->palette().color(roles[i]));
        p.setPen(Qt::black);
        p.drawEllipse(pix.rect().adjusted(3,3,-3,-3));
        p.end();
        icons[i] = QIcon(pix);
    }
}

/** The combobox filler you've read of several times before ;) */
void
Config::generateColorModes(QComboBox *box, QList<int> *wantedRoles)
{
    int oldIndex = box->currentIndex();
    ensureIcons();
    box->clear();
    box->setIconSize ( QSize(16,16) );
    if (wantedRoles)
    {
        foreach (int i, *wantedRoles)
            if (i < 8)
                box->addItem(icons[i], roleStrings[i], roles[i]);
    }
    else
    {
        for (int i = 0; i < 8; ++i)
            box->addItem(icons[i], roleStrings[i], roles[i]);
    }
    box->setCurrentIndex(oldIndex);
}

void
Config::reloadColorRoles()
{
    if ( !myColorsHaveChanged )
        return;
    myColorsHaveChanged = haveIcons = false;
    ensureIcons();
    generateColorModes(ui.tooltipRole);
    generateColorModes(ui.uno_role);
    generateColorModes(ui.crProgressBg);
    generateColorModes(ui.crProgressFg);
    generateColorModes(ui.crTabBar);
    generateColorModes(ui.crTabBarActive);
    generateColorModes(ui.crPopup);
    generateColorModes(ui.crMenuActive);
    generateColorModes(ui.btnRole);
    generateColorModes(ui.btnActiveRole);
    generateColorModes(ui.toolbuttonRole);
    generateColorModes(ui.toolbuttonActiveRole);
    generateColorModes(ui.scrollRole);
    generateColorModes(ui.scrollActiveRole);
    generateColorModes(ui.headerRole);
    generateColorModes(ui.headerSortingRole);
    QList<int> roles; roles << 3 << 4 << 6;
    generateColorModes(ui.viewShadingRole, &roles);

    generateColorModes(ui.kwinInactiveRole);
    generateColorModes(ui.kwinActiveRole);
    generateColorModes(ui.kwinInactiveText);
    generateColorModes(ui.kwinActiveText);
}

void
Config::generateGradientTypes(QComboBox *box)
{
    box->clear();
    box->addItem("None");
    box->addItem("Simple");
    box->addItem("Button");
    box->addItem("Sunken");
    box->addItem("Gloss");
    box->addItem("Glass");
    box->addItem("Metal");
    box->addItem("Cloudy");
    box->addItem("Shiny");
}


void
Config::setHeader(const QString &title)
{
//     setDefaultContextInfo("<qt><center><h1>" + title + "</h1></center></qt>");
    ui.header->setText("<qt><center><h1>" + title + "</h1></center></qt>"); // must force
//     resetInfo();
}
