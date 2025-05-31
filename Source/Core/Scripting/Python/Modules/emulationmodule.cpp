// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "Scripting/Python/Modules/emulationmodule.h"

#include "Core/HW/ProcessorInterface.h"
#include "Core/Movie.h"
#include "Core/System.h"

#include "Scripting/Python/Utils/module.h"
#include "Scripting/Python/PyScriptingBackend.h"

namespace PyScripting
{

struct EmulationModuleState
{
  Core::System* system;
};

static PyObject* EmulationResume(PyObject* self)
{
  EmulationModuleState* state = Py::GetState<EmulationModuleState>(self);
  if(Core::GetState(*state->system) == Core::State::Paused) {
    Core::SetState(*state->system, Core::State::Running);
  }
  Py_RETURN_NONE;
}

static PyObject* EmulationPause(PyObject* self)
{
  EmulationModuleState* state = Py::GetState<EmulationModuleState>(self);
  if(Core::GetState(*state->system) == Core::State::Running) {
    Core::SetState(*state->system, Core::State::Paused);
  }
  Py_RETURN_NONE;
}

static PyObject* EmulationReset(PyObject* self)
{
  EmulationModuleState* state = Py::GetState<EmulationModuleState>(self);
  // Copy from DolphinQt/MainWindow.cpp: MainWindow::Reset()
  auto& movie = state->system->GetMovie();
  if (movie.IsRecordingInput())
    movie.SetReset(true);
  state->system->GetProcessorInterface().ResetButton_Tap();
  Py_RETURN_NONE;
}

static void SetupEmulationModule(PyObject* module, EmulationModuleState* state)
{
  Core::System* system = PyScripting::PyScriptingBackend::GetCurrent()->GetSystem();
  state->system = system;
}

PyMODINIT_FUNC PyInit_emulation()
{
  static PyMethodDef methods[] = {
      Py::MakeMethodDef<EmulationResume>("resume"),
      Py::MakeMethodDef<EmulationPause>("pause"),
      Py::MakeMethodDef<EmulationReset>("reset"),

      {nullptr, nullptr, 0, nullptr}  // Sentinel
  };
  static PyModuleDef module_def =
      Py::MakeStatefulModuleDef<EmulationModuleState, SetupEmulationModule>("emulation", methods);
  PyObject* def_obj = PyModuleDef_Init(&module_def);
  return def_obj;
}

}  // namespace PyScripting
