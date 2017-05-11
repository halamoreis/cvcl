cmake_minimum_required(VERSION 3.7)
project(cvcl)

set(CMAKE_CXX_STANDARD 11)


set(OPENCL_INC_SEARCH_PATH

        ${OPENCL_INCLUDE_DIR}
        ${OPENCL_DIR}/include
        ${OPENCL_DIR}/OpenCL/common/inc
        $ENV{OPENCL_INCLUDE_DIR}
        $ENV{OPENCL_DIR}/include
        $ENV{OPENCL_DIR}/OpenCL/common/inc
        /usr/local/include
        /usr/include
        /opt/intel/opencl/include

)



set(OPENCL_LIB_SEARCH_PATH

        ${OPENCL_LIBRARY_DIR}
        ${OPENCL_DIR}/lib
        ${OPENCL_DIR}/lib/x86
        $ENV{OPENCL_LIBRARY_DIR}
        $ENV{OPENCL_DIR}/lib
        $ENV{OPENCL_DIR}/lib/x86
        /usr/local/lib64
        /usr/local/lib
        /usr/lib64
        /usr/lib
        /opt/intel/opencl


)


find_path(OpenCL_INCLUDE_DIR

        NAMES CL/cl.h
        PATHS ${OPENCL_INC_SEARCH_PATH}

)



find_library(OpenCL_LIBRARY

        NAMES OpenCL
        PATHS ${OPENCL_LIB_SEARCH_PATH}

)



include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(OPENCL

        DEFAULT_MSG
        OPENCL_LIBRARY OPENCL_INCLUDE_DIR

)



if(OPENCL_FOUND)

    set(OPENCL_LIBRARIES ${OPENCL_LIBRARY})

else(OPENCL_FOUND)

    set(OPENCL_LIBRARIES)

endif(OPENCL_FOUND)



mark_as_advanced(OPENCL_INCLUDE_DIR

        OPENCL_LIBRARY

)



set(SOURCE_FILES main.cpp)

find_package( OpenCL REQUIRED )
find_package( OpenCV REQUIRED)

include_directories( ${OpenCL_INCLUDE_DIR} )

add_executable(clcv ${SOURCE_FILES})

target_link_libraries( clcv ${OpenCL_LIBRARIES} ${OpenCV_LIBS})


