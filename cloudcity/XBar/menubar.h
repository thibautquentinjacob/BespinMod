/*
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

#ifndef MENUBAR_H
#define MENUBAR_H

#include <QGraphicsWidget>
#include <QStyleOption>

class XBar;
class QStyleOptionMenuItem;
class QGraphicsView;

class MenuBar : public QGraphicsWidget
{
    Q_OBJECT
public:
    MenuBar ( const QString &service = QString(), qlonglong key = 0, QGraphicsWidget *parent = 0, QWidget *dummy = 0);
//    virtual ~MenuBar();
    QAction *addAction(const QString & text, int idx = -1, QMenu *menu = 0);
    void addAction(QAction *action, int idx = -1);
    QAction *addMenu(QMenu *menu);
    QMenu *addMenu(const QString &title);
    QAction *addSeparator();
    const QRect &actionGeometry(int idx) const;
    void removeAction(int idx);
    QAction *takeAction(int idx);
    void changeAction(int idx, const QString & text);
    void clear();
    inline int count() const { return d.actions.count(); }
    QAction *action(int idx) const;
//    void show();
    void hide();
    QPointF mapFromGlobal(const QPoint &pt);
    QPoint mapToGlobal(const QPointF &pt);
    inline const QString& service() const { return d.service; }
    inline qlonglong key() const { return d.key; }
    inline int openPopup() const { return d.openPopup; }
    inline void setAppTitle(const QString &title) { d.appTitle = title; }
    QGraphicsView *view() const;
signals:
    void hovered(int);
    void triggered(int);
protected:
    inline void initStyleOption(QStyleOption *option) const
    {
        if (QStyleOptionMenuItem *mopt = qstyleoption_cast<QStyleOptionMenuItem*>(option))
            initStyleOption(mopt, -1);
        else
            QGraphicsWidget::initStyleOption(option);
    }
    void initStyleOption(QStyleOptionMenuItem *option, int idx) const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *ev);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *ev);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *ev);
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    virtual void rightMouseButtonEvent(int, QGraphicsSceneMouseEvent *) {}
    void wheelEvent(QGraphicsSceneWheelEvent *);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget = 0 );
    inline virtual void show() { QGraphicsItem::show(); }
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint ) const;
    void timerEvent(QTimerEvent *event);
friend class XBar;
    inline QList<QAction*> &actions() { return d.actions; }
    void popDown();
    void setOpenPopup(int popup);
friend class DummyQMenuBar;
    QAction *action(const QPoint &pos) const;
private:
    void mouseMoved(const QPointF &pos, const QPointF &lastPos);
    int index(const QPoint &pos);
    void updateSize();
private slots:
    void actionChanged();
    void popupClosed();
private:
    struct
    {
        QList<QAction*> actions;
        QList<QRect> actionRects;
        QString service, appTitle;
        QSizeF preferredSize;
        qlonglong key;
        int hoverIndex;
        int openPopup;
        QWidget *widget;
    } d;
};

#endif //XBAR_H
