/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKTAPHANDLER_H
#define QQUICKTAPHANDLER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qquickitem.h"
#include "qevent.h"
#include "qquickpointersinglehandler_p.h"
#include <QtCore/qbasictimer.h>

QT_BEGIN_NAMESPACE

class Q_AUTOTEST_EXPORT QQuickTapHandler : public QQuickPointerSingleHandler
{
    Q_OBJECT
    Q_PROPERTY(bool isPressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(int tapCount READ tapCount NOTIFY tapCountChanged)
    Q_PROPERTY(qreal timeHeld READ timeHeld NOTIFY timeHeldChanged)
    Q_PROPERTY(qreal longPressThreshold READ longPressThreshold WRITE setLongPressThreshold NOTIFY longPressThresholdChanged)
    Q_PROPERTY(GesturePolicy gesturePolicy READ gesturePolicy WRITE setGesturePolicy NOTIFY gesturePolicyChanged)

public:
    enum GesturePolicy {
        DragThreshold,
        WithinBounds,
        ReleaseWithinBounds
    };
    Q_ENUM(GesturePolicy)

    QQuickTapHandler(QObject *parent = 0);
    ~QQuickTapHandler();

    bool wantsEventPoint(QQuickEventPoint *point) override;
    void handleEventPoint(QQuickEventPoint *point) override;

    bool isPressed() const { return m_pressed; }

    int tapCount() const { return m_tapCount; }
    qreal timeHeld() const { return (m_holdTimer.isValid() ? m_holdTimer.elapsed() / 1000.0 : -1.0); }

    qreal longPressThreshold() const;
    void setLongPressThreshold(qreal longPressThreshold);

    GesturePolicy gesturePolicy() const { return m_gesturePolicy; }
    void setGesturePolicy(GesturePolicy gesturePolicy);

Q_SIGNALS:
    void pressedChanged();
    void tapCountChanged();
    void timeHeldChanged();
    void longPressThresholdChanged();
    void gesturePolicyChanged();
    void tapped(QQuickEventPoint *point);
    void longPressed();

protected:
    void handleGrabCancel(QQuickEventPoint *point) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void setPressed(bool press, bool cancel, QQuickEventPoint *point);
    int longPressThresholdMilliseconds() const;
    void connectPreRenderSignal(bool conn = true);
    void updateTimeHeld();

private:
    bool m_pressed;
    GesturePolicy m_gesturePolicy;
    int m_tapCount;
    int m_longPressThreshold;
    QBasicTimer m_longPressTimer;
    QElapsedTimer m_holdTimer;
    QPointF m_lastTapPos;
    qreal m_lastTapTimestamp;

    static qreal m_multiTapInterval;
    static int m_mouseMultiClickDistanceSquared;
    static int m_touchMultiTapDistanceSquared;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTapHandler)

#endif // QQUICKTAPHANDLER_H