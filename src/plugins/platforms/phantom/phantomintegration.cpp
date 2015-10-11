/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "phantomintegration.h"
#include "phantombackingstore.h"

#include <QtGui/private/qpixmap_raster_p.h>
#include <qpa/qplatformwindow.h>
#include <qpa/qplatformfontdatabase.h>
#include <qpa/qplatformnativeinterface.h>

#if defined(Q_OS_MAC)
# include <QtPlatformSupport/private/qcoretextfontdatabase_p.h>
#else
# include <QtPlatformSupport/private/qgenericunixfontdatabase_p.h>
#endif

#include <QtPlatformSupport/private/qgenericunixeventdispatcher_p.h>

QT_BEGIN_NAMESPACE

PhantomIntegration::PhantomIntegration()
#if defined(Q_OS_MAC)
    : m_fontDb(new QCoreTextFontDatabase),
#else
    : m_fontDb(new QGenericUnixFontDatabase)
#endif
{
    m_primaryScreen = new PhantomScreen();
}

PhantomIntegration::~PhantomIntegration()
{
    delete m_primaryScreen;
}

void PhantomIntegration::initialize()
{
    // Simulate typical desktop screen
    int width = 1024;
    int height = 768;
    int dpi = 72;
    qreal physicalWidth = width * 25.4 / dpi;
    qreal physicalHeight = height * 25.4 / dpi;
    m_primaryScreen->mGeometry = QRect(0, 0, width, height);
    m_primaryScreen->mPhysicalSize = QSizeF(physicalWidth, physicalHeight);

    m_primaryScreen->mDepth = 32;
    m_primaryScreen->mFormat = QImage::Format_ARGB32_Premultiplied;

    screenAdded(m_primaryScreen);

    m_nativeInterface.reset(new QPlatformNativeInterface);
}

bool PhantomIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformWindow* PhantomIntegration::createPlatformWindow(QWindow* window) const
{
    return new QPlatformWindow(window);
}

QPlatformBackingStore* PhantomIntegration::createPlatformBackingStore(QWindow* window) const
{
    return new PhantomBackingStore(window);
}

QPlatformFontDatabase *PhantomIntegration::fontDatabase() const
{
    return m_fontDb.data();
}

QAbstractEventDispatcher *PhantomIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}

QPlatformNativeInterface *PhantomIntegration::nativeInterface() const
{
    return m_nativeInterface.data();
}

QT_END_NAMESPACE
