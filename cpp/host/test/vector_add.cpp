#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include "../src/saoclib.hpp"

using namespace saoclib;

/**
 * This definition is used to avoid link errors when lookup implementation for function 'cleanup' declared in AOCLUtils.
 */
void cleanup() {};


// Entry point.
int main(int argc, char **argv) {
    /* assign the size of vector */
    const size_t N = 100000;
    const unsigned num_args = 3;

    /* prepare raw data */
    scoped_aligned_ptr<float> a(N), b(N), c(N);
    for (unsigned i = 0; i < N; i++) {
        a[i] = 3.14;
        b[i] = 3.14;
    }

    /* wrap the raw data to KernelArg objects */
    ArgFloatBuffer A_data = ArgFloatBuffer::Input(&a, N);
    ArgFloatBuffer B_data = ArgFloatBuffer::Input(&b, N);
    ArgFloatBuffer C_data = ArgFloatBuffer::Output(&c, N);
    KernelArg *args[num_args] = {&A_data, &B_data, &C_data};

    /* set inputs and output limits */
    KernelArgLimit arg_limits[num_args] = {KernelArgLimit::AlignedBufferInput<float>(N),
                                           KernelArgLimit::AlignedBufferInput<float>(N),
                                           KernelArgLimit::AlignedBufferOutput<float>(N)};
    /* init an FPGA image */
    ClEnv env;
    env.init_opencl();

    ClImage image(&env, "vector_add");
    auto device = env.getDeviceId(0);
    image.deploy_image(&device, 1);

    /* init the kernel */
    size_t global_work_size[1] = {N};
    NDRangeKernel kernel(1, global_work_size, NULL,
                         &image, device, "vector_add", arg_limits, num_args);
    /* call kernel with inputs and output */
    kernel.call(args, num_args);

    /* print results */
    for (unsigned i = 0; i < N; i++) {
        printf("%f,", c[i]);
    }

    /* test for multi calls */
    printf("call kernel of 2 times:\n");
    kernel.call(args,num_args);
    /* print results */
    for (unsigned i = 0; i < N; i++) {
        printf("%f,", c[i]);
    }

    return 0;
}


