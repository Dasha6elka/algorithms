file(GLOB SRC ${algorithms_SOURCE_DIR}/src/queue_and_stack/*.cpp)
file(GLOB UTILS ${algorithms_SOURCE_DIR}/test/utils/*.cpp)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(queue_and_stack_test queue_and_stack.spec.cpp ${SRC} ${UTILS})
