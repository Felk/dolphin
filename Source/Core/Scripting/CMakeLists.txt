add_library(scripting
  ScriptingEngine.cpp
  ScriptingEngine.h
  Python/PyScriptingBackend.cpp
  Python/PyScriptingBackend.h
  Python/Modules/controllermodule.cpp
  Python/Modules/controllermodule.h
  Python/Modules/doliomodule.cpp
  Python/Modules/doliomodule.h
  Python/Modules/dolphinmodule.cpp
  Python/Modules/dolphinmodule.h
  Python/Modules/eventmodule.cpp
  Python/Modules/eventmodule.h
  Python/Modules/emulationmodule.cpp
  Python/Modules/emulationmodule.h
  Python/Modules/guimodule.cpp
  Python/Modules/guimodule.h
  Python/Modules/memorymodule.cpp
  Python/Modules/memorymodule.h
  Python/Modules/registersmodule.cpp
  Python/Modules/registersmodule.h
  Python/Modules/savestatemodule.cpp
  Python/Modules/savestatemodule.h
  Python/Utils/as_py_func.h
  Python/Utils/convert.h
  Python/Utils/fmt.h
  Python/Utils/invoke.h
  Python/Utils/module.h
  Python/Utils/object_wrapper.cpp
  Python/Utils/object_wrapper.h
)

if(WIN32)
  set(Python3_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Externals/python/x64/include")
  set(Python3_LIBRARIES 
    "${CMAKE_SOURCE_DIR}/Externals/python/x64/libs/python3.lib"
    "${CMAKE_SOURCE_DIR}/Externals/python/x64/libs/python3_d.lib"
    "${CMAKE_SOURCE_DIR}/Externals/python/x64/libs/python312.lib"
    "${CMAKE_SOURCE_DIR}/Externals/python/x64/libs/python312_d.lib"
  )
else()
  find_package(Python3 REQUIRED COMPONENTS Development)
endif()
include_directories(${Python3_INCLUDE_DIRS})
# TODO imgui shouldn't be here
target_link_libraries(scripting PRIVATE ${Python3_LIBRARIES} imgui core)
