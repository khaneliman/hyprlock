#pragma once

#include <wayland-client.h>
#include "ext-session-lock-v1-protocol.h"
#include "fractional-scale-v1-protocol.h"
#include "viewporter-protocol.h"
#include "Output.hpp"
#include "CursorShape.hpp"

#include <memory>
#include <vector>

#include <xkbcommon/xkbcommon.h>

class CHyprlock {
  public:
    CHyprlock();

    void                            run();

    void                            onGlobal(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version);
    void                            onGlobalRemoved(void* data, struct wl_registry* registry, uint32_t name);

    void                            onLockLocked();
    void                            onLockFinished();

    void                            lockSession();
    void                            unlockSession();

    void                            onKey(uint32_t key);

    size_t                          getPasswordBufferLen();

    ext_session_lock_manager_v1*    getSessionLockMgr();
    ext_session_lock_v1*            getSessionLock();
    wl_compositor*                  getCompositor();
    wl_display*                     getDisplay();
    wp_fractional_scale_manager_v1* getFractionalMgr();
    wp_viewporter*                  getViewporter();

    wl_pointer*                     m_pPointer = nullptr;
    wl_keyboard*                    m_pKeeb    = nullptr;

    std::unique_ptr<CCursorShape>   m_pCursorShape;

    xkb_context*                    m_pXKBContext = nullptr;
    xkb_keymap*                     m_pXKBKeymap  = nullptr;
    xkb_state*                      m_pXKBState   = nullptr;

    bool                            m_bTerminate = false;

  private:
    struct {
        wl_display*                     display     = nullptr;
        wl_registry*                    registry    = nullptr;
        wl_seat*                        seat        = nullptr;
        ext_session_lock_manager_v1*    sessionLock = nullptr;
        wl_compositor*                  compositor  = nullptr;
        wp_fractional_scale_manager_v1* fractional  = nullptr;
        wp_viewporter*                  viewporter  = nullptr;
    } m_sWaylandState;

    struct {
        ext_session_lock_v1* lock = nullptr;
    } m_sLockState;

    struct {
        std::string passBuffer = "";
    } m_sPasswordState;

    std::vector<std::unique_ptr<COutput>> m_vOutputs;
};

inline std::unique_ptr<CHyprlock> g_pHyprlock;