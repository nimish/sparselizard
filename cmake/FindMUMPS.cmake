include(FindPackageHandleStandardArgs)

find_library(MUMPS_LIBRARY NAMES cmumps)

find_package_handle_standard_args(MUMPS DEFAULT_MSG MUMPS_LIBRARY)

if(MUMPS_FOUND)
    mark_as_advanced(MUMPS_LIBRARY)
endif()

IF(MUMPS_FOUND AND NOT TARGET MUMPS::MUMPS)
    add_library(MUMPS::MUMPS IMPORTED SHARED)
    set_property(TARGET MUMPS::MUMPS PROPERTY IMPORTED_LOCATION ${MUMPS_LIBRARY})
endif()
