package com.pzque.sparkdl.examples

import com.intel.analytics.bigdl.tensor.{Tensor, TensorKernel}
import com.intel.analytics.bigdl.utils.T
import com.pzque.sparkdl.saoclib._


object MatrixMultTest {
  def main(args: Array[String]): Unit = {
    System.loadLibrary("saoclib")

    // init opencl essentials
    val env = new CLEnv()
    env.initOpenCL()

    // construct an opencl image from file path
    val image = new CLImage(env, "/home/pcz/Projects/saoclib/bin/matrix_mult")

    // get available devices
    val device_id_list = env.getDeviceIDList.get
    print("devices: ")
    println(device_id_list.mkString("[", ",", "]"))
    val device_id = device_id_list(0)

    // deploy the image to specific devices
    image.deployImage(device_id_list)

    // construct a kernel
    val N: Int = 2
    val BLOCK_SIZE: Int = 2
    val aH: Int = N * BLOCK_SIZE
    val aW: Int = N * BLOCK_SIZE
    val bH: Int = aW
    val bW: Int = N * BLOCK_SIZE
    val cH: Int = aH
    val cW: Int = bW
    val aSize = aH * aW
    val bSize = bH * bW
    val cSize = cH * cW

    val limits: Array[KernelArgLimit] = Array(
      limit(c_int, mode_input),
      limit(c_int, mode_input),
      limit(c_array(c_float, aSize), mode_input),
      limit(c_array(c_float, bSize), mode_input),
      limit(c_array(c_float, cSize), mode_output)
    )
    val kernel = new NDRangeKernel(
      _workDim = 2,
      _globalWorkSizeList = Array(cW, cH),
      _localWorkSizeList = Array(BLOCK_SIZE, BLOCK_SIZE),
      _clImage = image,
      _deviceID = device_id,
      _kernelName = "matrixMult",
      _argLimits = limits
    )

    // prepare kernel arguments
    val aWArg = ArgVal[Int](aW)(mode_input)
    val bWArg = ArgVal[Int](bW)(mode_input)
    val a = Tensor[Float](
      T(T(1f, 2f, 3f, 4f),
        T(1f, 2f, 3f, 4f),
        T(1f, 2f, 3f, 4f),
        T(1f, 2f, 3f, 4f)
      )
    )
    val c = Tensor[Float](4, 4)
    val aArg: ArgArray[Float] = ArgArray(TensorKernel.tensor2array(a))(mode_input)
    val bArg: ArgArray[Float] = ArgArray(TensorKernel.tensor2array(a))(mode_input)
    val cArg: ArgArray[Float] = ArgArray(TensorKernel.tensor2array(c))(mode_output)

    // call kernel
    var start, end: Long = 0
    start = System.currentTimeMillis()
    kernel.call(aWArg, bWArg, aArg, bArg, cArg)
    end = System.currentTimeMillis()
    println(s"Kernel cost: ${end - start}ms\n")
    println(s"c:\n${c}\n")
  }
}
