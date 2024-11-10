#ifndef ae2f_BmpCL_BmpCL_h
#define ae2f_BmpCL_BmpCL_h

#include <CL/cl.h>
#include "Programme.h"

ae2f_extern ae2f_SHAREDCALL cl_int ae2f_BmpCL_Init(
    cl_context context,
    cl_uint clDeviceNumber,
    const cl_device_id* lpDevice
);

ae2f_extern ae2f_SHAREDCALL cl_int ae2f_BmpCL_End();

#endif