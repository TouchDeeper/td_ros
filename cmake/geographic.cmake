add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/GeographicLib)
include_directories(${PROJECT_SOURCE_DIR}/third_party/GeographicLib/include/)
list(APPEND GeoGraphic_LIBRARIES libGeographiccc)