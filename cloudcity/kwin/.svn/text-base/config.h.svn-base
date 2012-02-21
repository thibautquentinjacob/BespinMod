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

#ifndef CONFIG_H
#define CONFIG_H

#include "../config/bconfig.h"
#include "ui_configdialog.h"

class KConfigGroup;
class QListWidgetItem;

class Config : public BConfig
{
    Q_OBJECT
public:
    Config(QWidget* parent);
public slots:
    void createNewPreset();
    void deleteCurrentPreset();
    void presetChanged(QListWidgetItem*, QListWidgetItem*);
    void save(KConfigGroup&);
private:
    void loadPresets();
    void savePresets();
private slots:
    void catchClones(QListWidgetItem*);
    void watchBgMode();
    void watchButtonGradient();
    void watchDecoGradient();
    void watchShadowSize(int);
private:
   Ui::Config ui;
};

#endif // KNIFTYCONFIG_H
