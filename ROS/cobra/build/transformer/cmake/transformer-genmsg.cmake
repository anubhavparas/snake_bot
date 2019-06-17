# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "transformer: 1 messages, 0 services")

set(MSG_I_FLAGS "-Itransformer:/home/anshul/catkin_ws/src/transformer/msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(transformer_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(transformer
  "/home/anshul/catkin_ws/src/transformer/msg/Angle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/transformer
)

### Generating Services

### Generating Module File
_generate_module_cpp(transformer
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/transformer
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(transformer_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(transformer_generate_messages transformer_generate_messages_cpp)

# target for backward compatibility
add_custom_target(transformer_gencpp)
add_dependencies(transformer_gencpp transformer_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS transformer_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(transformer
  "/home/anshul/catkin_ws/src/transformer/msg/Angle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/transformer
)

### Generating Services

### Generating Module File
_generate_module_lisp(transformer
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/transformer
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(transformer_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(transformer_generate_messages transformer_generate_messages_lisp)

# target for backward compatibility
add_custom_target(transformer_genlisp)
add_dependencies(transformer_genlisp transformer_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS transformer_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(transformer
  "/home/anshul/catkin_ws/src/transformer/msg/Angle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/transformer
)

### Generating Services

### Generating Module File
_generate_module_py(transformer
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/transformer
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(transformer_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(transformer_generate_messages transformer_generate_messages_py)

# target for backward compatibility
add_custom_target(transformer_genpy)
add_dependencies(transformer_genpy transformer_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS transformer_generate_messages_py)


debug_message(2 "transformer: Iflags=${MSG_I_FLAGS}")


if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/transformer)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/transformer
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(transformer_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/transformer)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/transformer
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(transformer_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/transformer)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/transformer\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/transformer
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(transformer_generate_messages_py std_msgs_generate_messages_py)
