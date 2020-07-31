cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11 CACHE STRING "Build for 10.11")

project(midi-monitor VERSION 0.9.0 LANGUAGES CXX)

add_subdirectory(lib/JUCE)

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

juce_add_plugin(midi-monitor
    PRODUCT_NAME "MidiMonitor"
    COMPANY_NAME "Surge Synth Team"  
    BUNDLE_ID "org.surge-synth-team.midi-monitor"
    PLUGIN_MANUFACTURER_CODE VmbA
    PLUGIN_CODE MdMo

    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    
    FORMATS AU VST3 Standalone
)

juce_generate_juce_header( midi-monitor )

set_property(TARGET midi-monitor PROPERTY CXX_STANDARD 17)

file(GLOB TWS_RESOURCES_GLOB
  resources/*
  )

juce_add_binary_data( midi-monitor-binary
  SOURCES ${TWS_RESOURCES_GLOB} LICENSE
)

set_target_properties(midi-monitor-binary PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)
    
target_include_directories(midi-monitor 
  PRIVATE
  Source
)

configure_file(
  ${CMAKE_SOURCE_DIR}/Source/version.cpp.in
  ${CMAKE_BINARY_DIR}/generated/version.cpp
)

target_sources(midi-monitor PRIVATE
  Source/MainPanel.cpp
  Source/PluginEditor.cpp
  Source/PluginProcessor.cpp

  ${CMAKE_BINARY_DIR}/generated/version.cpp
)

target_compile_definitions(midi-monitor PUBLIC
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1

    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0

    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0

    JUCE_ALSA=1
    JUCE_JACK=1
)

target_link_libraries(midi-monitor PRIVATE
    midi-monitor-binary
    juce::juce_audio_utils
    juce::juce_audio_processors
)



# Build installers
get_target_property( OUTPUT_DIR midi-monitor RUNTIME_OUTPUT_DIRECTORY )
add_custom_target( well-named-assets )
if( APPLE )
  add_custom_target( well-named-au )
  add_dependencies( well-named-au midi-monitor_AU )
  add_dependencies( well-named-assets well-named-au )
endif()
add_custom_target( well-named-vst3 )
add_dependencies( well-named-vst3 midi-monitor_VST3 )
add_dependencies( well-named-assets well-named-vst3 )

add_custom_target( well-named-standalone )
add_dependencies( well-named-standalone midi-monitor_Standalone )
add_dependencies( well-named-assets well-named-standalone )

add_custom_target( installer-pkg )
add_dependencies( installer-pkg well-named-assets )
set( INSTALLER_DIR ${CMAKE_BINARY_DIR}/asset )
set( WELL_NAMED_ASSET_DIR ${CMAKE_BINARY_DIR}/product )
set( INSTALLER_BASENAME "MidiMonitor" )

add_custom_command(
  TARGET well-named-vst3
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory  ${WELL_NAMED_ASSET_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${OUTPUT_DIR}/VST3 ${WELL_NAMED_ASSET_DIR}
  )

add_custom_command(
  TARGET well-named-standalone
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory  ${WELL_NAMED_ASSET_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${OUTPUT_DIR}/Standalone ${WELL_NAMED_ASSET_DIR}
  )

if( APPLE )
  add_custom_command(
    TARGET well-named-au
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory  ${WELL_NAMED_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${OUTPUT_DIR}/AU ${WELL_NAMED_ASSET_DIR}
  )
endif()

if( APPLE )
  add_custom_command(
    TARGET installer-pkg
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory  ${INSTALLER_DIR}
    COMMAND hdiutil create ${INSTALLER_DIR}/${INSTALLER_BASENAME}-macos-${GIT_COMMIT_HASH}.dmg -ov -volname "${INSTALLER_BASENAME}-${GIT_COMMIT_HASH}" -fs HFS+ -srcfolder ${WELL_NAMED_ASSET_DIR}
    )
elseif( UNIX )
  add_custom_command(
    TARGET installer-pkg
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory  ${INSTALLER_DIR}
    COMMAND ls -l ${WELL_NAMED_ASSET_DIR}
    COMMAND cd ${WELL_NAMED_ASSET_DIR} && tar czf "${INSTALLER_DIR}/${INSTALLER_BASENAME}-linux-${GIT_COMMIT_HASH}.tgz" .
    )
else()
  file( TO_NATIVE_PATH "${INSTALLER_DIR}/${INSTALLER_BASENAME}-win-${CMAKE_WIN_INSTALLER_NAME}-${GIT_COMMIT_HASH}.zip" OUTPUT_ZIP )
  message( STATUS "Final product will be  ${OUTPUT_ZIP} from ${WELL_NAMED_ASSET_DIR}" )
  add_custom_command(
    TARGET installer-pkg
    POST_BUILD
    WORKING_DIRECTORY ${WELL_NAMED_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory  ${INSTALLER_DIR}
    COMMAND powershell Compress-Archive 
             -DestinationPath "${OUTPUT_ZIP}"
             -Path "."
    )
endif()
