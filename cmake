add_library(hey ../lib/helpers.c)
set(LIB_FILES ${CMAKE_SOURCE_DIR}/lib/helpers.c ${PROJECT_SOURCE_DIR}/lib/_string.c ${PROJECT_SOURCE_DIR}/lib/dictionary.c ${PROJECT_SOURCE_DIR}/lib/helpers.c ${PROJECT_SOURCE_DIR}/lib/DataBase.c)

set(VENDOR_FILES ${PROJECT_SOURCE_DIR}/vendor/cJSON/cJSON.c)

set(MODEL_FILES ${PROJECT_SOURCE_DIR}/server/models/user.c)

link_libraries(${LIB_FILES} ${VENDOR_FILES} ${MODEL_FILES})
