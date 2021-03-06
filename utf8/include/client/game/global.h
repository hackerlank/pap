/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id global.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 16:35:03
 * @uses client game global sets
 */
#ifndef CLIENT_GAME_GLOBAL_H_
#define CLIENT_GAME_GLOBAL_H_

#include "common/base/type.h"
#include "vengine/classes.h"
#include "vengine/kernel/base.h"

extern vengine_capability::Debuger* g_debuger;
extern vengine_variable::System* g_variablesystem;
extern vengine_sound::System* g_soundsystem;
extern vengine_game::WorldSystem* g_worldsystem;
extern vengine_game::EventSystem* g_eventsystem;
extern vengine_resource::Provider* g_resourceprovider;
extern vengine_db::System* g_dbsystem;
extern vengine_time::System* g_timesystem;
extern vengine_kernel::Base g_root_kernel; //区分vgui中的核心
extern HWND g_mainwindow_handle;
extern HINSTANCE g_instance_handle;
extern const char kVersionInfo[];
extern const char kGameTitle[];
extern bool g_debugmode; //是否为调试模式

#endif //CLIENT_GAME_GLOBAL_H_
