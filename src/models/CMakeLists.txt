file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE INCS *.hpp *.h)

target_sources(${PROJECT_NAME} PRIVATE ${INCS} ${SRCS})
