// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <Python.h>

#include "Core/API/Controller.h"
#include "Core/API/Events.h"
#include "Core/API/Gui.h"

namespace PyScripting
{

class PyScriptingBackend
{
public:
  PyScriptingBackend(std::filesystem::path script_filepath, API::EventHub& event_hub, API::Gui& gui,
                     Core::System& system,
                     API::BaseManip& gc_manip, API::BaseManip& wii_manip, API::BaseManip& wii_classic_manip,
                     API::BaseManip& wii_nunchuk_manip, API::BaseManip& gba_manip);
  ~PyScriptingBackend();
  static PyScriptingBackend* GetCurrent();
  API::EventHub* GetEventHub();
  API::Gui* GetGui();
  Core::System* GetSystem();
  API::BaseManip* GetGCManip();
  API::BaseManip* GetWiiManip();
  API::BaseManip* GetWiiClassicManip();
  API::BaseManip* GetWiiNunchukManip();
  API::BaseManip* GetGBAManip();
  void AddCleanupFunc(std::function<void()> cleanup_func);

  // this class somewhat is a wrapper around a python interpreter state,
  // and that isn't copyable, so this class isn't copyable either.
  // Moving could work if you get rid of the event_hub reference.
  PyScriptingBackend(const PyScriptingBackend&) = delete;
  PyScriptingBackend& operator=(const PyScriptingBackend&) = delete;
  PyScriptingBackend(PyScriptingBackend&&) = delete;
  PyScriptingBackend& operator=(PyScriptingBackend&&) = delete;

private:
  static std::map<u64, PyScriptingBackend*> s_instances;
  static PyThreadState* s_main_threadstate;
  // creation and deletion of this class handles the bookkeeping of python's
  // main- and sub-interpreters. None of that can safely run concurrently.
  static std::mutex s_bookkeeping_lock;
  PyThreadState* m_interp_threadstate;
  API::EventHub& m_event_hub;
  API::Gui& m_gui;
  Core::System& m_system;
  API::BaseManip& m_gc_manip;
  API::BaseManip& m_wii_manip;
  API::BaseManip& m_wii_classic_manip;
  API::BaseManip& m_wii_nunchuk_manip;
  API::BaseManip& m_gba_manip;
  std::vector<std::function<void()>> m_cleanups;
};

}  // namespace PyScripting
