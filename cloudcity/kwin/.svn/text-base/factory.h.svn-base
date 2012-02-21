//////////////////////////////////////////////////////////////////////////////
//
// -------------------
// Bespin window decoration for KDE.
// -------------------
// Copyright (c) 2008/2009 Thomas Lübking <baghira-style@gmx.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#ifndef BESPIN_H
#define BESPIN_H

#include <QHash>
#include <QObject>
#include <QPixmap>
#include <QVector>
#include <kdecorationfactory.h>
#include "../blib/gradients.h"
#include "../blib/xproperty.h"
#include "button.h"

class QMenu;
class QTextBrowser;

namespace Bespin
{

class Client;

typedef struct _Preset
{
    WindowData data;
    QStringList classes;
    QList<NET::WindowType>types;
} Preset;

typedef struct
{
    bool forceUserColors, trimmCaption, resizeCorner, roundCorners, hideInactiveButtons, verticalTitle, variableShadowSizes;
    int slickButtons, titleAlign;
    Gradients::Type gradient[2][2], buttonGradient;
    QStringList smallTitleClasses;
} Config;

class Factory : public QObject, public KDecorationFactory
{
    friend class BespinDecoAdaptor;
    friend class Client;
    Q_OBJECT
public:
    Factory();
    ~Factory();
    KDecoration *createDecoration(KDecorationBridge *b);
    bool reset(unsigned long changed);
    bool supports( Ability ability ) const;
    inline static Gradients::Type buttonGradient() {return ourConfig.buttonGradient;}
    inline static int buttonSize(bool small) {return ourButtonSize[small];}
    inline static int edgeSize() { return ourBorderSize[1] ? ourBorderSize[1] : !weAreComposited; }
    inline static int baseSize() { return ourBorderSize[0] ? ourBorderSize[0] : !weAreComposited; }
    inline static Qt::KeyboardModifier commandKey() { return ourCommandKey; }
    inline static bool compositingActive() { return weAreComposited; }
    inline static int initialized() { return weAreInitialized; }
    inline static bool isCompiz() { return weAreCompiz; }
//    virtual void checkRequirements( KDecorationProvides* provides );
    inline static int titleSize(bool minimal = false) {return ourTitleSize[minimal];}
    inline static const Config *config() { return &ourConfig; }
    static WindowData *decoInfo(qint64 pid);
    static WindowData *decoInfo(QString WMclass, NET::WindowType type);
    static int defaultBgMode() { return ourBgMode; }
    inline static const QVector<Button::Type> &multiButtons() { return ourMultiButton; }
    inline static bool roundCorners() { return ourConfig.roundCorners; }
    inline static int slickButtons() { return ourConfig.slickButtons; }
    static inline float smallFactor() { return 0.75; }
    static void showDesktopMenu(const QPoint &p, Client *client);
    static void showInfo(const QPoint &p, WId id);
    static void showWindowList(const QPoint &p, Client *client);
    inline static bool variableShadowSizes() { return ourConfig.variableShadowSizes; }
    inline static bool verticalTitle() { return ourConfig.verticalTitle; }
protected:
    static BgSet *bgSet(const QColor &c, bool vertical, int intensity, qint64 *hash = 0);
    static void forget(qint64 pid);
    static void kickBgSet(qint64 hash);
    static void learn(qint64 pid, QByteArray data);
    static QPixmap mask;
    void updateDeco(WId id);
    void setNetbookMode(bool on);
private:
    bool readConfig();
private slots:
    void cleanUp();
    void postInit();
    void updateCompositingState(bool);
private:
    static Qt::KeyboardModifier ourCommandKey;
    static QHash<qint64, WindowData*> ourDecoInfos;
    static QHash<qint64, BgSet*> ourBgSets;
    static QList<Preset*> ourPresets;
    static bool weAreInitialized, weAreComposited, weAreCompiz;
    static int ourButtonSize[2], ourTitleSize[2], ourBgMode, ourBorderSize[2];
    static QVector<Button::Type> ourMultiButton;
    static Config ourConfig;
    static QMenu *ourDesktopMenu, *ourWindowList;
    static QTextBrowser *ourWindowInfo;
};

} //namespace

#endif
