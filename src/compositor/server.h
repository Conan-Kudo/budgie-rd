/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

#include <QWaylandCompositor>
#include <QWaylandSeat>
#include <QWaylandSurface>
#include <QWaylandWlShell>
#include <QWaylandWlShellSurface>
#include <QWaylandXdgShellV5>
#include <QWaylandXdgSurfaceV5>

#include "compositor-input-interface.h"
#include "display.h"
#include "window.h"

namespace Budgie::Compositor
{
    /**
     * This is the main Compositor implementation, responsible for managing
     * the display(s) in a desktop-like fashion. Additionally it will access
     * the rendering plugin from the Manager to provide visual output.
     */
    class Server : public QWaylandCompositor, public InputInterface
    {
        Q_OBJECT

    public:
        explicit Server(RendererInterface *renderer);

        // Allow explicit initialisation from the Manager
        bool start();

        // Implement InputInterface
        void setMouseFocus(Window *w) override;
        void setKeyFocus(Window *w) override;
        void dispatchMouseEvent(QMouseEvent *e) override;
        void dispatchTouchEvent(QTouchEvent *e) override;
        void dispatchKeyEvent(QKeyEvent *e) override;

    private:
        RendererInterface *m_renderer;

        QWaylandWlShell *m_wl_shell;
        QWaylandXdgShellV5 *m_xdg_shell_v5;
        QList<QSharedPointer<Display>> m_displays;
        QWaylandSeat *m_seat;

        QHash<QWaylandSurface *, QSharedPointer<Window>> m_surfaces;

    private slots:
        void surfaceCreated(QWaylandSurface *surface);
        void surfaceDestroying(QWaylandSurface *surface);
        void wlShellCreated(QWaylandWlShellSurface *shell);
        void xdgShellv5Created(QWaylandXdgSurfaceV5 *shell);
        void wlSeatChanged(QWaylandSeat *newSeat, QWaylandSeat *oldSeat);

        void wlCreated();
    };
}
/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */
