set(KIT ${APPLIB_NAME})

if(Slicer_USE_PYTHONQT_WITH_TCL)
  if(Slicer_BUILD_CLI_SUPPORT)
    if(Slicer_BUILD_EMSegment)
      include_directories(
        ${EMSegment_SOURCE_DIR}
        ${RemoteIO_SOURCE_DIR} ${RemoteIO_BINARY_DIR})
    endif()
  endif()
endif()

set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN "DEBUG_LEAKS_ENABLE_EXIT_ERROR();" )
set(KIT_TEST_SRCS
  qSlicerAppMainWindowTest1.cxx
  qSlicerModuleFactoryManagerTest1.cxx
  )
if(Slicer_USE_PYTHONQT_WITH_TCL)
  list(APPEND KIT_TEST_SRCS qSlicerApplicationTpyclTest1.cxx)
  if(Slicer_BUILD_CLI_SUPPORT)
    if(Slicer_BUILD_EMSegment)
      list(APPEND KIT_TEST_SRCS qSlicerApplicationTpyclEMSegmentIntegrationTest.cxx)
    endif()
  endif()
endif()
create_test_sourcelist(Tests ${KIT}CxxTests.cxx
  ${KIT_TEST_SRCS}
  EXTRA_INCLUDE vtkMRMLDebugLeaksMacro.h
  )

set(target_libraries ${KIT})
if(Slicer_USE_PYTHONQT_WITH_TCL)
  if(Slicer_BUILD_CLI_SUPPORT)
    if(Slicer_BUILD_EMSegment)
      list(APPEND target_libraries vtkSlicerEMSegmentModuleLogic)
    endif()
  endif()
endif()

ctk_add_executable_utf8(${KIT}CxxTests ${Tests})
target_link_libraries(${KIT}CxxTests  ${target_libraries})
set_target_properties(${KIT}CxxTests PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})

#
# Add Tests
#

if(Slicer_USE_PYTHONQT_WITH_TCL)
  if(Slicer_HAS_CONSOLE_IO_SUPPORT)
    simple_test( qSlicerApplicationTpyclTest1 )
    set_tests_properties(qSlicerApplicationTpyclTest1 PROPERTIES PASS_REGULAR_EXPRESSION stringArray)
  endif()
  if(Slicer_BUILD_CLI_SUPPORT)
    if(Slicer_BUILD_EMSegment)
      simple_test( qSlicerApplicationTpyclEMSegmentIntegrationTest $<TARGET_FILE:EMSegmentCommandLine>)
    endif()
  endif()
endif()
simple_test( qSlicerAppMainWindowTest1 )
simple_test( qSlicerModuleFactoryManagerTest1 )

#
# Application tests
#

if(Slicer_HAS_CONSOLE_IO_SUPPORT)
  add_test(
    NAME slicer_nomainwindow_DisableModulesCommandLineOptionsTest
    COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:${APP_TARGET_NAME}>
    ${ARGN} --testing --verbose-module-discovery --disable-modules
    )
  add_test(
    NAME slicer_nomainwindow_DisableModulesCommandLineOptionsTest2
    COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:${APP_TARGET_NAME}>
    ${ARGN} --testing --verbose-module-discovery --disable-cli-modules --disable-loadable-modules --disable-scripted-loadable-modules
    )
  set_tests_properties(
    slicer_nomainwindow_DisableModulesCommandLineOptionsTest
    slicer_nomainwindow_DisableModulesCommandLineOptionsTest2
    PROPERTIES PASS_REGULAR_EXPRESSION "Number of loaded modules: 1"
    )

  add_test(
    NAME slicer_nomainwindow_NoApplicationInformationOptionTest
    COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:${APP_TARGET_NAME}>
    --disable-modules --ignore-slicerrc --exit-after-startup
    )
  set_tests_properties(
    slicer_nomainwindow_NoApplicationInformationOptionTest
    PROPERTIES FAIL_REGULAR_EXPRESSION "Session start time"
    )
  add_test(
    NAME slicer_nomainwindow_ApplicationInformationOptionTest
    COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:${APP_TARGET_NAME}>
    --disable-modules --ignore-slicerrc --exit-after-startup --application-information
    )
  set_tests_properties(
    slicer_nomainwindow_ApplicationInformationOptionTest
    PROPERTIES PASS_REGULAR_EXPRESSION "Session start time"
    )
endif()

