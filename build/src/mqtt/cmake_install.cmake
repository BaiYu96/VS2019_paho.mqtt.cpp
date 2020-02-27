# Install script for directory: F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/paho-mqtt-cpp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mqtt" TYPE FILE FILES
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/async_client.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/buffer_ref.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/buffer_view.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/callback.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/client.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/connect_options.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/delivery_token.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/disconnect_options.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/exception.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/iaction_listener.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/iasync_client.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/iclient_persistence.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/message.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/properties.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/response_options.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/server_response.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/ssl_options.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/string_collection.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/subscribe_options.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/thread_queue.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/token.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/topic.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/types.h"
    "F:/学习笔记/C++/paho.mqtt.cpp/src/mqtt/will_options.h"
    )
endif()

