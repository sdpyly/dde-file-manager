cmake_minimum_required(VERSION 3.10)

project(test-dfm-framework)

set(DPFIncludePath ${PROJECT_INCLUDE_PATH}/dfm-framework/)
set(DPFSrcPath ${PROJECT_SOURCE_PATH}/dfm-framework/)

# UT文件
file(GLOB_RECURSE UT_CXX_FILE
    FILES_MATCHING PATTERN "*.cpp" "*.h")

add_executable(${PROJECT_NAME}
    ${UT_CXX_FILE}
    ${CPP_STUB_SRC}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    DFM::framework
)


add_test(
  NAME framework
  COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)
